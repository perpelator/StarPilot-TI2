#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4629685827320122449);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8757749050678507284);
void pose_H_mod_fun(double *state, double *out_5053584943541973484);
void pose_f_fun(double *state, double dt, double *out_4398664509741735976);
void pose_F_fun(double *state, double dt, double *out_6038848360723463246);
void pose_h_4(double *state, double *unused, double *out_1967691091348868206);
void pose_H_4(double *state, double *unused, double *out_6873283669448270345);
void pose_h_10(double *state, double *unused, double *out_4208360954594629467);
void pose_H_10(double *state, double *unused, double *out_4681463386096154266);
void pose_h_13(double *state, double *unused, double *out_2556445490971921155);
void pose_H_13(double *state, double *unused, double *out_737347538868430584);
void pose_h_14(double *state, double *unused, double *out_705003315889852073);
void pose_H_14(double *state, double *unused, double *out_8490671971965908975);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}