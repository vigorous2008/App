/*
 * File: lx_smooth.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 23-Oct-2017 13:29:03
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "lx_smooth.h"
#include "extmessage_emxutil.h"
#include "filter.h"
#include "any.h"
#include "diff.h"

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * moving average of the data.
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                double span_data[]
 *                emxArray_real_T *c
 * Return Type  : void
 */
void moving(const emxArray_real_T *x, const emxArray_real_T *y, double
            span_data[], emxArray_real_T *c)
{
  emxArray_boolean_T *ynan;
  int i1;
  int loop_ub;
  double u0;
  double u1;
  emxArray_real_T *yy;
  emxArray_boolean_T *b_yy;
  boolean_T xreps;
  emxArray_real_T *b_ynan;
  emxArray_real_T *c_yy;
  emxArray_real_T *cbegin;
  int k;
  double b_cbegin[797];
  int i2;
  int i;
  int i3;
  double b_span_data[1];
  int i4;
  int vstride;
  emxInit_boolean_T(&ynan, 1);

  /* -------------------------------------------------------------------- */
  i1 = ynan->size[0];
  ynan->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)ynan, i1, sizeof(boolean_T));
  loop_ub = y->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    ynan->data[i1] = rtIsNaN(y->data[i1]);
  }

  loop_ub = y->size[0];
  u0 = span_data[0];
  u1 = loop_ub;
  if (u0 < u1) {
    u1 = u0;
  }

  emxInit_real_T(&yy, 1);
  emxInit_boolean_T(&b_yy, 1);

  /* width = span(1)-1+mod(span,2); % force it to be odd */
  diff(x, yy);
  i1 = b_yy->size[0];
  b_yy->size[0] = yy->size[0];
  emxEnsureCapacity((emxArray__common *)b_yy, i1, sizeof(boolean_T));
  loop_ub = yy->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_yy->data[i1] = (yy->data[i1] == 0.0);
  }

  xreps = any(b_yy);

  /*  if width==1 && ~xreps && ~any(ynan), c = y; return; end */
  emxFree_boolean_T(&b_yy);
  emxInit_real_T(&b_ynan, 1);
  emxInit_real_T(&c_yy, 1);
  emxInit_real_T(&cbegin, 1);
  if ((!xreps) && (!any(ynan))) {
    /*  simplest method for most common case */
    filter(y, c);
    for (i1 = 0; i1 < 797; i1++) {
      b_cbegin[i1] = y->data[i1];
    }

    for (k = 0; k < 796; k++) {
      b_cbegin[k + 1] += b_cbegin[k];
    }

    if (y->size[0] - 796 > y->size[0]) {
      i1 = 1;
      i2 = 1;
      i3 = 0;
    } else {
      i1 = y->size[0];
      i2 = -1;
      i3 = y->size[0] - 796;
    }

    i4 = yy->size[0];
    yy->size[0] = div_s32_floor(i3 - i1, i2) + 1;
    emxEnsureCapacity((emxArray__common *)yy, i4, sizeof(double));
    loop_ub = div_s32_floor(i3 - i1, i2);
    for (i4 = 0; i4 <= loop_ub; i4++) {
      yy->data[i4] = y->data[(i1 + i2 * i4) - 1];
    }

    i = 2;
    if (div_s32_floor(i3 - i1, i2) + 1 != 1) {
      i = 1;
    }

    if (i <= 1) {
      i4 = div_s32_floor(i3 - i1, i2);
    } else {
      i4 = 0;
    }

    if ((!(div_s32_floor(i3 - i1, i2) + 1 == 0)) && (i4 + 1 > 1)) {
      vstride = 1;
      k = 1;
      while (k <= i - 1) {
        vstride *= div_s32_floor(i3 - i1, i2) + 1;
        k = 2;
      }

      for (loop_ub = 0; loop_ub + 1 <= vstride; loop_ub++) {
        for (k = 1; k <= i4; k++) {
          yy->data[loop_ub + k * vstride] += yy->data[loop_ub + (k - 1) *
            vstride];
        }
      }
    }

    if (1 > yy->size[0]) {
      i1 = 1;
      i2 = 1;
      i3 = 0;
    } else {
      i1 = yy->size[0];
      i2 = -2;
      i3 = 1;
    }

    if (799 > c->size[0]) {
      i4 = -798;
      k = 0;
    } else {
      i4 = 0;
      k = c->size[0];
    }

    i = c_yy->size[0];
    c_yy->size[0] = div_s32_floor(i3 - i1, i2) + 1;
    emxEnsureCapacity((emxArray__common *)c_yy, i, sizeof(double));
    loop_ub = div_s32_floor(i3 - i1, i2);
    for (i3 = 0; i3 <= loop_ub; i3++) {
      c_yy->data[i3] = yy->data[(i1 + i2 * i3) - 1];
    }

    i1 = cbegin->size[0];
    cbegin->size[0] = k - i4;
    emxEnsureCapacity((emxArray__common *)cbegin, i1, sizeof(double));
    for (i1 = 0; i1 < 399; i1++) {
      cbegin->data[i1] = b_cbegin[i1 << 1] / (1.0 + 2.0 * (double)i1);
    }

    loop_ub = k - i4;
    for (i1 = 0; i1 <= loop_ub - 799; i1++) {
      cbegin->data[i1 + 399] = c->data[(i4 + i1) + 798];
    }

    for (i1 = 0; i1 < 399; i1++) {
      cbegin->data[((i1 + k) - i4) - 399] = c_yy->data[i1] / (797.0 + -2.0 *
        (double)i1);
    }

    i1 = c->size[0];
    c->size[0] = cbegin->size[0];
    emxEnsureCapacity((emxArray__common *)c, i1, sizeof(double));
    loop_ub = cbegin->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      c->data[i1] = cbegin->data[i1];
    }
  } else if (!xreps) {
    /*  with no x repeats, can take ratio of two smoothed sequences */
    i1 = yy->size[0];
    yy->size[0] = y->size[0];
    emxEnsureCapacity((emxArray__common *)yy, i1, sizeof(double));
    loop_ub = y->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      yy->data[i1] = y->data[i1];
    }

    loop_ub = ynan->size[0];
    for (i = 0; i < loop_ub; i++) {
      if (ynan->data[i]) {
        yy->data[i] = 0.0;
      }
    }

    b_span_data[0] = u1;
    moving(x, yy, b_span_data, c);
    i1 = b_ynan->size[0];
    b_ynan->size[0] = ynan->size[0];
    emxEnsureCapacity((emxArray__common *)b_ynan, i1, sizeof(double));
    loop_ub = ynan->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_ynan->data[i1] = !ynan->data[i1];
    }

    b_span_data[0] = u1;
    moving(x, b_ynan, b_span_data, yy);
    i1 = c->size[0];
    emxEnsureCapacity((emxArray__common *)c, i1, sizeof(double));
    loop_ub = c->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      c->data[i1] /= yy->data[i1];
    }
  } else {
    /*  with some x repeats, loop */
    /*      notnan = ~ynan; */
    /*      yy = y; */
    /*      yy(ynan) = 0; */
    /*      c = zeros(n,1,'like',y); */
    /*      for i=1:n */
    /*          if i>1 && x(i)==x(i-1) */
    /*              c(i) = c(i-1); */
    /*              continue; */
    /*          end */
    /*          R = i;                                 % find rightmost value with same x */
    /*          while(R<n && x(R+1)==x(R)) */
    /*              R = R+1; */
    /*          end */
    /*          hf = ceil(max(0,(span - (R-i+1))/2));  % need this many more on each side */
    /*          hf = min(min(hf,(i-1)), (n-R)); */
    /*          L = i-hf;                              % find leftmost point needed */
    /*          while(L>1 && x(L)==x(L-1)) */
    /*              L = L-1; */
    /*          end */
    /*          R = R+hf;                              % find rightmost point needed */
    /*          while(R<n && x(R)==x(R+1)) */
    /*              R = R+1; */
    /*          end */
    /*          c(i) = sum(yy(L:R)) / sum(notnan(L:R)); */
    /*      end */
    filter(y, c);
  }

  emxFree_real_T(&cbegin);
  emxFree_real_T(&c_yy);
  emxFree_real_T(&b_ynan);
  emxFree_real_T(&yy);
  emxFree_boolean_T(&ynan);
}

/*
 * File trailer for lx_smooth.c
 *
 * [EOF]
 */
