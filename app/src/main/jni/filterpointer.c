/*
 * File: filterpointer.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 24-Oct-2017 11:07:21
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
  int ixstart;
  int n;
  int nxin;
  int nx;
  double mtmp;
  boolean_T exitg1;
  double y;
  int k;
  emxArray_int32_T *ii;
  emxArray_boolean_T *b;
  emxArray_real_T *b_IndMax;
  emxInit_boolean_T(&x, 1);
  emxInit_real_T(&r2, 1);
  diff(IndMax, r2);
  i6 = x->size[0];
  x->size[0] = r2->size[0];
  emxEnsureCapacity((emxArray__common *)x, i6, sizeof(boolean_T));
  ixstart = r2->size[0];
  for (i6 = 0; i6 < ixstart; i6++) {
    x->data[i6] = (r2->data[i6] > 1000.0);
  }

  emxFree_real_T(&r2);
  ixstart = x->size[0] - 1;
  n = 0;
  for (nxin = 0; nxin <= ixstart; nxin++) {
    if (x->data[nxin]) {
      n++;
    }
  }

  nx = 0;
  for (nxin = 0; nxin <= ixstart; nxin++) {
    if (x->data[nxin]) {
      IndMax->data[nx] = IndMax->data[nxin];
      nx++;
    }
  }

  i6 = IndMax->size[0];
  IndMax->size[0] = n;
  emxEnsureCapacity((emxArray__common *)IndMax, i6, sizeof(double));

  /*  figure; */
  /*  plot(diff(IndMax)); */
  /*  figure;    */
  /*  plot(IndMax); */
  /*  tempdata = data(IndMax); */
  ixstart = 1;
  n = IndMax->size[0];
  mtmp = data->data[(int)IndMax->data[0] - 1];
  if (IndMax->size[0] > 1) {
    if (rtIsNaN(mtmp)) {
      nx = 2;
      exitg1 = false;
      while ((!exitg1) && (nx <= n)) {
        ixstart = nx;
        if (!rtIsNaN(data->data[(int)IndMax->data[nx - 1] - 1])) {
          mtmp = data->data[(int)IndMax->data[nx - 1] - 1];
          exitg1 = true;
        } else {
          nx++;
        }
      }
    }

    if (ixstart < IndMax->size[0]) {
      while (ixstart + 1 <= n) {
        if (data->data[(int)IndMax->data[ixstart] - 1] > mtmp) {
          mtmp = data->data[(int)IndMax->data[ixstart] - 1];
        }

        ixstart++;
      }
    }
  }

  i6 = IndMax->size[0];
  for (nxin = 0; nxin < i6; nxin++) {
    y = data->data[(int)(IndMax->data[nxin] + -500.0) - 1];
    for (k = 0; k < 1000; k++) {
      y += data->data[(int)(IndMax->data[nxin] + (-500.0 + ((double)k + 1.0))) -
        1];
    }

    if ((data->data[(int)IndMax->data[nxin] - 1] < y / 1001.0) || (data->data
         [(int)IndMax->data[nxin] - 1] < mtmp / 6.0)) {
      IndMax->data[nxin] = 0.0;
    }
  }

  i6 = x->size[0];
  x->size[0] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)x, i6, sizeof(boolean_T));
  ixstart = IndMax->size[0];
  for (i6 = 0; i6 < ixstart; i6++) {
    x->data[i6] = (IndMax->data[i6] == 0.0);
  }

  emxInit_int32_T1(&ii, 1);
  nx = x->size[0];
  n = 0;
  i6 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
  ixstart = 1;
  exitg1 = false;
  while ((!exitg1) && (ixstart <= nx)) {
    if (x->data[ixstart - 1]) {
      n++;
      ii->data[n - 1] = ixstart;
      if (n >= nx) {
        exitg1 = true;
      } else {
        ixstart++;
      }
    } else {
      ixstart++;
    }
  }

  if (x->size[0] == 1) {
    if (n == 0) {
      i6 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
    }
  } else {
    i6 = ii->size[0];
    if (1 > n) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = n;
    }

    emxEnsureCapacity((emxArray__common *)ii, i6, sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_boolean_T1(&b, 2);
  nxin = IndMax->size[0];
  i6 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)b, i6, sizeof(boolean_T));
  ixstart = IndMax->size[0];
  for (i6 = 0; i6 < ixstart; i6++) {
    b->data[i6] = false;
  }

  for (k = 1; k <= ii->size[0]; k++) {
    b->data[ii->data[k - 1] - 1] = true;
  }

  emxFree_int32_T(&ii);
  n = 0;
  for (k = 1; k <= b->size[1]; k++) {
    n += b->data[k - 1];
  }

  ixstart = IndMax->size[0] - n;
  nx = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      nx++;
      IndMax->data[nx] = IndMax->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (1 > ixstart) {
    ixstart = 0;
  }

  emxInit_real_T(&b_IndMax, 1);
  i6 = b_IndMax->size[0];
  b_IndMax->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)b_IndMax, i6, sizeof(double));
  for (i6 = 0; i6 < ixstart; i6++) {
    b_IndMax->data[i6] = IndMax->data[i6];
  }

  i6 = IndMax->size[0];
  IndMax->size[0] = b_IndMax->size[0];
  emxEnsureCapacity((emxArray__common *)IndMax, i6, sizeof(double));
  ixstart = b_IndMax->size[0];
  for (i6 = 0; i6 < ixstart; i6++) {
    IndMax->data[i6] = b_IndMax->data[i6];
  }

  emxFree_real_T(&b_IndMax);
}

/*
 * File trailer for filterpointer.c
 *
 * [EOF]
 */
