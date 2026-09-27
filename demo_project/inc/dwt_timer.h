/*
 * dwt_timer.h
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */

#ifndef DWT_TIMER_H
#define DWT_TIMER_H

#include <stdint.h>

/* Initialize and start the DWT cycle counter */
void dwt_init(void);

/* Read the current 32-bit cycle count */
uint32_t dwt_get_cycles(void);

/* Reset the cycle counter to zero */
void dwt_reset(void);

#endif /* DWT_TIMER_H */
