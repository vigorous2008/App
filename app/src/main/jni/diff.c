/*
 * File: diff.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
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
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int dimSize;
  int orderForDim;
  int ySize[2];
  int newDimSize;
  emxArray_real_T *work;
  int iyStart;
  int r;
  int ixLead;
  int iyLead;
  int m;
  double tmp1;
  int k;
  double tmp2;
  dimSize = x->size[0];
  if (x->size[0] == 0) {
    for (orderForDim = 0; orderForDim < 2; orderForDim++) {
      ySize[orderForDim] = x->size[orderForDim];
    }

    orderForDim = y->size[0] * y->size[1];
    y->size[0] = 0;
    y->size[1] = ySize[1];
    emxEnsureCapacity((emxArray__common *)y, orderForDim, sizeof(double));
  } else {
    orderForDim = x->size[0] - 1;
    if (!(orderForDim < 1)) {
      orderForDim = 1;
    }

    if (orderForDim < 1) {
      for (orderForDim = 0; orderForDim < 2; orderForDim++) {
        ySize[orderForDim] = x->size[orderForDim];
      }

      orderForDim = y->size[0] * y->size[1];
      y->size[0] = 0;
      y->size[1] = ySize[1];
      emxEnsureCapacity((emxArray__common *)y, orderForDim, sizeof(double));
    } else {
      newDimSize = x->size[0] - 1;
      for (orderForDim = 0; orderForDim < 2; orderForDim++) {
        ySize[orderForDim] = x->size[orderForDim];
      }

      emxInit_real_T(&work, 1);
      orderForDim = work->size[0];
      work->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)work, orderForDim, sizeof(double));
      orderForDim = y->size[0] * y->size[1];
      y->size[0] = newDimSize;
      y->size[1] = ySize[1];
      emxEnsureCapacity((emxArray__common *)y, orderForDim, sizeof(double));
      if (!((y->size[0] == 0) || (y->size[1] == 0))) {
        orderForDim = 1;
        iyStart = 0;
        for (r = 1; r <= x->size[1]; r++) {
          ixLead = orderForDim;
          iyLead = iyStart;
          work->data[0] = x->data[orderForDim - 1];
          for (m = 2; m <= dimSize; m++) {
            tmp1 = x->data[ixLead];
            for (k = 0; k + 1 < 2; k++) {
              tmp2 = work->data[k];
              work->data[k] = tmp1;
              tmp1 -= tmp2;
            }

            ixLead++;
            y->data[iyLead] = tmp1;
            iyLead++;
          }

          orderForDim += dimSize;
          iyStart += newDimSize;
        }
      }

      emxFree_real_T(&work);
    }
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
