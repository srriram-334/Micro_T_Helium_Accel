/*
 * usermain.c - Micro T-Helium-Accel Benchmark Test & RTOS Reentrancy
 * Hardware: Renesas EK-RA8P1 (Cortex-M85)
 */

#include <benchmark.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "micro_helium_math.h"

LOCAL void test_task(INT stacd, void *exinf);
LOCAL void preempt_task(INT stacd, void *exinf);

LOCAL ID test_tskid;
LOCAL ID preempt_tskid;

/* Primary Benchmark Task (Lower Priority = Higher Number in micro T-Kernel) */
LOCAL T_CTSK ctsk_test = {
    .itskpri = 10,
    .stksz   = 2048,
    .task    = test_task,
    .tskatr  = TA_HLNG | TA_RNG3,
};

/* Interrupting Preemption Task (Higher Priority = Lower Number) */
LOCAL T_CTSK ctsk_preempt = {
    .itskpri = 5,
    .stksz   = 1024,
    .task    = preempt_task,
    .tskatr  = TA_HLNG | TA_RNG3,
};

static float32_t dummy_src[100];
static float32_t dummy_dst[100];

LOCAL void test_task(INT stacd, void *exinf)
{
    /* Run the complete suite from benchmark.c */
    run_full_benchmark();

    /* Suspend task after completion to free up the scheduler */
    tk_slp_tsk(TMO_FEVR);
}

LOCAL void preempt_task(INT stacd, void *exinf)
{
    while (1) {
        /* Wait 10ms then interrupt the lower-priority benchmark suite mid-execution */
        tk_dly_tsk(10);

        tm_printf((UB*)"\n[Preempt Task] High priority preemption triggered!\n");

        /* This execution forces the CPU to stack the active task's vector registers */
        mve_status_t status = hel_vec_offset_f32(dummy_src, 5.0f, dummy_dst, 100);

        if (status == MVE_OK) {
            tm_printf((UB*)"[Preempt Task] Helium vector operation successfully completed.\n");
        } else {
            tm_printf((UB*)"[Preempt Task] HW Error during preemption!\n");
        }

        /* Yield to allow the main benchmark to resume and prove context restoration */
        tk_slp_tsk(TMO_FEVR);
    }
}

EXPORT INT usermain(void)
{
    /* Initialize Dummy Data */
    for(int i = 0; i < 100; i++) dummy_src[i] = (float32_t)i;

    /* Create & Start Benchmark Task */
    test_tskid = tk_cre_tsk(&ctsk_test);

    /* Create & Start Preemption Task */
    preempt_tskid = tk_cre_tsk(&ctsk_preempt);

    /* Start tasks. Preempt starts immediately but delays, allowing test_task to run */
    tk_sta_tsk(test_tskid, 0);
    tk_sta_tsk(preempt_tskid, 0);

    /* Suspend the root task */
    tk_slp_tsk(TMO_FEVR);

    return 0;
}
