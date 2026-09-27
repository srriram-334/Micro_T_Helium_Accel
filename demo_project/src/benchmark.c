/*
 * benchmark.c
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */
#include <benchmark.h>
#include <dwt_timer.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <math.h>
#include "micro_helium_math.h"
#include "scalar_math_baseline.h"

#define TEST_LEN 1024
#define MAT_DIM  32     /* 32x32 = 1024 for matrix tests */
#define EPSILON  1e-4f  /* Float tolerance for MVE vs Scalar rounding differences */

/* Static buffers aligned to 16 bytes for maximum MVE load/store performance */
static float32_t arrayA[TEST_LEN] HEL_ALIGN;
static float32_t arrayB[TEST_LEN] HEL_ALIGN;
static float32_t res_scalar[TEST_LEN] HEL_ALIGN;
static float32_t res_helium[TEST_LEN] HEL_ALIGN;

/* Helper: Verify Array Equality */
static int verify_array(const float32_t *s, const float32_t *h, uint32_t len) {
    int errors = 0;
    for (uint32_t i = 0; i < len; i++) {
        if (fabsf(s[i] - h[i]) > EPSILON) errors++;
    }
    return errors;
}

/* Helper: Verify Scalar Equality */
static int verify_scalar(float32_t s, float32_t h) {
    return (fabsf(s - h) > EPSILON) ? 1 : 0;
}

/* Helper: Print Results */
static void print_res(const char* name, uint32_t c_s, uint32_t c_h, int err) {
    uint32_t speedup_x100 = (c_h > 0) ? (c_s * 100) / c_h : 0;

    if (err == 0) {
        tm_printf((UB*)"| %-14s | %10u | %10u | %u.%02ux   |\n",
                  name, c_s, c_h, speedup_x100 / 100, speedup_x100 % 100);
    } else {
        tm_printf((UB*)"| %-14s | %10u | %10u | FAILED  |\n",
                  name, c_s, c_h);
    }
}
void run_full_benchmark(void) {
    uint32_t t_start;
    uint32_t c_s, c_h;
    int err;
    float32_t val_s, val_h;
    uint32_t idx_s, idx_h;

    /* Initialize arrays with normalized values (-1.0 to 1.0) */
    for (uint32_t i = 0; i < TEST_LEN; i++) {
        arrayA[i] = sinf((float32_t)i * 0.1f);
        arrayB[i] = cosf((float32_t)i * 0.1f);
    }

    dwt_init();

    tm_printf((UB*)"\n=======================================================\n");
        tm_printf((UB*)"      Micro T-Helium-Accel Benchmark Suite\n");
        tm_printf((UB*)"      Array: %d elements | Matrix: %dx%d\n", TEST_LEN, MAT_DIM, MAT_DIM);
        tm_printf((UB*)"=======================================================\n");
        tm_printf((UB*)"| Operation      | Scalar Cyc | Helium Cyc | Speedup |\n");
        tm_printf((UB*)"|----------------|------------|------------|---------|\n");
    /* --- 1. VECTOR BASICS --- */
    t_start = dwt_get_cycles(); scalar_vec_add_f32(arrayA, arrayB, res_scalar, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_add_f32(arrayA, arrayB, res_helium, TEST_LEN);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec Add", c_s, c_h, verify_array(res_scalar, res_helium, TEST_LEN));

    t_start = dwt_get_cycles(); scalar_vec_mult_f32(arrayA, arrayB, res_scalar, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_mult_f32(arrayA, arrayB, res_helium, TEST_LEN);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec Mult", c_s, c_h, verify_array(res_scalar, res_helium, TEST_LEN));

    t_start = dwt_get_cycles(); scalar_vec_offset_f32(arrayA, 2.5f, res_scalar, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_offset_f32(arrayA, 2.5f, res_helium, TEST_LEN);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec Offset", c_s, c_h, verify_array(res_scalar, res_helium, TEST_LEN));

    /* --- 2. STATISTICS --- */
    t_start = dwt_get_cycles(); scalar_vec_max_f32(arrayA, &val_s, &idx_s, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_max_f32(arrayA, &val_h, &idx_h, TEST_LEN);    c_h = dwt_get_cycles() - t_start;
    err = verify_scalar(val_s, val_h) || (idx_s != idx_h);
    print_res("Vec Max", c_s, c_h, err);

    t_start = dwt_get_cycles(); val_s = scalar_vec_var_f32(arrayA, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_var_f32(arrayA, TEST_LEN, &val_h);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec Variance", c_s, c_h, verify_scalar(val_s, val_h));

    /* --- 3. DSP / SIGNAL PROCESSING --- */
    t_start = dwt_get_cycles(); val_s = scalar_vec_dot_f32(arrayA, arrayB, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_dot_f32(arrayA, arrayB, TEST_LEN, &val_h);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec Dot Prod", c_s, c_h, verify_scalar(val_s, val_h));

    t_start = dwt_get_cycles(); val_s = scalar_vec_rms_f32(arrayA, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_vec_rms_f32(arrayA, TEST_LEN, &val_h);    c_h = dwt_get_cycles() - t_start;
    print_res("Vec RMS", c_s, c_h, verify_scalar(val_s, val_h));

    /* --- 4. MATRIX OPERATIONS --- */
    t_start = dwt_get_cycles(); scalar_mat_vec_mult_f32(arrayA, arrayB, res_scalar, MAT_DIM, MAT_DIM); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_mat_vec_mult_f32(arrayA, arrayB, res_helium, MAT_DIM, MAT_DIM);    c_h = dwt_get_cycles() - t_start;
    print_res("Mat-Vec Mult", c_s, c_h, verify_array(res_scalar, res_helium, MAT_DIM));

    t_start = dwt_get_cycles(); scalar_mat_mult_f32(arrayA, MAT_DIM, MAT_DIM, arrayB, MAT_DIM, res_scalar); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_mat_mult_f32(arrayA, MAT_DIM, MAT_DIM, arrayB, MAT_DIM, res_helium);    c_h = dwt_get_cycles() - t_start;
    print_res("Mat Multiply", c_s, c_h, verify_array(res_scalar, res_helium, TEST_LEN));

    /* --- 5. NEURAL NETWORK ACTIVATIONS --- */
    t_start = dwt_get_cycles(); scalar_nn_relu_f32(arrayA, res_scalar, TEST_LEN); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_nn_relu_f32(arrayA, res_helium, TEST_LEN);    c_h = dwt_get_cycles() - t_start;
    print_res("NN ReLU", c_s, c_h, verify_array(res_scalar, res_helium, TEST_LEN));

    t_start = dwt_get_cycles(); scalar_nn_softmax_f32(arrayA, res_scalar, MAT_DIM); c_s = dwt_get_cycles() - t_start;
    t_start = dwt_get_cycles(); hel_nn_softmax_f32(arrayA, res_helium, MAT_DIM);    c_h = dwt_get_cycles() - t_start;
    print_res("NN Softmax", c_s, c_h, verify_array(res_scalar, res_helium, MAT_DIM));

    tm_printf((UB*)"=======================================================\n");
    tm_printf((UB*)"Benchmark Complete.\n");
}
