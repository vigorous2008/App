/*
 * File: extmessage.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 20-Oct-2017 14:06:37
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "extmessage_emxutil.h"
#include "nullAssignment.h"
#include "diff.h"
#include "lx_smooth.h"
#include "ifft.h"
#include "fft.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : const emxArray_real_T *data
 *                int fs
 *                int channel
 *                emxArray_real_T *msg
 * Return Type  : void
 */
void extmessage(const emxArray_real_T *data, int fs, int channel,
                emxArray_real_T *msg)
{
  emxArray_real_T *x;
  unsigned int data_idx_0;
  int i0;
  int nx;
  int halfn;
  emxArray_creal_T *b_x;
  int lastIndexToDouble;
  int c_x[1];
  emxArray_real_T d_x;
  int idx;
  static const double dv0[10] = { 2.7286178710984876E-5, -0.00024557560839886389,
    0.00098230243359545555, -0.0022920390117227296, 0.0034380585175840944,
    -0.0034380585175840944, 0.0022920390117227296, -0.00098230243359545555,
    0.00024557560839886389, -2.7286178710984876E-5 };

  double as;
  int i;
  static const double dv1[10] = { 1.0, 5.3784007355745374, 14.351021573292872,
    24.359475433583761, 28.681925047537014, 24.146178660964374,
    14.48696021351463, 5.96617110974047, 1.5316196564413922, 0.18733002742274185
  };

  emxArray_creal_T *e_x;
  emxArray_real_T *f_x;
  emxArray_real_T *sm;
  emxArray_real_T *g_x;
  int b_sm[2];
  emxArray_boolean_T *h_x;
  emxArray_real_T *r0;
  emxArray_int32_T *ii;
  boolean_T exitg1;
  emxArray_real_T *IndMax;
  int u1;
  emxArray_boolean_T *i_x;
  emxArray_int32_T *b_ii;
  boolean_T guard1 = false;
  boolean_T j_x[11];
  int i1;
  int i2;
  int i3;
  int i4;
  (void)fs;
  (void)channel;
  emxInit_real_T(&x, 1);

  /* 高通滤波 */
  /* 使用注意事项：通带或阻带的截止频率的选取范围是不能超过采样率的一半 */
  /* 即，f1,f3的值都要小于 Fs/2 */
  /* x:需要带通滤波的序列 */
  /*  f 1：通带截止频率 */
  /*  f 2：阻带截止频率 */
  /* rp：边带区衰减DB数设置 */
  /* rs：截止区衰减DB数设置 */
  /* FS：序列x的采样频率 */
  /*  rp=0.1;rs=30;%通带边衰减DB值和阻带边衰减DB值 */
  /*  Fs=2000;%采样率 */
  /*  */
  /*  设计切比雪夫滤波器； */
  /* 查看设计滤波器的曲线 */
  /* figure;plot(w,h);title('所设计滤波器的通带曲线');grid on; */
  data_idx_0 = (unsigned int)data->size[0];
  i0 = x->size[0];
  x->size[0] = (int)data_idx_0;
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  nx = data->size[0];
  halfn = x->size[0];
  i0 = x->size[0];
  x->size[0] = halfn;
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  for (i0 = 0; i0 < halfn; i0++) {
    x->data[i0] = 0.0;
  }

  for (halfn = 1; halfn <= nx; halfn++) {
    lastIndexToDouble = (nx - halfn) + 1;
    if (!(lastIndexToDouble < 10)) {
      lastIndexToDouble = 10;
    }

    for (idx = -1; idx + 2 <= lastIndexToDouble; idx++) {
      x->data[halfn + idx] += data->data[halfn - 1] * dv0[idx + 1];
    }

    lastIndexToDouble = nx - halfn;
    if (!(lastIndexToDouble < 9)) {
      lastIndexToDouble = 9;
    }

    as = -x->data[halfn - 1];
    for (idx = 1; idx <= lastIndexToDouble; idx++) {
      x->data[(halfn + idx) - 1] += as * dv1[idx];
    }
  }

  emxInit_creal_T(&b_x, 1);
  c_x[0] = x->size[0];
  d_x = *x;
  d_x.size = (int *)&c_x;
  d_x.numDimensions = 1;
  fft(&d_x, b_x);
  halfn = x->size[0] >> 1;
  if ((x->size[0] & 1) == 0) {
    lastIndexToDouble = halfn;
  } else {
    lastIndexToDouble = halfn + 1;
  }

  for (i = 1; i + 1 <= lastIndexToDouble; i++) {
    b_x->data[i].re *= 2.0;
    b_x->data[i].im *= 2.0;
  }

  for (i = halfn + 1; i + 1 <= x->size[0]; i++) {
    b_x->data[i].re = 0.0;
    b_x->data[i].im = 0.0;
  }

  emxInit_creal_T(&e_x, 1);
  i0 = e_x->size[0];
  e_x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)e_x, i0, sizeof(creal_T));
  halfn = b_x->size[0];
  for (i0 = 0; i0 < halfn; i0++) {
    e_x->data[i0] = b_x->data[i0];
  }

  ifft(e_x, b_x);
  data_idx_0 = (unsigned int)b_x->size[0];
  i0 = x->size[0];
  x->size[0] = (int)data_idx_0;
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  halfn = 0;
  emxFree_creal_T(&e_x);
  while (halfn + 1 <= b_x->size[0]) {
    x->data[halfn] = rt_hypotd_snf(b_x->data[halfn].re, b_x->data[halfn].im);
    halfn++;
  }

  emxFree_creal_T(&b_x);
  emxInit_real_T(&f_x, 1);

  /*  figure;grid; */
  /*  title('hilbert'); */
  /*   plot(1:length(x),am); */
  halfn = x->size[0];
  i0 = f_x->size[0];
  f_x->size[0] = halfn;
  emxEnsureCapacity((emxArray__common *)f_x, i0, sizeof(double));
  for (i0 = 0; i0 < halfn; i0++) {
    f_x->data[i0] = x->data[i0];
  }

  emxInit_real_T(&sm, 1);
  emxInit_real_T1(&g_x, 2);
  lx_smooth(f_x, sm);

  /*  figure;grid; */
  /*  title('smooth'); */
  /*   plot(sm); */
  /*  %signdif  */
  /*  sdifsm = sign(diff(sm));  */
  /*  %Indmin */
  /*  IndMin=find(diff(sdifsm)>0)+1; */
  /*  %IndMax */
  /*  IndMax=find(diff(sdifsm)<0)+1; */
  /* signdif  */
  /*  sdifsm = sign(diff(sm));  */
  /* Indmin */
  /*  IndMin=find(diff(sign(diff(sm)))>0)+1; */
  /* IndMax */
  b_sm[0] = sm->size[0];
  b_sm[1] = 1;
  d_x = *sm;
  d_x.size = (int *)&b_sm;
  d_x.numDimensions = 1;
  b_diff(&d_x, g_x);
  nx = g_x->size[0];
  halfn = 0;
  emxFree_real_T(&f_x);
  while (halfn + 1 <= nx) {
    as = g_x->data[halfn];
    if (g_x->data[halfn] < 0.0) {
      as = -1.0;
    } else if (g_x->data[halfn] > 0.0) {
      as = 1.0;
    } else {
      if (g_x->data[halfn] == 0.0) {
        as = 0.0;
      }
    }

    g_x->data[halfn] = as;
    halfn++;
  }

  emxInit_boolean_T(&h_x, 2);
  emxInit_real_T1(&r0, 2);
  b_diff(g_x, r0);
  i0 = h_x->size[0] * h_x->size[1];
  h_x->size[0] = r0->size[0];
  h_x->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)h_x, i0, sizeof(boolean_T));
  halfn = r0->size[0] * r0->size[1];
  emxFree_real_T(&g_x);
  for (i0 = 0; i0 < halfn; i0++) {
    h_x->data[i0] = (r0->data[i0] < 0.0);
  }

  emxFree_real_T(&r0);
  emxInit_int32_T(&ii, 1);
  nx = h_x->size[0];
  lastIndexToDouble = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  halfn = 1;
  exitg1 = false;
  while ((!exitg1) && (halfn <= nx)) {
    if (h_x->data[halfn - 1]) {
      lastIndexToDouble++;
      ii->data[lastIndexToDouble - 1] = halfn;
      if (lastIndexToDouble >= nx) {
        exitg1 = true;
      } else {
        halfn++;
      }
    } else {
      halfn++;
    }
  }

  if (nx == 1) {
    if (lastIndexToDouble == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > lastIndexToDouble) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = lastIndexToDouble;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  }

  i0 = x->size[0];
  x->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  halfn = ii->size[0];
  for (i0 = 0; i0 < halfn; i0++) {
    x->data[i0] = ii->data[i0];
  }

  emxInit_real_T1(&IndMax, 2);
  i0 = IndMax->size[0] * IndMax->size[1];
  IndMax->size[0] = x->size[0];
  IndMax->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)IndMax, i0, sizeof(double));
  halfn = x->size[0];
  for (i0 = 0; i0 < halfn; i0++) {
    IndMax->data[i0] = x->data[i0] + 1.0;
  }

  emxFree_real_T(&x);
  i0 = msg->size[0] * msg->size[1];
  msg->size[0] = 1;
  msg->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
  msg->data[0] = 1.0;

  /* testshow(IndMax,sm); */
  halfn = IndMax->size[0];
  if (!(halfn > 1)) {
    halfn = 1;
  }

  if (IndMax->size[0] == 0) {
    halfn = 0;
  }

  for (i = 0; i <= halfn - 2; i++) {
    if ((fabs(IndMax->data[i] - IndMax->data[i + 1]) < 20.0) || ((sm->data[(int)
          IndMax->data[i] - 1] - sm->data[(int)IndMax->data[i + 1] - 1] <
          0.00015) && (sm->data[(int)IndMax->data[i] - 1] < 0.005)) || (sm->
         data[(int)IndMax->data[i] - 1] < 0.01)) {
      IndMax->data[i] = 0.0;
    }
  }

  emxFree_real_T(&sm);
  i0 = h_x->size[0] * h_x->size[1];
  h_x->size[0] = IndMax->size[0];
  h_x->size[1] = IndMax->size[1];
  emxEnsureCapacity((emxArray__common *)h_x, i0, sizeof(boolean_T));
  halfn = IndMax->size[0] * IndMax->size[1];
  for (i0 = 0; i0 < halfn; i0++) {
    h_x->data[i0] = (IndMax->data[i0] == 0.0);
  }

  nx = h_x->size[0];
  lastIndexToDouble = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  halfn = 1;
  exitg1 = false;
  while ((!exitg1) && (halfn <= nx)) {
    if (h_x->data[halfn - 1]) {
      lastIndexToDouble++;
      ii->data[lastIndexToDouble - 1] = halfn;
      if (lastIndexToDouble >= nx) {
        exitg1 = true;
      } else {
        halfn++;
      }
    } else {
      halfn++;
    }
  }

  if (nx == 1) {
    if (lastIndexToDouble == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > lastIndexToDouble) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = lastIndexToDouble;
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
    halfn = IndMax->size[0];
    u1 = IndMax->size[1];
    if (halfn > u1) {
      u1 = halfn;
    }
  }

  i = 0;
  emxInit_boolean_T(&i_x, 2);
  emxInit_int32_T1(&b_ii, 2);
  while (i <= u1 - 1) {
    guard1 = false;
    if (1 + i > 10) {
      if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
        lastIndexToDouble = 0;
      } else {
        halfn = IndMax->size[0];
        lastIndexToDouble = IndMax->size[1];
        if (halfn > lastIndexToDouble) {
          lastIndexToDouble = halfn;
        }
      }

      if (1 + i < lastIndexToDouble - 10) {
        as = 50000.0 + IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          j_x[i0] = (IndMax->data[(int)((unsigned int)i0 + i)] < as);
        }

        lastIndexToDouble = 0;
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn < 12)) {
          if (j_x[halfn - 1]) {
            lastIndexToDouble++;
            if (lastIndexToDouble >= 11) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        as = IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          j_x[i0] = (as < 50000.0 + IndMax->data[(i0 + i) - 10]);
        }

        idx = 0;
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn < 12)) {
          if (j_x[halfn - 1]) {
            idx++;
            if (idx >= 11) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        if (1 > lastIndexToDouble) {
          i1 = 0;
        } else {
          i1 = lastIndexToDouble;
        }

        if (1 > idx) {
          i2 = 0;
        } else {
          i2 = idx;
        }

        if (i1 + i2 < 10) {
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
        as = 50000.0 + IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          j_x[i0] = (IndMax->data[(int)((unsigned int)i0 + i)] < as);
        }

        lastIndexToDouble = 0;
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn < 12)) {
          if (j_x[halfn - 1]) {
            lastIndexToDouble++;
            if (lastIndexToDouble >= 11) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        as = IndMax->data[i];
        i0 = i_x->size[0] * i_x->size[1];
        i_x->size[0] = 1;
        i_x->size[1] = i + 1;
        emxEnsureCapacity((emxArray__common *)i_x, i0, sizeof(boolean_T));
        for (i0 = 0; i0 <= i; i0++) {
          i_x->data[i_x->size[0] * i0] = (as < 50000.0 + IndMax->data[i0]);
        }

        nx = i_x->size[1];
        idx = 0;
        i0 = b_ii->size[0] * b_ii->size[1];
        b_ii->size[0] = 1;
        b_ii->size[1] = i_x->size[1];
        emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn <= nx)) {
          if (i_x->data[halfn - 1]) {
            idx++;
            b_ii->data[idx - 1] = halfn;
            if (idx >= nx) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        if (i_x->size[1] == 1) {
          if (idx == 0) {
            i0 = b_ii->size[0] * b_ii->size[1];
            b_ii->size[0] = 1;
            b_ii->size[1] = 0;
            emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
          }
        } else {
          i0 = b_ii->size[0] * b_ii->size[1];
          if (1 > idx) {
            b_ii->size[1] = 0;
          } else {
            b_ii->size[1] = idx;
          }

          emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
        }

        if (1 > lastIndexToDouble) {
          i3 = 0;
        } else {
          i3 = lastIndexToDouble;
        }

        if ((double)i3 + (double)b_ii->size[1] < 10.0) {
          IndMax->data[i] = 0.0;
        }
      } else {
        if ((IndMax->size[0] == 0) || (IndMax->size[1] == 0)) {
          lastIndexToDouble = 0;
        } else {
          halfn = IndMax->size[0];
          lastIndexToDouble = IndMax->size[1];
          if (halfn > lastIndexToDouble) {
            lastIndexToDouble = halfn;
          }
        }

        if (1 + i > lastIndexToDouble) {
          i0 = 1;
          lastIndexToDouble = 0;
        } else {
          i0 = i + 1;
        }

        as = 50000.0 + IndMax->data[i];
        idx = i_x->size[0] * i_x->size[1];
        i_x->size[0] = 1;
        i_x->size[1] = (lastIndexToDouble - i0) + 1;
        emxEnsureCapacity((emxArray__common *)i_x, idx, sizeof(boolean_T));
        halfn = (lastIndexToDouble - i0) + 1;
        for (idx = 0; idx < halfn; idx++) {
          i_x->data[i_x->size[0] * idx] = (IndMax->data[(i0 + idx) - 1] < as);
        }

        nx = i_x->size[1];
        lastIndexToDouble = 0;
        i0 = b_ii->size[0] * b_ii->size[1];
        b_ii->size[0] = 1;
        b_ii->size[1] = i_x->size[1];
        emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn <= nx)) {
          if (i_x->data[halfn - 1]) {
            lastIndexToDouble++;
            b_ii->data[lastIndexToDouble - 1] = halfn;
            if (lastIndexToDouble >= nx) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        if (i_x->size[1] == 1) {
          if (lastIndexToDouble == 0) {
            i0 = b_ii->size[0] * b_ii->size[1];
            b_ii->size[0] = 1;
            b_ii->size[1] = 0;
            emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
          }
        } else {
          i0 = b_ii->size[0] * b_ii->size[1];
          if (1 > lastIndexToDouble) {
            b_ii->size[1] = 0;
          } else {
            b_ii->size[1] = lastIndexToDouble;
          }

          emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(int));
        }

        as = IndMax->data[i];
        for (i0 = 0; i0 < 11; i0++) {
          j_x[i0] = (as < 50000.0 + IndMax->data[(i0 + i) - 10]);
        }

        lastIndexToDouble = 0;
        halfn = 1;
        exitg1 = false;
        while ((!exitg1) && (halfn < 12)) {
          if (j_x[halfn - 1]) {
            lastIndexToDouble++;
            if (lastIndexToDouble >= 11) {
              exitg1 = true;
            } else {
              halfn++;
            }
          } else {
            halfn++;
          }
        }

        if (1 > lastIndexToDouble) {
          i4 = 0;
        } else {
          i4 = lastIndexToDouble;
        }

        if ((double)b_ii->size[1] + (double)i4 < 10.0) {
          IndMax->data[i] = 0.0;
        }
      }
    }

    i++;
  }

  emxFree_int32_T(&b_ii);
  emxFree_boolean_T(&i_x);
  i0 = h_x->size[0] * h_x->size[1];
  h_x->size[0] = IndMax->size[0];
  h_x->size[1] = IndMax->size[1];
  emxEnsureCapacity((emxArray__common *)h_x, i0, sizeof(boolean_T));
  halfn = IndMax->size[0] * IndMax->size[1];
  for (i0 = 0; i0 < halfn; i0++) {
    h_x->data[i0] = (IndMax->data[i0] == 0.0);
  }

  nx = h_x->size[0] * h_x->size[1];
  lastIndexToDouble = 0;
  i0 = ii->size[0];
  ii->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  halfn = 1;
  exitg1 = false;
  while ((!exitg1) && (halfn <= nx)) {
    if (h_x->data[halfn - 1]) {
      lastIndexToDouble++;
      ii->data[lastIndexToDouble - 1] = halfn;
      if (lastIndexToDouble >= nx) {
        exitg1 = true;
      } else {
        halfn++;
      }
    } else {
      halfn++;
    }
  }

  emxFree_boolean_T(&h_x);
  if (nx == 1) {
    if (lastIndexToDouble == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > lastIndexToDouble) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = lastIndexToDouble;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  }

  nullAssignment(IndMax, ii);

  /*  figure;hold on; */
  /*  %plot(IndMin,sm(IndMin),'r^') */
  /*  plot(IndMax,sm(IndMax),'k*') */
  /*  plot(sm); */
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
    halfn = IndMax->size[0];
    u1 = IndMax->size[1];
    if (halfn > u1) {
      u1 = halfn;
    }
  }

  for (i = 1; i - 1 <= u1 - 2; i++) {
    if ((IndMax->data[i] - IndMax->data[i - 1] < 2000.0) && (IndMax->data[i] -
         IndMax->data[i - 1] > 1000.0)) {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 1;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 1.0;
    } else if ((IndMax->data[i] - IndMax->data[i - 1] >= 2000.0) &&
               (IndMax->data[i] - IndMax->data[i] < 4000.0)) {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 2;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 0.0;
      msg->data[halfn + 1] = 1.0;
    } else {
      if ((IndMax->data[i] - IndMax->data[i - 1] >= 4000.0) && (IndMax->data[i]
           - IndMax->data[i] < 6000.0)) {
        halfn = msg->size[1];
        i0 = msg->size[0] * msg->size[1];
        msg->size[1] = halfn + 2;
        emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
        msg->data[halfn] = 0.0;
        msg->data[halfn + 1] = 0.0;
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
