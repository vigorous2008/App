/*
 * File: extmessage.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "extmessage_emxutil.h"
#include "nullAssignment.h"
#include "diff.h"
#include "sign.h"
#include "lx_smooth.h"
#include "abs.h"
#include "hilbert.h"
#include "highp.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *data
 *                double fs
 *                double channel
 *                emxArray_real_T *msg
 * Return Type  : void
 */
void extmessage(const emxArray_real_T *data, double fs, double channel,
                emxArray_real_T *msg)
{
  emxArray_real_T *x;
  emxArray_creal_T *bl;
  emxArray_real_T *IndMax;
  emxArray_real_T *sm;
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  emxArray_real_T *r0;
  int b_sm[2];
  emxArray_real_T c_sm;
  int d_sm[2];
  int i0;
  int nx;
  int idx;
  int b_ii;
  boolean_T exitg1;
  int i;
  int u1;
  emxArray_boolean_T *c_x;
  emxArray_int32_T *c_ii;
  emxArray_int32_T *d_ii;
  emxArray_uint32_T *e_ii;
  emxArray_int8_T *f_ii;
  emxArray_int8_T *g_ii;
  emxArray_uint32_T *h_ii;
  emxArray_int8_T *i_ii;
  emxArray_int8_T *j_ii;
  boolean_T guard1 = false;
  double b_IndMax;
  boolean_T d_x[11];
  (void)fs;
  (void)channel;
  emxInit_real_T(&x, 1);
  emxInit_creal_T(&bl, 1);
  emxInit_real_T1(&IndMax, 2);
  emxInit_real_T(&sm, 1);
  emxInit_boolean_T(&b_x, 2);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T1(&r0, 2);
  highp(data, x);
  hilbert(x, bl);
  c_abs(bl, x);

  /* plot(1:length(x),am); */
  lx_smooth(x, sm);
  b_sm[0] = sm->size[0];
  b_sm[1] = 1;
  c_sm = *sm;
  c_sm.size = (int *)&b_sm;
  c_sm.numDimensions = 1;
  diff(&c_sm, IndMax);
  b_sign(IndMax);
  d_sm[0] = sm->size[0];
  d_sm[1] = 1;
  c_sm = *sm;
  c_sm.size = (int *)&d_sm;
  c_sm.numDimensions = 1;
  diff(&c_sm, IndMax);
  b_sign(IndMax);
  diff(IndMax, r0);
  i0 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = r0->size[0];
  b_x->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
  nx = r0->size[0] * r0->size[1];
  emxFree_creal_T(&bl);
  for (i0 = 0; i0 < nx; i0++) {
    b_x->data[i0] = (r0->data[i0] < 0.0);
  }

  emxFree_real_T(&r0);
  nx = b_x->size[0] * b_x->size[1];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  b_ii = 1;
  exitg1 = false;
  while ((!exitg1) && (b_ii <= nx)) {
    if (b_x->data[b_ii - 1]) {
      idx++;
      ii->data[idx - 1] = b_ii;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        b_ii++;
      }
    } else {
      b_ii++;
    }
  }

  if (nx == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  }

  i0 = x->size[0];
  x->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  nx = ii->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    x->data[i0] = ii->data[i0];
  }

  i0 = IndMax->size[0] * IndMax->size[1];
  IndMax->size[0] = x->size[0];
  IndMax->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)IndMax, i0, sizeof(double));
  nx = x->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    IndMax->data[i0] = x->data[i0] + 1.0;
  }

  emxFree_real_T(&x);
  i0 = msg->size[0] * msg->size[1];
  msg->size[0] = 1;
  msg->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
  msg->data[0] = 1.0;

  /* testshow(IndMax,sm); */
  b_ii = IndMax->size[0];
  if (!(b_ii > 1)) {
    b_ii = 1;
  }

  if (IndMax->size[0] == 0) {
    b_ii = 0;
  }

  for (i = 0; i <= b_ii - 2; i++) {
    if ((fabs((double)(unsigned int)IndMax->data[i] - (double)(unsigned int)
              IndMax->data[i + 1]) < 20.0) || ((sm->data[(int)(unsigned int)
          IndMax->data[i] - 1] - sm->data[(int)(unsigned int)IndMax->data[i + 1]
          - 1] < 0.00015) && (sm->data[(int)(unsigned int)IndMax->data[i] - 1] <
          0.005)) || (sm->data[(int)(unsigned int)IndMax->data[i] - 1] < 0.01))
    {
      IndMax->data[i] = 0.0;
    }
  }

  emxFree_real_T(&sm);
  i0 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = IndMax->size[0];
  b_x->size[1] = IndMax->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
  nx = IndMax->size[0] * IndMax->size[1];
  for (i0 = 0; i0 < nx; i0++) {
    b_x->data[i0] = (IndMax->data[i0] == 0.0);
  }

  nx = b_x->size[0];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  b_ii = 1;
  exitg1 = false;
  while ((!exitg1) && (b_ii <= nx)) {
    if (b_x->data[b_ii - 1]) {
      idx++;
      ii->data[idx - 1] = b_ii;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        b_ii++;
      }
    } else {
      b_ii++;
    }
  }

  if (nx == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  }

  nullAssignment(IndMax, ii);

  /* testshow(IndMax,sm); */
  /*  for i = 2 :length(IndMax) */
  /*      if i<length(IndMax) - 10 */
  /*          if abs(IndMax(i-1)-IndMax(i))>9000 && abs(IndMax(i+1)-IndMax(i))<9000 && length(find(IndMax(i:i+10)-IndMax(i)<10000))<10 */
  /*              if i>10 */
  /*                  if length(find(IndMax(i-10:i)-IndMax(i)<10000))<10 */
  /*                      IndMax(i-1)=0; */
  /*                  end */
  /*              else */
  /*                  IndMax(i-1)=0; */
  /*              end */
  /*          end */
  /*      end */
  /*  end */
  if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
    u1 = 0;
  } else {
    b_ii = IndMax->size[0];
    u1 = IndMax->size[1];
    if (b_ii > u1) {
      u1 = b_ii;
    }
  }

  i = 0;
  emxInit_boolean_T(&c_x, 2);
  emxInit_int32_T1(&c_ii, 2);
  emxInit_int32_T1(&d_ii, 2);
  emxInit_uint32_T(&e_ii, 2);
  emxInit_int8_T(&f_ii, 2);
  emxInit_int8_T(&g_ii, 2);
  emxInit_uint32_T(&h_ii, 2);
  emxInit_int8_T(&i_ii, 2);
  emxInit_int8_T(&j_ii, 2);
  while (i <= u1 - 1) {
    guard1 = false;
    if (1 + i > 10) {
      if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
        nx = 0;
      } else {
        b_ii = IndMax->size[0];
        nx = IndMax->size[1];
        if (b_ii > nx) {
          nx = b_ii;
        }
      }

      if (1 + i < nx - 10) {
        b_IndMax = 50000.0 + IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          d_x[i0] = (IndMax->data[(int)((unsigned int)i0 + i)] < b_IndMax);
        }

        idx = 0;
        i0 = c_ii->size[0] * c_ii->size[1];
        c_ii->size[0] = 1;
        c_ii->size[1] = 11;
        emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii < 12)) {
          if (d_x[b_ii - 1]) {
            idx++;
            c_ii->data[idx - 1] = b_ii;
            if (idx >= 11) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (1 > idx) {
          nx = 0;
        } else {
          nx = idx;
        }

        i0 = i_ii->size[0] * i_ii->size[1];
        i_ii->size[0] = 1;
        i_ii->size[1] = c_ii->size[1];
        emxEnsureCapacity((emxArray__common *)i_ii, i0, sizeof(signed char));
        b_ii = c_ii->size[1];
        for (i0 = 0; i0 < b_ii; i0++) {
          i_ii->data[i_ii->size[0] * i0] = (signed char)c_ii->data[c_ii->size[0]
            * i0];
        }

        i0 = c_ii->size[0] * c_ii->size[1];
        c_ii->size[0] = 1;
        c_ii->size[1] = nx;
        emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
        for (i0 = 0; i0 < nx; i0++) {
          c_ii->data[c_ii->size[0] * i0] = i_ii->data[i0];
        }

        b_IndMax = IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          d_x[i0] = (b_IndMax < 50000.0 + IndMax->data[(i0 + i) - 10]);
        }

        idx = 0;
        i0 = d_ii->size[0] * d_ii->size[1];
        d_ii->size[0] = 1;
        d_ii->size[1] = 11;
        emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii < 12)) {
          if (d_x[b_ii - 1]) {
            idx++;
            d_ii->data[idx - 1] = b_ii;
            if (idx >= 11) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (1 > idx) {
          nx = 0;
        } else {
          nx = idx;
        }

        i0 = j_ii->size[0] * j_ii->size[1];
        j_ii->size[0] = 1;
        j_ii->size[1] = d_ii->size[1];
        emxEnsureCapacity((emxArray__common *)j_ii, i0, sizeof(signed char));
        b_ii = d_ii->size[1];
        for (i0 = 0; i0 < b_ii; i0++) {
          j_ii->data[j_ii->size[0] * i0] = (signed char)d_ii->data[d_ii->size[0]
            * i0];
        }

        i0 = d_ii->size[0] * d_ii->size[1];
        d_ii->size[0] = 1;
        d_ii->size[1] = nx;
        emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
        for (i0 = 0; i0 < nx; i0++) {
          d_ii->data[d_ii->size[0] * i0] = j_ii->data[i0];
        }

        if (c_ii->size[1] + d_ii->size[1] < 10) {
          IndMax->data[i] = 0.0;
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      if (1 + i < 11) {
        b_IndMax = 50000.0 + IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          d_x[i0] = (IndMax->data[(int)((unsigned int)i0 + i)] < b_IndMax);
        }

        idx = 0;
        i0 = c_ii->size[0] * c_ii->size[1];
        c_ii->size[0] = 1;
        c_ii->size[1] = 11;
        emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii < 12)) {
          if (d_x[b_ii - 1]) {
            idx++;
            c_ii->data[idx - 1] = b_ii;
            if (idx >= 11) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (1 > idx) {
          nx = 0;
        } else {
          nx = idx;
        }

        i0 = g_ii->size[0] * g_ii->size[1];
        g_ii->size[0] = 1;
        g_ii->size[1] = c_ii->size[1];
        emxEnsureCapacity((emxArray__common *)g_ii, i0, sizeof(signed char));
        b_ii = c_ii->size[1];
        for (i0 = 0; i0 < b_ii; i0++) {
          g_ii->data[g_ii->size[0] * i0] = (signed char)c_ii->data[c_ii->size[0]
            * i0];
        }

        i0 = c_ii->size[0] * c_ii->size[1];
        c_ii->size[0] = 1;
        c_ii->size[1] = nx;
        emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
        for (i0 = 0; i0 < nx; i0++) {
          c_ii->data[c_ii->size[0] * i0] = g_ii->data[i0];
        }

        nx = i + 1;
        b_IndMax = IndMax->data[i];
        i0 = c_x->size[0] * c_x->size[1];
        c_x->size[0] = 1;
        c_x->size[1] = i + 1;
        emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(boolean_T));
        for (i0 = 0; i0 < nx; i0++) {
          c_x->data[c_x->size[0] * i0] = (b_IndMax < 50000.0 + IndMax->data[i0]);
        }

        nx = c_x->size[1];
        idx = 0;
        i0 = d_ii->size[0] * d_ii->size[1];
        d_ii->size[0] = 1;
        d_ii->size[1] = c_x->size[1];
        emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii <= nx)) {
          if (c_x->data[b_ii - 1]) {
            idx++;
            d_ii->data[idx - 1] = b_ii;
            if (idx >= nx) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (c_x->size[1] == 1) {
          if (idx == 0) {
            i0 = d_ii->size[0] * d_ii->size[1];
            d_ii->size[0] = 1;
            d_ii->size[1] = 0;
            emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
          }
        } else {
          if (1 > idx) {
            nx = 0;
          } else {
            nx = idx;
          }

          i0 = h_ii->size[0] * h_ii->size[1];
          h_ii->size[0] = 1;
          h_ii->size[1] = d_ii->size[1];
          emxEnsureCapacity((emxArray__common *)h_ii, i0, sizeof(unsigned int));
          b_ii = d_ii->size[1];
          for (i0 = 0; i0 < b_ii; i0++) {
            h_ii->data[h_ii->size[0] * i0] = (unsigned int)d_ii->data[d_ii->
              size[0] * i0];
          }

          i0 = d_ii->size[0] * d_ii->size[1];
          d_ii->size[0] = 1;
          d_ii->size[1] = nx;
          emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
          for (i0 = 0; i0 < nx; i0++) {
            d_ii->data[d_ii->size[0] * i0] = (int)h_ii->data[i0];
          }
        }

        if ((unsigned int)c_ii->size[1] + d_ii->size[1] < 10U) {
          IndMax->data[i] = 0.0;
        }
      } else {
        if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
          nx = 0;
        } else {
          b_ii = IndMax->size[0];
          nx = IndMax->size[1];
          if (b_ii > nx) {
            nx = b_ii;
          }
        }

        if (1 + i > nx) {
          i0 = 1;
          nx = 0;
        } else {
          i0 = i + 1;
        }

        b_IndMax = 50000.0 + IndMax->data[i];
        b_ii = c_x->size[0] * c_x->size[1];
        c_x->size[0] = 1;
        c_x->size[1] = (nx - i0) + 1;
        emxEnsureCapacity((emxArray__common *)c_x, b_ii, sizeof(boolean_T));
        nx = (nx - i0) + 1;
        for (b_ii = 0; b_ii < nx; b_ii++) {
          c_x->data[c_x->size[0] * b_ii] = (IndMax->data[(i0 + b_ii) - 1] <
            b_IndMax);
        }

        nx = c_x->size[1];
        idx = 0;
        i0 = c_ii->size[0] * c_ii->size[1];
        c_ii->size[0] = 1;
        c_ii->size[1] = c_x->size[1];
        emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii <= nx)) {
          if (c_x->data[b_ii - 1]) {
            idx++;
            c_ii->data[idx - 1] = b_ii;
            if (idx >= nx) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (c_x->size[1] == 1) {
          if (idx == 0) {
            i0 = c_ii->size[0] * c_ii->size[1];
            c_ii->size[0] = 1;
            c_ii->size[1] = 0;
            emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
          }
        } else {
          if (1 > idx) {
            nx = 0;
          } else {
            nx = idx;
          }

          i0 = e_ii->size[0] * e_ii->size[1];
          e_ii->size[0] = 1;
          e_ii->size[1] = c_ii->size[1];
          emxEnsureCapacity((emxArray__common *)e_ii, i0, sizeof(unsigned int));
          b_ii = c_ii->size[1];
          for (i0 = 0; i0 < b_ii; i0++) {
            e_ii->data[e_ii->size[0] * i0] = (unsigned int)c_ii->data[c_ii->
              size[0] * i0];
          }

          i0 = c_ii->size[0] * c_ii->size[1];
          c_ii->size[0] = 1;
          c_ii->size[1] = nx;
          emxEnsureCapacity((emxArray__common *)c_ii, i0, sizeof(int));
          for (i0 = 0; i0 < nx; i0++) {
            c_ii->data[c_ii->size[0] * i0] = (int)e_ii->data[i0];
          }
        }

        b_IndMax = IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          d_x[i0] = (b_IndMax < 50000.0 + IndMax->data[(i0 + i) - 10]);
        }

        idx = 0;
        i0 = d_ii->size[0] * d_ii->size[1];
        d_ii->size[0] = 1;
        d_ii->size[1] = 11;
        emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii < 12)) {
          if (d_x[b_ii - 1]) {
            idx++;
            d_ii->data[idx - 1] = b_ii;
            if (idx >= 11) {
              exitg1 = true;
            } else {
              b_ii++;
            }
          } else {
            b_ii++;
          }
        }

        if (1 > idx) {
          nx = 0;
        } else {
          nx = idx;
        }

        i0 = f_ii->size[0] * f_ii->size[1];
        f_ii->size[0] = 1;
        f_ii->size[1] = d_ii->size[1];
        emxEnsureCapacity((emxArray__common *)f_ii, i0, sizeof(signed char));
        b_ii = d_ii->size[1];
        for (i0 = 0; i0 < b_ii; i0++) {
          f_ii->data[f_ii->size[0] * i0] = (signed char)d_ii->data[d_ii->size[0]
            * i0];
        }

        i0 = d_ii->size[0] * d_ii->size[1];
        d_ii->size[0] = 1;
        d_ii->size[1] = nx;
        emxEnsureCapacity((emxArray__common *)d_ii, i0, sizeof(int));
        for (i0 = 0; i0 < nx; i0++) {
          d_ii->data[d_ii->size[0] * i0] = f_ii->data[i0];
        }

        if ((unsigned int)c_ii->size[1] + d_ii->size[1] < 10U) {
          IndMax->data[i] = 0.0;
        }
      }
    }

    i++;
  }

  emxFree_int8_T(&j_ii);
  emxFree_int8_T(&i_ii);
  emxFree_uint32_T(&h_ii);
  emxFree_int8_T(&g_ii);
  emxFree_int8_T(&f_ii);
  emxFree_uint32_T(&e_ii);
  emxFree_int32_T(&d_ii);
  emxFree_int32_T(&c_ii);
  emxFree_boolean_T(&c_x);
  i0 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = IndMax->size[0];
  b_x->size[1] = IndMax->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
  nx = IndMax->size[0] * IndMax->size[1];
  for (i0 = 0; i0 < nx; i0++) {
    b_x->data[i0] = (IndMax->data[i0] == 0.0);
  }

  nx = b_x->size[0] * b_x->size[1];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  b_ii = 1;
  exitg1 = false;
  while ((!exitg1) && (b_ii <= nx)) {
    if (b_x->data[b_ii - 1]) {
      idx++;
      ii->data[idx - 1] = b_ii;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        b_ii++;
      }
    } else {
      b_ii++;
    }
  }

  emxFree_boolean_T(&b_x);
  if (nx == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  }

  nullAssignment(IndMax, ii);

  /* plot(IndMin,sm(IndMin),'r^') */
  /*  figure; hold on; */
  /*  tempS = sm(210000:270000); */
  /*  tempI = IndMax(find(IndMax<270000)); */
  /*  plot(tempI-210000,sm(tempI),'k*'); */
  /*  plot(tempS); */
  /* testshow(IndMax,sm); */
  emxFree_int32_T(&ii);
  if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
    u1 = 0;
  } else {
    b_ii = IndMax->size[0];
    u1 = IndMax->size[1];
    if (b_ii > u1) {
      u1 = b_ii;
    }
  }

  for (i = 0; i <= u1 - 2; i++) {
    if (((int)(unsigned int)IndMax->data[i + 1] - (int)(unsigned int)
         IndMax->data[i] < 2000) && ((int)(unsigned int)IndMax->data[i + 1] -
         (int)(unsigned int)IndMax->data[i] > 1000)) {
      b_ii = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = b_ii + 1;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[b_ii] = 1.0;
    } else if ((int)(unsigned int)IndMax->data[i + 1] - (int)(unsigned int)
               IndMax->data[i] >= 2000) {
      b_ii = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = b_ii + 2;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[b_ii] = 0.0;
      msg->data[b_ii + 1] = 1.0;
    } else {
      if ((int)(unsigned int)IndMax->data[i + 1] - (int)(unsigned int)
          IndMax->data[i] >= 4000) {
        b_ii = msg->size[1];
        i0 = msg->size[0] * msg->size[1];
        msg->size[1] = b_ii + 2;
        emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
        msg->data[b_ii] = 0.0;
        msg->data[b_ii + 1] = 0.0;
      }
    }
  }

  emxFree_real_T(&IndMax);
}

/*
 * File trailer for extmessage.c
 *
 * [EOF]
 */
