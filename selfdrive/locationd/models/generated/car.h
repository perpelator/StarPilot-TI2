#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1078971157951247187);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9221680005543334647);
void car_H_mod_fun(double *state, double *out_1560983139609357698);
void car_f_fun(double *state, double dt, double *out_1831363007709931192);
void car_F_fun(double *state, double dt, double *out_3414175597684435281);
void car_h_25(double *state, double *unused, double *out_2355823219186371619);
void car_H_25(double *state, double *unused, double *out_6954072952532068320);
void car_h_24(double *state, double *unused, double *out_7808481367190892153);
void car_H_24(double *state, double *unused, double *out_8641889388401172511);
void car_h_30(double *state, double *unused, double *out_8511270415027031748);
void car_H_30(double *state, double *unused, double *out_2426376622404460122);
void car_h_26(double *state, double *unused, double *out_4737538044523468383);
void car_H_26(double *state, double *unused, double *out_3212569633658012096);
void car_h_27(double *state, double *unused, double *out_6781184134484603152);
void car_H_27(double *state, double *unused, double *out_4649970693588403339);
void car_h_29(double *state, double *unused, double *out_5906865094218334097);
void car_H_29(double *state, double *unused, double *out_2936607966718852306);
void car_h_28(double *state, double *unused, double *out_6022830068143991629);
void car_H_28(double *state, double *unused, double *out_2145791050350678268);
void car_h_31(double *state, double *unused, double *out_9126658445536722555);
void car_H_31(double *state, double *unused, double *out_2586361531424660620);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}