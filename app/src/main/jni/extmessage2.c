/*
 * File: extmessage2.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 07-Nov-2017 15:17:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage2.h"
#include "extmessage2_emxutil.h"
#include "diff.h"
#include "xcorr.h"
#include "sin.h"
#include "highp.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * highp
 * Arguments    : const emxArray_real_T *data
 *                int fs
 *                int channel
 *                emxArray_char_T *msg
 * Return Type  : void
 */
void extmessage2(const emxArray_real_T *data, int fs, int channel,
                 emxArray_char_T *msg)
{
  emxArray_real_T *x;
  int yk;
  int n;
  emxArray_int32_T *b_n;
  int i0;
  emxArray_real_T *t;
  int idx;
  int ndbl;
  emxArray_real_T *Indx;
  double mc;
  emxArray_real_T *y;
  double apnd;
  emxArray_real_T *tts;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *c;
  boolean_T exitg1;
  int i;
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  emxArray_real_T *b_ii;
  emxArray_char_T *g;
  static const char pattern[3] = { '2', '0', '0' };

  emxArray_int32_T *match_out;
  emxArray_int32_T *matches;
  static const char cv0[3] = { '2', '0', '0' };

  emxArray_char_T *tempg;
  emxArray_int8_T *out;
  emxArray_char_T *text;
  int i1;
  boolean_T b_bool;
  int exitg2;
  static const signed char iv0[4] = { 21, 22, 23, 24 };

  static const char cv1[4] = { '1', '0', '1', '0' };

  static const signed char iv1[4] = { 1, 2, 3, 4 };

  static const signed char iv2[4] = { 0, 1, 2, 3 };

  (void)channel;
  emxInit_real_T(&x, 1);
  highp(data, x);

  /* xo */
  /* n */
  if (fs < -2147483647) {
    yk = MIN_int32_T;
  } else {
    yk = fs - 1;
  }

  yk = (int)rt_roundd_snf((double)yk / 20.0);
  if (yk < 0) {
    n = 0;
  } else {
    n = yk + 1;
  }

  emxInit_int32_T(&b_n, 2);
  i0 = b_n->size[0] * b_n->size[1];
  b_n->size[0] = 1;
  b_n->size[1] = n;
  emxEnsureCapacity((emxArray__common *)b_n, i0, sizeof(int));
  if (n > 0) {
    b_n->data[0] = 0;
    yk = 0;
    for (idx = 2; idx <= n; idx++) {
      yk++;
      b_n->data[idx - 1] = yk;
    }
  }

  emxInit_real_T1(&t, 2);

  /* t */
  i0 = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = b_n->size[1];
  emxEnsureCapacity((emxArray__common *)t, i0, sizeof(double));
  ndbl = b_n->size[0] * b_n->size[1];
  for (i0 = 0; i0 < ndbl; i0++) {
    t->data[i0] = (double)b_n->data[i0] / (double)fs;
  }

  emxFree_int32_T(&b_n);
  emxInit_real_T1(&Indx, 2);

  /* tt */
  mc = (double)t->size[1] / 2.0;
  if (mc < 1.0) {
    i0 = Indx->size[0] * Indx->size[1];
    Indx->size[0] = 1;
    Indx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)Indx, i0, sizeof(double));
  } else {
    i0 = Indx->size[0] * Indx->size[1];
    Indx->size[0] = 1;
    Indx->size[1] = (int)floor(mc - 1.0) + 1;
    emxEnsureCapacity((emxArray__common *)Indx, i0, sizeof(double));
    ndbl = (int)floor(mc - 1.0);
    for (i0 = 0; i0 <= ndbl; i0++) {
      Indx->data[Indx->size[0] * i0] = 1.0 + (double)i0;
    }
  }

  emxInit_real_T1(&y, 2);

  /* tts */
  mc = (double)t->size[1] / 2.0;
  if (mc < 1.0) {
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
  } else if (floor(mc) == mc) {
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)floor(-(1.0 - mc)) + 1;
    emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
    ndbl = (int)floor(-(1.0 - mc));
    for (i0 = 0; i0 <= ndbl; i0++) {
      y->data[y->size[0] * i0] = mc - (double)i0;
    }
  } else {
    ndbl = (int)floor((1.0 - mc) / -1.0 + 0.5);
    apnd = mc + -(double)ndbl;
    if (fabs(1.0 - apnd) < 4.4408920985006262E-16 * mc) {
      ndbl++;
      apnd = 1.0;
    } else if (1.0 - apnd > 0.0) {
      apnd = mc + -((double)ndbl - 1.0);
    } else {
      ndbl++;
    }

    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = ndbl;
    emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
    if (ndbl > 0) {
      y->data[0] = mc;
      if (ndbl > 1) {
        y->data[ndbl - 1] = apnd;
        yk = (ndbl - 1) / 2;
        for (idx = 1; idx < yk; idx++) {
          y->data[idx] = mc + -(double)idx;
          y->data[(ndbl - idx) - 1] = apnd - (-(double)idx);
        }

        if (yk << 1 == ndbl - 1) {
          y->data[yk] = (mc + apnd) / 2.0;
        } else {
          y->data[yk] = mc + -(double)yk;
          y->data[yk + 1] = apnd - (-(double)yk);
        }
      }
    }
  }

  emxInit_real_T1(&tts, 2);
  i0 = tts->size[0] * tts->size[1];
  tts->size[0] = 1;
  tts->size[1] = Indx->size[1] + y->size[1];
  emxEnsureCapacity((emxArray__common *)tts, i0, sizeof(double));
  ndbl = Indx->size[1];
  for (i0 = 0; i0 < ndbl; i0++) {
    tts->data[tts->size[0] * i0] = Indx->data[Indx->size[0] * i0];
  }

  ndbl = y->size[1];
  for (i0 = 0; i0 < ndbl; i0++) {
    tts->data[tts->size[0] * (i0 + Indx->size[1])] = y->data[y->size[0] * i0];
  }

  emxFree_real_T(&y);
  if (1 > tts->size[1]) {
    ndbl = 0;
  } else {
    ndbl = tts->size[1];
  }

  emxInit_real_T1(&r0, 2);
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = ndbl;
  emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(double));
  for (i0 = 0; i0 < ndbl; i0++) {
    r0->data[r0->size[0] * i0] = 113097.33552923256 * t->data[i0];
  }

  emxFree_real_T(&t);
  emxInit_real_T1(&r1, 2);
  b_sin(r0);

  /* xcorr */
  i0 = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)r1, i0, sizeof(double));
  ndbl = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < ndbl; i0++) {
    r1->data[i0] = r0->data[i0] * tts->data[i0];
  }

  emxFree_real_T(&r0);
  emxFree_real_T(&tts);
  emxInit_real_T(&c, 1);
  xcorr(x, r1, c);

  /* idindex */
  yk = 1;
  n = c->size[0];
  mc = c->data[0];
  emxFree_real_T(&r1);
  if (c->size[0] > 1) {
    if (rtIsNaN(c->data[0])) {
      ndbl = 2;
      exitg1 = false;
      while ((!exitg1) && (ndbl <= n)) {
        yk = ndbl;
        if (!rtIsNaN(c->data[ndbl - 1])) {
          mc = c->data[ndbl - 1];
          exitg1 = true;
        } else {
          ndbl++;
        }
      }
    }

    if (yk < c->size[0]) {
      while (yk + 1 <= n) {
        if (c->data[yk] > mc) {
          mc = c->data[yk];
        }

        yk++;
      }
    }
  }

  mc /= 10.0;
  yk = c->size[0];
  for (i = 0; i < yk; i++) {
    if (c->data[i] < mc) {
      c->data[i] = 0.0;
    }
  }

  emxInit_boolean_T(&b_x, 1);
  i0 = b_x->size[0];
  b_x->size[0] = c->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
  ndbl = c->size[0];
  for (i0 = 0; i0 < ndbl; i0++) {
    b_x->data[i0] = (c->data[i0] != 0.0);
  }

  emxInit_int32_T1(&ii, 1);
  ndbl = b_x->size[0];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  yk = 1;
  exitg1 = false;
  while ((!exitg1) && (yk <= ndbl)) {
    if (b_x->data[yk - 1]) {
      idx++;
      ii->data[idx - 1] = yk;
      if (idx >= ndbl) {
        exitg1 = true;
      } else {
        yk++;
      }
    } else {
      yk++;
    }
  }

  if (b_x->size[0] == 1) {
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

  emxInit_real_T(&b_ii, 1);
  i0 = b_ii->size[0];
  b_ii->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)b_ii, i0, sizeof(double));
  ndbl = ii->size[0];
  for (i0 = 0; i0 < ndbl; i0++) {
    b_ii->data[i0] = ii->data[i0];
  }

  diff(b_ii, x);
  yk = x->size[0];
  emxFree_real_T(&b_ii);
  for (i = 0; i < yk; i++) {
    if (x->data[i] < 1000.0) {
      x->data[i] = 0.0;
    }
  }

  i0 = b_x->size[0];
  b_x->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)b_x, i0, sizeof(boolean_T));
  ndbl = x->size[0];
  for (i0 = 0; i0 < ndbl; i0++) {
    b_x->data[i0] = (x->data[i0] != 0.0);
  }

  ndbl = b_x->size[0];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  yk = 1;
  exitg1 = false;
  while ((!exitg1) && (yk <= ndbl)) {
    if (b_x->data[yk - 1]) {
      idx++;
      ii->data[idx - 1] = yk;
      if (idx >= ndbl) {
        exitg1 = true;
      } else {
        yk++;
      }
    } else {
      yk++;
    }
  }

  if (b_x->size[0] == 1) {
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

  emxFree_boolean_T(&b_x);
  i0 = c->size[0];
  c->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)c, i0, sizeof(double));
  ndbl = ii->size[0];
  for (i0 = 0; i0 < ndbl; i0++) {
    c->data[i0] = ii->data[i0];
  }

  emxFree_int32_T(&ii);
  emxInit_char_T(&g, 2);

  /* g */
  i0 = g->size[0] * g->size[1];
  g->size[0] = 1;
  g->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)g, i0, sizeof(char));
  for (i0 = 0; i0 < 3; i0++) {
    g->data[i0] = pattern[i0];
  }

  for (i = 0; i < c->size[0]; i++) {
    if (1.0 + (double)i == 1.0) {
      mc = c->data[0];
    } else {
      mc = c->data[i] - c->data[(int)((1.0 + (double)i) - 1.0) - 1];
    }

    mc = rt_roundd_snf(mc / 1000.0);
    for (n = 0; n < (int)mc; n++) {
      yk = g->size[1];
      i0 = g->size[0] * g->size[1];
      g->size[1] = yk + 1;
      emxEnsureCapacity((emxArray__common *)g, i0, sizeof(char));
      g->data[yk] = '1';
    }

    if (x->data[(int)c->data[i] - 1] > 60000.0) {
      yk = g->size[1];
      i0 = g->size[0] * g->size[1];
      g->size[1] = yk + 3;
      emxEnsureCapacity((emxArray__common *)g, i0, sizeof(char));
      for (i0 = 0; i0 < 3; i0++) {
        g->data[yk + i0] = pattern[i0];
      }
    } else {
      mc = rt_roundd_snf(x->data[(int)c->data[i] - 1] / 1800.0);
      for (n = 0; n < (int)mc; n++) {
        yk = g->size[1];
        i0 = g->size[0] * g->size[1];
        g->size[1] = yk + 1;
        emxEnsureCapacity((emxArray__common *)g, i0, sizeof(char));
        g->data[yk] = '0';
      }
    }
  }

  emxFree_real_T(&c);
  emxFree_real_T(&x);

  /* msg */
  yk = g->size[1];
  i0 = g->size[0] * g->size[1];
  g->size[1] = yk + 3;
  emxEnsureCapacity((emxArray__common *)g, i0, sizeof(char));
  for (i0 = 0; i0 < 3; i0++) {
    g->data[yk + i0] = pattern[i0];
  }

  emxInit_int32_T(&match_out, 2);
  emxInit_int32_T(&matches, 2);
  i0 = msg->size[0] * msg->size[1];
  msg->size[0] = 1;
  msg->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(char));
  i0 = matches->size[0] * matches->size[1];
  matches->size[0] = 1;
  matches->size[1] = g->size[1];
  emxEnsureCapacity((emxArray__common *)matches, i0, sizeof(int));
  idx = 0;
  for (i = 1; i <= g->size[1] - 2; i++) {
    n = 1;
    while ((n <= 3) && (g->data[(i + n) - 2] == cv0[n - 1])) {
      n++;
    }

    if (n > 3) {
      matches->data[idx] = i;
      idx++;
    }
  }

  i0 = match_out->size[0] * match_out->size[1];
  match_out->size[0] = 1;
  match_out->size[1] = idx;
  emxEnsureCapacity((emxArray__common *)match_out, i0, sizeof(int));
  for (i = 0; i + 1 <= idx; i++) {
    match_out->data[i] = matches->data[i];
  }

  i0 = Indx->size[0] * Indx->size[1];
  Indx->size[0] = 1;
  Indx->size[1] = match_out->size[1];
  emxEnsureCapacity((emxArray__common *)Indx, i0, sizeof(double));
  ndbl = match_out->size[0] * match_out->size[1];
  for (i0 = 0; i0 < ndbl; i0++) {
    Indx->data[i0] = match_out->data[i0];
  }

  i = 0;
  emxInit_char_T(&tempg, 2);
  emxInit_int8_T(&out, 2);
  emxInit_char_T(&text, 2);
  while (i <= Indx->size[1] - 2) {
    if ((int)Indx->data[1 + i] - (int)Indx->data[i] >= 27) {
      if ((int)Indx->data[i] + 3U > (unsigned int)((int)Indx->data[i + 1] - 1))
      {
        i0 = 1;
        i1 = 1;
      } else {
        i0 = (int)((int)Indx->data[i] + 3U);
        i1 = (int)Indx->data[i + 1];
      }

      n = tempg->size[0] * tempg->size[1];
      tempg->size[0] = 1;
      tempg->size[1] = i1 - i0;
      emxEnsureCapacity((emxArray__common *)tempg, n, sizeof(char));
      ndbl = i1 - i0;
      for (n = 0; n < ndbl; n++) {
        tempg->data[tempg->size[0] * n] = g->data[(i0 + n) - 1];
      }

      yk = i1 - i0;
      if (20 < yk) {
        yk = 20;
      }

      if (1 > yk) {
        ndbl = 0;
      } else {
        ndbl = yk;
      }

      n = text->size[0] * text->size[1];
      text->size[0] = 1;
      text->size[1] = ndbl;
      emxEnsureCapacity((emxArray__common *)text, n, sizeof(char));
      for (n = 0; n < ndbl; n++) {
        text->data[text->size[0] * n] = tempg->data[n];
      }

      if (ndbl == 0) {
        n = out->size[0] * out->size[1];
        out->size[0] = 1;
        out->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)out, n, sizeof(signed char));
      } else {
        n = matches->size[0] * matches->size[1];
        matches->size[0] = 1;
        matches->size[1] = ndbl;
        emxEnsureCapacity((emxArray__common *)matches, n, sizeof(int));
        idx = 0;
        for (yk = 1; yk <= ndbl - 2; yk++) {
          n = 1;
          while ((n <= 3) && (text->data[(yk + n) - 2] == cv0[n - 1])) {
            n++;
          }

          if (n > 3) {
            matches->data[idx] = yk;
            idx++;
          }
        }

        n = match_out->size[0] * match_out->size[1];
        match_out->size[0] = 1;
        match_out->size[1] = (signed char)idx;
        emxEnsureCapacity((emxArray__common *)match_out, n, sizeof(int));
        for (yk = 0; yk + 1 <= idx; yk++) {
          match_out->data[yk] = (signed char)matches->data[yk];
        }

        n = out->size[0] * out->size[1];
        out->size[0] = 1;
        out->size[1] = match_out->size[1];
        emxEnsureCapacity((emxArray__common *)out, n, sizeof(signed char));
        ndbl = match_out->size[0] * match_out->size[1];
        for (n = 0; n < ndbl; n++) {
          out->data[n] = (signed char)match_out->data[n];
        }
      }

      if (out->size[1] > 0) {
      } else {
        b_bool = false;
        yk = 1;
        do {
          exitg2 = 0;
          if (yk < 5) {
            if (tempg->data[iv0[yk - 1] - 1] != cv1[yk - 1]) {
              exitg2 = 1;
            } else {
              yk++;
            }
          } else {
            b_bool = true;
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if (b_bool) {
          b_bool = false;
          yk = 1;
          do {
            exitg2 = 0;
            if (yk < 5) {
              if (tempg->data[iv1[yk - 1] - 1] != cv1[yk - 1]) {
                exitg2 = 1;
              } else {
                yk++;
              }
            } else {
              b_bool = true;
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if (b_bool) {
            for (ndbl = 0; ndbl < 4; ndbl++) {
              yk = (ndbl << 2) + 5;
              if (yk + 3 <= i1 - i0) {
                /*          msgx = [msgx, char('a'+bin2dec(tempg(ic:ic+3))-1)] */
                mc = 0.0;
                apnd = 1.0;
                for (n = 0; n < 4; n++) {
                  if (tempg->data[(iv2[3 - n] + yk) - 1] == '1') {
                    mc += apnd;
                  }

                  apnd += apnd;
                }

                yk = msg->size[1];
                n = msg->size[0] * msg->size[1];
                msg->size[1] = yk + 1;
                emxEnsureCapacity((emxArray__common *)msg, n, sizeof(char));
                mc = (97.0 + mc) - 1.0;
                if (rtIsInf(mc)) {
                  mc = 0.0;
                } else {
                  mc = fmod(mc, 256.0);
                }

                msg->data[yk] = (signed char)(unsigned char)mc;
              }
            }
          }
        }
      }
    }

    i++;
  }

  emxFree_char_T(&text);
  emxFree_int8_T(&out);
  emxFree_int32_T(&matches);
  emxFree_int32_T(&match_out);
  emxFree_char_T(&tempg);
  emxFree_real_T(&Indx);
  emxFree_char_T(&g);

  /*   if strcmp(gchar,'') */
  /*      msg = g  ; */
  /*   end */
}

/*
 * File trailer for extmessage2.c
 *
 * [EOF]
 */
