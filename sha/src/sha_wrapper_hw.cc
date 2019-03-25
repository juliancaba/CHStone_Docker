// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "sha_wrapper_hw.h"
#include "sha.h"
#include "hls_casting.h"

void
sha(hls::stream<unsigned int> &slave,
	hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  int i,k;
  unsigned char c_aux[4];
  
  static unsigned int in_i[VSIZE];
  static unsigned char indata[VSIZE][BLOCK_SIZE];
  static unsigned int outdata[5];
  
  for(i=0; i != VSIZE; i++)  
    in_i[i] = slave.read();

  i=0;k=0;
  for(int j=0; j != sizeof(indata)/4; j++){
    if (j == BLOCK_SIZE/4){
      i++;k=0;
    }
    toSequence8_int(slave.read(), c_aux);
    indata[i][k++] = c_aux[0];
    indata[i][k++] = c_aux[1];
    indata[i][k++] = c_aux[2];
    indata[i][k++] = c_aux[3];
  }

  sha_stream(in_i, indata, outdata);
  
  for(i=0; i != 5; i++)  
    master.write(outdata[i]);   
}
