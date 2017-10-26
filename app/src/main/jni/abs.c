/*
 * File: abs.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "abs.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x_data[]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void b_abs(const boolean_T x_data[], double y_data[], int y_size[2])
{
  y_size[0] = 1;
  y_size[1] = 1;
  y_data[0] = x_data[0];
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
