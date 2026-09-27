/*
 * dwt_timer.c
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */


#include "dwt_timer.h"

/* ARM Cortex-M CoreDebug and DWT Register Addresses */
#define DEMCR              (*((volatile uint32_t *)0xE000EDFC))
#define DWT_CTRL           (*((volatile uint32_t *)0xE0001000))
#define DWT_CYCCNT         (*((volatile uint32_t *)0xE0001004))
#define DWT_LAR            (*((volatile uint32_t *)0xE0001FB0)) // Lock Access Register

/* Register Bit Definitions */
#define DEMCR_TRCENA       (1 << 24)
#define DWT_CTRL_CYCCNTENA (1 << 0)
#define DWT_LAR_UNLOCK     0xC5ACCE55

void dwt_init(void) {
    /* 1. Enable trace and debug block (TRCENA) */
    DEMCR |= DEMCR_TRCENA;

    /* 2. Unlock DWT registers (Required for Cortex-M7, M33, M55, M85) */
    DWT_LAR = DWT_LAR_UNLOCK;

    /* 3. Reset the cycle counter */
    DWT_CYCCNT = 0;

    /* 4. Enable the cycle counter */
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;
}

uint32_t dwt_get_cycles(void) {
    /* Return the live cycle count */
    return DWT_CYCCNT;
}

void dwt_reset(void) {
    /* Reset the cycle count to zero */
    DWT_CYCCNT = 0;
}
