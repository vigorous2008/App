/*
 * File: diff.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 23-Oct-2017 13:29:03
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "diff.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int dimSize;
  int orderForDim;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  double tmp2;
  dimSize = x->size[0];
  if (x->size[0] == 0) {
    iyLead = y->size[0] * y->size[1];
    y->size[0] = 0;
    y->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
  } else {
    orderForDim = x->size[0] - 1;
    if (!(orderForDim < 1)) {
      orderForDim = 1;
    }

    if (orderForDim < 1) {
      iyLead = y->size[0] * y->size[1];
      y->size[0] = 0;
      y->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
    } else {
      orderForDim = x->size[0] - 1;
      iyLead = y->size[0] * y->size[1];
      y->size[0] = orderForDim;
      y->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
      if (!(y->size[0] == 0)) {
        orderForDim = 1;
        iyLead = 0;
        work_data_idx_0 = x->data[0];
        for (m = 2; m <= dimSize; m++) {
          tmp1 = x->data[orderForDim];
          tmp2 = work_data_idx_0;
          work_data_idx_0 = tmp1;
          tmp1 -= tmp2;
          orderForDim++;
          y->data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int orderForDim;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  double tmp2;
  if (x->size[0] == 0) {
    iyLead = y->size[0];
    y->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
  } else {
    orderForDim = x->size[0] - 1;
    if (!(orderForDim < 1)) {
      orderForDim = 1;
    }

    if (orderForDim < 1) {
      iyLead = y->size[0];
      y->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
    } else {
      orderForDim = x->size[0] - 1;
      iyLead = y->size[0];
      y->size[0] = orderForDim;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
      if (!(y->size[0] == 0)) {
        orderForDim = 1;
        iyLead = 0;
        work_data_idx_0 = x->data[0];
        for (m = 2; m <= x->size[0]; m++) {
          tmp1 = x->data[orderForDim];
          tmp2 = work_data_idx_0;
          work_data_idx_0 = tmp1;
          tmp1 -= tmp2;
          orderForDim++;
          y->data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
