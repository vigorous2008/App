/*
 * File: highp.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 07-Nov-2017 15:17:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage2.h"
#include "highp.h"
#include "extmessage2_emxutil.h"

/* Function Definitions */

/*
 * ��ͨ�˲�
 * ʹ��ע�����ͨ��������Ľ�ֹƵ�ʵ�ѡȡ��Χ�ǲ��ܳ��������ʵ�һ��
 * ����f1,f3��ֵ��ҪС�� Fs/2
 * x:��Ҫ��ͨ�˲�������
 *  f 1��ͨ����ֹƵ��
 *  f 2�������ֹƵ��
 * rp���ߴ���˥��DB������
 * rs����ֹ��˥��DB������
 * FS������x�Ĳ���Ƶ��
 *  rp=0.1;rs=30;%ͨ����˥��DBֵ�������˥��DBֵ
 *  Fs=2000;%������
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void highp(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int k;
  int nx;
  int naxpy;
  int j;
  static const double dv0[9] = { 8.567905661780301E-6, -6.8543245294242408E-5,
    0.00023990135852984846, -0.00047980271705969692, 0.00059975339632462119,
    -0.00047980271705969692, 0.00023990135852984846, -6.8543245294242408E-5,
    8.567905661780301E-6 };

  double as;
  static const double dv1[9] = { 1.0, 5.8748452954799513, 15.929009885013079,
    25.863390191642498, 27.396164743675833, 19.338559612922506,
    8.870573689031211, 2.4158496311041762, 0.29911519546637977 };

  /*  ����б�ѩ���˲����� */
  /* �鿴����˲��������� */
  /* figure;plot(w,h);title('������˲�����ͨ������');grid on; */
  x_idx_0 = (unsigned int)x->size[0];
  k = y->size[0];
  y->size[0] = (int)x_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, sizeof(double));
  nx = x->size[0];
  naxpy = y->size[0];
  k = y->size[0];
  y->size[0] = naxpy;
  emxEnsureCapacity((emxArray__common *)y, k, sizeof(double));
  for (k = 0; k < naxpy; k++) {
    y->data[k] = 0.0;
  }

  for (k = 0; k + 1 <= nx; k++) {
    naxpy = nx - k;
    if (!(naxpy < 9)) {
      naxpy = 9;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y->data[k + j] += x->data[k] * dv0[j];
    }

    naxpy = (nx - k) - 1;
    if (!(naxpy < 8)) {
      naxpy = 8;
    }

    as = -y->data[k];
    for (j = 1; j <= naxpy; j++) {
      y->data[k + j] += as * dv1[j];
    }
  }
}

/*
 * File trailer for highp.c
 *
 * [EOF]
 */
