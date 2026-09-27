/*
 * micro_helium_math.c
 *
 *  Created on: 27-Sept-2026
 *      Author: skull
 */

#include "micro_helium_math.h"
#include <math.h>

/* MVFR1 Register Address for runtime hardware detection */
#define SCB_MVFR1 (*(volatile uint32_t *)0xE000EF44)

/* Internal helper to check if Helium Floating-Point is enabled */
static mve_status_t check_mve_hw(void) {
    uint32_t mve_support = (SCB_MVFR1 >> 8) & 0x0F;
    if (mve_support == 0x02) return MVE_OK;
    return MVE_NO_HW;
}

/* Vector Addition */
mve_status_t hel_vec_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    if (!pSrcA || !pSrcB || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecA = vld1q_z_f32(&pSrcA[i], p);
        float32x4_t vecB = vld1q_z_f32(&pSrcB[i], p);

        float32x4_t vecDst = vaddq_m_f32(vuninitializedq_f32(), vecA, vecB, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Subtraction */
mve_status_t hel_vec_sub_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    if (!pSrcA || !pSrcB || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecA = vld1q_z_f32(&pSrcA[i], p);
        float32x4_t vecB = vld1q_z_f32(&pSrcB[i], p);

        float32x4_t vecDst = vsubq_m_f32(vuninitializedq_f32(), vecA, vecB, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Multiplication */
mve_status_t hel_vec_mult_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t length) {
    if (!pSrcA || !pSrcB || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecA = vld1q_z_f32(&pSrcA[i], p);
        float32x4_t vecB = vld1q_z_f32(&pSrcB[i], p);

        float32x4_t vecDst = vmulq_m_f32(vuninitializedq_f32(), vecA, vecB, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Negate */
mve_status_t hel_vec_negate_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDst = vnegq_m_f32(vuninitializedq_f32(), vecIn, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Offset */
mve_status_t hel_vec_offset_f32(const float32_t *pSrc, float32_t offset, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecOffset = vdupq_n_f32(offset);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDst = vaddq_m_f32(vuninitializedq_f32(), vecIn, vecOffset, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Scale */
mve_status_t hel_vec_scale_f32(const float32_t *pSrc, float32_t scale, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecScale = vdupq_n_f32(scale);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDst = vmulq_m_f32(vuninitializedq_f32(), vecIn, vecScale, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Absolute Value */
mve_status_t hel_vec_abs_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDst = vabsq_m_f32(vuninitializedq_f32(), vecIn, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Vector Minimum */
mve_status_t hel_vec_min_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length) {
    if (!pSrc || !pResult || !pIndex) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;
    if (length == 0) return MVE_OK;

    float32_t minVal = pSrc[0];
    uint32_t minIdx = 0;

    for (uint32_t i = 1; i < length; i++) {
        if (pSrc[i] < minVal) {
            minVal = pSrc[i];
            minIdx = i;
        }
    }
    *pResult = minVal;
    *pIndex = minIdx;
    return MVE_OK;
}

/* Vector Maximum */
mve_status_t hel_vec_max_f32(const float32_t *pSrc, float32_t *pResult, uint32_t *pIndex, uint32_t length) {
    if (!pSrc || !pResult || !pIndex) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;
    if (length == 0) return MVE_OK;

    float32_t maxVal = pSrc[0];
    uint32_t maxIdx = 0;

    for (uint32_t i = 1; i < length; i++) {
        if (pSrc[i] > maxVal) {
            maxVal = pSrc[i];
            maxIdx = i;
        }
    }
    *pResult = maxVal;
    *pIndex = maxIdx;
    return MVE_OK;
}

/* Vector Mean */
mve_status_t hel_vec_mean_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult) {
    if (!pSrc || !pResult) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;
    if (length == 0) { *pResult = 0.0f; return MVE_OK; }

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecAcc = vdupq_n_f32(0.0f);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        vecAcc = vaddq_m_f32(vecAcc, vecAcc, vecIn, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }

    *pResult = (vgetq_lane_f32(vecAcc, 0) + vgetq_lane_f32(vecAcc, 1) + vgetq_lane_f32(vecAcc, 2) + vgetq_lane_f32(vecAcc, 3)) / (float32_t)length;
    return MVE_OK;
}

/* Vector Variance */
mve_status_t hel_vec_var_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult) {
    if (!pSrc || !pResult) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;
    if (length <= 1) { *pResult = 0.0f; return MVE_OK; }

    float32_t mean;
    hel_vec_mean_f32(pSrc, length, &mean);

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecAcc = vdupq_n_f32(0.0f);
    float32x4_t vecMean = vdupq_n_f32(mean);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDiff = vsubq_m_f32(vuninitializedq_f32(), vecIn, vecMean, p);
        vecAcc = vfmaq_m_f32(vecAcc, vecDiff, vecDiff, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }

    *pResult = (vgetq_lane_f32(vecAcc, 0) + vgetq_lane_f32(vecAcc, 1) + vgetq_lane_f32(vecAcc, 2) + vgetq_lane_f32(vecAcc, 3)) / (float32_t)length;
    return MVE_OK;
}

/* Vector Standard Deviation */
mve_status_t hel_vec_std_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult) {
    float32_t var;
    mve_status_t status = hel_vec_var_f32(pSrc, length, &var);
    if (status == MVE_OK) *pResult = sqrtf(var);
    return status;
}

/* Vector Dot Product */
mve_status_t hel_vec_dot_f32(const float32_t *pSrcA, const float32_t *pSrcB, uint32_t length, float32_t *pResult) {
    if (!pSrcA || !pSrcB || !pResult) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecAcc = vdupq_n_f32(0.0f);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecA = vld1q_z_f32(&pSrcA[i], p);
        float32x4_t vecB = vld1q_z_f32(&pSrcB[i], p);

        vecAcc = vfmaq_m_f32(vecAcc, vecA, vecB, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }

    *pResult = (vgetq_lane_f32(vecAcc, 0) + vgetq_lane_f32(vecAcc, 1) + vgetq_lane_f32(vecAcc, 2) + vgetq_lane_f32(vecAcc, 3));
    return MVE_OK;
}

/* Vector Power */
mve_status_t hel_vec_power_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult) {
    return hel_vec_dot_f32(pSrc, pSrc, length, pResult);
}

/* Vector Root Mean Square (RMS) */
mve_status_t hel_vec_rms_f32(const float32_t *pSrc, uint32_t length, float32_t *pResult) {
    if (!pResult) return MVE_BAD_PTR;
    if (length == 0) { *pResult = 0.0f; return MVE_OK; }

    float32_t power;
    mve_status_t status = hel_vec_power_f32(pSrc, length, &power);
    if (status == MVE_OK) *pResult = sqrtf(power / (float32_t)length);
    return status;
}

/* Matrix Addition */
mve_status_t hel_mat_add_f32(const float32_t *pSrcA, const float32_t *pSrcB, float32_t *pDst, uint32_t numRows, uint32_t numCols) {
    return hel_vec_add_f32(pSrcA, pSrcB, pDst, numRows * numCols);
}

/* Matrix Transpose */
mve_status_t hel_mat_trans_f32(const float32_t *pSrc, uint32_t numRows, uint32_t numCols, float32_t *pDst) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    for (uint32_t i = 0; i < numRows; i++) {
        for (uint32_t j = 0; j < numCols; j++) {
            pDst[j * numRows + i] = pSrc[i * numCols + j];
        }
    }
    return MVE_OK;
}

/* Matrix-Vector Multiplication */
mve_status_t hel_mat_vec_mult_f32(const float32_t *pMat, const float32_t *pVec, float32_t *pDst, uint32_t numRows, uint32_t numCols) {
    if (!pMat || !pVec || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    for (uint32_t i = 0; i < numRows; i++) {
        hel_vec_dot_f32(&pMat[i * numCols], pVec, numCols, &pDst[i]);
    }
    return MVE_OK;
}

/* Matrix Multiplication */
mve_status_t hel_mat_mult_f32(const float32_t *pSrcA, uint32_t numRowsA, uint32_t numColsA, const float32_t *pSrcB, uint32_t numColsB, float32_t *pDst) {
    if (!pSrcA || !pSrcB || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    for (uint32_t i = 0; i < numRowsA; i++) {
        for (uint32_t j = 0; j < numColsB; j++) {
            float32x4_t vecAcc = vdupq_n_f32(0.0f);
            uint32_t k = 0;
            uint32_t blkCnt = numColsA;

            while (blkCnt > 0) {
                mve_pred16_t p = vctp32q(blkCnt);
                float32x4_t vecA = vld1q_z_f32(&pSrcA[i * numColsA + k], p);

                float32x4_t vecB = vdupq_n_f32(0.0f);
                if (blkCnt > 0) vecB = vsetq_lane_f32(pSrcB[(k + 0) * numColsB + j], vecB, 0);
                if (blkCnt > 1) vecB = vsetq_lane_f32(pSrcB[(k + 1) * numColsB + j], vecB, 1);
                if (blkCnt > 2) vecB = vsetq_lane_f32(pSrcB[(k + 2) * numColsB + j], vecB, 2);
                if (blkCnt > 3) vecB = vsetq_lane_f32(pSrcB[(k + 3) * numColsB + j], vecB, 3);

                vecAcc = vfmaq_m_f32(vecAcc, vecA, vecB, p);
                k += 4;
                blkCnt -= (blkCnt < 4) ? blkCnt : 4;
            }
            pDst[i * numColsB + j] = (vgetq_lane_f32(vecAcc, 0) + vgetq_lane_f32(vecAcc, 1) + vgetq_lane_f32(vecAcc, 2) + vgetq_lane_f32(vecAcc, 3));
        }
    }
    return MVE_OK;
}

/* ReLU Activation */
mve_status_t hel_nn_relu_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    uint32_t blkCnt = length;
    uint32_t i = 0;
    float32x4_t vecZero = vdupq_n_f32(0.0f);

    while (blkCnt > 0) {
        mve_pred16_t p = vctp32q(blkCnt);
        float32x4_t vecIn = vld1q_z_f32(&pSrc[i], p);

        float32x4_t vecDst = vmaxnmq_m_f32(vuninitializedq_f32(), vecIn, vecZero, p);
        vstrwq_p_f32(&pDst[i], vecDst, p);

        i += 4;
        blkCnt -= (blkCnt < 4) ? blkCnt : 4;
    }
    return MVE_OK;
}

/* Softmax Activation */
mve_status_t hel_nn_softmax_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;
    if (length == 0) return MVE_OK;

    float32_t maxVal;
    uint32_t dummyIdx;
    hel_vec_max_f32(pSrc, &maxVal, &dummyIdx, length);

    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < length; i++) {
        pDst[i] = expf(pSrc[i] - maxVal);
        sum += pDst[i];
    }

    return hel_vec_scale_f32(pDst, 1.0f / sum, pDst, length);
}

/* Sigmoid Activation */
mve_status_t hel_nn_sigmoid_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    for (uint32_t i = 0; i < length; i++) {
        pDst[i] = 1.0f / (1.0f + expf(-pSrc[i]));
    }
    return MVE_OK;
}

/* Tanh Activation */
mve_status_t hel_nn_tanh_f32(const float32_t *pSrc, float32_t *pDst, uint32_t length) {
    if (!pSrc || !pDst) return MVE_BAD_PTR;
    if (check_mve_hw() != MVE_OK) return MVE_NO_HW;

    for (uint32_t i = 0; i < length; i++) {
        pDst[i] = tanhf(pSrc[i]);
    }
    return MVE_OK;
}
