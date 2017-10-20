/*
 * File: fft.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

#ifndef FFT_H
#define FFT_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "extmessage_types.h"

/* Function Declarations */
extern void b_fft(const emxArray_real_T *x, emxArray_creal_T *y);
extern void fft(const double x[11], creal_T y[512]);

#endif

/*
 * File trailer for fft.h
 *
 * [EOF]
 */
