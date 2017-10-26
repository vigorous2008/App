/*
 * File: sign.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "sign.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_sign(emxArray_real_T *x)
{
  int nx;
  int k;
  double b_x;
  nx = x->size[0];
  for (k = 0; k + 1 <= nx; k++) {
    b_x = x->data[k];
    if (x->data[k] < 0.0) {
      b_x = -1.0;
    } else if (x->data[k] > 0.0) {
      b_x = 1.0;
    } else {
      if (x->data[k] == 0.0) {
        b_x = 0.0;
      }
    }

    x->data[k] = b_x;
  }
}

/*
 * File trailer for sign.c
 *
 * [EOF]
 */
