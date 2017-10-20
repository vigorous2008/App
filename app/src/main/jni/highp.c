/*
 * File: highp.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 19-Oct-2017 14:36:17
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "highp.h"
#include "extmessage_emxutil.h"
#include "log10.h"
#include "abs.h"
#include "freqz.h"

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
  static const double b[11] = { 3.2498310006647061E-5, -0.00032498310006647061,
    0.0014624239502991178, -0.0038997972007976467, 0.0068246451013958829,
    -0.0081895741216750587, 0.0068246451013958829, -0.0038997972007976467,
    0.0014624239502991178, -0.00032498310006647061, 3.2498310006647061E-5 };

  static const double a[11] = { 1.0, 5.1042819547169112, 13.72332468001014,
    24.483964501771233, 31.589371819975355, 30.507394926991218,
    22.223440483027083, 12.032617378454402, 4.636622670955993,
    1.1521241545404568, 0.14128687615136459 };

  creal_T h[256];
  double w[256];
  double dv0[256];
  double unusedExpr[256];
  unsigned int unnamed_idx_0;
  int k;
  int nx;
  int naxpy;
  int j;
  static const double dv1[11] = { 3.2498310006647061E-5, -0.00032498310006647061,
    0.0014624239502991178, -0.0038997972007976467, 0.0068246451013958829,
    -0.0081895741216750587, 0.0068246451013958829, -0.0038997972007976467,
    0.0014624239502991178, -0.00032498310006647061, 3.2498310006647061E-5 };

  double as;
  static const double dv2[11] = { 1.0, 5.1042819547169112, 13.72332468001014,
    24.483964501771233, 31.589371819975355, 30.507394926991218,
    22.223440483027083, 12.032617378454402, 4.636622670955993,
    1.1521241545404568, 0.14128687615136459 };

  /*  ����б�ѩ���˲����� */
  /* �鿴����˲��������� */
  freqz(b, a, h, w);
  b_abs(h, dv0);
  b_log10(dv0, unusedExpr);

  /* figure;plot(w,h);title('������˲�����ͨ������');grid on; */
  unnamed_idx_0 = (unsigned int)x->size[0];
  k = y->size[0];
  y->size[0] = (int)unnamed_idx_0;
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
    if (!(naxpy < 11)) {
      naxpy = 11;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y->data[k + j] += x->data[k] * dv1[j];
    }

    naxpy = (nx - k) - 1;
    if (!(naxpy < 10)) {
      naxpy = 10;
    }

    as = -y->data[k];
    for (j = 1; j <= naxpy; j++) {
      y->data[k + j] += as * dv2[j];
    }
  }
}

/*
 * File trailer for highp.c
 *
 * [EOF]
 */
