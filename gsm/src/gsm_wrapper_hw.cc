// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "gsm_wrapper_hw.h"
#include "gsm.h"
#include "hls_casting.h"

void
gsm(hls::stream<unsigned int> &slave,
	hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  unsigned short s_aux[2];
  unsigned short w32[2];
  static word s[N];
  static word LARc[N];

  for(int i=0; i != N; i+=2){
    toSequence16_int(slave.read(), w32);
    
    s[i] = w32[0];//(w32>>16) & 0xFFFF;//s_aux[0];
    s[i+1] = w32[1];//s_aux[1];
  }
  
  Gsm_LPC_Analysis(s, LARc);
  
  for(int i=0; i != N; i+=2)
    master.write(toInt(s[i],s[i+1]));
  
  for(int i=0; i != M; i+=2) 
    master.write(toInt(LARc[i],LARc[i+1])); 
}
