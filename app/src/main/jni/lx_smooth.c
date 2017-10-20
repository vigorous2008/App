/*
 * File: lx_smooth.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 20-Oct-2017 14:06:37
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
static void moving(const emxArray_real_T *x, const emxArray_real_T *y, double
                   span_data[], emxArray_real_T *c);

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
static void moving(const emxArray_real_T *x, const emxArray_real_T *y, double
                   span_data[], emxArray_real_T *c)
{
  emxArray_boolean_T *ynan;
  int i5;
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
  double b_cbegin[597];
  int i6;
  int i;
  int i7;
  double b_span_data[1];
  int i8;
  int vstride;
  emxInit_boolean_T1(&ynan, 1);

  /* -------------------------------------------------------------------- */
  i5 = ynan->size[0];
  ynan->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)ynan, i5, sizeof(boolean_T));
  loop_ub = y->size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    ynan->data[i5] = rtIsNaN(y->data[i5]);
  }

  loop_ub = y->size[0];
  u0 = span_data[0];
  u1 = loop_ub;
  if (u0 < u1) {
    u1 = u0;
  }

  emxInit_real_T(&yy, 1);
  emxInit_boolean_T1(&b_yy, 1);

  /* width = span(1)-1+mod(span,2); % force it to be odd */
  diff(x, yy);
  i5 = b_yy->size[0];
  b_yy->size[0] = yy->size[0];
  emxEnsureCapacity((emxArray__common *)b_yy, i5, sizeof(boolean_T));
  loop_ub = yy->size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    b_yy->data[i5] = (yy->data[i5] == 0.0);
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
    for (i5 = 0; i5 < 597; i5++) {
      b_cbegin[i5] = y->data[i5];
    }

    for (k = 0; k < 596; k++) {
      b_cbegin[k + 1] += b_cbegin[k];
    }

    if (y->size[0] - 596 > y->size[0]) {
      i5 = 1;
      i6 = 1;
      i7 = 0;
    } else {
      i5 = y->size[0];
      i6 = -1;
      i7 = y->size[0] - 596;
    }

    i8 = yy->size[0];
    yy->size[0] = div_s32_floor(i7 - i5, i6) + 1;
    emxEnsureCapacity((emxArray__common *)yy, i8, sizeof(double));
    loop_ub = div_s32_floor(i7 - i5, i6);
    for (i8 = 0; i8 <= loop_ub; i8++) {
      yy->data[i8] = y->data[(i5 + i6 * i8) - 1];
    }

    i = 2;
    if (div_s32_floor(i7 - i5, i6) + 1 != 1) {
      i = 1;
    }

    if (i <= 1) {
      i8 = div_s32_floor(i7 - i5, i6);
    } else {
      i8 = 0;
    }

    if ((!(div_s32_floor(i7 - i5, i6) + 1 == 0)) && (i8 + 1 > 1)) {
      vstride = 1;
      k = 1;
      while (k <= i - 1) {
        vstride *= div_s32_floor(i7 - i5, i6) + 1;
        k = 2;
      }

      for (loop_ub = 0; loop_ub + 1 <= vstride; loop_ub++) {
        for (k = 1; k <= i8; k++) {
          yy->data[loop_ub + k * vstride] += yy->data[loop_ub + (k - 1) *
            vstride];
        }
      }
    }

    if (1 > yy->size[0]) {
      i5 = 1;
      i6 = 1;
      i7 = 0;
    } else {
      i5 = yy->size[0];
      i6 = -2;
      i7 = 1;
    }

    if (599 > c->size[0]) {
      i8 = -598;
      k = 0;
    } else {
      i8 = 0;
      k = c->size[0];
    }

    i = c_yy->size[0];
    c_yy->size[0] = div_s32_floor(i7 - i5, i6) + 1;
    emxEnsureCapacity((emxArray__common *)c_yy, i, sizeof(double));
    loop_ub = div_s32_floor(i7 - i5, i6);
    for (i7 = 0; i7 <= loop_ub; i7++) {
      c_yy->data[i7] = yy->data[(i5 + i6 * i7) - 1];
    }

    i5 = cbegin->size[0];
    cbegin->size[0] = k - i8;
    emxEnsureCapacity((emxArray__common *)cbegin, i5, sizeof(double));
    for (i5 = 0; i5 < 299; i5++) {
      cbegin->data[i5] = b_cbegin[i5 << 1] / (1.0 + 2.0 * (double)i5);
    }

    loop_ub = k - i8;
    for (i5 = 0; i5 <= loop_ub - 599; i5++) {
      cbegin->data[i5 + 299] = c->data[(i8 + i5) + 598];
    }

    for (i5 = 0; i5 < 299; i5++) {
      cbegin->data[((i5 + k) - i8) - 299] = c_yy->data[i5] / (597.0 + -2.0 *
        (double)i5);
    }

    i5 = c->size[0];
    c->size[0] = cbegin->size[0];
    emxEnsureCapacity((emxArray__common *)c, i5, sizeof(double));
    loop_ub = cbegin->size[0];
    for (i5 = 0; i5 < loop_ub; i5++) {
      c->data[i5] = cbegin->data[i5];
    }
  } else if (!xreps) {
    /*  with no x repeats, can take ratio of two smoothed sequences */
    i5 = yy->size[0];
    yy->size[0] = y->size[0];
    emxEnsureCapacity((emxArray__common *)yy, i5, sizeof(double));
    loop_ub = y->size[0];
    for (i5 = 0; i5 < loop_ub; i5++) {
      yy->data[i5] = y->data[i5];
    }

    loop_ub = ynan->size[0];
    for (i = 0; i < loop_ub; i++) {
      if (ynan->data[i]) {
        yy->data[i] = 0.0;
      }
    }

    b_span_data[0] = u1;
    moving(x, yy, b_span_data, c);
    i5 = b_ynan->size[0];
    b_ynan->size[0] = ynan->size[0];
    emxEnsureCapacity((emxArray__common *)b_ynan, i5, sizeof(double));
    loop_ub = ynan->size[0];
    for (i5 = 0; i5 < loop_ub; i5++) {
      b_ynan->data[i5] = !ynan->data[i5];
    }

    b_span_data[0] = u1;
    moving(x, b_ynan, b_span_data, yy);
    i5 = c->size[0];
    emxEnsureCapacity((emxArray__common *)c, i5, sizeof(double));
    loop_ub = c->size[0];
    for (i5 = 0; i5 < loop_ub; i5++) {
      c->data[i5] /= yy->data[i5];
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
 * SMOOTH  Smooth data.
 *    Z = SMOOTH(Y) smooths data Y using a 5-point moving average.
 *
 *    Z = SMOOTH(Y,SPAN) smooths data Y using SPAN as the number of points used
 *    to compute each element of Z.
 *
 *    Z = SMOOTH(Y,SPAN,METHOD) smooths data Y with specified METHOD. The
 *    available methods are:
 *
 *            'moving'   - Moving average (default)
 *            'lowess'   - Lowess (linear fit)
 *            'loess'    - Loess (quadratic fit)
 *            'sgolay'   - Savitzky-Golay
 *            'rlowess'  - Robust Lowess (linear fit)
 *            'rloess'   - Robust Loess (quadratic fit)
 *
 *    Z = SMOOTH(Y,METHOD) uses the default SPAN 5.
 *
 *    Z = SMOOTH(Y,SPAN,'sgolay',DEGREE) and Z = SMOOTH(Y,'sgolay',DEGREE)
 *    additionally specify the degree of the polynomial to be used in the
 *    Savitzky-Golay method. The default DEGREE is 2. DEGREE must be smaller
 *    than SPAN.
 *
 *    Z = SMOOTH(X,Y,...) additionally specifies the X coordinates.  If X is
 *    not provided, methods that require X coordinates assume X = 1:N, where
 *    N is the length of Y.
 *
 *    Notes:
 *    1. When X is given and X is not uniformly distributed, the default method
 *    is 'lowess'.  The 'moving' method is not recommended.
 *
 *    2. For the 'moving' and 'sgolay' methods, SPAN must be odd.
 *    If an even SPAN is specified, it is reduced by 1.
 *
 *    3. If SPAN is greater than the length of Y, it is reduced to the
 *    length of Y.
 *
 *    4. In the case of (robust) lowess and (robust) loess, it is also
 *    possible to specify the SPAN as a percentage of the total number
 *    of data points. When SPAN is less than or equal to 1, it is
 *    treated as a percentage.
 *
 *    For example:
 *
 *    Z = SMOOTH(Y) uses the moving average method with span 5 and
 *    X=1:length(Y).
 *
 *    Z = SMOOTH(Y,7) uses the moving average method with span 7 and
 *    X=1:length(Y).
 *
 *    Z = SMOOTH(Y,'sgolay') uses the Savitzky-Golay method with DEGREE=2,
 *    SPAN = 5, X = 1:length(Y).
 *
 *    Z = SMOOTH(X,Y,'lowess') uses the lowess method with SPAN=5.
 *
 *    Z = SMOOTH(X,Y,SPAN,'rloess') uses the robust loess method.
 *
 *    Z = SMOOTH(X,Y) where X is unevenly distributed uses the
 *    'lowess' method with span 5.
 *
 *    Z = SMOOTH(X,Y,8,'sgolay') uses the Savitzky-Golay method with
 *    span 7 (8 is reduced by 1 to make it odd).
 *
 *    Z = SMOOTH(X,Y,0.3,'loess') uses the loess method where span is
 *    30% of the data, i.e. span = ceil(0.3*length(Y)).
 *
 *    See also SPLINE.
 * Arguments    : const emxArray_real_T *varargin_1
 *                emxArray_real_T *c
 * Return Type  : void
 */
void lx_smooth(const emxArray_real_T *varargin_1, emxArray_real_T *c)
{
  emxArray_uint32_T *idx;
  unsigned int ySize_idx_0;
  int i;
  int loop_ub;
  emxArray_real_T *x;
  emxArray_boolean_T *ok;
  int end;
  emxArray_int32_T *r1;
  emxArray_real_T *b_x;
  emxArray_real_T *b_varargin_1;
  emxArray_real_T *b_y1;
  double tmp_data[1];
  emxArray_int32_T *r2;
  emxArray_real_T *b_c;

  /*    Copyright 2001-2016 The MathWorks, Inc. */
  /*  ws = warning('query','all'); % Leave warning state alone but save it so resets are no-ops. */
  /*  is x given as the first argument? */
  /*  smooth(Y) | smooth(Y,span,...) | smooth(Y,method,...) */
  /*  x is not given */
  emxInit_uint32_T(&idx, 2);
  if (varargin_1->size[0] < 1) {
    i = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
  } else {
    ySize_idx_0 = varargin_1->size[0] + MAX_uint32_T;
    i = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = (int)ySize_idx_0 + 1;
    emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
    loop_ub = (int)ySize_idx_0;
    for (i = 0; i <= loop_ub; i++) {
      idx->data[idx->size[0] * i] = 1U + i;
    }
  }

  emxInit_real_T(&x, 1);
  i = x->size[0];
  x->size[0] = idx->size[1];
  emxEnsureCapacity((emxArray__common *)x, i, sizeof(double));
  loop_ub = idx->size[1];
  for (i = 0; i < loop_ub; i++) {
    x->data[i] = idx->data[idx->size[0] * i];
  }

  /*  is span given? */
  /*  smooth(...,SPAN,...) */
  /*  is method given? */
  /*  method = []; */
  /*  if nargin >= 2+is_x+is_span */
  /*      % smooth(...,Y,method,...) | smooth(...,Y,span,method,...) */
  /*      method = varargin{2+is_x+is_span}; */
  /*  end */
  if (varargin_1->size[0] == 0) {
    i = c->size[0];
    c->size[0] = varargin_1->size[0];
    emxEnsureCapacity((emxArray__common *)c, i, sizeof(double));
    loop_ub = varargin_1->size[0];
    for (i = 0; i < loop_ub; i++) {
      c->data[i] = varargin_1->data[i];
    }
  } else {
    /*  realize span */
    /*  percent convention */
    /*  smooth(Y,[],method) */
    if (varargin_1->size[0] < 1) {
      i = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
    } else {
      ySize_idx_0 = varargin_1->size[0] + MAX_uint32_T;
      i = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = (int)ySize_idx_0 + 1;
      emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
      loop_ub = (int)ySize_idx_0;
      for (i = 0; i <= loop_ub; i++) {
        idx->data[idx->size[0] * i] = 1U + i;
      }
    }

    /*  if NaNs not all at end */
    ySize_idx_0 = (unsigned int)varargin_1->size[0];
    i = c->size[0];
    c->size[0] = (int)ySize_idx_0;
    emxEnsureCapacity((emxArray__common *)c, i, sizeof(double));
    loop_ub = (int)ySize_idx_0;
    for (i = 0; i < loop_ub; i++) {
      c->data[i] = rtNaN;
    }

    emxInit_boolean_T1(&ok, 1);
    i = ok->size[0];
    ok->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i, sizeof(boolean_T));
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      ok->data[i] = rtIsNaN(x->data[i]);
    }

    i = ok->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i, sizeof(boolean_T));
    loop_ub = ok->size[0];
    for (i = 0; i < loop_ub; i++) {
      ok->data[i] = !ok->data[i];
    }

    end = ok->size[0] - 1;
    loop_ub = 0;
    for (i = 0; i <= end; i++) {
      loop_ub++;
    }

    emxInit_int32_T(&r1, 1);
    i = r1->size[0];
    r1->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)r1, i, sizeof(int));
    loop_ub = 0;
    for (i = 0; i <= end; i++) {
      r1->data[loop_ub] = i + 1;
      loop_ub++;
    }

    emxInit_real_T(&b_x, 1);
    i = b_x->size[0];
    b_x->size[0] = r1->size[0];
    emxEnsureCapacity((emxArray__common *)b_x, i, sizeof(double));
    loop_ub = r1->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_x->data[i] = x->data[r1->data[i] - 1];
    }

    emxInit_real_T(&b_varargin_1, 1);
    i = b_varargin_1->size[0];
    b_varargin_1->size[0] = r1->size[0];
    emxEnsureCapacity((emxArray__common *)b_varargin_1, i, sizeof(double));
    loop_ub = r1->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_varargin_1->data[i] = varargin_1->data[r1->data[i] - 1];
    }

    emxFree_int32_T(&r1);
    emxInit_real_T(&b_y1, 1);
    tmp_data[0] = 600.0;
    moving(b_x, b_varargin_1, tmp_data, b_y1);
    end = ok->size[0];
    loop_ub = 0;
    emxFree_real_T(&b_varargin_1);
    emxFree_real_T(&b_x);
    emxFree_boolean_T(&ok);
    for (i = 0; i < end; i++) {
      c->data[i] = b_y1->data[loop_ub];
      loop_ub++;
    }

    emxFree_real_T(&b_y1);
    emxInit_int32_T1(&r2, 2);
    i = r2->size[0] * r2->size[1];
    r2->size[0] = 1;
    r2->size[1] = idx->size[1];
    emxEnsureCapacity((emxArray__common *)r2, i, sizeof(int));
    loop_ub = idx->size[0] * idx->size[1];
    for (i = 0; i < loop_ub; i++) {
      r2->data[i] = (int)idx->data[i];
    }

    emxInit_real_T(&b_c, 1);
    i = b_c->size[0];
    b_c->size[0] = r2->size[0] * r2->size[1];
    emxEnsureCapacity((emxArray__common *)b_c, i, sizeof(double));
    loop_ub = r2->size[0] * r2->size[1];
    for (i = 0; i < loop_ub; i++) {
      b_c->data[i] = c->data[i];
    }

    loop_ub = b_c->size[0];
    for (i = 0; i < loop_ub; i++) {
      c->data[r2->data[i] - 1] = b_c->data[i];
    }

    emxFree_real_T(&b_c);
    emxFree_int32_T(&r2);
  }

  emxFree_real_T(&x);
  emxFree_uint32_T(&idx);
}

/*
 * File trailer for lx_smooth.c
 *
 * [EOF]
 */
