// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "mips_wrapper_hw.h"
#include "mips.h"

void
mips_top(hls::stream<unsigned int> &slave,
		 hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  static int A[8];
  static int B[8];

  for(int i=0; i != 8; i++)  
    A[i] = slave.read();

  int _ret = mips(A, B);
  
  master.write(_ret);
  
  for(int i=0; i != 8; i++)
	master.write(B[i]);
}
