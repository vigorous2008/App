/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "sort1.h"
#include "sortIdx.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void sort(emxArray_real_T *x)
{
  int dim;
  int i7;
  emxArray_real_T *vwork;
  int j;
  int vstride;
  int k;
  emxArray_int32_T *b_vwork;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  if (dim <= 1) {
    i7 = x->size[0];
  } else {
    i7 = 1;
  }

  emxInit_real_T(&vwork, 1);
  j = vwork->size[0];
  vwork->size[0] = i7;
  emxEnsureCapacity((emxArray__common *)vwork, j, sizeof(double));
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x->size[0];
    k = 2;
  }

  j = 0;
  emxInit_int32_T1(&b_vwork, 1);
  while (j + 1 <= vstride) {
    for (k = 0; k + 1 <= i7; k++) {
      vwork->data[k] = x->data[j + k * vstride];
    }

    sortIdx(vwork, b_vwork);
    for (k = 0; k + 1 <= i7; k++) {
      x->data[j + k * vstride] = vwork->data[k];
    }

    j++;
  }

  emxFree_int32_T(&b_vwork);
  emxFree_real_T(&vwork);
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
