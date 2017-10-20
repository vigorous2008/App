/*
 * File: lx_smooth.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "lx_smooth.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

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
  int i2;
  int ySize_idx_0;
  emxArray_real_T *idx;
  emxArray_int32_T *r1;

  /*    Copyright 2001-2016 The MathWorks, Inc. */
  /*  ws = warning('query','all'); % Leave warning state alone but save it so resets are no-ops. */
  /*  is x given as the first argument? */
  /*  smooth(Y) | smooth(Y,span,...) | smooth(Y,method,...) */
  /*  x is not given */
  i2 = c->size[0];
  c->size[0] = varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)c, i2, sizeof(double));
  ySize_idx_0 = varargin_1->size[0];
  for (i2 = 0; i2 < ySize_idx_0; i2++) {
    c->data[i2] = varargin_1->data[i2];
  }

  emxInit_real_T1(&idx, 2);

  /*  is span given? */
  /*  smooth(...,SPAN,...) */
  /*  is method given? */
  /*  method = []; */
  /*  if nargin >= 2+is_x+is_span */
  /*      % smooth(...,Y,method,...) | smooth(...,Y,span,method,...) */
  /*      method = varargin{2+is_x+is_span}; */
  /*  end */
  if (varargin_1->size[0] != 0) {
    /*  realize span */
    /*  percent convention */
    /*  smooth(Y,[],method) */
    if (varargin_1->size[0] < 1) {
      i2 = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)idx, i2, sizeof(double));
    } else {
      i2 = varargin_1->size[0];
      ySize_idx_0 = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = (int)((double)i2 - 1.0) + 1;
      emxEnsureCapacity((emxArray__common *)idx, ySize_idx_0, sizeof(double));
      ySize_idx_0 = (int)((double)i2 - 1.0);
      for (i2 = 0; i2 <= ySize_idx_0; i2++) {
        idx->data[idx->size[0] * i2] = 1.0 + (double)i2;
      }
    }

    /*  if NaNs not all at end */
    ySize_idx_0 = varargin_1->size[0];
    i2 = c->size[0];
    c->size[0] = ySize_idx_0;
    emxEnsureCapacity((emxArray__common *)c, i2, sizeof(double));
    for (i2 = 0; i2 < ySize_idx_0; i2++) {
      c->data[i2] = rtNaN;
    }

    emxInit_int32_T1(&r1, 2);

    /*  warning(ws); % reset warn state before erroring */
    /*  error(message('curvefit:smooth:unrecognizedMethod')); */
    i2 = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    r1->size[1] = idx->size[1];
    emxEnsureCapacity((emxArray__common *)r1, i2, sizeof(int));
    ySize_idx_0 = idx->size[0] * idx->size[1];
    for (i2 = 0; i2 < ySize_idx_0; i2++) {
      r1->data[i2] = (int)idx->data[i2];
    }

    ySize_idx_0 = r1->size[0] * r1->size[1];
    for (i2 = 0; i2 < ySize_idx_0; i2++) {
      c->data[r1->data[i2] - 1] = rtNaN;
    }

    emxFree_int32_T(&r1);
  }

  emxFree_real_T(&idx);
}

/*
 * File trailer for lx_smooth.c
 *
 * [EOF]
 */
