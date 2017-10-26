/*
 * File: filterpointer2.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "filterpointer2.h"
#include "extmessage_emxutil.h"
#include "mod.h"
#include "diff.h"
#include "sort1.h"
#include "nullAssignment.h"
#include "sign.h"
#include "abs.h"
#include "mean.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *data1
 *                emxArray_char_T *indexout1
 * Return Type  : void
 */
void filterpointer2(const emxArray_real_T *data1, emxArray_char_T *indexout1)
{
  emxArray_real_T *data;
  int i4;
  int n;
  double mdata_data[1];
  int mdata_size[2];
  boolean_T data1_data[1];
  boolean_T tmp_data_idx_0;
  int i;
  emxArray_real_T *xcx;
  emxArray_boolean_T *x;
  emxArray_real_T *r2;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg1;
  emxArray_real_T *Indmax;
  emxArray_real_T *Indmin;
  double mtmp;
  int ii_size[2];
  emxArray_real_T *indexout;
  emxArray_boolean_T *b_x;
  emxArray_char_T *g;
  static const char pattern[3] = { '2', '0', '0' };

  emxArray_real_T *tempidiss;
  emxArray_int32_T *match_out;
  emxArray_int32_T *matches;
  int i5;
  int i6;
  int j;
  static const char cv0[7] = { '2', '0', '0', '1', '0', '1', '0' };

  emxArray_int32_T *Indx;
  emxArray_char_T *tempg;
  static const char cv1[3] = { '2', '0', '0' };

  int exitg2;
  int matches_data[20];
  static const signed char iv0[4] = { 17, 18, 19, 20 };

  static const char cv2[4] = { '1', '0', '1', '0' };

  double p2;
  static const signed char iv1[4] = { 0, 1, 2, 3 };

  emxInit_real_T1(&data, 2);
  i4 = data->size[0] * data->size[1];
  data->size[0] = data1->size[0];
  data->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)data, i4, sizeof(double));
  n = data1->size[0] * data1->size[1];
  for (i4 = 0; i4 < n; i4++) {
    data->data[i4] = data1->data[i4];
  }

  mean(data1, mdata_data, mdata_size);
  n = data1->size[0] * data1->size[1];
  for (i4 = 0; i4 < n; i4++) {
    data1_data[i4] = (data1->data[i4] < mdata_data[i4]);
  }

  b_abs(data1_data, mdata_data, mdata_size);
  tmp_data_idx_0 = (mdata_data[0] != 0.0);
  n = 0;
  for (i = 0; i < 1; i++) {
    if (tmp_data_idx_0) {
      n++;
    }
  }

  for (i4 = 0; i4 < n; i4++) {
    data->data[0] = 0.0;
  }

  emxInit_real_T1(&xcx, 2);
  emxInit_boolean_T1(&x, 2);
  emxInit_real_T1(&r2, 2);

  /*  figure; */
  /*  plot(data); */
  b_diff(data, xcx);
  b_diff(xcx, data);
  b_sign(data);
  b_diff(data, r2);
  i4 = x->size[0] * x->size[1];
  x->size[0] = r2->size[0];
  x->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)x, i4, sizeof(boolean_T));
  n = r2->size[0] * r2->size[1];
  for (i4 = 0; i4 < n; i4++) {
    x->data[i4] = (r2->data[i4] < 0.0);
  }

  emxInit_int32_T1(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i4 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  n = 1;
  exitg1 = false;
  while ((!exitg1) && (n <= nx)) {
    if (x->data[n - 1]) {
      idx++;
      ii->data[idx - 1] = n;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        n++;
      }
    } else {
      n++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i4 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
    }
  } else {
    i4 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  }

  emxInit_real_T(&Indmax, 1);
  i4 = Indmax->size[0];
  Indmax->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)Indmax, i4, sizeof(double));
  n = ii->size[0];
  for (i4 = 0; i4 < n; i4++) {
    Indmax->data[i4] = (double)ii->data[i4] + 1.0;
  }

  b_diff(xcx, data);
  b_sign(data);
  b_diff(data, r2);
  i4 = x->size[0] * x->size[1];
  x->size[0] = r2->size[0];
  x->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)x, i4, sizeof(boolean_T));
  n = r2->size[0] * r2->size[1];
  emxFree_real_T(&data);
  for (i4 = 0; i4 < n; i4++) {
    x->data[i4] = (r2->data[i4] > 0.0);
  }

  emxFree_real_T(&r2);
  nx = x->size[0];
  idx = 0;
  i4 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  n = 1;
  exitg1 = false;
  while ((!exitg1) && (n <= nx)) {
    if (x->data[n - 1]) {
      idx++;
      ii->data[idx - 1] = n;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        n++;
      }
    } else {
      n++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i4 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
    }
  } else {
    i4 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_real_T(&Indmin, 1);
  i4 = Indmin->size[0];
  Indmin->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)Indmin, i4, sizeof(double));
  n = ii->size[0];
  for (i4 = 0; i4 < n; i4++) {
    Indmin->data[i4] = (double)ii->data[i4] + 1.0;
  }

  n = xcx->size[0];
  nx = 1;
  mtmp = xcx->data[0];
  if (n > 1) {
    if (rtIsNaN(xcx->data[0])) {
      idx = 2;
      exitg1 = false;
      while ((!exitg1) && (idx <= n)) {
        nx = idx;
        if (!rtIsNaN(xcx->data[idx - 1])) {
          mtmp = xcx->data[idx - 1];
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }

    if (nx < n) {
      while (nx + 1 <= n) {
        if (xcx->data[nx] > mtmp) {
          mtmp = xcx->data[nx];
        }

        nx++;
      }
    }
  }

  if (xcx->data[(int)Indmax->data[0] - 1] < mtmp / 2.0) {
    ii_size[0] = 1;
    ii_size[1] = 1;
  } else {
    ii_size[0] = 0;
    ii_size[1] = 0;
  }

  nullAssignment(Indmax, ii_size);
  if (xcx->data[(int)Indmin->data[0] - 1] > -mtmp / 2.0) {
    ii_size[0] = 1;
    ii_size[1] = 1;
  } else {
    ii_size[0] = 0;
    ii_size[1] = 0;
  }

  emxFree_real_T(&xcx);
  emxInit_real_T(&indexout, 1);
  nullAssignment(Indmin, ii_size);

  /*   figure; hold on; */
  /*   plot(Indmax,xcx(Indmax),'k*'); */
  /*  plot(Indmin,xcx(Indmin),'r^'); */
  /*   plot(xcx); */
  i4 = indexout->size[0];
  indexout->size[0] = Indmax->size[0] + Indmin->size[0];
  emxEnsureCapacity((emxArray__common *)indexout, i4, sizeof(double));
  n = Indmax->size[0];
  for (i4 = 0; i4 < n; i4++) {
    indexout->data[i4] = Indmax->data[i4];
  }

  n = Indmin->size[0];
  for (i4 = 0; i4 < n; i4++) {
    indexout->data[i4 + Indmax->size[0]] = Indmin->data[i4];
  }

  emxInit_boolean_T(&b_x, 1);
  sort(indexout);
  diff(indexout, Indmax);
  i4 = b_x->size[0];
  b_x->size[0] = Indmax->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, i4, sizeof(boolean_T));
  n = Indmax->size[0];
  for (i4 = 0; i4 < n; i4++) {
    b_x->data[i4] = (Indmax->data[i4] > 60000.0);
  }

  nx = b_x->size[0];
  idx = 0;
  i4 = ii->size[0];
  ii->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  n = 1;
  exitg1 = false;
  while ((!exitg1) && (n <= nx)) {
    if (b_x->data[n - 1]) {
      idx++;
      ii->data[idx - 1] = n;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        n++;
      }
    } else {
      n++;
    }
  }

  if (b_x->size[0] == 1) {
    if (idx == 0) {
      i4 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
    }
  } else {
    i4 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i4, sizeof(int));
  }

  emxFree_boolean_T(&b_x);
  i4 = Indmax->size[0];
  Indmax->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)Indmax, i4, sizeof(double));
  n = ii->size[0];
  for (i4 = 0; i4 < n; i4++) {
    Indmax->data[i4] = ii->data[i4];
  }

  emxFree_int32_T(&ii);
  emxInit_char_T(&g, 2);
  i4 = g->size[0] * g->size[1];
  g->size[0] = 1;
  g->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
  for (i4 = 0; i4 < 3; i4++) {
    g->data[i4] = pattern[i4];
  }

  if (Indmax->size[0] == 0) {
    i4 = indexout1->size[0] * indexout1->size[1];
    indexout1->size[0] = 1;
    indexout1->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)indexout1, i4, sizeof(char));
  } else {
    i = 0;
    emxInit_real_T(&tempidiss, 1);
    while (i <= Indmax->size[0]) {
      if (i == 0) {
        if (1.0 > Indmax->data[0]) {
          n = 0;
        } else {
          n = (int)Indmax->data[0];
        }

        i4 = Indmin->size[0];
        Indmin->size[0] = n;
        emxEnsureCapacity((emxArray__common *)Indmin, i4, sizeof(double));
        for (i4 = 0; i4 < n; i4++) {
          Indmin->data[i4] = indexout->data[i4];
        }
      } else if (i == Indmax->size[0]) {
        if (Indmax->data[i - 1] + 1.0 > indexout->size[0]) {
          i4 = 0;
          i5 = 0;
        } else {
          i4 = (int)(Indmax->data[i - 1] + 1.0) - 1;
          i5 = indexout->size[0];
        }

        i6 = Indmin->size[0];
        Indmin->size[0] = i5 - i4;
        emxEnsureCapacity((emxArray__common *)Indmin, i6, sizeof(double));
        n = i5 - i4;
        for (i5 = 0; i5 < n; i5++) {
          Indmin->data[i5] = indexout->data[i4 + i5];
        }
      } else {
        if (Indmax->data[i - 1] + 1.0 > Indmax->data[i]) {
          i4 = 0;
          i5 = 0;
        } else {
          i4 = (int)(Indmax->data[i - 1] + 1.0) - 1;
          i5 = (int)Indmax->data[i];
        }

        i6 = Indmin->size[0];
        Indmin->size[0] = i5 - i4;
        emxEnsureCapacity((emxArray__common *)Indmin, i6, sizeof(double));
        n = i5 - i4;
        for (i5 = 0; i5 < n; i5++) {
          Indmin->data[i5] = indexout->data[i4 + i5];
        }
      }

      if (!(Indmin->size[0] < 10)) {
        diff(Indmin, tempidiss);
        n = 0;
        for (j = 0; j < tempidiss->size[0]; j++) {
          if (b_mod(1.0 + (double)j) == 1.0) {
            if ((tempidiss->data[j] < 2200.0) && (n < 24)) {
              idx = g->size[1];
              i4 = g->size[0] * g->size[1];
              g->size[1] = idx + 1;
              emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
              g->data[idx] = '1';
              n++;
            }

            mtmp = tempidiss->data[j] / 2200.0;
            for (nx = 0; nx < (int)mtmp; nx++) {
              if (n < 24) {
                idx = g->size[1];
                i4 = g->size[0] * g->size[1];
                g->size[1] = idx + 1;
                emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
                g->data[idx] = '1';
                n++;
              }
            }
          } else {
            if ((tempidiss->data[j] < 1650.0) && (n < 24)) {
              idx = g->size[1];
              i4 = g->size[0] * g->size[1];
              g->size[1] = idx + 1;
              emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
              g->data[idx] = '0';
              n++;
            }

            mtmp = tempidiss->data[j] / 1650.0;
            for (nx = 0; nx < (int)mtmp; nx++) {
              if (n < 24) {
                idx = g->size[1];
                i4 = g->size[0] * g->size[1];
                g->size[1] = idx + 1;
                emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
                g->data[idx] = '0';
                n++;
              }
            }
          }
        }

        idx = g->size[1];
        i4 = g->size[0] * g->size[1];
        g->size[1] = idx + 3;
        emxEnsureCapacity((emxArray__common *)g, i4, sizeof(char));
        for (i4 = 0; i4 < 3; i4++) {
          g->data[idx + i4] = pattern[i4];
        }
      }

      i++;
    }

    emxFree_real_T(&tempidiss);
    emxInit_int32_T(&match_out, 2);
    emxInit_int32_T(&matches, 2);
    i4 = indexout1->size[0] * indexout1->size[1];
    indexout1->size[0] = 1;
    indexout1->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)indexout1, i4, sizeof(char));
    i4 = matches->size[0] * matches->size[1];
    matches->size[0] = 1;
    matches->size[1] = g->size[1];
    emxEnsureCapacity((emxArray__common *)matches, i4, sizeof(int));
    n = 0;
    for (i = 1; i <= g->size[1] - 6; i++) {
      j = 1;
      while ((j <= 7) && (g->data[(i + j) - 2] == cv0[j - 1])) {
        j++;
      }

      if (j > 7) {
        matches->data[n] = i;
        n++;
      }
    }

    i4 = match_out->size[0] * match_out->size[1];
    match_out->size[0] = 1;
    match_out->size[1] = n;
    emxEnsureCapacity((emxArray__common *)match_out, i4, sizeof(int));
    for (i = 0; i + 1 <= n; i++) {
      match_out->data[i] = matches->data[i];
    }

    emxFree_int32_T(&matches);
    emxInit_int32_T(&Indx, 2);
    i4 = Indx->size[0] * Indx->size[1];
    Indx->size[0] = 1;
    Indx->size[1] = match_out->size[1];
    emxEnsureCapacity((emxArray__common *)Indx, i4, sizeof(int));
    n = match_out->size[0] * match_out->size[1];
    for (i4 = 0; i4 < n; i4++) {
      Indx->data[i4] = match_out->data[i4];
    }

    i = 0;
    emxInit_char_T(&tempg, 2);
    while (i <= Indx->size[1] - 2) {
      if (Indx->data[1 + i] - Indx->data[i] >= 27) {
        if (Indx->data[i] + 7U > (unsigned int)(Indx->data[i + 1] - 1)) {
          i4 = 0;
          i5 = 0;
        } else {
          i4 = Indx->data[i] + 6;
          i5 = Indx->data[i + 1] - 1;
        }

        i6 = tempg->size[0] * tempg->size[1];
        tempg->size[0] = 1;
        tempg->size[1] = i5 - i4;
        emxEnsureCapacity((emxArray__common *)tempg, i6, sizeof(char));
        n = i5 - i4;
        for (i6 = 0; i6 < n; i6++) {
          tempg->data[tempg->size[0] * i6] = g->data[i4 + i6];
        }

        n = i5 - i4;
        if (20 < n) {
          n = 20;
        }

        if (1 > n) {
          i6 = 0;
        } else {
          i6 = n;
        }

        if (i6 == 0) {
          n = 0;
        } else {
          n = 0;
          for (nx = 1; nx <= i6 - 2; nx++) {
            j = 1;
            while ((j <= 3) && (tempg->data[(nx + j) - 2] == cv1[j - 1])) {
              j++;
            }

            if (j > 3) {
              matches_data[n] = nx;
              n++;
            }
          }

          i6 = match_out->size[0] * match_out->size[1];
          match_out->size[0] = 1;
          match_out->size[1] = (signed char)n;
          emxEnsureCapacity((emxArray__common *)match_out, i6, sizeof(int));
          for (nx = 0; nx + 1 <= n; nx++) {
            match_out->data[nx] = (signed char)matches_data[nx];
          }

          n = match_out->size[1];
        }

        if (n > 0) {
        } else {
          tmp_data_idx_0 = false;
          n = 0;
          do {
            exitg2 = 0;
            if (n + 1 < 5) {
              if (tempg->data[iv0[n] - 1] != cv2[n]) {
                exitg2 = 1;
              } else {
                n++;
              }
            } else {
              tmp_data_idx_0 = true;
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if (tmp_data_idx_0) {
            for (nx = 0; nx < 4; nx++) {
              n = (nx << 2) + 1;
              if (n + 3 <= i5 - i4) {
                /*          msgx = [msgx, char('a'+bin2dec(tempg(ic:ic+3))-1)] */
                mtmp = 0.0;
                p2 = 1.0;
                for (j = 0; j < 4; j++) {
                  if (tempg->data[(iv1[3 - j] + n) - 1] == '1') {
                    mtmp += p2;
                  }

                  p2 += p2;
                }

                idx = indexout1->size[1];
                i6 = indexout1->size[0] * indexout1->size[1];
                indexout1->size[1] = idx + 1;
                emxEnsureCapacity((emxArray__common *)indexout1, i6, sizeof(char));
                mtmp = (97.0 + mtmp) - 1.0;
                if (rtIsInf(mtmp)) {
                  mtmp = 0.0;
                } else {
                  mtmp = fmod(mtmp, 256.0);
                }

                indexout1->data[idx] = (signed char)(unsigned char)mtmp;
              }
            }
          }
        }
      }

      i++;
    }

    emxFree_int32_T(&match_out);
    emxFree_char_T(&tempg);
    emxFree_int32_T(&Indx);
  }

  emxFree_char_T(&g);
  emxFree_real_T(&indexout);
  emxFree_real_T(&Indmin);
  emxFree_real_T(&Indmax);

  /*  %FILTERPOINTER Summary of this function goes here */
  /*  %   Detailed explanation goes here */
  /*  % figure; */
  /*  % plot(IndMax); */
  /*  figure; */
  /*  plot(diff(IndMax)); */
  /*  figure;   */
  /*  IndMax = IndMax(find(diff(IndMax)>100)); */
  /*  testshow(IndMax,data); */
  /*    */
  /*  % plot(IndMax); */
  /*  % tempdata = data(IndMax); */
  /*  [datamax,indmax] = max(data(IndMax)); */
  /*   */
  /*  for i = 1:length(IndMax) */
  /*  if(data(IndMax(i))<mean(data(IndMax(i)-500:IndMax(i)+500))) || data(IndMax(i))<0.001 */
  /*  IndMax(i) =0; */
  /*  end */
  /*  end */
  /*  IndMax(find(IndMax==0)) =[]; */
  /*  end */
}

/*
 * File trailer for filterpointer2.c
 *
 * [EOF]
 */
