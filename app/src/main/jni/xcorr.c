/*
 * File: xcorr.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 07-Nov-2017 15:17:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage2.h"
#include "xcorr.h"
#include "extmessage2_emxutil.h"
#include "ifft.h"
#include "fft.h"

/* Function Declarations */
static void crosscorr(const emxArray_real_T *x, const emxArray_real_T *y, double
                      maxlag, emxArray_real_T *c);
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                double maxlag
 *                emxArray_real_T *c
 * Return Type  : void
 */
static void crosscorr(const emxArray_real_T *x, const emxArray_real_T *y, double
                      maxlag, emxArray_real_T *c)
{
  int u0;
  int m;
  double mxl;
  double c0;
  int maxmn;
  double ceilLog2;
  double m2;
  int n;
  double Sn;
  emxArray_creal_T *X;
  emxArray_creal_T *Y;
  emxArray_creal_T *b_X;
  int loop_ub;
  emxArray_real_T *c1;
  double ihi;
  emxArray_real_T *r2;
  u0 = x->size[0];
  m = y->size[0];
  if (u0 > m) {
    m = u0;
  }

  mxl = (double)m - 1.0;
  if (maxlag < mxl) {
    mxl = maxlag;
  }

  c0 = frexp(fabs(2.0 * (double)m - 1.0), &maxmn);
  ceilLog2 = maxmn;
  if (c0 == 0.5) {
    ceilLog2 = (double)maxmn - 1.0;
  }

  m2 = rt_powd_snf(2.0, ceilLog2);
  u0 = x->size[0];
  m = y->size[0];
  if (u0 > m) {
    m = u0;
  }

  u0 = x->size[0];
  n = y->size[0];
  if (u0 < n) {
    n = u0;
  }

  c0 = 2.0 * (double)n - 1.0;
  if (mxl <= (double)n - 1.0) {
    Sn = mxl * ((c0 - mxl) - 1.0);
    if (mxl <= m - n) {
      c0 = (c0 + mxl * c0) + Sn;
    } else {
      c0 = ((c0 + (double)(m - n) * c0) + (mxl - (double)(m - n)) * ((((double)m
               - mxl) + (double)n) - 2.0)) + Sn;
    }
  } else if (mxl <= (double)m - 1.0) {
    Sn = ((double)n - 1.0) * ((double)n - 1.0);
    if (mxl <= m - n) {
      c0 = (c0 + mxl * c0) + Sn;
    } else {
      c0 = ((c0 + (double)(m - n) * c0) + (mxl - (double)(m - n)) * ((((double)m
               - mxl) + (double)n) - 2.0)) + Sn;
    }
  } else {
    c0 = 2.0 * (double)m * (double)n - ((double)((unsigned int)m + n) - 1.0);
  }

  if (c0 < m2 * (15.0 * ceilLog2 + 6.0)) {
    m = x->size[0];
    n = y->size[0];
    u0 = x->size[0];
    maxmn = y->size[0];
    if (u0 > maxmn) {
      maxmn = u0;
    }

    ceilLog2 = (double)maxmn - 1.0;
    if (mxl < ceilLog2) {
      ceilLog2 = mxl;
    }

    c0 = 2.0 * ceilLog2 + 1.0;
    u0 = c->size[0];
    c->size[0] = (int)c0;
    emxEnsureCapacity((emxArray__common *)c, u0, sizeof(double));
    loop_ub = (int)c0;
    for (u0 = 0; u0 < loop_ub; u0++) {
      c->data[u0] = 0.0;
    }

    for (maxmn = 0; maxmn < (int)(ceilLog2 + 1.0); maxmn++) {
      c0 = (double)m - (double)maxmn;
      ihi = n;
      if (c0 < ihi) {
        ihi = c0;
      }

      Sn = 0.0;
      for (u0 = 0; u0 < (int)ihi; u0++) {
        c0 = x->data[(int)((double)maxmn + (1.0 + (double)u0)) - 1];
        Sn += y->data[u0] * c0;
      }

      c->data[(int)((ceilLog2 + (double)maxmn) + 1.0) - 1] = Sn;
    }

    for (maxmn = 0; maxmn < (int)ceilLog2; maxmn++) {
      ihi = (double)n - (1.0 + (double)maxmn);
      c0 = m;
      if (c0 < ihi) {
        ihi = c0;
      }

      Sn = 0.0;
      for (u0 = 0; u0 < (int)ihi; u0++) {
        c0 = y->data[(int)((1.0 + (double)maxmn) + (1.0 + (double)u0)) - 1];
        Sn += c0 * x->data[u0];
      }

      c->data[(int)((ceilLog2 - (1.0 + (double)maxmn)) + 1.0) - 1] = Sn;
    }
  } else {
    emxInit_creal_T(&X, 1);
    emxInit_creal_T(&Y, 1);
    emxInit_creal_T(&b_X, 1);
    fft(x, m2, X);
    fft(y, m2, Y);
    u0 = b_X->size[0];
    b_X->size[0] = X->size[0];
    emxEnsureCapacity((emxArray__common *)b_X, u0, sizeof(creal_T));
    loop_ub = X->size[0];
    for (u0 = 0; u0 < loop_ub; u0++) {
      c0 = Y->data[u0].re;
      Sn = -Y->data[u0].im;
      ceilLog2 = X->data[u0].re;
      ihi = X->data[u0].im;
      b_X->data[u0].re = ceilLog2 * c0 - ihi * Sn;
      b_X->data[u0].im = ceilLog2 * Sn + ihi * c0;
    }

    emxFree_creal_T(&Y);
    emxInit_real_T(&c1, 1);
    ifft(b_X, X);
    u0 = c1->size[0];
    c1->size[0] = X->size[0];
    emxEnsureCapacity((emxArray__common *)c1, u0, sizeof(double));
    loop_ub = X->size[0];
    emxFree_creal_T(&b_X);
    for (u0 = 0; u0 < loop_ub; u0++) {
      c1->data[u0] = X->data[u0].re;
    }

    emxFree_creal_T(&X);
    emxInit_real_T1(&r2, 2);
    if (mxl < 1.0) {
      u0 = r2->size[0] * r2->size[1];
      r2->size[0] = 1;
      r2->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)r2, u0, sizeof(double));
    } else {
      u0 = r2->size[0] * r2->size[1];
      r2->size[0] = 1;
      r2->size[1] = (int)floor(mxl - 1.0) + 1;
      emxEnsureCapacity((emxArray__common *)r2, u0, sizeof(double));
      loop_ub = (int)floor(mxl - 1.0);
      for (u0 = 0; u0 <= loop_ub; u0++) {
        r2->data[r2->size[0] * u0] = 1.0 + (double)u0;
      }
    }

    if (1.0 > mxl + 1.0) {
      loop_ub = 0;
    } else {
      loop_ub = (int)(mxl + 1.0);
    }

    m2 -= mxl;
    u0 = c->size[0];
    c->size[0] = r2->size[1] + loop_ub;
    emxEnsureCapacity((emxArray__common *)c, u0, sizeof(double));
    maxmn = r2->size[1];
    for (u0 = 0; u0 < maxmn; u0++) {
      c->data[u0] = c1->data[(int)(m2 + r2->data[r2->size[0] * u0]) - 1];
    }

    for (u0 = 0; u0 < loop_ub; u0++) {
      c->data[u0 + r2->size[1]] = c1->data[u0];
    }

    emxFree_real_T(&r2);
    emxFree_real_T(&c1);
  }
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = 1.0;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *varargin_1
 *                emxArray_real_T *c
 * Return Type  : void
 */
void xcorr(const emxArray_real_T *x, const emxArray_real_T *varargin_1,
           emxArray_real_T *c)
{
  int u0;
  int u1;
  emxArray_real_T *c1;
  int b_varargin_1[1];
  emxArray_real_T c_varargin_1;
  int i2;
  u0 = x->size[0];
  u1 = varargin_1->size[1];
  if (u0 > u1) {
    u1 = u0;
  }

  emxInit_real_T(&c1, 1);
  b_varargin_1[0] = varargin_1->size[1];
  c_varargin_1 = *varargin_1;
  c_varargin_1.size = (int *)&b_varargin_1;
  c_varargin_1.numDimensions = 1;
  crosscorr(x, &c_varargin_1, (double)u1 - 1.0, c1);
  i2 = c->size[0];
  c->size[0] = (int)(2.0 * ((double)u1 - 1.0) + 1.0);
  emxEnsureCapacity((emxArray__common *)c, i2, sizeof(double));
  u0 = (int)(2.0 * ((double)u1 - 1.0) + 1.0);
  for (i2 = 0; i2 < u0; i2++) {
    c->data[i2] = 0.0;
  }

  u0 = c1->size[0] - 1;
  for (i2 = 0; i2 <= u0; i2++) {
    c->data[i2] = c1->data[i2];
  }

  emxFree_real_T(&c1);
}

/*
 * File trailer for xcorr.c
 *
 * [EOF]
 */
