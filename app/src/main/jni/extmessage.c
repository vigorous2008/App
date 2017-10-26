/*
 * File: extmessage.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 26-Oct-2017 12:54:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "extmessage_emxutil.h"
#include "filterpointer2.h"
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
 *                emxArray_char_T *msg
 * Return Type  : void
 */
void extmessage(const emxArray_real_T *data, int fs, int channel,
                emxArray_char_T *msg)
{
  emxArray_real_T *x;
  unsigned int data_idx_0;
  int i;
  int nx;
  int halfn;
  emxArray_creal_T *b_x;
  int lastIndexToDouble;
  int c_x[1];
  emxArray_real_T d_x;
  static const double dv0[9] = { 8.567905661780301E-6, -6.8543245294242408E-5,
    0.00023990135852984846, -0.00047980271705969692, 0.00059975339632462119,
    -0.00047980271705969692, 0.00023990135852984846, -6.8543245294242408E-5,
    8.567905661780301E-6 };

  double as;
  static const double dv1[9] = { 1.0, 5.8748452954799513, 15.929009885013079,
    25.863390191642498, 27.396164743675833, 19.338559612922506,
    8.870573689031211, 2.4158496311041762, 0.29911519546637977 };

  emxArray_creal_T *e_x;
  emxArray_real_T *am;
  emxArray_real_T *varargin_1;
  emxArray_uint32_T *idx;
  emxArray_real_T *sm;
  emxArray_real_T *b_y1;
  int b_sm[2];
  emxArray_boolean_T *ok;
  emxArray_int32_T *r0;
  emxArray_real_T *f_x;
  emxArray_real_T *b_varargin_1;
  double tmp_data[1];
  emxArray_int32_T *r1;
  emxArray_real_T *c_sm;
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
  i = x->size[0];
  x->size[0] = (int)data_idx_0;
  emxEnsureCapacity((emxArray__common *)x, i, sizeof(double));
  nx = data->size[0];
  halfn = x->size[0];
  i = x->size[0];
  x->size[0] = halfn;
  emxEnsureCapacity((emxArray__common *)x, i, sizeof(double));
  for (i = 0; i < halfn; i++) {
    x->data[i] = 0.0;
  }

  for (halfn = 0; halfn + 1 <= nx; halfn++) {
    lastIndexToDouble = nx - halfn;
    if (!(lastIndexToDouble < 9)) {
      lastIndexToDouble = 9;
    }

    for (i = 0; i + 1 <= lastIndexToDouble; i++) {
      x->data[halfn + i] += data->data[halfn] * dv0[i];
    }

    lastIndexToDouble = (nx - halfn) - 1;
    if (!(lastIndexToDouble < 8)) {
      lastIndexToDouble = 8;
    }

    as = -x->data[halfn];
    for (i = 1; i <= lastIndexToDouble; i++) {
      x->data[halfn + i] += as * dv1[i];
    }
  }

  emxInit_creal_T(&b_x, 1);

  /*  plot(data); */
  /*  figure; */
  /*  plot(x); */
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
  i = e_x->size[0];
  e_x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)e_x, i, sizeof(creal_T));
  halfn = b_x->size[0];
  for (i = 0; i < halfn; i++) {
    e_x->data[i] = b_x->data[i];
  }

  emxInit_real_T(&am, 1);
  ifft(e_x, b_x);
  data_idx_0 = (unsigned int)b_x->size[0];
  i = am->size[0];
  am->size[0] = (int)data_idx_0;
  emxEnsureCapacity((emxArray__common *)am, i, sizeof(double));
  halfn = 0;
  emxFree_creal_T(&e_x);
  while (halfn + 1 <= b_x->size[0]) {
    am->data[halfn] = rt_hypotd_snf(b_x->data[halfn].re, b_x->data[halfn].im);
    halfn++;
  }

  emxFree_creal_T(&b_x);
  emxInit_real_T(&varargin_1, 1);

  /*  figure;grid; */
  /*  title('hilbert'); */
  /*   plot(1:length(x),am); */
  halfn = am->size[0];
  i = varargin_1->size[0];
  varargin_1->size[0] = halfn;
  emxEnsureCapacity((emxArray__common *)varargin_1, i, sizeof(double));
  for (i = 0; i < halfn; i++) {
    varargin_1->data[i] = am->data[i];
  }

  emxInit_uint32_T(&idx, 2);

  /* SMOOTH  Smooth data. */
  /*    Z = SMOOTH(Y) smooths data Y using a 5-point moving average. */
  /*  */
  /*    Z = SMOOTH(Y,SPAN) smooths data Y using SPAN as the number of points used */
  /*    to compute each element of Z. */
  /*  */
  /*    Z = SMOOTH(Y,SPAN,METHOD) smooths data Y with specified METHOD. The */
  /*    available methods are: */
  /*  */
  /*            'moving'   - Moving average (default) */
  /*            'lowess'   - Lowess (linear fit) */
  /*            'loess'    - Loess (quadratic fit) */
  /*            'sgolay'   - Savitzky-Golay */
  /*            'rlowess'  - Robust Lowess (linear fit) */
  /*            'rloess'   - Robust Loess (quadratic fit) */
  /*  */
  /*    Z = SMOOTH(Y,METHOD) uses the default SPAN 5. */
  /*  */
  /*    Z = SMOOTH(Y,SPAN,'sgolay',DEGREE) and Z = SMOOTH(Y,'sgolay',DEGREE) */
  /*    additionally specify the degree of the polynomial to be used in the */
  /*    Savitzky-Golay method. The default DEGREE is 2. DEGREE must be smaller */
  /*    than SPAN. */
  /*  */
  /*    Z = SMOOTH(X,Y,...) additionally specifies the X coordinates.  If X is */
  /*    not provided, methods that require X coordinates assume X = 1:N, where */
  /*    N is the length of Y. */
  /*  */
  /*    Notes: */
  /*    1. When X is given and X is not uniformly distributed, the default method */
  /*    is 'lowess'.  The 'moving' method is not recommended. */
  /*  */
  /*    2. For the 'moving' and 'sgolay' methods, SPAN must be odd. */
  /*    If an even SPAN is specified, it is reduced by 1. */
  /*  */
  /*    3. If SPAN is greater than the length of Y, it is reduced to the */
  /*    length of Y. */
  /*  */
  /*    4. In the case of (robust) lowess and (robust) loess, it is also */
  /*    possible to specify the SPAN as a percentage of the total number */
  /*    of data points. When SPAN is less than or equal to 1, it is */
  /*    treated as a percentage. */
  /*  */
  /*    For example: */
  /*  */
  /*    Z = SMOOTH(Y) uses the moving average method with span 5 and */
  /*    X=1:length(Y). */
  /*  */
  /*    Z = SMOOTH(Y,7) uses the moving average method with span 7 and */
  /*    X=1:length(Y). */
  /*  */
  /*    Z = SMOOTH(Y,'sgolay') uses the Savitzky-Golay method with DEGREE=2, */
  /*    SPAN = 5, X = 1:length(Y). */
  /*  */
  /*    Z = SMOOTH(X,Y,'lowess') uses the lowess method with SPAN=5. */
  /*  */
  /*    Z = SMOOTH(X,Y,SPAN,'rloess') uses the robust loess method. */
  /*  */
  /*    Z = SMOOTH(X,Y) where X is unevenly distributed uses the */
  /*    'lowess' method with span 5. */
  /*  */
  /*    Z = SMOOTH(X,Y,8,'sgolay') uses the Savitzky-Golay method with */
  /*    span 7 (8 is reduced by 1 to make it odd). */
  /*  */
  /*    Z = SMOOTH(X,Y,0.3,'loess') uses the loess method where span is */
  /*    30% of the data, i.e. span = ceil(0.3*length(Y)). */
  /*  */
  /*    See also SPLINE. */
  /*    Copyright 2001-2016 The MathWorks, Inc. */
  /*  ws = warning('query','all'); % Leave warning state alone but save it so resets are no-ops. */
  /*  is x given as the first argument? */
  /*  smooth(Y) | smooth(Y,span,...) | smooth(Y,method,...) */
  /*  x is not given */
  halfn = am->size[0];
  if (halfn < 1) {
    i = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
  } else {
    i = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = halfn;
    emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
    halfn--;
    for (i = 0; i <= halfn; i++) {
      idx->data[idx->size[0] * i] = 1U + i;
    }
  }

  i = x->size[0];
  x->size[0] = idx->size[1];
  emxEnsureCapacity((emxArray__common *)x, i, sizeof(double));
  halfn = idx->size[1];
  for (i = 0; i < halfn; i++) {
    x->data[i] = idx->data[idx->size[0] * i];
  }

  /*  is span given? */
  /*  smooth(...,SPAN,...) */
  /*  is method given? */
  /*  method = []; */
  /*  if nargin >= 2+is_x+is_span */
  /*      % smooth(...,Y,method,...) | smooth(...,Y,span,method,...) */
  /*      method = varargin{2+is_x+is_span}; */
  /*  end */
  halfn = am->size[0];
  emxInit_real_T(&sm, 1);
  if (halfn == 0) {
    halfn = am->size[0];
    i = sm->size[0];
    sm->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)sm, i, sizeof(double));
    for (i = 0; i < halfn; i++) {
      sm->data[i] = varargin_1->data[i];
    }
  } else {
    /*  realize span */
    /*  percent convention */
    /*  smooth(Y,[],method) */
    i = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = halfn;
    emxEnsureCapacity((emxArray__common *)idx, i, sizeof(unsigned int));
    halfn--;
    for (i = 0; i <= halfn; i++) {
      idx->data[idx->size[0] * i] = 1U + i;
    }

    emxInit_real_T(&b_y1, 1);

    /*  if NaNs not all at end */
    halfn = am->size[0];
    i = sm->size[0];
    sm->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)sm, i, sizeof(double));
    for (i = 0; i < halfn; i++) {
      sm->data[i] = rtNaN;
    }

    emxInit_boolean_T(&ok, 1);
    i = ok->size[0];
    ok->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i, sizeof(boolean_T));
    halfn = x->size[0];
    for (i = 0; i < halfn; i++) {
      ok->data[i] = rtIsNaN(x->data[i]);
    }

    i = ok->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i, sizeof(boolean_T));
    halfn = ok->size[0];
    for (i = 0; i < halfn; i++) {
      ok->data[i] = !ok->data[i];
    }

    lastIndexToDouble = ok->size[0] - 1;
    halfn = 0;
    for (i = 0; i <= lastIndexToDouble; i++) {
      halfn++;
    }

    emxInit_int32_T1(&r0, 1);
    i = r0->size[0];
    r0->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)r0, i, sizeof(int));
    halfn = 0;
    for (i = 0; i <= lastIndexToDouble; i++) {
      r0->data[halfn] = i + 1;
      halfn++;
    }

    emxInit_real_T(&f_x, 1);
    i = f_x->size[0];
    f_x->size[0] = r0->size[0];
    emxEnsureCapacity((emxArray__common *)f_x, i, sizeof(double));
    halfn = r0->size[0];
    for (i = 0; i < halfn; i++) {
      f_x->data[i] = x->data[r0->data[i] - 1];
    }

    emxInit_real_T(&b_varargin_1, 1);
    i = b_varargin_1->size[0];
    b_varargin_1->size[0] = r0->size[0];
    emxEnsureCapacity((emxArray__common *)b_varargin_1, i, sizeof(double));
    halfn = r0->size[0];
    for (i = 0; i < halfn; i++) {
      b_varargin_1->data[i] = varargin_1->data[r0->data[i] - 1];
    }

    emxFree_int32_T(&r0);
    tmp_data[0] = 600.0;
    moving(f_x, b_varargin_1, tmp_data, b_y1);
    lastIndexToDouble = ok->size[0];
    halfn = 0;
    emxFree_real_T(&b_varargin_1);
    emxFree_real_T(&f_x);
    emxFree_boolean_T(&ok);
    for (i = 0; i < lastIndexToDouble; i++) {
      sm->data[i] = b_y1->data[halfn];
      halfn++;
    }

    emxFree_real_T(&b_y1);
    emxInit_int32_T(&r1, 2);
    i = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    r1->size[1] = idx->size[1];
    emxEnsureCapacity((emxArray__common *)r1, i, sizeof(int));
    halfn = idx->size[0] * idx->size[1];
    for (i = 0; i < halfn; i++) {
      r1->data[i] = (int)idx->data[i];
    }

    emxInit_real_T(&c_sm, 1);
    i = c_sm->size[0];
    c_sm->size[0] = r1->size[0] * r1->size[1];
    emxEnsureCapacity((emxArray__common *)c_sm, i, sizeof(double));
    halfn = r1->size[0] * r1->size[1];
    for (i = 0; i < halfn; i++) {
      c_sm->data[i] = sm->data[i];
    }

    halfn = c_sm->size[0];
    for (i = 0; i < halfn; i++) {
      sm->data[r1->data[i] - 1] = c_sm->data[i];
    }

    emxFree_real_T(&c_sm);
    emxFree_int32_T(&r1);
  }

  emxFree_uint32_T(&idx);
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&am);
  emxFree_real_T(&x);
  b_sm[0] = sm->size[0];
  b_sm[1] = 1;
  d_x = *sm;
  d_x.size = (int *)&b_sm;
  d_x.numDimensions = 1;
  filterpointer2(&d_x, msg);

  /*  figure;hold on; */
  /*  %plot(IndMin,sm(IndMin),'r^') */
  /*  plot(IndMax,sm(IndMax),'k*') */
  /*  plot(sm); */
  /*  testshow(IndMax,sm); */
  /*  figure;grid; */
  /*  title('smooth'); */
  /*   plot(sm); */
  /*  IndMax = []; */
  /*  % %signdif  */
  /*  % sdifsm = sign(diff(sm));  */
  /*  % %Indmin */
  /*  % IndMin=find(diff(sdifsm)>0)+1; */
  /*  % %IndMax */
  /*  % IndMax=find(diff(sdifsm)<0)+1; */
  /*  %signdif  */
  /*  % sdifsm = sign(diff(sm));  */
  /*  %Indmin */
  /*  % IndMin=find(diff(sign(diff(sm)))>0)+1; */
  /*  %IndMax */
  /*  IndMax=find(diff(sign(diff(sm)))<0)+1;  */
  /*   */
  /*  ge = [1]; */
  /*  testshow(IndMax,sm); */
  /*  for i = 2 :length(IndMax) */
  /*  if abs(IndMax(i-1)-IndMax(i))<20 || (abs(sm(IndMax(i-1)) - sm(IndMax(i))<0.00015)  && sm(IndMax(i-1))<0.008) ||sm(IndMax(i-1))<0.01 */
  /*  IndMax(i-1)=0; */
  /*  end */
  /*  end */
  /*  IndMax(find(IndMax==0))=[]; */
  /*  testshow(IndMax,sm); */
  /*  % for i = 2 :length(IndMax) */
  /*  %     if i<length(IndMax) - 10 */
  /*  %         if abs(IndMax(i-1)-IndMax(i))>9000 && abs(IndMax(i+1)-IndMax(i))<9000 && length(find(IndMax(i:i+10)-IndMax(i)<10000))<10 */
  /*  %             if i>10 */
  /*  %                 if length(find(IndMax(i-10:i)-IndMax(i)<10000))<10 */
  /*  %                     IndMax(i-1)=0; */
  /*  %                 end */
  /*  %             else */
  /*  %                 IndMax(i-1)=0; */
  /*  %             end */
  /*  %         end */
  /*  %     end */
  /*  % end */
  /*  tempP = 50000; */
  /*  for i = 1 :length(IndMax)  */
  /*      if i==86 */
  /*          lx = 86; */
  /*      end */
  /*      if i>10 &&i<length(IndMax) -10 */
  /*          if length(find(IndMax(i:i+10)<tempP+IndMax(i)))+length(find(IndMax(i)<tempP+IndMax(i-10:i)))<10 */
  /*              IndMax(i)=0; */
  /*          end */
  /*      elseif i<11  */
  /*          if length(find(IndMax(i:i+10)<tempP+IndMax(i)))+length(find(IndMax(i)<tempP+IndMax(1:i)))<10 */
  /*              IndMax(i)=0; */
  /*          end */
  /*      else  */
  /*          if length(find(IndMax(i:length(IndMax))<tempP+IndMax(i)))+length(find(IndMax(i)<tempP+IndMax(i-10:i)))<10 */
  /*              IndMax(i)=0; */
  /*          end */
  /*      end */
  /*       */
  /*  end */
  /*  % IndMax(find(IndMax==0))=[]; */
  /*  figure;hold on; */
  /*  %plot(IndMin,sm(IndMin),'r^') */
  /*  plot(IndMax,sm(IndMax),'k*') */
  /*  plot(sm); */
  /*  figure; hold on; */
  /*  tempS = sm(210000:270000); */
  /*  tempI = IndMax(find(IndMax<270000)); */
  /*  plot(tempI-210000,sm(tempI),'k*'); */
  /*  plot(tempS); */
  /*  for i=2:length(IndMax) */
  /*  if IndMax(i)-IndMax(i-1) <2000 && IndMax(i) - IndMax(i-1)>1000 */
  /*  ge = [ge,1]; */
  /*  elseif IndMax(i) - IndMax(i-1)>=2000 && IndMax(i)-IndMax(i)<4000 */
  /*  ge = [ge,0,1];  */
  /*  elseif IndMax(i) - IndMax(i-1)>=4000 && IndMax(i)-IndMax(i)<6000 */
  /*  ge = [ge,0,0,1]; */
  /*  i=i+1; */
  /*  else */
  /*  ge = ge; */
  /*  end */
  /*  end */
  emxFree_real_T(&sm);
}

/*
 * File trailer for extmessage.c
 *
 * [EOF]
 */
