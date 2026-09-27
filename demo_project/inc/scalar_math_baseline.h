/*
 * scalar_math_baseline.h
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */


#ifndef SCALAR_MATH_BASELINE_H
#define SCALAR_MATH_BASELINE_H

#include <stdint.h>
#include <arm_mve.h>

/* Scalar Baseline Function Signatures */
void scalar_vec_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
void scalar_vec_sub_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
void scalar_vec_mult_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length);
void scalar_vec_negate_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
void scalar_vec_offset_f32(const float32_t *pSrc, float32_t offset, float32_t *pDst, uint32_t length);
void scalar_vec_scale_f32(const float32_t *pSrc, float32_t scale, float32_t *pDst, uint32_t length);

void scalar_vec_abs_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
void scalar_vec_min_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length);
void scalar_vec_max_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length);
float32_t scalar_vec_mean_f32(const float32_t *pSrc, uint32_t length);
float32_t scalar_vec_var_f32(const float32_t *pSrc, uint32_t length);
float32_t scalar_vec_std_f32(const float32_t *pSrc, uint32_t length);

float32_t scalar_vec_dot_f32(const float32_t *pSrcA, const float32_t *pSrcB, uint32_t length);
float32_t scalar_vec_power_f32(const float32_t *pSrc, uint32_t length);
float32_t scalar_vec_rms_f32(const float32_t *pSrc, uint32_t length);

void scalar_mat_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t numRows, uint32_t numCols);
void scalar_mat_trans_f32(const float32_t *pSrc, uint32_t numRows, uint32_t numCols, float32_t *pDst);
void scalar_mat_vec_mult_f32(const float32_t *pMat, const float32_t *pVec, float32_t *pDst, uint32_t numRows, uint32_t numCols);
void scalar_mat_mult_f32(const float32_t *pSrcA, uint32_t numRowsA, uint32_t numColsA, const float32_t *pSrcB, uint32_t numColsB, float32_t *pDst);

void scalar_nn_relu_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
void scalar_nn_softmax_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
void scalar_nn_sigmoid_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);
void scalar_nn_tanh_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length);

#endif /* SCALAR_MATH_BASELINE_H */
