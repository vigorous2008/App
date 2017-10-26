/*
 * File: mod.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "mod.h"

/* Function Definitions */

/*
 * Arguments    : double x
 * Return Type  : double
 */
double b_mod(double x)
{
  double r;
  if (!rtIsNaN(x)) {
    r = fmod(x, 2.0);
    if (r == 0.0) {
      r = 0.0;
    }
  } else {
    r = rtNaN;
  }

  return r;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
