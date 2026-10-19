#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1078971157951247187) {
   out_1078971157951247187[0] = delta_x[0] + nom_x[0];
   out_1078971157951247187[1] = delta_x[1] + nom_x[1];
   out_1078971157951247187[2] = delta_x[2] + nom_x[2];
   out_1078971157951247187[3] = delta_x[3] + nom_x[3];
   out_1078971157951247187[4] = delta_x[4] + nom_x[4];
   out_1078971157951247187[5] = delta_x[5] + nom_x[5];
   out_1078971157951247187[6] = delta_x[6] + nom_x[6];
   out_1078971157951247187[7] = delta_x[7] + nom_x[7];
   out_1078971157951247187[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9221680005543334647) {
   out_9221680005543334647[0] = -nom_x[0] + true_x[0];
   out_9221680005543334647[1] = -nom_x[1] + true_x[1];
   out_9221680005543334647[2] = -nom_x[2] + true_x[2];
   out_9221680005543334647[3] = -nom_x[3] + true_x[3];
   out_9221680005543334647[4] = -nom_x[4] + true_x[4];
   out_9221680005543334647[5] = -nom_x[5] + true_x[5];
   out_9221680005543334647[6] = -nom_x[6] + true_x[6];
   out_9221680005543334647[7] = -nom_x[7] + true_x[7];
   out_9221680005543334647[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1560983139609357698) {
   out_1560983139609357698[0] = 1.0;
   out_1560983139609357698[1] = 0.0;
   out_1560983139609357698[2] = 0.0;
   out_1560983139609357698[3] = 0.0;
   out_1560983139609357698[4] = 0.0;
   out_1560983139609357698[5] = 0.0;
   out_1560983139609357698[6] = 0.0;
   out_1560983139609357698[7] = 0.0;
   out_1560983139609357698[8] = 0.0;
   out_1560983139609357698[9] = 0.0;
   out_1560983139609357698[10] = 1.0;
   out_1560983139609357698[11] = 0.0;
   out_1560983139609357698[12] = 0.0;
   out_1560983139609357698[13] = 0.0;
   out_1560983139609357698[14] = 0.0;
   out_1560983139609357698[15] = 0.0;
   out_1560983139609357698[16] = 0.0;
   out_1560983139609357698[17] = 0.0;
   out_1560983139609357698[18] = 0.0;
   out_1560983139609357698[19] = 0.0;
   out_1560983139609357698[20] = 1.0;
   out_1560983139609357698[21] = 0.0;
   out_1560983139609357698[22] = 0.0;
   out_1560983139609357698[23] = 0.0;
   out_1560983139609357698[24] = 0.0;
   out_1560983139609357698[25] = 0.0;
   out_1560983139609357698[26] = 0.0;
   out_1560983139609357698[27] = 0.0;
   out_1560983139609357698[28] = 0.0;
   out_1560983139609357698[29] = 0.0;
   out_1560983139609357698[30] = 1.0;
   out_1560983139609357698[31] = 0.0;
   out_1560983139609357698[32] = 0.0;
   out_1560983139609357698[33] = 0.0;
   out_1560983139609357698[34] = 0.0;
   out_1560983139609357698[35] = 0.0;
   out_1560983139609357698[36] = 0.0;
   out_1560983139609357698[37] = 0.0;
   out_1560983139609357698[38] = 0.0;
   out_1560983139609357698[39] = 0.0;
   out_1560983139609357698[40] = 1.0;
   out_1560983139609357698[41] = 0.0;
   out_1560983139609357698[42] = 0.0;
   out_1560983139609357698[43] = 0.0;
   out_1560983139609357698[44] = 0.0;
   out_1560983139609357698[45] = 0.0;
   out_1560983139609357698[46] = 0.0;
   out_1560983139609357698[47] = 0.0;
   out_1560983139609357698[48] = 0.0;
   out_1560983139609357698[49] = 0.0;
   out_1560983139609357698[50] = 1.0;
   out_1560983139609357698[51] = 0.0;
   out_1560983139609357698[52] = 0.0;
   out_1560983139609357698[53] = 0.0;
   out_1560983139609357698[54] = 0.0;
   out_1560983139609357698[55] = 0.0;
   out_1560983139609357698[56] = 0.0;
   out_1560983139609357698[57] = 0.0;
   out_1560983139609357698[58] = 0.0;
   out_1560983139609357698[59] = 0.0;
   out_1560983139609357698[60] = 1.0;
   out_1560983139609357698[61] = 0.0;
   out_1560983139609357698[62] = 0.0;
   out_1560983139609357698[63] = 0.0;
   out_1560983139609357698[64] = 0.0;
   out_1560983139609357698[65] = 0.0;
   out_1560983139609357698[66] = 0.0;
   out_1560983139609357698[67] = 0.0;
   out_1560983139609357698[68] = 0.0;
   out_1560983139609357698[69] = 0.0;
   out_1560983139609357698[70] = 1.0;
   out_1560983139609357698[71] = 0.0;
   out_1560983139609357698[72] = 0.0;
   out_1560983139609357698[73] = 0.0;
   out_1560983139609357698[74] = 0.0;
   out_1560983139609357698[75] = 0.0;
   out_1560983139609357698[76] = 0.0;
   out_1560983139609357698[77] = 0.0;
   out_1560983139609357698[78] = 0.0;
   out_1560983139609357698[79] = 0.0;
   out_1560983139609357698[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1831363007709931192) {
   out_1831363007709931192[0] = state[0];
   out_1831363007709931192[1] = state[1];
   out_1831363007709931192[2] = state[2];
   out_1831363007709931192[3] = state[3];
   out_1831363007709931192[4] = state[4];
   out_1831363007709931192[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1831363007709931192[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1831363007709931192[7] = state[7];
   out_1831363007709931192[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3414175597684435281) {
   out_3414175597684435281[0] = 1;
   out_3414175597684435281[1] = 0;
   out_3414175597684435281[2] = 0;
   out_3414175597684435281[3] = 0;
   out_3414175597684435281[4] = 0;
   out_3414175597684435281[5] = 0;
   out_3414175597684435281[6] = 0;
   out_3414175597684435281[7] = 0;
   out_3414175597684435281[8] = 0;
   out_3414175597684435281[9] = 0;
   out_3414175597684435281[10] = 1;
   out_3414175597684435281[11] = 0;
   out_3414175597684435281[12] = 0;
   out_3414175597684435281[13] = 0;
   out_3414175597684435281[14] = 0;
   out_3414175597684435281[15] = 0;
   out_3414175597684435281[16] = 0;
   out_3414175597684435281[17] = 0;
   out_3414175597684435281[18] = 0;
   out_3414175597684435281[19] = 0;
   out_3414175597684435281[20] = 1;
   out_3414175597684435281[21] = 0;
   out_3414175597684435281[22] = 0;
   out_3414175597684435281[23] = 0;
   out_3414175597684435281[24] = 0;
   out_3414175597684435281[25] = 0;
   out_3414175597684435281[26] = 0;
   out_3414175597684435281[27] = 0;
   out_3414175597684435281[28] = 0;
   out_3414175597684435281[29] = 0;
   out_3414175597684435281[30] = 1;
   out_3414175597684435281[31] = 0;
   out_3414175597684435281[32] = 0;
   out_3414175597684435281[33] = 0;
   out_3414175597684435281[34] = 0;
   out_3414175597684435281[35] = 0;
   out_3414175597684435281[36] = 0;
   out_3414175597684435281[37] = 0;
   out_3414175597684435281[38] = 0;
   out_3414175597684435281[39] = 0;
   out_3414175597684435281[40] = 1;
   out_3414175597684435281[41] = 0;
   out_3414175597684435281[42] = 0;
   out_3414175597684435281[43] = 0;
   out_3414175597684435281[44] = 0;
   out_3414175597684435281[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3414175597684435281[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3414175597684435281[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3414175597684435281[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3414175597684435281[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3414175597684435281[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3414175597684435281[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3414175597684435281[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3414175597684435281[53] = -9.8100000000000005*dt;
   out_3414175597684435281[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3414175597684435281[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3414175597684435281[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3414175597684435281[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3414175597684435281[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3414175597684435281[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3414175597684435281[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3414175597684435281[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3414175597684435281[62] = 0;
   out_3414175597684435281[63] = 0;
   out_3414175597684435281[64] = 0;
   out_3414175597684435281[65] = 0;
   out_3414175597684435281[66] = 0;
   out_3414175597684435281[67] = 0;
   out_3414175597684435281[68] = 0;
   out_3414175597684435281[69] = 0;
   out_3414175597684435281[70] = 1;
   out_3414175597684435281[71] = 0;
   out_3414175597684435281[72] = 0;
   out_3414175597684435281[73] = 0;
   out_3414175597684435281[74] = 0;
   out_3414175597684435281[75] = 0;
   out_3414175597684435281[76] = 0;
   out_3414175597684435281[77] = 0;
   out_3414175597684435281[78] = 0;
   out_3414175597684435281[79] = 0;
   out_3414175597684435281[80] = 1;
}
void h_25(double *state, double *unused, double *out_2355823219186371619) {
   out_2355823219186371619[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6954072952532068320) {
   out_6954072952532068320[0] = 0;
   out_6954072952532068320[1] = 0;
   out_6954072952532068320[2] = 0;
   out_6954072952532068320[3] = 0;
   out_6954072952532068320[4] = 0;
   out_6954072952532068320[5] = 0;
   out_6954072952532068320[6] = 1;
   out_6954072952532068320[7] = 0;
   out_6954072952532068320[8] = 0;
}
void h_24(double *state, double *unused, double *out_7808481367190892153) {
   out_7808481367190892153[0] = state[4];
   out_7808481367190892153[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8641889388401172511) {
   out_8641889388401172511[0] = 0;
   out_8641889388401172511[1] = 0;
   out_8641889388401172511[2] = 0;
   out_8641889388401172511[3] = 0;
   out_8641889388401172511[4] = 1;
   out_8641889388401172511[5] = 0;
   out_8641889388401172511[6] = 0;
   out_8641889388401172511[7] = 0;
   out_8641889388401172511[8] = 0;
   out_8641889388401172511[9] = 0;
   out_8641889388401172511[10] = 0;
   out_8641889388401172511[11] = 0;
   out_8641889388401172511[12] = 0;
   out_8641889388401172511[13] = 0;
   out_8641889388401172511[14] = 1;
   out_8641889388401172511[15] = 0;
   out_8641889388401172511[16] = 0;
   out_8641889388401172511[17] = 0;
}
void h_30(double *state, double *unused, double *out_8511270415027031748) {
   out_8511270415027031748[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2426376622404460122) {
   out_2426376622404460122[0] = 0;
   out_2426376622404460122[1] = 0;
   out_2426376622404460122[2] = 0;
   out_2426376622404460122[3] = 0;
   out_2426376622404460122[4] = 1;
   out_2426376622404460122[5] = 0;
   out_2426376622404460122[6] = 0;
   out_2426376622404460122[7] = 0;
   out_2426376622404460122[8] = 0;
}
void h_26(double *state, double *unused, double *out_4737538044523468383) {
   out_4737538044523468383[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3212569633658012096) {
   out_3212569633658012096[0] = 0;
   out_3212569633658012096[1] = 0;
   out_3212569633658012096[2] = 0;
   out_3212569633658012096[3] = 0;
   out_3212569633658012096[4] = 0;
   out_3212569633658012096[5] = 0;
   out_3212569633658012096[6] = 0;
   out_3212569633658012096[7] = 1;
   out_3212569633658012096[8] = 0;
}
void h_27(double *state, double *unused, double *out_6781184134484603152) {
   out_6781184134484603152[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4649970693588403339) {
   out_4649970693588403339[0] = 0;
   out_4649970693588403339[1] = 0;
   out_4649970693588403339[2] = 0;
   out_4649970693588403339[3] = 1;
   out_4649970693588403339[4] = 0;
   out_4649970693588403339[5] = 0;
   out_4649970693588403339[6] = 0;
   out_4649970693588403339[7] = 0;
   out_4649970693588403339[8] = 0;
}
void h_29(double *state, double *unused, double *out_5906865094218334097) {
   out_5906865094218334097[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2936607966718852306) {
   out_2936607966718852306[0] = 0;
   out_2936607966718852306[1] = 1;
   out_2936607966718852306[2] = 0;
   out_2936607966718852306[3] = 0;
   out_2936607966718852306[4] = 0;
   out_2936607966718852306[5] = 0;
   out_2936607966718852306[6] = 0;
   out_2936607966718852306[7] = 0;
   out_2936607966718852306[8] = 0;
}
void h_28(double *state, double *unused, double *out_6022830068143991629) {
   out_6022830068143991629[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2145791050350678268) {
   out_2145791050350678268[0] = 1;
   out_2145791050350678268[1] = 0;
   out_2145791050350678268[2] = 0;
   out_2145791050350678268[3] = 0;
   out_2145791050350678268[4] = 0;
   out_2145791050350678268[5] = 0;
   out_2145791050350678268[6] = 0;
   out_2145791050350678268[7] = 0;
   out_2145791050350678268[8] = 0;
}
void h_31(double *state, double *unused, double *out_9126658445536722555) {
   out_9126658445536722555[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2586361531424660620) {
   out_2586361531424660620[0] = 0;
   out_2586361531424660620[1] = 0;
   out_2586361531424660620[2] = 0;
   out_2586361531424660620[3] = 0;
   out_2586361531424660620[4] = 0;
   out_2586361531424660620[5] = 0;
   out_2586361531424660620[6] = 0;
   out_2586361531424660620[7] = 0;
   out_2586361531424660620[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1078971157951247187) {
  err_fun(nom_x, delta_x, out_1078971157951247187);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9221680005543334647) {
  inv_err_fun(nom_x, true_x, out_9221680005543334647);
}
void car_H_mod_fun(double *state, double *out_1560983139609357698) {
  H_mod_fun(state, out_1560983139609357698);
}
void car_f_fun(double *state, double dt, double *out_1831363007709931192) {
  f_fun(state,  dt, out_1831363007709931192);
}
void car_F_fun(double *state, double dt, double *out_3414175597684435281) {
  F_fun(state,  dt, out_3414175597684435281);
}
void car_h_25(double *state, double *unused, double *out_2355823219186371619) {
  h_25(state, unused, out_2355823219186371619);
}
void car_H_25(double *state, double *unused, double *out_6954072952532068320) {
  H_25(state, unused, out_6954072952532068320);
}
void car_h_24(double *state, double *unused, double *out_7808481367190892153) {
  h_24(state, unused, out_7808481367190892153);
}
void car_H_24(double *state, double *unused, double *out_8641889388401172511) {
  H_24(state, unused, out_8641889388401172511);
}
void car_h_30(double *state, double *unused, double *out_8511270415027031748) {
  h_30(state, unused, out_8511270415027031748);
}
void car_H_30(double *state, double *unused, double *out_2426376622404460122) {
  H_30(state, unused, out_2426376622404460122);
}
void car_h_26(double *state, double *unused, double *out_4737538044523468383) {
  h_26(state, unused, out_4737538044523468383);
}
void car_H_26(double *state, double *unused, double *out_3212569633658012096) {
  H_26(state, unused, out_3212569633658012096);
}
void car_h_27(double *state, double *unused, double *out_6781184134484603152) {
  h_27(state, unused, out_6781184134484603152);
}
void car_H_27(double *state, double *unused, double *out_4649970693588403339) {
  H_27(state, unused, out_4649970693588403339);
}
void car_h_29(double *state, double *unused, double *out_5906865094218334097) {
  h_29(state, unused, out_5906865094218334097);
}
void car_H_29(double *state, double *unused, double *out_2936607966718852306) {
  H_29(state, unused, out_2936607966718852306);
}
void car_h_28(double *state, double *unused, double *out_6022830068143991629) {
  h_28(state, unused, out_6022830068143991629);
}
void car_H_28(double *state, double *unused, double *out_2145791050350678268) {
  H_28(state, unused, out_2145791050350678268);
}
void car_h_31(double *state, double *unused, double *out_9126658445536722555) {
  h_31(state, unused, out_9126658445536722555);
}
void car_H_31(double *state, double *unused, double *out_2586361531424660620) {
  H_31(state, unused, out_2586361531424660620);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
