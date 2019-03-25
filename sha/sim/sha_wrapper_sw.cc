#include "sha_wrapper_sw.h"
#include "sha_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"



void
sha_wrapper (unsigned int in_i[VSIZE],  unsigned char indata[VSIZE][BLOCK_SIZE], unsigned int outdata[5])
{
  int head1, head2;
  float _ret;

  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  int i,j;
  for(i=0; i != VSIZE; i++)
    input.write(in_i[i]);
  
  for(i=0; i != VSIZE; i++)
    for(j=0; j != BLOCK_SIZE; j+=4)
      input.write((indata[i][j]<<24) | (indata[i][j+1]<<16) | (indata[i][j+2]<<8) | indata[i][j+3]);

  sha(input, output);
  
  for(i=0; i != 5; i++)
    outdata[i] = output.read();
}
