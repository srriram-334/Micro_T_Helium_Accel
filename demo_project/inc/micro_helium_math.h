/*
 * micro_helium_math.h
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */

#ifndef MICRO_HELIUM_MATH_H
#define MICRO_HELIUM_MATH_H

#include <stdint.h>
#include <arm_mve.h>

/* 16-Byte (128-bit) Alignment Macro for Maximum MVE Read/Write Speed */
#define HEL_ALIGN __attribute__((aligned(16)))

/* Hardware Status Enum for MVE operations */
typedef enum {
    MVE_OK = 0,
    MVE_NO_HW,
    MVE_BAD_PTR
} mve_status_t;

/* Vector Math Operations */
mve_status_t hel_vec_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_sub_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_mult_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_negate_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_offset_f32(const float32_t *pSrc, float32_t offset, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_scale_f32(const float32_t *pSrc, float32_t scale, float32_t *pDst, uint32_t length);

/* Data Cleaning & Statistics */
mve_status_t hel_vec_abs_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
mve_status_t hel_vec_min_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length);
mve_status_t hel_vec_max_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length);
mve_status_t hel_vec_mean_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult);
mve_status_t hel_vec_var_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult);
mve_status_t hel_vec_std_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult);

/* DSP & Signal Processing */
mve_status_t hel_vec_dot_f32(const float32_t *pSrcA, const float32_t *pSrcB, uint32_t length, float32_t *pResult);
mve_status_t hel_vec_power_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult);
mve_status_t hel_vec_rms_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult);

/* Linear Algebra & Matrix Operations (Row-Major) */
mve_status_t hel_mat_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t numRows, uint32_t numCols);
mve_status_t hel_mat_trans_f32(const float32_t *pSrc, uint32_t numRows, uint32_t numCols, float32_t *pDst);
mve_status_t hel_mat_vec_mult_f32(const float32_t *pMat, const float32_t *pVec, float32_t *pDst, uint32_t numRows, uint32_t numCols);
mve_status_t hel_mat_mult_f32(const float32_t *pSrcA, uint32_t numRowsA, uint32_t numColsA, const float32_t *pSrcB, uint32_t numColsB, float32_t *pDst);

/* TinyML Activation Functions */
mve_status_t hel_nn_relu_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
mve_status_t hel_nn_softmax_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
mve_status_t hel_nn_sigmoid_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
mve_status_t hel_nn_tanh_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);

#endif /* MICRO_HELIUM_MATH_H */
