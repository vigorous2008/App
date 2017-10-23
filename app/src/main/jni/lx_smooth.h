/*
 * File: lx_smooth.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 23-Oct-2017 13:29:03
 */

#ifndef LX_SMOOTH_H
#define LX_SMOOTH_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "extmessage_types.h"

/* Function Declarations */
extern void moving(const emxArray_real_T *x, const emxArray_real_T *y, double
                   span_data[], emxArray_real_T *c);

#endif

/*
 * File trailer for lx_smooth.h
 *
 * [EOF]
 */
