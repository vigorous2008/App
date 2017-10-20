/*
 * File: hilbert.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "hilbert.h"
#include "extmessage_emxutil.h"
#include "ifft.h"
#include "fft.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *xr
 *                emxArray_creal_T *x
 * Return Type  : void
 */
void hilbert(const emxArray_real_T *xr, emxArray_creal_T *x)
{
  int b_xr[1];
  emxArray_real_T c_xr;
  int maxval;
  int halfn;
  int lastIndexToDouble;
  int i;
  emxArray_creal_T *b_x;
  b_xr[0] = xr->size[0];
  c_xr = *xr;
  c_xr.size = (int *)&b_xr;
  c_xr.numDimensions = 1;
  b_fft(&c_xr, x);
  maxval = xr->size[0];
  halfn = maxval >> 1;
  if ((maxval & 1) == 0) {
    lastIndexToDouble = halfn;
  } else {
    lastIndexToDouble = halfn + 1;
  }

  for (i = 1; i + 1 <= lastIndexToDouble; i++) {
    x->data[i].re *= 2.0;
    x->data[i].im *= 2.0;
  }

  for (i = halfn + 1; i + 1 <= maxval; i++) {
    x->data[i].re = 0.0;
    x->data[i].im = 0.0;
  }

  emxInit_creal_T(&b_x, 1);
  maxval = b_x->size[0];
  b_x->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, maxval, sizeof(creal_T));
  halfn = x->size[0];
  for (maxval = 0; maxval < halfn; maxval++) {
    b_x->data[maxval] = x->data[maxval];
  }

  ifft(b_x, x);
  emxFree_creal_T(&b_x);
}

/*
 * File trailer for hilbert.c
 *
 * [EOF]
 */
