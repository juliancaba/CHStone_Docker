#include "mips_wrapper_sw.h"
#include "mips_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"



int
mips_wrapper (int A[8], int B[8])
{
  int _ret;

  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  int i;
  
  for(i=0; i != 8; i++)
    input.write(A[i]);
  
  mips_top(input, output);

  _ret = output.read();
  for(i=0; i != 8; i++)
    B[i] = output.read();
  
  return _ret;
}

