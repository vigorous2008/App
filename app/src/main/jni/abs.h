/*
 * File: abs.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

#ifndef ABS_H
#define ABS_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "extmessage_types.h"

/* Function Declarations */
extern void b_abs(const creal_T x[256], double y[256]);
extern void c_abs(const emxArray_creal_T *x, emxArray_real_T *y);

#endif

/*
 * File trailer for abs.h
 *
 * [EOF]
 */
