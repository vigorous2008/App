/*
 * File: freqz.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "freqz.h"
#include "fft.h"

/* Function Declarations */
static void iirfreqz(const double b_in[11], const double a_in[11], creal_T h[512]);

/* Function Definitions */

/*
 * Arguments    : const double b_in[11]
 *                const double a_in[11]
 *                creal_T h[512]
 * Return Type  : void
 */
static void iirfreqz(const double b_in[11], const double a_in[11], creal_T h[512])
{
  creal_T x[512];
  creal_T y[512];
  int i1;
  double brm;
  double bim;
  double d;
  fft(b_in, x);
  fft(a_in, y);
  for (i1 = 0; i1 < 512; i1++) {
    if (y[i1].im == 0.0) {
      if (x[i1].im == 0.0) {
        h[i1].re = x[i1].re / y[i1].re;
        h[i1].im = 0.0;
      } else if (x[i1].re == 0.0) {
        h[i1].re = 0.0;
        h[i1].im = x[i1].im / y[i1].re;
      } else {
        h[i1].re = x[i1].re / y[i1].re;
        h[i1].im = x[i1].im / y[i1].re;
      }
    } else if (y[i1].re == 0.0) {
      if (x[i1].re == 0.0) {
        h[i1].re = x[i1].im / y[i1].im;
        h[i1].im = 0.0;
      } else if (x[i1].im == 0.0) {
        h[i1].re = 0.0;
        h[i1].im = -(x[i1].re / y[i1].im);
      } else {
        h[i1].re = x[i1].im / y[i1].im;
        h[i1].im = -(x[i1].re / y[i1].im);
      }
    } else {
      brm = fabs(y[i1].re);
      bim = fabs(y[i1].im);
      if (brm > bim) {
        bim = y[i1].im / y[i1].re;
        d = y[i1].re + bim * y[i1].im;
        h[i1].re = (x[i1].re + bim * x[i1].im) / d;
        h[i1].im = (x[i1].im - bim * x[i1].re) / d;
      } else if (bim == brm) {
        if (y[i1].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (y[i1].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        h[i1].re = (x[i1].re * bim + x[i1].im * d) / brm;
        h[i1].im = (x[i1].im * bim - x[i1].re * d) / brm;
      } else {
        bim = y[i1].re / y[i1].im;
        d = y[i1].im + bim * y[i1].re;
        h[i1].re = (bim * x[i1].re + x[i1].im) / d;
        h[i1].im = (bim * x[i1].im - x[i1].re) / d;
      }
    }
  }
}

/*
 * Arguments    : const double b[11]
 *                const double a[11]
 *                creal_T varargout_1[256]
 *                double varargout_2[256]
 * Return Type  : void
 */
void freqz(const double b[11], const double a[11], creal_T varargout_1[256],
           double varargout_2[256])
{
  creal_T hh[512];
  int i;
  iirfreqz(b, a, hh);
  for (i = 0; i < 256; i++) {
    varargout_1[i] = hh[i];
    varargout_2[i] = 93.75 * (double)i;
  }
}

/*
 * File trailer for freqz.c
 *
 * [EOF]
 */
