/*
 * File: filterpointer.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 25-Oct-2017 12:21:32
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
  emxArray_real_T *r2;
  int i6;
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
  emxInit_real_T(&r2, 1);
  diff(IndMax, r2);
  i6 = x->size[0];
  x->size[0] = r2->size[0];
  emxEnsureCapacity((emxArray__common *)x, i6, sizeof(boolean_T));
  nxout = r2->size[0];
  for (i6 = 0; i6 < nxout; i6++) {
    x->data[i6] = (r2->data[i6] > 1000.0);
  }

  emxFree_real_T(&r2);
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

  i6 = IndMax->size[0];
  IndMax->size[0] = idx;
  emxEnsureCapacity((emxArray__common *)IndMax, i6, sizeof(double));

  /*  figure; */
  /*  plot(diff(IndMax)); */
  /*  figure;    */
  /*  plot(IndMax); */
  /*  tempdata = data(IndMax); */
  i6 = IndMax->size[0];
  for (i = 0; i < i6; i++) {
    y = data->data[(int)(IndMax->data[i] + -500.0) - 1];
    for (k = 0; k < 1000; k++) {
      y += data->data[(int)(IndMax->data[i] + (-500.0 + ((double)k + 1.0))) - 1];
    }

    if ((data->data[(int)IndMax->data[i] - 1] < y / 1001.0) || (data->data[(int)
         IndMax->data[i] - 1] < 0.01)) {
      IndMax->data[i] = 0.0;
    }
  }

  i6 = x->size[0];
  x->size[0] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)x, i6, sizeof(boolean_T));
  nxout = IndMax->size[0];
  for (i6 = 0; i6 < nxout; i6++) {
    x->data[i6] = (IndMax->data[i6] == 0.0);
  }

  emxInit_int32_T1(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i6 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
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
      i6 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
    }
  } else {
    i6 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_boolean_T1(&b, 2);
  idx = IndMax->size[0];
  i6 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)b, i6, sizeof(boolean_T));
  nxout = IndMax->size[0];
  for (i6 = 0; i6 < nxout; i6++) {
    b->data[i6] = false;
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
  i6 = b_IndMax->size[0];
  b_IndMax->size[0] = nxout;
  emxEnsureCapacity((emxArray__common *)b_IndMax, i6, sizeof(double));
  for (i6 = 0; i6 < nxout; i6++) {
    b_IndMax->data[i6] = IndMax->data[i6];
  }

  i6 = IndMax->size[0];
  IndMax->size[0] = b_IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)IndMax, i6, sizeof(double));
  nxout = b_IndMax->size[0];
  for (i6 = 0; i6 < nxout; i6++) {
    IndMax->data[i6] = b_IndMax->data[i6];
  }

  emxFree_real_T(&b_IndMax);
}

/*
 * File trailer for filterpointer.c
 *
 * [EOF]
 */
