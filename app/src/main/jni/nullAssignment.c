/*
 * File: nullAssignment.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "nullAssignment.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 *                const int idx_size[2]
 * Return Type  : void
 */
void nullAssignment(emxArray_real_T *x, const int idx_size[2])
{
  emxArray_boolean_T *b;
  int nxin;
  int k0;
  int nxout;
  int k;
  int exitg1;
  emxArray_real_T *b_x;
  emxInit_boolean_T1(&b, 2);
  nxin = x->size[0];
  k0 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = x->size[0];
  emxEnsureCapacity((emxArray__common *)b, k0, sizeof(boolean_T));
  nxout = x->size[0];
  for (k0 = 0; k0 < nxout; k0++) {
    b->data[k0] = false;
  }

  k0 = idx_size[0] * idx_size[1];
  k = 1;
  while (k <= k0) {
    b->data[0] = true;
    k = 2;
  }

  nxout = 0;
  k = 1;
  do {
    exitg1 = 0;
    k0 = x->size[0];
    if (k <= k0) {
      nxout += b->data[k - 1];
      k++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  nxout = x->size[0] - nxout;
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (1 > nxout) {
    nxout = 0;
  }

  emxInit_real_T(&b_x, 1);
  k0 = b_x->size[0];
  b_x->size[0] = nxout;
  emxEnsureCapacity((emxArray__common *)b_x, k0, sizeof(double));
  for (k0 = 0; k0 < nxout; k0++) {
    b_x->data[k0] = x->data[k0];
  }

  k0 = x->size[0];
  x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)x, k0, sizeof(double));
  nxout = b_x->size[0];
  for (k0 = 0; k0 < nxout; k0++) {
    x->data[k0] = b_x->data[k0];
  }

  emxFree_real_T(&b_x);
}

/*
 * File trailer for nullAssignment.c
 *
 * [EOF]
 */
