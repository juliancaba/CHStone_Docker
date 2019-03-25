#include "motion_wrapper_sw.h"
#include "motion_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"


void Initialize_Buffer_wrapper ()
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;
  input.write(0x1);
  motion(input, output);
}


void
motion_vectors_wrapper (int PMV[2][2][2], int dmvector[2], int motion_vertical_field_select[2][2],
		  int s, int motion_vector_count, int mv_format, int h_r_size,
		  int v_r_size, int dmv, int mvscale)
{
  int head1, head2;
  float _ret;

  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x2);
  
  int i,j,k;

  for (i = 0; i < 2; i++)
    for (j = 0; j < 2; j++)
      for (k = 0; k < 2; k++)
	input.write(PMV[i][j][k]);
	
  for (k = 0; k < 2; k++)
    input.write(dmvector[k]);

  for (j = 0; j < 2; j++)
    for (k = 0; k < 2; k++)
      input.write(motion_vertical_field_select[j][k]);

  input.write(s);
  input.write(motion_vector_count);
  input.write(mv_format);
  input.write(h_r_size);
  input.write(v_r_size);
  input.write(dmv);
  input.write(mvscale);

  motion(input, output);
  
  for (i = 0; i < 2; i++)
    for (j = 0; j < 2; j++)
      for (k = 0; k < 2; k++)
    	  PMV[i][j][k] = output.read();
  
  for (j = 0; j < 2; j++)
    for (k = 0; k < 2; k++)
      motion_vertical_field_select[j][k] = output.read();  
}
