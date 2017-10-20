/*
 * File: log10.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "log10.h"

/* Function Declarations */
static void c_log10(double x[256]);

/* Function Definitions */

/*
 * Arguments    : double x[256]
 * Return Type  : void
 */
static void c_log10(double x[256])
{
  int k;
  for (k = 0; k < 256; k++) {
    x[k] = log10(x[k]);
  }
}

/*
 * Arguments    : const double x[256]
 *                double b_x[256]
 * Return Type  : void
 */
void b_log10(const double x[256], double b_x[256])
{
  memcpy(&b_x[0], &x[0], sizeof(double) << 8);
  c_log10(b_x);
}

/*
 * File trailer for log10.c
 *
 * [EOF]
 */
