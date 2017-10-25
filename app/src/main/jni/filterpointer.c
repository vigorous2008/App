/*
 * File: filterpointer.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 25-Oct-2017 09:40:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "filterpointer.h"
#include "extmessage_emxutil.h"
#include "diff.h"

/* Function Definitions */

/*
 * FILTERPOINTER Summary of this function goes here
 *    Detailed explanation goes here
 *  figure;
 *  plot(IndMax);
 * Arguments    : emxArray_real_T *IndMax
 *                const emxArray_real_T *data
 * Return Type  : void
 */
void filterpointer(emxArray_real_T *IndMax, const emxArray_real_T *data)
{
  emxArray_boolean_T *x;
  emxArray_real_T *r3;
  int i7;
  int nxout;
  int idx;
  int i;
  int nx;
  double y;
  int k;
  emxArray_int32_T *ii;
  boolean_T exitg1;
  emxArray_boolean_T *b;
  emxArray_real_T *b_IndMax;
  emxInit_boolean_T(&x, 1);
  emxInit_real_T(&r3, 1);
  diff(IndMax, r3);
  i7 = x->size[0];
  x->size[0] = r3->size[0];
  emxEnsureCapacity((emxArray__common *)x, i7, sizeof(boolean_T));
  nxout = r3->size[0];
  for (i7 = 0; i7 < nxout; i7++) {
    x->data[i7] = (r3->data[i7] > 1000.0);
  }

  emxFree_real_T(&r3);
  nxout = x->size[0] - 1;
  idx = 0;
  for (i = 0; i <= nxout; i++) {
    if (x->data[i]) {
      idx++;
    }
  }

  nx = 0;
  for (i = 0; i <= nxout; i++) {
    if (x->data[i]) {
      IndMax->data[nx] = IndMax->data[i];
      nx++;
    }
  }

  i7 = IndMax->size[0];
  IndMax->size[0] = idx;
  emxEnsureCapacity((emxArray__common *)IndMax, i7, sizeof(double));

  /*  figure; */
  /*  plot(diff(IndMax)); */
  /*  figure;    */
  /*  plot(IndMax); */
  /*  tempdata = data(IndMax); */
  i7 = IndMax->size[0];
  for (i = 0; i < i7; i++) {
    y = data->data[(int)(IndMax->data[i] + -500.0) - 1];
    for (k = 0; k < 1000; k++) {
      y += data->data[(int)(IndMax->data[i] + (-500.0 + ((double)k + 1.0))) - 1];
    }

    if ((data->data[(int)IndMax->data[i] - 1] < y / 1001.0) || (data->data[(int)
         IndMax->data[i] - 1] < 0.01)) {
      IndMax->data[i] = 0.0;
    }
  }

  i7 = x->size[0];
  x->size[0] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)x, i7, sizeof(boolean_T));
  nxout = IndMax->size[0];
  for (i7 = 0; i7 < nxout; i7++) {
    x->data[i7] = (IndMax->data[i7] == 0.0);
  }

  emxInit_int32_T1(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i7 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i7, sizeof(int));
  nxout = 1;
  exitg1 = false;
  while ((!exitg1) && (nxout <= nx)) {
    if (x->data[nxout - 1]) {
      idx++;
      ii->data[idx - 1] = nxout;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        nxout++;
      }
    } else {
      nxout++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i7 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i7, sizeof(int));
    }
  } else {
    i7 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i7, sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_boolean_T1(&b, 2);
  idx = IndMax->size[0];
  i7 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)b, i7, sizeof(boolean_T));
  nxout = IndMax->size[0];
  for (i7 = 0; i7 < nxout; i7++) {
    b->data[i7] = false;
  }

  for (k = 1; k <= ii->size[0]; k++) {
    b->data[ii->data[k - 1] - 1] = true;
  }

  emxFree_int32_T(&ii);
  nxout = 0;
  for (k = 1; k <= b->size[1]; k++) {
    nxout += b->data[k - 1];
  }

  nxout = IndMax->size[0] - nxout;
  nx = -1;
  for (k = 1; k <= idx; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      nx++;
      IndMax->data[nx] = IndMax->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (1 > nxout) {
    nxout = 0;
  }

  emxInit_real_T(&b_IndMax, 1);
  i7 = b_IndMax->size[0];
  b_IndMax->size[0] = nxout;
  emxEnsureCapacity((emxArray__common *)b_IndMax, i7, sizeof(double));
  for (i7 = 0; i7 < nxout; i7++) {
    b_IndMax->data[i7] = IndMax->data[i7];
  }

  i7 = IndMax->size[0];
  IndMax->size[0] = b_IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)IndMax, i7, sizeof(double));
  nxout = b_IndMax->size[0];
  for (i7 = 0; i7 < nxout; i7++) {
    IndMax->data[i7] = b_IndMax->data[i7];
  }

  emxFree_real_T(&b_IndMax);
}

/*
 * File trailer for filterpointer.c
 *
 * [EOF]
 */
