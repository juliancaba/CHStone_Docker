#ifndef ADPCM_H
#define ADPCM_H

int encode_wrapper (int, int);
void decode_wrapper (int input, int *xout1, int *xout2);
void reset_wrapper ();


#endif
