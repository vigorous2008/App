/*
 * File: mean.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "mean.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void mean(const emxArray_real_T *x, double y_data[], int y_size[2])
{
  double s;
  int k;
  if (x->size[0] == 0) {
    y_data[0] = 0.0;
  } else {
    s = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      s += x->data[k - 1];
    }

    y_data[0] = s;
  }

  y_size[0] = 1;
  y_size[1] = 1;
  k = x->size[0];
  y_data[0] /= (double)k;
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
