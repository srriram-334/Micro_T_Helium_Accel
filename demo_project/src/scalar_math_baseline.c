/*
 * scalar_math_baseline.c
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */

#include "scalar_math_baseline.h"
#include <math.h>

void scalar_vec_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = pSrcA[i] + pSrcB[i];
}

void scalar_vec_sub_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = pSrcA[i] - pSrcB[i];
}

void scalar_vec_mult_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = pSrcA[i] * pSrcB[i];
}

void scalar_vec_negate_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = -pSrc[i];
}

void scalar_vec_offset_f32(const float32_t *pSrc, float32_t offset, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = pSrc[i] + offset;
}

void scalar_vec_scale_f32(const float32_t *pSrc, float32_t scale, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = pSrc[i] * scale;
}

void scalar_vec_abs_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = fabsf(pSrc[i]);
}

void scalar_vec_min_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length) {
    if (length == 0) return;
    float32_t minVal = pSrc[0];
    uint32_t minIdx = 0;
    for (uint32_t i = 1; i < length; i++) {
        if (pSrc[i] < minVal) { minVal = pSrc[i]; minIdx = i; }
    }
    *pResult = minVal; *pIndex = minIdx;
}

void scalar_vec_max_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length) {
    if (length == 0) return;
    float32_t maxVal = pSrc[0];
    uint32_t maxIdx = 0;
    for (uint32_t i = 1; i < length; i++) {
        if (pSrc[i] > maxVal) { maxVal = pSrc[i]; maxIdx = i; }
    }
    *pResult = maxVal; *pIndex = maxIdx;
}

float32_t scalar_vec_mean_f32(const float32_t *pSrc, uint32_t length) {
    if (length == 0) return 0.0f;
    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < length; i++) sum += pSrc[i];
    return sum / (float32_t)length;
}

float32_t scalar_vec_var_f32(const float32_t *pSrc, uint32_t length) {
    if (length <= 1) return 0.0f;
    float32_t mean = scalar_vec_mean_f32(pSrc, length);
    float32_t sumSqDiff = 0.0f;
    for (uint32_t i = 0; i < length; i++) {
        float32_t diff = pSrc[i] - mean;
        sumSqDiff += diff * diff;
    }
    return sumSqDiff / (float32_t)length;
}

float32_t scalar_vec_std_f32(const float32_t *pSrc, uint32_t length) {
    return sqrtf(scalar_vec_var_f32(pSrc, length));
}

float32_t scalar_vec_dot_f32(const float32_t *pSrcA, const float32_t *pSrcB, uint32_t length) {
    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < length; i++) sum += pSrcA[i] * pSrcB[i];
    return sum;
}

float32_t scalar_vec_power_f32(const float32_t *pSrc, uint32_t length) {
    return scalar_vec_dot_f32(pSrc, pSrc, length);
}

float32_t scalar_vec_rms_f32(const float32_t *pSrc, uint32_t length) {
    if (length == 0) return 0.0f;
    return sqrtf(scalar_vec_power_f32(pSrc, length) / (float32_t)length);
}

void scalar_mat_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t numRows, uint32_t numCols) {
    scalar_vec_add_f32(pSrcA, pSrcB, pDst, numRows * numCols);
}

void scalar_mat_trans_f32(const float32_t *pSrc, uint32_t numRows, uint32_t numCols, float32_t *pDst) {
    for (uint32_t i = 0; i < numRows; i++) {
        for (uint32_t j = 0; j < numCols; j++) {
            pDst[j * numRows + i] = pSrc[i * numCols + j];
        }
    }
}

void scalar_mat_vec_mult_f32(const float32_t *pMat, const float32_t *pVec, float32_t *pDst, uint32_t numRows, uint32_t numCols) {
    for (uint32_t i = 0; i < numRows; i++) {
        pDst[i] = scalar_vec_dot_f32(&pMat[i * numCols], pVec, numCols);
    }
}

void scalar_mat_mult_f32(const float32_t *pSrcA, uint32_t numRowsA, uint32_t numColsA, const float32_t *pSrcB, uint32_t numColsB, float32_t *pDst) {
    for (uint32_t i = 0; i < numRowsA; i++) {
        for (uint32_t j = 0; j < numColsB; j++) {
            float32_t sum = 0.0f;
            for (uint32_t k = 0; k < numColsA; k++) {
                sum += pSrcA[i * numColsA + k] * pSrcB[k * numColsB + j];
            }
            pDst[i * numColsB + j] = sum;
        }
    }
}

void scalar_nn_relu_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = (pSrc[i] > 0.0f) ? pSrc[i] : 0.0f;
}

void scalar_nn_softmax_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (length == 0) return;
    float32_t maxVal; uint32_t dummyIdx;
    scalar_vec_max_f32(pSrc, &maxVal, &dummyIdx, length);
    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < length; i++) {
        pDst[i] = expf(pSrc[i] - maxVal);
        sum += pDst[i];
    }
    scalar_vec_scale_f32(pDst, 1.0f / sum, pDst, length);
}

void scalar_nn_sigmoid_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = 1.0f / (1.0f + expf(-pSrc[i]));
}

void scalar_nn_tanh_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) pDst[i] = tanhf(pSrc[i]);
}
