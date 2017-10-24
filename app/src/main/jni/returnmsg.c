/*
 * File: returnmsg.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 24-Oct-2017 11:07:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "returnmsg.h"
#include "extmessage_emxutil.h"
#include "diff.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *IndMax
 *                emxArray_char_T *msg
 * Return Type  : void
 */
void returnmsg(const emxArray_real_T *IndMax, emxArray_char_T *msg)
{
  emxArray_char_T *ge;
  int i4;
  emxArray_real_T *cc;
  static const char cv0[4] = { '2', '0', '0', '1' };

  int i;
  emxArray_int32_T *match_out;
  int match_idx;
  emxArray_int32_T *matches;
  static const char cv1[3] = { '2', '0', '0' };

  int j;
  static const char cv2[7] = { '2', '0', '0', '1', '0', '1', '0' };

  emxArray_int32_T *Indx;
  emxArray_char_T *tempg;
  int i5;
  int ic;
  double x;
  double p2;
  static const signed char iv0[4] = { 0, 1, 2, 3 };

  emxInit_char_T(&ge, 2);
  i4 = ge->size[0] * ge->size[1];
  ge->size[0] = 1;
  ge->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
  for (i4 = 0; i4 < 4; i4++) {
    ge->data[i4] = cv0[i4];
  }

  emxInit_real_T(&cc, 1);

  /*  for i=2:length(IndMax) */
  /*  if IndMax(i)-IndMax(i-1) <4000 && IndMax(i) - IndMax(i-1)>1500 */
  /*  ge = [ge,1]; */
  /*   elseif IndMax(i) - IndMax(i-1)>4000 && IndMax(i)-IndMax(i-1)<6000 */
  /*  ge = [ge,0,1]; */
  /*  elseif IndMax(i) - IndMax(i-1)>6000 && IndMax(i)-IndMax(i-1)<8000 */
  /*  ge = [ge,0,0,1]; */
  /*  i=i+1; */
  /*  else */
  /*  ge = [ge,200,1]; */
  /*  end */
  /*  end */
  diff(IndMax, cc);
  for (i = 0; i < cc->size[0]; i++) {
    if ((cc->data[i] < 4000.0) && (cc->data[i] > 1500.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 1;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '1';
    } else if ((cc->data[i] > 4000.0) && (cc->data[i] < 6000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 2;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '1';
    } else if ((cc->data[i] > 6000.0) && (cc->data[i] < 8000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 3;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '0';
      ge->data[match_idx + 2] = '1';

      /*  i=i+1; */
    } else if ((cc->data[i] > 8000.0) && (cc->data[i] < 12000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 4;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '0';
      ge->data[match_idx + 2] = '0';
      ge->data[match_idx + 3] = '1';
    } else if ((cc->data[i] > 12000.0) && (cc->data[i] < 14000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 5;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '0';
      ge->data[match_idx + 2] = '0';
      ge->data[match_idx + 3] = '0';
      ge->data[match_idx + 4] = '1';
    } else if ((cc->data[i] > 14000.0) && (cc->data[i] < 16000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 6;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '0';
      ge->data[match_idx + 2] = '0';
      ge->data[match_idx + 3] = '0';
      ge->data[match_idx + 4] = '0';
      ge->data[match_idx + 5] = '1';
    } else if ((cc->data[i] > 16000.0) && (cc->data[i] < 18000.0)) {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 7;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      ge->data[match_idx] = '0';
      ge->data[match_idx + 1] = '0';
      ge->data[match_idx + 2] = '0';
      ge->data[match_idx + 3] = '0';
      ge->data[match_idx + 4] = '0';
      ge->data[match_idx + 5] = '0';
      ge->data[match_idx + 6] = '1';
    } else {
      match_idx = ge->size[1];
      i4 = ge->size[0] * ge->size[1];
      ge->size[1] = match_idx + 4;
      emxEnsureCapacity((emxArray__common *)ge, i4, sizeof(char));
      for (i4 = 0; i4 < 3; i4++) {
        ge->data[match_idx + i4] = cv1[i4];
      }

      ge->data[match_idx + 3] = '1';
    }
  }

  emxFree_real_T(&cc);
  emxInit_int32_T(&match_out, 2);
  emxInit_int32_T(&matches, 2);
  i4 = msg->size[0] * msg->size[1];
  msg->size[0] = 1;
  msg->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)msg, i4, sizeof(char));
  i4 = matches->size[0] * matches->size[1];
  matches->size[0] = 1;
  matches->size[1] = ge->size[1];
  emxEnsureCapacity((emxArray__common *)matches, i4, sizeof(int));
  match_idx = 0;
  for (i = 1; i <= ge->size[1] - 6; i++) {
    j = 1;
    while ((j <= 7) && (ge->data[(i + j) - 2] == cv2[j - 1])) {
      j++;
    }

    if (j > 7) {
      matches->data[match_idx] = i;
      match_idx++;
    }
  }

  i4 = match_out->size[0] * match_out->size[1];
  match_out->size[0] = 1;
  match_out->size[1] = match_idx;
  emxEnsureCapacity((emxArray__common *)match_out, i4, sizeof(int));
  for (i = 0; i + 1 <= match_idx; i++) {
    match_out->data[i] = matches->data[i];
  }

  emxFree_int32_T(&matches);
  emxInit_int32_T(&Indx, 2);
  i4 = Indx->size[0] * Indx->size[1];
  Indx->size[0] = 1;
  Indx->size[1] = match_out->size[1];
  emxEnsureCapacity((emxArray__common *)Indx, i4, sizeof(int));
  match_idx = match_out->size[0] * match_out->size[1];
  for (i4 = 0; i4 < match_idx; i4++) {
    Indx->data[i4] = match_out->data[i4];
  }

  emxFree_int32_T(&match_out);
  i = 0;
  emxInit_char_T(&tempg, 2);
  while (i <= Indx->size[1] - 2) {
    if ((double)Indx->data[1 + i] - (double)Indx->data[i] >= 20.0) {
      if ((double)Indx->data[i] + 7.0 > (double)Indx->data[i + 1] - 1.0) {
        i4 = 1;
        i5 = 1;
      } else {
        i4 = (int)((double)Indx->data[i] + 7.0);
        i5 = (int)((double)Indx->data[i + 1] - 1.0) + 1;
      }

      j = tempg->size[0] * tempg->size[1];
      tempg->size[0] = 1;
      tempg->size[1] = i5 - i4;
      emxEnsureCapacity((emxArray__common *)tempg, j, sizeof(char));
      match_idx = i5 - i4;
      for (j = 0; j < match_idx; j++) {
        tempg->data[tempg->size[0] * j] = ge->data[(i4 + j) - 1];
      }

      for (ic = 0; ic < 4; ic++) {
        match_idx = (ic << 2) + 1;
        if (match_idx + 3 < i5 - i4) {
          /*          msgx = [msgx, char('a'+bin2dec(tempg(ic:ic+3))-1)] */
          x = 0.0;
          p2 = 1.0;
          for (j = 0; j < 4; j++) {
            if (tempg->data[(iv0[3 - j] + match_idx) - 1] == '1') {
              x += p2;
            }

            p2 += p2;
          }

          match_idx = msg->size[1];
          j = msg->size[0] * msg->size[1];
          msg->size[1] = match_idx + 1;
          emxEnsureCapacity((emxArray__common *)msg, j, sizeof(char));
          x = (97.0 + x) - 1.0;
          if (rtIsInf(x)) {
            x = 0.0;
          } else {
            x = fmod(x, 256.0);
          }

          msg->data[match_idx] = (signed char)(unsigned char)x;
        }
      }
    }

    i++;
  }

  emxFree_char_T(&tempg);
  emxFree_int32_T(&Indx);
  emxFree_char_T(&ge);
}

/*
 * File trailer for returnmsg.c
 *
 * [EOF]
 */
