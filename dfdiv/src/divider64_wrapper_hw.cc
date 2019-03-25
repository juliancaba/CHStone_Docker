// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "divider64_wrapper_hw.h"
#include "softfloat.h"
#include "hls_casting.h"

void
divider64(hls::stream<unsigned int> &slave,
		  hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  float64 a, b;
  unsigned int tmp_ret[2];

  a = toLongLong(slave.read(), slave.read());
  b = toLongLong(slave.read(), slave.read());

  float64 ret = float64_div(a, b);

  toSequence32_ll(ret, tmp_ret);
  master.write(tmp_ret[0]);
  master.write(tmp_ret[1]);   
}
