// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "blowfish_wrapper_hw.h"
#include "blowfish.h"
#include "hls_casting.h"

#define N 40

void
blowfish(hls::stream<unsigned int> &slave,
		 hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  int i,k;
  unsigned char c_aux[4];
  
  
  int op = slave.read();

  if (op == 1){
	int len = slave.read();
	unsigned char data[8];
	for(int i=0; i!=2; i++){
	  toSequence8_int(slave.read(), c_aux);
	  data[i*4+0] = c_aux[0];
	  data[i*4+1] = c_aux[1];
	  data[i*4+2] = c_aux[2];
	  data[i*4+3] = c_aux[3];
	}
	BF_set_key (len, data);
  }
  else{
	int length = slave.read();
	int num = slave.read();
	int encrypt = slave.read();
	static unsigned char in_i[N];
	static unsigned char out_i[N];
	static unsigned char ivec[8];
  
	for(int i=0; i != N; i+=4){
	  unsigned char c_aux[4];
	  toSequence8_int(slave.read(), c_aux);
	  in_i[i] = c_aux[0];
	  in_i[i+1] = c_aux[1];
	  in_i[i+2] = c_aux[2];
	  in_i[i+3] = c_aux[3];
	}
	BF_cfb64_encrypt (in_i, out_i, length, ivec, &num, encrypt);
	
	for(int i=0; i != N; i+=4)
	  master.write((out_i[i]<<24) | (out_i[i+1]<<16) | (out_i[i+2]<<8) | out_i[i+3]);
  }  
}
