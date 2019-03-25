#ifndef ADPCM_H
#define ADPCM_H

int encode (int, int);
void decode (int input, int *xout1, int *xout2);
int filtez (int *bpl, int *dlt);
void upzero (int dlt, int *dlti, int *bli);
int filtep (int rlt1, int al1, int rlt2, int al2);
int quantl (int el, int detl);
int logscl (int il, int nbl);
int scalel (int nbl, int shift_constant);
int uppol2 (int al1, int al2, int plt, int plt1, int plt2);
int uppol1 (int al1, int apl2, int plt, int plt1);
int logsch (int ih, int nbh);
void reset ();


#endif
