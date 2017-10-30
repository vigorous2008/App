/*
 * File: filter.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 25-Oct-2017 12:21:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "filter.h"
#include "extmessage_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int nx_m_nb;
  int nx;
  int jp;
  int k;
  int j;
  int naxpy;
  x_idx_0 = (unsigned int)x->size[0];
  nx_m_nb = y->size[0];
  y->size[0] = (int)x_idx_0;
  emxEnsureCapacity((emxArray__common *)y, nx_m_nb, sizeof(double));
  nx = x->size[0];
  jp = y->size[0];
  nx_m_nb = y->size[0];
  y->size[0] = jp;
  emxEnsureCapacity((emxArray__common *)y, nx_m_nb, sizeof(double));
  for (nx_m_nb = 0; nx_m_nb < jp; nx_m_nb++) {
    y->data[nx_m_nb] = 0.0;
  }

  if (x->size[0] >= 1598) {
    for (k = 0; k < 799; k++) {
      for (j = k; j + 1 <= nx; j++) {
        y->data[j] += 0.0012515644555694619 * x->data[j - k];
      }
    }
  } else {
    if (x->size[0] > 799) {
      nx_m_nb = x->size[0] - 799;
    } else {
      nx_m_nb = 0;
    }

    jp = -1;
    for (k = 1; k <= nx_m_nb; k++) {
      jp++;
      for (j = 0; j < 799; j++) {
        y->data[jp + j] += x->data[jp] * 0.0012515644555694619;
      }
    }

    naxpy = x->size[0] - nx_m_nb;
    for (k = nx_m_nb + 1; k <= nx; k++) {
      jp++;
      for (j = 0; j + 1 <= naxpy; j++) {
        y->data[jp + j] += x->data[jp] * 0.0012515644555694619;
      }

      naxpy--;
    }
  }
}

/*
 * File trailer for filter.c
 *
 * [EOF]
 */
