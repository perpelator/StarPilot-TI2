#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4629685827320122449) {
   out_4629685827320122449[0] = delta_x[0] + nom_x[0];
   out_4629685827320122449[1] = delta_x[1] + nom_x[1];
   out_4629685827320122449[2] = delta_x[2] + nom_x[2];
   out_4629685827320122449[3] = delta_x[3] + nom_x[3];
   out_4629685827320122449[4] = delta_x[4] + nom_x[4];
   out_4629685827320122449[5] = delta_x[5] + nom_x[5];
   out_4629685827320122449[6] = delta_x[6] + nom_x[6];
   out_4629685827320122449[7] = delta_x[7] + nom_x[7];
   out_4629685827320122449[8] = delta_x[8] + nom_x[8];
   out_4629685827320122449[9] = delta_x[9] + nom_x[9];
   out_4629685827320122449[10] = delta_x[10] + nom_x[10];
   out_4629685827320122449[11] = delta_x[11] + nom_x[11];
   out_4629685827320122449[12] = delta_x[12] + nom_x[12];
   out_4629685827320122449[13] = delta_x[13] + nom_x[13];
   out_4629685827320122449[14] = delta_x[14] + nom_x[14];
   out_4629685827320122449[15] = delta_x[15] + nom_x[15];
   out_4629685827320122449[16] = delta_x[16] + nom_x[16];
   out_4629685827320122449[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8757749050678507284) {
   out_8757749050678507284[0] = -nom_x[0] + true_x[0];
   out_8757749050678507284[1] = -nom_x[1] + true_x[1];
   out_8757749050678507284[2] = -nom_x[2] + true_x[2];
   out_8757749050678507284[3] = -nom_x[3] + true_x[3];
   out_8757749050678507284[4] = -nom_x[4] + true_x[4];
   out_8757749050678507284[5] = -nom_x[5] + true_x[5];
   out_8757749050678507284[6] = -nom_x[6] + true_x[6];
   out_8757749050678507284[7] = -nom_x[7] + true_x[7];
   out_8757749050678507284[8] = -nom_x[8] + true_x[8];
   out_8757749050678507284[9] = -nom_x[9] + true_x[9];
   out_8757749050678507284[10] = -nom_x[10] + true_x[10];
   out_8757749050678507284[11] = -nom_x[11] + true_x[11];
   out_8757749050678507284[12] = -nom_x[12] + true_x[12];
   out_8757749050678507284[13] = -nom_x[13] + true_x[13];
   out_8757749050678507284[14] = -nom_x[14] + true_x[14];
   out_8757749050678507284[15] = -nom_x[15] + true_x[15];
   out_8757749050678507284[16] = -nom_x[16] + true_x[16];
   out_8757749050678507284[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5053584943541973484) {
   out_5053584943541973484[0] = 1.0;
   out_5053584943541973484[1] = 0.0;
   out_5053584943541973484[2] = 0.0;
   out_5053584943541973484[3] = 0.0;
   out_5053584943541973484[4] = 0.0;
   out_5053584943541973484[5] = 0.0;
   out_5053584943541973484[6] = 0.0;
   out_5053584943541973484[7] = 0.0;
   out_5053584943541973484[8] = 0.0;
   out_5053584943541973484[9] = 0.0;
   out_5053584943541973484[10] = 0.0;
   out_5053584943541973484[11] = 0.0;
   out_5053584943541973484[12] = 0.0;
   out_5053584943541973484[13] = 0.0;
   out_5053584943541973484[14] = 0.0;
   out_5053584943541973484[15] = 0.0;
   out_5053584943541973484[16] = 0.0;
   out_5053584943541973484[17] = 0.0;
   out_5053584943541973484[18] = 0.0;
   out_5053584943541973484[19] = 1.0;
   out_5053584943541973484[20] = 0.0;
   out_5053584943541973484[21] = 0.0;
   out_5053584943541973484[22] = 0.0;
   out_5053584943541973484[23] = 0.0;
   out_5053584943541973484[24] = 0.0;
   out_5053584943541973484[25] = 0.0;
   out_5053584943541973484[26] = 0.0;
   out_5053584943541973484[27] = 0.0;
   out_5053584943541973484[28] = 0.0;
   out_5053584943541973484[29] = 0.0;
   out_5053584943541973484[30] = 0.0;
   out_5053584943541973484[31] = 0.0;
   out_5053584943541973484[32] = 0.0;
   out_5053584943541973484[33] = 0.0;
   out_5053584943541973484[34] = 0.0;
   out_5053584943541973484[35] = 0.0;
   out_5053584943541973484[36] = 0.0;
   out_5053584943541973484[37] = 0.0;
   out_5053584943541973484[38] = 1.0;
   out_5053584943541973484[39] = 0.0;
   out_5053584943541973484[40] = 0.0;
   out_5053584943541973484[41] = 0.0;
   out_5053584943541973484[42] = 0.0;
   out_5053584943541973484[43] = 0.0;
   out_5053584943541973484[44] = 0.0;
   out_5053584943541973484[45] = 0.0;
   out_5053584943541973484[46] = 0.0;
   out_5053584943541973484[47] = 0.0;
   out_5053584943541973484[48] = 0.0;
   out_5053584943541973484[49] = 0.0;
   out_5053584943541973484[50] = 0.0;
   out_5053584943541973484[51] = 0.0;
   out_5053584943541973484[52] = 0.0;
   out_5053584943541973484[53] = 0.0;
   out_5053584943541973484[54] = 0.0;
   out_5053584943541973484[55] = 0.0;
   out_5053584943541973484[56] = 0.0;
   out_5053584943541973484[57] = 1.0;
   out_5053584943541973484[58] = 0.0;
   out_5053584943541973484[59] = 0.0;
   out_5053584943541973484[60] = 0.0;
   out_5053584943541973484[61] = 0.0;
   out_5053584943541973484[62] = 0.0;
   out_5053584943541973484[63] = 0.0;
   out_5053584943541973484[64] = 0.0;
   out_5053584943541973484[65] = 0.0;
   out_5053584943541973484[66] = 0.0;
   out_5053584943541973484[67] = 0.0;
   out_5053584943541973484[68] = 0.0;
   out_5053584943541973484[69] = 0.0;
   out_5053584943541973484[70] = 0.0;
   out_5053584943541973484[71] = 0.0;
   out_5053584943541973484[72] = 0.0;
   out_5053584943541973484[73] = 0.0;
   out_5053584943541973484[74] = 0.0;
   out_5053584943541973484[75] = 0.0;
   out_5053584943541973484[76] = 1.0;
   out_5053584943541973484[77] = 0.0;
   out_5053584943541973484[78] = 0.0;
   out_5053584943541973484[79] = 0.0;
   out_5053584943541973484[80] = 0.0;
   out_5053584943541973484[81] = 0.0;
   out_5053584943541973484[82] = 0.0;
   out_5053584943541973484[83] = 0.0;
   out_5053584943541973484[84] = 0.0;
   out_5053584943541973484[85] = 0.0;
   out_5053584943541973484[86] = 0.0;
   out_5053584943541973484[87] = 0.0;
   out_5053584943541973484[88] = 0.0;
   out_5053584943541973484[89] = 0.0;
   out_5053584943541973484[90] = 0.0;
   out_5053584943541973484[91] = 0.0;
   out_5053584943541973484[92] = 0.0;
   out_5053584943541973484[93] = 0.0;
   out_5053584943541973484[94] = 0.0;
   out_5053584943541973484[95] = 1.0;
   out_5053584943541973484[96] = 0.0;
   out_5053584943541973484[97] = 0.0;
   out_5053584943541973484[98] = 0.0;
   out_5053584943541973484[99] = 0.0;
   out_5053584943541973484[100] = 0.0;
   out_5053584943541973484[101] = 0.0;
   out_5053584943541973484[102] = 0.0;
   out_5053584943541973484[103] = 0.0;
   out_5053584943541973484[104] = 0.0;
   out_5053584943541973484[105] = 0.0;
   out_5053584943541973484[106] = 0.0;
   out_5053584943541973484[107] = 0.0;
   out_5053584943541973484[108] = 0.0;
   out_5053584943541973484[109] = 0.0;
   out_5053584943541973484[110] = 0.0;
   out_5053584943541973484[111] = 0.0;
   out_5053584943541973484[112] = 0.0;
   out_5053584943541973484[113] = 0.0;
   out_5053584943541973484[114] = 1.0;
   out_5053584943541973484[115] = 0.0;
   out_5053584943541973484[116] = 0.0;
   out_5053584943541973484[117] = 0.0;
   out_5053584943541973484[118] = 0.0;
   out_5053584943541973484[119] = 0.0;
   out_5053584943541973484[120] = 0.0;
   out_5053584943541973484[121] = 0.0;
   out_5053584943541973484[122] = 0.0;
   out_5053584943541973484[123] = 0.0;
   out_5053584943541973484[124] = 0.0;
   out_5053584943541973484[125] = 0.0;
   out_5053584943541973484[126] = 0.0;
   out_5053584943541973484[127] = 0.0;
   out_5053584943541973484[128] = 0.0;
   out_5053584943541973484[129] = 0.0;
   out_5053584943541973484[130] = 0.0;
   out_5053584943541973484[131] = 0.0;
   out_5053584943541973484[132] = 0.0;
   out_5053584943541973484[133] = 1.0;
   out_5053584943541973484[134] = 0.0;
   out_5053584943541973484[135] = 0.0;
   out_5053584943541973484[136] = 0.0;
   out_5053584943541973484[137] = 0.0;
   out_5053584943541973484[138] = 0.0;
   out_5053584943541973484[139] = 0.0;
   out_5053584943541973484[140] = 0.0;
   out_5053584943541973484[141] = 0.0;
   out_5053584943541973484[142] = 0.0;
   out_5053584943541973484[143] = 0.0;
   out_5053584943541973484[144] = 0.0;
   out_5053584943541973484[145] = 0.0;
   out_5053584943541973484[146] = 0.0;
   out_5053584943541973484[147] = 0.0;
   out_5053584943541973484[148] = 0.0;
   out_5053584943541973484[149] = 0.0;
   out_5053584943541973484[150] = 0.0;
   out_5053584943541973484[151] = 0.0;
   out_5053584943541973484[152] = 1.0;
   out_5053584943541973484[153] = 0.0;
   out_5053584943541973484[154] = 0.0;
   out_5053584943541973484[155] = 0.0;
   out_5053584943541973484[156] = 0.0;
   out_5053584943541973484[157] = 0.0;
   out_5053584943541973484[158] = 0.0;
   out_5053584943541973484[159] = 0.0;
   out_5053584943541973484[160] = 0.0;
   out_5053584943541973484[161] = 0.0;
   out_5053584943541973484[162] = 0.0;
   out_5053584943541973484[163] = 0.0;
   out_5053584943541973484[164] = 0.0;
   out_5053584943541973484[165] = 0.0;
   out_5053584943541973484[166] = 0.0;
   out_5053584943541973484[167] = 0.0;
   out_5053584943541973484[168] = 0.0;
   out_5053584943541973484[169] = 0.0;
   out_5053584943541973484[170] = 0.0;
   out_5053584943541973484[171] = 1.0;
   out_5053584943541973484[172] = 0.0;
   out_5053584943541973484[173] = 0.0;
   out_5053584943541973484[174] = 0.0;
   out_5053584943541973484[175] = 0.0;
   out_5053584943541973484[176] = 0.0;
   out_5053584943541973484[177] = 0.0;
   out_5053584943541973484[178] = 0.0;
   out_5053584943541973484[179] = 0.0;
   out_5053584943541973484[180] = 0.0;
   out_5053584943541973484[181] = 0.0;
   out_5053584943541973484[182] = 0.0;
   out_5053584943541973484[183] = 0.0;
   out_5053584943541973484[184] = 0.0;
   out_5053584943541973484[185] = 0.0;
   out_5053584943541973484[186] = 0.0;
   out_5053584943541973484[187] = 0.0;
   out_5053584943541973484[188] = 0.0;
   out_5053584943541973484[189] = 0.0;
   out_5053584943541973484[190] = 1.0;
   out_5053584943541973484[191] = 0.0;
   out_5053584943541973484[192] = 0.0;
   out_5053584943541973484[193] = 0.0;
   out_5053584943541973484[194] = 0.0;
   out_5053584943541973484[195] = 0.0;
   out_5053584943541973484[196] = 0.0;
   out_5053584943541973484[197] = 0.0;
   out_5053584943541973484[198] = 0.0;
   out_5053584943541973484[199] = 0.0;
   out_5053584943541973484[200] = 0.0;
   out_5053584943541973484[201] = 0.0;
   out_5053584943541973484[202] = 0.0;
   out_5053584943541973484[203] = 0.0;
   out_5053584943541973484[204] = 0.0;
   out_5053584943541973484[205] = 0.0;
   out_5053584943541973484[206] = 0.0;
   out_5053584943541973484[207] = 0.0;
   out_5053584943541973484[208] = 0.0;
   out_5053584943541973484[209] = 1.0;
   out_5053584943541973484[210] = 0.0;
   out_5053584943541973484[211] = 0.0;
   out_5053584943541973484[212] = 0.0;
   out_5053584943541973484[213] = 0.0;
   out_5053584943541973484[214] = 0.0;
   out_5053584943541973484[215] = 0.0;
   out_5053584943541973484[216] = 0.0;
   out_5053584943541973484[217] = 0.0;
   out_5053584943541973484[218] = 0.0;
   out_5053584943541973484[219] = 0.0;
   out_5053584943541973484[220] = 0.0;
   out_5053584943541973484[221] = 0.0;
   out_5053584943541973484[222] = 0.0;
   out_5053584943541973484[223] = 0.0;
   out_5053584943541973484[224] = 0.0;
   out_5053584943541973484[225] = 0.0;
   out_5053584943541973484[226] = 0.0;
   out_5053584943541973484[227] = 0.0;
   out_5053584943541973484[228] = 1.0;
   out_5053584943541973484[229] = 0.0;
   out_5053584943541973484[230] = 0.0;
   out_5053584943541973484[231] = 0.0;
   out_5053584943541973484[232] = 0.0;
   out_5053584943541973484[233] = 0.0;
   out_5053584943541973484[234] = 0.0;
   out_5053584943541973484[235] = 0.0;
   out_5053584943541973484[236] = 0.0;
   out_5053584943541973484[237] = 0.0;
   out_5053584943541973484[238] = 0.0;
   out_5053584943541973484[239] = 0.0;
   out_5053584943541973484[240] = 0.0;
   out_5053584943541973484[241] = 0.0;
   out_5053584943541973484[242] = 0.0;
   out_5053584943541973484[243] = 0.0;
   out_5053584943541973484[244] = 0.0;
   out_5053584943541973484[245] = 0.0;
   out_5053584943541973484[246] = 0.0;
   out_5053584943541973484[247] = 1.0;
   out_5053584943541973484[248] = 0.0;
   out_5053584943541973484[249] = 0.0;
   out_5053584943541973484[250] = 0.0;
   out_5053584943541973484[251] = 0.0;
   out_5053584943541973484[252] = 0.0;
   out_5053584943541973484[253] = 0.0;
   out_5053584943541973484[254] = 0.0;
   out_5053584943541973484[255] = 0.0;
   out_5053584943541973484[256] = 0.0;
   out_5053584943541973484[257] = 0.0;
   out_5053584943541973484[258] = 0.0;
   out_5053584943541973484[259] = 0.0;
   out_5053584943541973484[260] = 0.0;
   out_5053584943541973484[261] = 0.0;
   out_5053584943541973484[262] = 0.0;
   out_5053584943541973484[263] = 0.0;
   out_5053584943541973484[264] = 0.0;
   out_5053584943541973484[265] = 0.0;
   out_5053584943541973484[266] = 1.0;
   out_5053584943541973484[267] = 0.0;
   out_5053584943541973484[268] = 0.0;
   out_5053584943541973484[269] = 0.0;
   out_5053584943541973484[270] = 0.0;
   out_5053584943541973484[271] = 0.0;
   out_5053584943541973484[272] = 0.0;
   out_5053584943541973484[273] = 0.0;
   out_5053584943541973484[274] = 0.0;
   out_5053584943541973484[275] = 0.0;
   out_5053584943541973484[276] = 0.0;
   out_5053584943541973484[277] = 0.0;
   out_5053584943541973484[278] = 0.0;
   out_5053584943541973484[279] = 0.0;
   out_5053584943541973484[280] = 0.0;
   out_5053584943541973484[281] = 0.0;
   out_5053584943541973484[282] = 0.0;
   out_5053584943541973484[283] = 0.0;
   out_5053584943541973484[284] = 0.0;
   out_5053584943541973484[285] = 1.0;
   out_5053584943541973484[286] = 0.0;
   out_5053584943541973484[287] = 0.0;
   out_5053584943541973484[288] = 0.0;
   out_5053584943541973484[289] = 0.0;
   out_5053584943541973484[290] = 0.0;
   out_5053584943541973484[291] = 0.0;
   out_5053584943541973484[292] = 0.0;
   out_5053584943541973484[293] = 0.0;
   out_5053584943541973484[294] = 0.0;
   out_5053584943541973484[295] = 0.0;
   out_5053584943541973484[296] = 0.0;
   out_5053584943541973484[297] = 0.0;
   out_5053584943541973484[298] = 0.0;
   out_5053584943541973484[299] = 0.0;
   out_5053584943541973484[300] = 0.0;
   out_5053584943541973484[301] = 0.0;
   out_5053584943541973484[302] = 0.0;
   out_5053584943541973484[303] = 0.0;
   out_5053584943541973484[304] = 1.0;
   out_5053584943541973484[305] = 0.0;
   out_5053584943541973484[306] = 0.0;
   out_5053584943541973484[307] = 0.0;
   out_5053584943541973484[308] = 0.0;
   out_5053584943541973484[309] = 0.0;
   out_5053584943541973484[310] = 0.0;
   out_5053584943541973484[311] = 0.0;
   out_5053584943541973484[312] = 0.0;
   out_5053584943541973484[313] = 0.0;
   out_5053584943541973484[314] = 0.0;
   out_5053584943541973484[315] = 0.0;
   out_5053584943541973484[316] = 0.0;
   out_5053584943541973484[317] = 0.0;
   out_5053584943541973484[318] = 0.0;
   out_5053584943541973484[319] = 0.0;
   out_5053584943541973484[320] = 0.0;
   out_5053584943541973484[321] = 0.0;
   out_5053584943541973484[322] = 0.0;
   out_5053584943541973484[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4398664509741735976) {
   out_4398664509741735976[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4398664509741735976[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4398664509741735976[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4398664509741735976[3] = dt*state[12] + state[3];
   out_4398664509741735976[4] = dt*state[13] + state[4];
   out_4398664509741735976[5] = dt*state[14] + state[5];
   out_4398664509741735976[6] = state[6];
   out_4398664509741735976[7] = state[7];
   out_4398664509741735976[8] = state[8];
   out_4398664509741735976[9] = state[9];
   out_4398664509741735976[10] = state[10];
   out_4398664509741735976[11] = state[11];
   out_4398664509741735976[12] = state[12];
   out_4398664509741735976[13] = state[13];
   out_4398664509741735976[14] = state[14];
   out_4398664509741735976[15] = state[15];
   out_4398664509741735976[16] = state[16];
   out_4398664509741735976[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6038848360723463246) {
   out_6038848360723463246[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6038848360723463246[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6038848360723463246[2] = 0;
   out_6038848360723463246[3] = 0;
   out_6038848360723463246[4] = 0;
   out_6038848360723463246[5] = 0;
   out_6038848360723463246[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6038848360723463246[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6038848360723463246[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6038848360723463246[9] = 0;
   out_6038848360723463246[10] = 0;
   out_6038848360723463246[11] = 0;
   out_6038848360723463246[12] = 0;
   out_6038848360723463246[13] = 0;
   out_6038848360723463246[14] = 0;
   out_6038848360723463246[15] = 0;
   out_6038848360723463246[16] = 0;
   out_6038848360723463246[17] = 0;
   out_6038848360723463246[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6038848360723463246[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6038848360723463246[20] = 0;
   out_6038848360723463246[21] = 0;
   out_6038848360723463246[22] = 0;
   out_6038848360723463246[23] = 0;
   out_6038848360723463246[24] = 0;
   out_6038848360723463246[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6038848360723463246[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6038848360723463246[27] = 0;
   out_6038848360723463246[28] = 0;
   out_6038848360723463246[29] = 0;
   out_6038848360723463246[30] = 0;
   out_6038848360723463246[31] = 0;
   out_6038848360723463246[32] = 0;
   out_6038848360723463246[33] = 0;
   out_6038848360723463246[34] = 0;
   out_6038848360723463246[35] = 0;
   out_6038848360723463246[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6038848360723463246[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6038848360723463246[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6038848360723463246[39] = 0;
   out_6038848360723463246[40] = 0;
   out_6038848360723463246[41] = 0;
   out_6038848360723463246[42] = 0;
   out_6038848360723463246[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6038848360723463246[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6038848360723463246[45] = 0;
   out_6038848360723463246[46] = 0;
   out_6038848360723463246[47] = 0;
   out_6038848360723463246[48] = 0;
   out_6038848360723463246[49] = 0;
   out_6038848360723463246[50] = 0;
   out_6038848360723463246[51] = 0;
   out_6038848360723463246[52] = 0;
   out_6038848360723463246[53] = 0;
   out_6038848360723463246[54] = 0;
   out_6038848360723463246[55] = 0;
   out_6038848360723463246[56] = 0;
   out_6038848360723463246[57] = 1;
   out_6038848360723463246[58] = 0;
   out_6038848360723463246[59] = 0;
   out_6038848360723463246[60] = 0;
   out_6038848360723463246[61] = 0;
   out_6038848360723463246[62] = 0;
   out_6038848360723463246[63] = 0;
   out_6038848360723463246[64] = 0;
   out_6038848360723463246[65] = 0;
   out_6038848360723463246[66] = dt;
   out_6038848360723463246[67] = 0;
   out_6038848360723463246[68] = 0;
   out_6038848360723463246[69] = 0;
   out_6038848360723463246[70] = 0;
   out_6038848360723463246[71] = 0;
   out_6038848360723463246[72] = 0;
   out_6038848360723463246[73] = 0;
   out_6038848360723463246[74] = 0;
   out_6038848360723463246[75] = 0;
   out_6038848360723463246[76] = 1;
   out_6038848360723463246[77] = 0;
   out_6038848360723463246[78] = 0;
   out_6038848360723463246[79] = 0;
   out_6038848360723463246[80] = 0;
   out_6038848360723463246[81] = 0;
   out_6038848360723463246[82] = 0;
   out_6038848360723463246[83] = 0;
   out_6038848360723463246[84] = 0;
   out_6038848360723463246[85] = dt;
   out_6038848360723463246[86] = 0;
   out_6038848360723463246[87] = 0;
   out_6038848360723463246[88] = 0;
   out_6038848360723463246[89] = 0;
   out_6038848360723463246[90] = 0;
   out_6038848360723463246[91] = 0;
   out_6038848360723463246[92] = 0;
   out_6038848360723463246[93] = 0;
   out_6038848360723463246[94] = 0;
   out_6038848360723463246[95] = 1;
   out_6038848360723463246[96] = 0;
   out_6038848360723463246[97] = 0;
   out_6038848360723463246[98] = 0;
   out_6038848360723463246[99] = 0;
   out_6038848360723463246[100] = 0;
   out_6038848360723463246[101] = 0;
   out_6038848360723463246[102] = 0;
   out_6038848360723463246[103] = 0;
   out_6038848360723463246[104] = dt;
   out_6038848360723463246[105] = 0;
   out_6038848360723463246[106] = 0;
   out_6038848360723463246[107] = 0;
   out_6038848360723463246[108] = 0;
   out_6038848360723463246[109] = 0;
   out_6038848360723463246[110] = 0;
   out_6038848360723463246[111] = 0;
   out_6038848360723463246[112] = 0;
   out_6038848360723463246[113] = 0;
   out_6038848360723463246[114] = 1;
   out_6038848360723463246[115] = 0;
   out_6038848360723463246[116] = 0;
   out_6038848360723463246[117] = 0;
   out_6038848360723463246[118] = 0;
   out_6038848360723463246[119] = 0;
   out_6038848360723463246[120] = 0;
   out_6038848360723463246[121] = 0;
   out_6038848360723463246[122] = 0;
   out_6038848360723463246[123] = 0;
   out_6038848360723463246[124] = 0;
   out_6038848360723463246[125] = 0;
   out_6038848360723463246[126] = 0;
   out_6038848360723463246[127] = 0;
   out_6038848360723463246[128] = 0;
   out_6038848360723463246[129] = 0;
   out_6038848360723463246[130] = 0;
   out_6038848360723463246[131] = 0;
   out_6038848360723463246[132] = 0;
   out_6038848360723463246[133] = 1;
   out_6038848360723463246[134] = 0;
   out_6038848360723463246[135] = 0;
   out_6038848360723463246[136] = 0;
   out_6038848360723463246[137] = 0;
   out_6038848360723463246[138] = 0;
   out_6038848360723463246[139] = 0;
   out_6038848360723463246[140] = 0;
   out_6038848360723463246[141] = 0;
   out_6038848360723463246[142] = 0;
   out_6038848360723463246[143] = 0;
   out_6038848360723463246[144] = 0;
   out_6038848360723463246[145] = 0;
   out_6038848360723463246[146] = 0;
   out_6038848360723463246[147] = 0;
   out_6038848360723463246[148] = 0;
   out_6038848360723463246[149] = 0;
   out_6038848360723463246[150] = 0;
   out_6038848360723463246[151] = 0;
   out_6038848360723463246[152] = 1;
   out_6038848360723463246[153] = 0;
   out_6038848360723463246[154] = 0;
   out_6038848360723463246[155] = 0;
   out_6038848360723463246[156] = 0;
   out_6038848360723463246[157] = 0;
   out_6038848360723463246[158] = 0;
   out_6038848360723463246[159] = 0;
   out_6038848360723463246[160] = 0;
   out_6038848360723463246[161] = 0;
   out_6038848360723463246[162] = 0;
   out_6038848360723463246[163] = 0;
   out_6038848360723463246[164] = 0;
   out_6038848360723463246[165] = 0;
   out_6038848360723463246[166] = 0;
   out_6038848360723463246[167] = 0;
   out_6038848360723463246[168] = 0;
   out_6038848360723463246[169] = 0;
   out_6038848360723463246[170] = 0;
   out_6038848360723463246[171] = 1;
   out_6038848360723463246[172] = 0;
   out_6038848360723463246[173] = 0;
   out_6038848360723463246[174] = 0;
   out_6038848360723463246[175] = 0;
   out_6038848360723463246[176] = 0;
   out_6038848360723463246[177] = 0;
   out_6038848360723463246[178] = 0;
   out_6038848360723463246[179] = 0;
   out_6038848360723463246[180] = 0;
   out_6038848360723463246[181] = 0;
   out_6038848360723463246[182] = 0;
   out_6038848360723463246[183] = 0;
   out_6038848360723463246[184] = 0;
   out_6038848360723463246[185] = 0;
   out_6038848360723463246[186] = 0;
   out_6038848360723463246[187] = 0;
   out_6038848360723463246[188] = 0;
   out_6038848360723463246[189] = 0;
   out_6038848360723463246[190] = 1;
   out_6038848360723463246[191] = 0;
   out_6038848360723463246[192] = 0;
   out_6038848360723463246[193] = 0;
   out_6038848360723463246[194] = 0;
   out_6038848360723463246[195] = 0;
   out_6038848360723463246[196] = 0;
   out_6038848360723463246[197] = 0;
   out_6038848360723463246[198] = 0;
   out_6038848360723463246[199] = 0;
   out_6038848360723463246[200] = 0;
   out_6038848360723463246[201] = 0;
   out_6038848360723463246[202] = 0;
   out_6038848360723463246[203] = 0;
   out_6038848360723463246[204] = 0;
   out_6038848360723463246[205] = 0;
   out_6038848360723463246[206] = 0;
   out_6038848360723463246[207] = 0;
   out_6038848360723463246[208] = 0;
   out_6038848360723463246[209] = 1;
   out_6038848360723463246[210] = 0;
   out_6038848360723463246[211] = 0;
   out_6038848360723463246[212] = 0;
   out_6038848360723463246[213] = 0;
   out_6038848360723463246[214] = 0;
   out_6038848360723463246[215] = 0;
   out_6038848360723463246[216] = 0;
   out_6038848360723463246[217] = 0;
   out_6038848360723463246[218] = 0;
   out_6038848360723463246[219] = 0;
   out_6038848360723463246[220] = 0;
   out_6038848360723463246[221] = 0;
   out_6038848360723463246[222] = 0;
   out_6038848360723463246[223] = 0;
   out_6038848360723463246[224] = 0;
   out_6038848360723463246[225] = 0;
   out_6038848360723463246[226] = 0;
   out_6038848360723463246[227] = 0;
   out_6038848360723463246[228] = 1;
   out_6038848360723463246[229] = 0;
   out_6038848360723463246[230] = 0;
   out_6038848360723463246[231] = 0;
   out_6038848360723463246[232] = 0;
   out_6038848360723463246[233] = 0;
   out_6038848360723463246[234] = 0;
   out_6038848360723463246[235] = 0;
   out_6038848360723463246[236] = 0;
   out_6038848360723463246[237] = 0;
   out_6038848360723463246[238] = 0;
   out_6038848360723463246[239] = 0;
   out_6038848360723463246[240] = 0;
   out_6038848360723463246[241] = 0;
   out_6038848360723463246[242] = 0;
   out_6038848360723463246[243] = 0;
   out_6038848360723463246[244] = 0;
   out_6038848360723463246[245] = 0;
   out_6038848360723463246[246] = 0;
   out_6038848360723463246[247] = 1;
   out_6038848360723463246[248] = 0;
   out_6038848360723463246[249] = 0;
   out_6038848360723463246[250] = 0;
   out_6038848360723463246[251] = 0;
   out_6038848360723463246[252] = 0;
   out_6038848360723463246[253] = 0;
   out_6038848360723463246[254] = 0;
   out_6038848360723463246[255] = 0;
   out_6038848360723463246[256] = 0;
   out_6038848360723463246[257] = 0;
   out_6038848360723463246[258] = 0;
   out_6038848360723463246[259] = 0;
   out_6038848360723463246[260] = 0;
   out_6038848360723463246[261] = 0;
   out_6038848360723463246[262] = 0;
   out_6038848360723463246[263] = 0;
   out_6038848360723463246[264] = 0;
   out_6038848360723463246[265] = 0;
   out_6038848360723463246[266] = 1;
   out_6038848360723463246[267] = 0;
   out_6038848360723463246[268] = 0;
   out_6038848360723463246[269] = 0;
   out_6038848360723463246[270] = 0;
   out_6038848360723463246[271] = 0;
   out_6038848360723463246[272] = 0;
   out_6038848360723463246[273] = 0;
   out_6038848360723463246[274] = 0;
   out_6038848360723463246[275] = 0;
   out_6038848360723463246[276] = 0;
   out_6038848360723463246[277] = 0;
   out_6038848360723463246[278] = 0;
   out_6038848360723463246[279] = 0;
   out_6038848360723463246[280] = 0;
   out_6038848360723463246[281] = 0;
   out_6038848360723463246[282] = 0;
   out_6038848360723463246[283] = 0;
   out_6038848360723463246[284] = 0;
   out_6038848360723463246[285] = 1;
   out_6038848360723463246[286] = 0;
   out_6038848360723463246[287] = 0;
   out_6038848360723463246[288] = 0;
   out_6038848360723463246[289] = 0;
   out_6038848360723463246[290] = 0;
   out_6038848360723463246[291] = 0;
   out_6038848360723463246[292] = 0;
   out_6038848360723463246[293] = 0;
   out_6038848360723463246[294] = 0;
   out_6038848360723463246[295] = 0;
   out_6038848360723463246[296] = 0;
   out_6038848360723463246[297] = 0;
   out_6038848360723463246[298] = 0;
   out_6038848360723463246[299] = 0;
   out_6038848360723463246[300] = 0;
   out_6038848360723463246[301] = 0;
   out_6038848360723463246[302] = 0;
   out_6038848360723463246[303] = 0;
   out_6038848360723463246[304] = 1;
   out_6038848360723463246[305] = 0;
   out_6038848360723463246[306] = 0;
   out_6038848360723463246[307] = 0;
   out_6038848360723463246[308] = 0;
   out_6038848360723463246[309] = 0;
   out_6038848360723463246[310] = 0;
   out_6038848360723463246[311] = 0;
   out_6038848360723463246[312] = 0;
   out_6038848360723463246[313] = 0;
   out_6038848360723463246[314] = 0;
   out_6038848360723463246[315] = 0;
   out_6038848360723463246[316] = 0;
   out_6038848360723463246[317] = 0;
   out_6038848360723463246[318] = 0;
   out_6038848360723463246[319] = 0;
   out_6038848360723463246[320] = 0;
   out_6038848360723463246[321] = 0;
   out_6038848360723463246[322] = 0;
   out_6038848360723463246[323] = 1;
}
void h_4(double *state, double *unused, double *out_1967691091348868206) {
   out_1967691091348868206[0] = state[6] + state[9];
   out_1967691091348868206[1] = state[7] + state[10];
   out_1967691091348868206[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6873283669448270345) {
   out_6873283669448270345[0] = 0;
   out_6873283669448270345[1] = 0;
   out_6873283669448270345[2] = 0;
   out_6873283669448270345[3] = 0;
   out_6873283669448270345[4] = 0;
   out_6873283669448270345[5] = 0;
   out_6873283669448270345[6] = 1;
   out_6873283669448270345[7] = 0;
   out_6873283669448270345[8] = 0;
   out_6873283669448270345[9] = 1;
   out_6873283669448270345[10] = 0;
   out_6873283669448270345[11] = 0;
   out_6873283669448270345[12] = 0;
   out_6873283669448270345[13] = 0;
   out_6873283669448270345[14] = 0;
   out_6873283669448270345[15] = 0;
   out_6873283669448270345[16] = 0;
   out_6873283669448270345[17] = 0;
   out_6873283669448270345[18] = 0;
   out_6873283669448270345[19] = 0;
   out_6873283669448270345[20] = 0;
   out_6873283669448270345[21] = 0;
   out_6873283669448270345[22] = 0;
   out_6873283669448270345[23] = 0;
   out_6873283669448270345[24] = 0;
   out_6873283669448270345[25] = 1;
   out_6873283669448270345[26] = 0;
   out_6873283669448270345[27] = 0;
   out_6873283669448270345[28] = 1;
   out_6873283669448270345[29] = 0;
   out_6873283669448270345[30] = 0;
   out_6873283669448270345[31] = 0;
   out_6873283669448270345[32] = 0;
   out_6873283669448270345[33] = 0;
   out_6873283669448270345[34] = 0;
   out_6873283669448270345[35] = 0;
   out_6873283669448270345[36] = 0;
   out_6873283669448270345[37] = 0;
   out_6873283669448270345[38] = 0;
   out_6873283669448270345[39] = 0;
   out_6873283669448270345[40] = 0;
   out_6873283669448270345[41] = 0;
   out_6873283669448270345[42] = 0;
   out_6873283669448270345[43] = 0;
   out_6873283669448270345[44] = 1;
   out_6873283669448270345[45] = 0;
   out_6873283669448270345[46] = 0;
   out_6873283669448270345[47] = 1;
   out_6873283669448270345[48] = 0;
   out_6873283669448270345[49] = 0;
   out_6873283669448270345[50] = 0;
   out_6873283669448270345[51] = 0;
   out_6873283669448270345[52] = 0;
   out_6873283669448270345[53] = 0;
}
void h_10(double *state, double *unused, double *out_4208360954594629467) {
   out_4208360954594629467[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4208360954594629467[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4208360954594629467[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4681463386096154266) {
   out_4681463386096154266[0] = 0;
   out_4681463386096154266[1] = 9.8100000000000005*cos(state[1]);
   out_4681463386096154266[2] = 0;
   out_4681463386096154266[3] = 0;
   out_4681463386096154266[4] = -state[8];
   out_4681463386096154266[5] = state[7];
   out_4681463386096154266[6] = 0;
   out_4681463386096154266[7] = state[5];
   out_4681463386096154266[8] = -state[4];
   out_4681463386096154266[9] = 0;
   out_4681463386096154266[10] = 0;
   out_4681463386096154266[11] = 0;
   out_4681463386096154266[12] = 1;
   out_4681463386096154266[13] = 0;
   out_4681463386096154266[14] = 0;
   out_4681463386096154266[15] = 1;
   out_4681463386096154266[16] = 0;
   out_4681463386096154266[17] = 0;
   out_4681463386096154266[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4681463386096154266[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4681463386096154266[20] = 0;
   out_4681463386096154266[21] = state[8];
   out_4681463386096154266[22] = 0;
   out_4681463386096154266[23] = -state[6];
   out_4681463386096154266[24] = -state[5];
   out_4681463386096154266[25] = 0;
   out_4681463386096154266[26] = state[3];
   out_4681463386096154266[27] = 0;
   out_4681463386096154266[28] = 0;
   out_4681463386096154266[29] = 0;
   out_4681463386096154266[30] = 0;
   out_4681463386096154266[31] = 1;
   out_4681463386096154266[32] = 0;
   out_4681463386096154266[33] = 0;
   out_4681463386096154266[34] = 1;
   out_4681463386096154266[35] = 0;
   out_4681463386096154266[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4681463386096154266[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4681463386096154266[38] = 0;
   out_4681463386096154266[39] = -state[7];
   out_4681463386096154266[40] = state[6];
   out_4681463386096154266[41] = 0;
   out_4681463386096154266[42] = state[4];
   out_4681463386096154266[43] = -state[3];
   out_4681463386096154266[44] = 0;
   out_4681463386096154266[45] = 0;
   out_4681463386096154266[46] = 0;
   out_4681463386096154266[47] = 0;
   out_4681463386096154266[48] = 0;
   out_4681463386096154266[49] = 0;
   out_4681463386096154266[50] = 1;
   out_4681463386096154266[51] = 0;
   out_4681463386096154266[52] = 0;
   out_4681463386096154266[53] = 1;
}
void h_13(double *state, double *unused, double *out_2556445490971921155) {
   out_2556445490971921155[0] = state[3];
   out_2556445490971921155[1] = state[4];
   out_2556445490971921155[2] = state[5];
}
void H_13(double *state, double *unused, double *out_737347538868430584) {
   out_737347538868430584[0] = 0;
   out_737347538868430584[1] = 0;
   out_737347538868430584[2] = 0;
   out_737347538868430584[3] = 1;
   out_737347538868430584[4] = 0;
   out_737347538868430584[5] = 0;
   out_737347538868430584[6] = 0;
   out_737347538868430584[7] = 0;
   out_737347538868430584[8] = 0;
   out_737347538868430584[9] = 0;
   out_737347538868430584[10] = 0;
   out_737347538868430584[11] = 0;
   out_737347538868430584[12] = 0;
   out_737347538868430584[13] = 0;
   out_737347538868430584[14] = 0;
   out_737347538868430584[15] = 0;
   out_737347538868430584[16] = 0;
   out_737347538868430584[17] = 0;
   out_737347538868430584[18] = 0;
   out_737347538868430584[19] = 0;
   out_737347538868430584[20] = 0;
   out_737347538868430584[21] = 0;
   out_737347538868430584[22] = 1;
   out_737347538868430584[23] = 0;
   out_737347538868430584[24] = 0;
   out_737347538868430584[25] = 0;
   out_737347538868430584[26] = 0;
   out_737347538868430584[27] = 0;
   out_737347538868430584[28] = 0;
   out_737347538868430584[29] = 0;
   out_737347538868430584[30] = 0;
   out_737347538868430584[31] = 0;
   out_737347538868430584[32] = 0;
   out_737347538868430584[33] = 0;
   out_737347538868430584[34] = 0;
   out_737347538868430584[35] = 0;
   out_737347538868430584[36] = 0;
   out_737347538868430584[37] = 0;
   out_737347538868430584[38] = 0;
   out_737347538868430584[39] = 0;
   out_737347538868430584[40] = 0;
   out_737347538868430584[41] = 1;
   out_737347538868430584[42] = 0;
   out_737347538868430584[43] = 0;
   out_737347538868430584[44] = 0;
   out_737347538868430584[45] = 0;
   out_737347538868430584[46] = 0;
   out_737347538868430584[47] = 0;
   out_737347538868430584[48] = 0;
   out_737347538868430584[49] = 0;
   out_737347538868430584[50] = 0;
   out_737347538868430584[51] = 0;
   out_737347538868430584[52] = 0;
   out_737347538868430584[53] = 0;
}
void h_14(double *state, double *unused, double *out_705003315889852073) {
   out_705003315889852073[0] = state[6];
   out_705003315889852073[1] = state[7];
   out_705003315889852073[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8490671971965908975) {
   out_8490671971965908975[0] = 0;
   out_8490671971965908975[1] = 0;
   out_8490671971965908975[2] = 0;
   out_8490671971965908975[3] = 0;
   out_8490671971965908975[4] = 0;
   out_8490671971965908975[5] = 0;
   out_8490671971965908975[6] = 1;
   out_8490671971965908975[7] = 0;
   out_8490671971965908975[8] = 0;
   out_8490671971965908975[9] = 0;
   out_8490671971965908975[10] = 0;
   out_8490671971965908975[11] = 0;
   out_8490671971965908975[12] = 0;
   out_8490671971965908975[13] = 0;
   out_8490671971965908975[14] = 0;
   out_8490671971965908975[15] = 0;
   out_8490671971965908975[16] = 0;
   out_8490671971965908975[17] = 0;
   out_8490671971965908975[18] = 0;
   out_8490671971965908975[19] = 0;
   out_8490671971965908975[20] = 0;
   out_8490671971965908975[21] = 0;
   out_8490671971965908975[22] = 0;
   out_8490671971965908975[23] = 0;
   out_8490671971965908975[24] = 0;
   out_8490671971965908975[25] = 1;
   out_8490671971965908975[26] = 0;
   out_8490671971965908975[27] = 0;
   out_8490671971965908975[28] = 0;
   out_8490671971965908975[29] = 0;
   out_8490671971965908975[30] = 0;
   out_8490671971965908975[31] = 0;
   out_8490671971965908975[32] = 0;
   out_8490671971965908975[33] = 0;
   out_8490671971965908975[34] = 0;
   out_8490671971965908975[35] = 0;
   out_8490671971965908975[36] = 0;
   out_8490671971965908975[37] = 0;
   out_8490671971965908975[38] = 0;
   out_8490671971965908975[39] = 0;
   out_8490671971965908975[40] = 0;
   out_8490671971965908975[41] = 0;
   out_8490671971965908975[42] = 0;
   out_8490671971965908975[43] = 0;
   out_8490671971965908975[44] = 1;
   out_8490671971965908975[45] = 0;
   out_8490671971965908975[46] = 0;
   out_8490671971965908975[47] = 0;
   out_8490671971965908975[48] = 0;
   out_8490671971965908975[49] = 0;
   out_8490671971965908975[50] = 0;
   out_8490671971965908975[51] = 0;
   out_8490671971965908975[52] = 0;
   out_8490671971965908975[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_4629685827320122449) {
  err_fun(nom_x, delta_x, out_4629685827320122449);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8757749050678507284) {
  inv_err_fun(nom_x, true_x, out_8757749050678507284);
}
void pose_H_mod_fun(double *state, double *out_5053584943541973484) {
  H_mod_fun(state, out_5053584943541973484);
}
void pose_f_fun(double *state, double dt, double *out_4398664509741735976) {
  f_fun(state,  dt, out_4398664509741735976);
}
void pose_F_fun(double *state, double dt, double *out_6038848360723463246) {
  F_fun(state,  dt, out_6038848360723463246);
}
void pose_h_4(double *state, double *unused, double *out_1967691091348868206) {
  h_4(state, unused, out_1967691091348868206);
}
void pose_H_4(double *state, double *unused, double *out_6873283669448270345) {
  H_4(state, unused, out_6873283669448270345);
}
void pose_h_10(double *state, double *unused, double *out_4208360954594629467) {
  h_10(state, unused, out_4208360954594629467);
}
void pose_H_10(double *state, double *unused, double *out_4681463386096154266) {
  H_10(state, unused, out_4681463386096154266);
}
void pose_h_13(double *state, double *unused, double *out_2556445490971921155) {
  h_13(state, unused, out_2556445490971921155);
}
void pose_H_13(double *state, double *unused, double *out_737347538868430584) {
  H_13(state, unused, out_737347538868430584);
}
void pose_h_14(double *state, double *unused, double *out_705003315889852073) {
  h_14(state, unused, out_705003315889852073);
}
void pose_H_14(double *state, double *unused, double *out_8490671971965908975) {
  H_14(state, unused, out_8490671971965908975);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
