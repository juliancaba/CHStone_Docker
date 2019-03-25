// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "jpeg_wrapper_hw.h"
#include "jpeg.h"

#define RGB_NUM  3
#define BMP_OUT_SIZE  (90 * 59)

void
jpeg(hls::stream<unsigned int> &slave,
	 hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master


  //static unsigned char in_i[JPEGSIZE];
  static unsigned char out_i[RGB_NUM][BMP_OUT_SIZE];
  static int width, height;
	
  // for(int i=0; i != JPEGSIZE; i+=4){
  // 	unsigned char c_aux[4];
  // 	toSequence8_int(slave.read(), c_aux);
  // 	in_i[i] = c_aux[0];
  // 	in_i[i+1] = c_aux[1];
  // 	in_i[i+2] = c_aux[2];
  // 	in_i[i+3] = c_aux[3];
  // }
	  
  jpeg_read (hana_jpg, &width, &height, out_i);

  master.write(width);
  master.write(height);
  
  // for(int i=0; i != RGB_NUM; i++)
  // 	for(int j=0; j != BMP_OUT_SIZE; j+=4)
  // 	  master.write((out_i[i][j]<<24) | (out_i[j][j+1]<<16) | (out_i[i][j+2]<<8) | out_i[i][j+3]);
  
}
