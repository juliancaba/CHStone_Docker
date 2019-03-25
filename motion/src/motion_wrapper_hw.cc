// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "motion_wrapper_hw.h"
#include "motion.h"

void
motion(hls::stream<unsigned int> &slave,
	   hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  int i,j,k;
  int op = slave.read();

  if (op == 1){
	Initialize_Buffer();
  }
  else{


	  //int PMV[2][2][2] = { {{45, 207}, {70, 41}}, {{4, 180}, {120, 216}} };
	  //int motion_vertical_field_select[2][2] = { {232, 200}, {32, 240} };

	static int PMV[2][2][2];
	for (i = 0; i < 2; i++)
	  for (j = 0; j < 2; j++)
		for (k = 0; k < 2; k++)
		  PMV[i][j][k]=slave.read();

	static int dmvector[2];
	for (k = 0; k < 2; k++)
	  dmvector[k]=slave.read();

	static int motion_vertical_field_select[2][2];
	for (j = 0; j < 2; j++)
	  for (k = 0; k < 2; k++)
		motion_vertical_field_select[j][k]=slave.read();


	static int s = slave.read();
	static int motion_vector_count = slave.read();
	static int mv_format = slave.read();
	static int h_r_size = slave.read();
	static int v_r_size = slave.read();
	static int dmv = slave.read();
	static int mvscale = slave.read();

	s = 0;
	motion_vector_count = 1;
	mv_format = 0;
	h_r_size = 200;
	v_r_size = 200;
	dmv = 0;
	mvscale = 1;

	motion_vectors (PMV, dmvector, motion_vertical_field_select, s, motion_vector_count, mv_format, h_r_size, v_r_size, dmv, mvscale);
	
	for (i = 0; i < 2; i++)
	  for (j = 0; j < 2; j++)
		for (k = 0; k < 2; k++)
		  master.write(PMV[i][j][k]);
  
	for (j = 0; j < 2; j++)
	  for (k = 0; k < 2; k++)
		master.write(motion_vertical_field_select[j][k]); 	
  }


}
