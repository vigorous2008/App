/*
 * File: extmessage.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 23-Oct-2017 13:29:03
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "extmessage.h"
#include "extmessage_emxutil.h"
#include "diff.h"
#include "filterpointer.h"
#include "lx_smooth.h"
#include "ifft.h"
#include "fft.h"
#include "highp.h"

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
  emxArray_creal_T *b_x;
  int c_x[1];
  emxArray_real_T d_x;
  int halfn;
  int lastIndexToDouble;
  int nx;
  emxArray_creal_T *e_x;
  int i0;
  emxArray_real_T *am;
  unsigned int x_idx_0;
  emxArray_real_T *varargin_1;
  emxArray_uint32_T *idx;
  emxArray_real_T *IndMax;
  emxArray_real_T *b_y1;
  emxArray_int32_T *ii;
  emxArray_real_T *f_x;
  int c_y1[2];
  emxArray_boolean_T *ok;
  emxArray_boolean_T *g_x;
  double h_x;
  emxArray_real_T *r0;
  emxArray_real_T *i_x;
  boolean_T exitg1;
  emxArray_real_T *b_varargin_1;
  double tmp_data[1];
  int d_y1[2];
  emxArray_int32_T *r1;
  emxArray_real_T *e_y1;
  (void)fs;
  (void)channel;
  emxInit_real_T(&x, 1);
  emxInit_creal_T(&b_x, 1);
  highp(data, x);
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

  for (nx = 1; nx + 1 <= lastIndexToDouble; nx++) {
    b_x->data[nx].re *= 2.0;
    b_x->data[nx].im *= 2.0;
  }

  for (nx = halfn + 1; nx + 1 <= x->size[0]; nx++) {
    b_x->data[nx].re = 0.0;
    b_x->data[nx].im = 0.0;
  }

  emxInit_creal_T(&e_x, 1);
  i0 = e_x->size[0];
  e_x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)e_x, i0, sizeof(creal_T));
  halfn = b_x->size[0];
  for (i0 = 0; i0 < halfn; i0++) {
    e_x->data[i0] = b_x->data[i0];
  }

  emxInit_real_T(&am, 1);
  ifft(e_x, b_x);
  x_idx_0 = (unsigned int)b_x->size[0];
  i0 = am->size[0];
  am->size[0] = (int)x_idx_0;
  emxEnsureCapacity((emxArray__common *)am, i0, sizeof(double));
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
  i0 = varargin_1->size[0];
  varargin_1->size[0] = halfn;
  emxEnsureCapacity((emxArray__common *)varargin_1, i0, sizeof(double));
  for (i0 = 0; i0 < halfn; i0++) {
    varargin_1->data[i0] = am->data[i0];
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
    i0 = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)idx, i0, sizeof(unsigned int));
  } else {
    i0 = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = halfn;
    emxEnsureCapacity((emxArray__common *)idx, i0, sizeof(unsigned int));
    halfn--;
    for (i0 = 0; i0 <= halfn; i0++) {
      idx->data[idx->size[0] * i0] = 1U + i0;
    }
  }

  i0 = x->size[0];
  x->size[0] = idx->size[1];
  emxEnsureCapacity((emxArray__common *)x, i0, sizeof(double));
  halfn = idx->size[1];
  for (i0 = 0; i0 < halfn; i0++) {
    x->data[i0] = idx->data[idx->size[0] * i0];
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
  emxInit_real_T(&IndMax, 1);
  emxInit_real_T(&b_y1, 1);
  emxInit_int32_T1(&ii, 1);
  if (halfn == 0) {
    halfn = am->size[0];
    i0 = b_y1->size[0];
    b_y1->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)b_y1, i0, sizeof(double));
    for (i0 = 0; i0 < halfn; i0++) {
      b_y1->data[i0] = varargin_1->data[i0];
    }
  } else {
    /*  realize span */
    /*  percent convention */
    /*  smooth(Y,[],method) */
    i0 = idx->size[0] * idx->size[1];
    idx->size[0] = 1;
    idx->size[1] = halfn;
    emxEnsureCapacity((emxArray__common *)idx, i0, sizeof(unsigned int));
    halfn--;
    for (i0 = 0; i0 <= halfn; i0++) {
      idx->data[idx->size[0] * i0] = 1U + i0;
    }

    /*  if NaNs not all at end */
    halfn = am->size[0];
    i0 = b_y1->size[0];
    b_y1->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)b_y1, i0, sizeof(double));
    for (i0 = 0; i0 < halfn; i0++) {
      b_y1->data[i0] = rtNaN;
    }

    emxInit_boolean_T(&ok, 1);
    i0 = ok->size[0];
    ok->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i0, sizeof(boolean_T));
    halfn = x->size[0];
    for (i0 = 0; i0 < halfn; i0++) {
      ok->data[i0] = rtIsNaN(x->data[i0]);
    }

    i0 = ok->size[0];
    emxEnsureCapacity((emxArray__common *)ok, i0, sizeof(boolean_T));
    halfn = ok->size[0];
    for (i0 = 0; i0 < halfn; i0++) {
      ok->data[i0] = !ok->data[i0];
    }

    lastIndexToDouble = ok->size[0] - 1;
    halfn = 0;
    for (nx = 0; nx <= lastIndexToDouble; nx++) {
      halfn++;
    }

    i0 = ii->size[0];
    ii->size[0] = halfn;
    emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
    halfn = 0;
    for (nx = 0; nx <= lastIndexToDouble; nx++) {
      ii->data[halfn] = nx + 1;
      halfn++;
    }

    emxInit_real_T(&i_x, 1);
    i0 = i_x->size[0];
    i_x->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)i_x, i0, sizeof(double));
    halfn = ii->size[0];
    for (i0 = 0; i0 < halfn; i0++) {
      i_x->data[i0] = x->data[ii->data[i0] - 1];
    }

    emxInit_real_T(&b_varargin_1, 1);
    i0 = b_varargin_1->size[0];
    b_varargin_1->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)b_varargin_1, i0, sizeof(double));
    halfn = ii->size[0];
    for (i0 = 0; i0 < halfn; i0++) {
      b_varargin_1->data[i0] = varargin_1->data[ii->data[i0] - 1];
    }

    tmp_data[0] = 600.0;
    moving(i_x, b_varargin_1, tmp_data, IndMax);
    lastIndexToDouble = ok->size[0];
    halfn = 0;
    emxFree_real_T(&b_varargin_1);
    emxFree_real_T(&i_x);
    emxFree_boolean_T(&ok);
    for (nx = 0; nx < lastIndexToDouble; nx++) {
      b_y1->data[nx] = IndMax->data[halfn];
      halfn++;
    }

    emxInit_int32_T(&r1, 2);
    i0 = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    r1->size[1] = idx->size[1];
    emxEnsureCapacity((emxArray__common *)r1, i0, sizeof(int));
    halfn = idx->size[0] * idx->size[1];
    for (i0 = 0; i0 < halfn; i0++) {
      r1->data[i0] = (int)idx->data[i0];
    }

    emxInit_real_T(&e_y1, 1);
    i0 = e_y1->size[0];
    e_y1->size[0] = r1->size[0] * r1->size[1];
    emxEnsureCapacity((emxArray__common *)e_y1, i0, sizeof(double));
    halfn = r1->size[0] * r1->size[1];
    for (i0 = 0; i0 < halfn; i0++) {
      e_y1->data[i0] = b_y1->data[i0];
    }

    halfn = e_y1->size[0];
    for (i0 = 0; i0 < halfn; i0++) {
      b_y1->data[r1->data[i0] - 1] = e_y1->data[i0];
    }

    emxFree_real_T(&e_y1);
    emxFree_int32_T(&r1);
  }

  emxFree_uint32_T(&idx);
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&am);
  emxFree_real_T(&x);
  emxInit_real_T1(&f_x, 2);
  c_y1[0] = b_y1->size[0];
  c_y1[1] = 1;
  d_x = *b_y1;
  d_x.size = (int *)&c_y1;
  d_x.numDimensions = 1;
  b_diff(&d_x, f_x);
  nx = f_x->size[0];
  for (halfn = 0; halfn + 1 <= nx; halfn++) {
    h_x = f_x->data[halfn];
    if (f_x->data[halfn] < 0.0) {
      h_x = -1.0;
    } else if (f_x->data[halfn] > 0.0) {
      h_x = 1.0;
    } else {
      if (f_x->data[halfn] == 0.0) {
        h_x = 0.0;
      }
    }

    f_x->data[halfn] = h_x;
  }

  emxInit_boolean_T1(&g_x, 2);
  emxInit_real_T1(&r0, 2);
  b_diff(f_x, r0);
  i0 = g_x->size[0] * g_x->size[1];
  g_x->size[0] = r0->size[0];
  g_x->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)g_x, i0, sizeof(boolean_T));
  halfn = r0->size[0] * r0->size[1];
  emxFree_real_T(&f_x);
  for (i0 = 0; i0 < halfn; i0++) {
    g_x->data[i0] = (r0->data[i0] < 0.0);
  }

  emxFree_real_T(&r0);
  nx = g_x->size[0];
  lastIndexToDouble = 0;
  i0 = ii->size[0];
  ii->size[0] = g_x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  halfn = 1;
  exitg1 = false;
  while ((!exitg1) && (halfn <= nx)) {
    if (g_x->data[halfn - 1]) {
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

  if (g_x->size[0] == 1) {
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

  emxFree_boolean_T(&g_x);
  i0 = IndMax->size[0];
  IndMax->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)IndMax, i0, sizeof(double));
  halfn = ii->size[0];
  for (i0 = 0; i0 < halfn; i0++) {
    IndMax->data[i0] = (double)ii->data[i0] + 1.0;
  }

  emxFree_int32_T(&ii);
  d_y1[0] = b_y1->size[0];
  d_y1[1] = 1;
  d_x = *b_y1;
  d_x.size = (int *)&d_y1;
  d_x.numDimensions = 1;
  filterpointer(IndMax, &d_x);

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
  /*   testshow(IndMax,sm); */
  i0 = msg->size[0] * msg->size[1];
  msg->size[0] = 1;
  msg->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
  msg->data[0] = 1.0;

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
  diff(IndMax, b_y1);
  nx = 0;
  emxFree_real_T(&IndMax);
  while (nx <= b_y1->size[0] - 1) {
    if ((b_y1->data[nx] < 4000.0) && (b_y1->data[nx] > 1500.0)) {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 1;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 1.0;
    } else if ((b_y1->data[nx] > 4000.0) && (b_y1->data[nx] < 6000.0)) {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 2;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 0.0;
      msg->data[halfn + 1] = 1.0;
    } else if ((b_y1->data[nx] > 6000.0) && (b_y1->data[nx] < 8000.0)) {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 3;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 0.0;
      msg->data[halfn + 1] = 0.0;
      msg->data[halfn + 2] = 1.0;

      /*  i=i+1; */
    } else {
      halfn = msg->size[1];
      i0 = msg->size[0] * msg->size[1];
      msg->size[1] = halfn + 2;
      emxEnsureCapacity((emxArray__common *)msg, i0, sizeof(double));
      msg->data[halfn] = 200.0;
      msg->data[halfn + 1] = 1.0;
    }

    nx++;
  }

  emxFree_real_T(&b_y1);

  /*  for i=2:length(IndMax) */
  /*  if IndMax(i)-IndMax(i-1) <2000 && IndMax(i) - IndMax(i-1)>1000 */
  /*  ge = [ge,1]; */
  /*  elseif IndMax(i) - IndMax(i-1)>=2000 && IndMax(i)-IndMax(i)<4000 */
  /*  ge = [ge,0,1]; */
  /*  elseif IndMax(i) - IndMax(i-1)>=4000 && IndMax(i)-IndMax(i)<6000 */
  /*  ge = [ge,0,0,1]; */
  /*  i=i+1; */
  /*  else */
  /*  ge = ge; */
  /*  end */
  /*  end */
}

/*
 * File trailer for extmessage.c
 *
 * [EOF]
 */
