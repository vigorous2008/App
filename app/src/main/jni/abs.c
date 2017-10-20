/*
 * File: abs.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "abs.h"
#include "extmessage_emxutil.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : const creal_T x[256]
 *                double y[256]
 * Return Type  : void
 */
void b_abs(const creal_T x[256], double y[256])
{
  int k;
  for (k = 0; k < 256; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void c_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  unsigned int unnamed_idx_0;
  int k;
  unnamed_idx_0 = (unsigned int)x->size[0];
  k = y->size[0];
  y->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, sizeof(double));
  for (k = 0; k + 1 <= x->size[0]; k++) {
    y->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
