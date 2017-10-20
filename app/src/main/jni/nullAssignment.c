/*
 * File: nullAssignment.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "nullAssignment.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 *                const emxArray_int32_T *idx
 * Return Type  : void
 */
void nullAssignment(emxArray_real_T *x, const emxArray_int32_T *idx)
{
  emxArray_boolean_T *b;
  int nxin;
  int nrowx;
  int ncolx;
  int k;
  int n;
  int nxout;
  int k0;
  emxArray_real_T *b_x;
  emxArray_real_T *c_x;
  emxInit_boolean_T(&b, 2);
  nxin = x->size[0] * x->size[1];
  nrowx = x->size[0];
  ncolx = x->size[1];
  k = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = nxin;
  emxEnsureCapacity((emxArray__common *)b, k, sizeof(boolean_T));
  for (k = 0; k < nxin; k++) {
    b->data[k] = false;
  }

  for (k = 1; k <= idx->size[0]; k++) {
    b->data[idx->data[k - 1] - 1] = true;
  }

  n = 0;
  for (k = 1; k <= b->size[1]; k++) {
    n += b->data[k - 1];
  }

  nxout = nxin - n;
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  emxInit_real_T1(&b_x, 2);
  emxInit_real_T(&c_x, 1);
  if ((nrowx != 1) && (ncolx == 1)) {
    if (1 > nxout) {
      n = 0;
    } else {
      n = nxout;
    }

    k = c_x->size[0];
    c_x->size[0] = n;
    emxEnsureCapacity((emxArray__common *)c_x, k, sizeof(double));
    for (k = 0; k < n; k++) {
      c_x->data[k] = x->data[k];
    }

    k = x->size[0] * x->size[1];
    x->size[0] = n;
    x->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)x, k, sizeof(double));
    for (k = 0; k < 1; k++) {
      for (k0 = 0; k0 < n; k0++) {
        x->data[k0] = c_x->data[k0];
      }
    }
  } else {
    if (1 > nxout) {
      n = 0;
    } else {
      n = nxout;
    }

    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_x, k, sizeof(double));
    for (k = 0; k < n; k++) {
      b_x->data[b_x->size[0] * k] = x->data[k];
    }

    k = x->size[0] * x->size[1];
    x->size[0] = b_x->size[0];
    x->size[1] = b_x->size[1];
    emxEnsureCapacity((emxArray__common *)x, k, sizeof(double));
    n = b_x->size[1];
    for (k = 0; k < n; k++) {
      nxout = b_x->size[0];
      for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0 + x->size[0] * k] = b_x->data[k0 + b_x->size[0] * k];
      }
    }
  }

  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
}

/*
 * File trailer for nullAssignment.c
 *
 * [EOF]
 */
