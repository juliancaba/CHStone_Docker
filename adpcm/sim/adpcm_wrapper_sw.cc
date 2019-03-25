#include "adpcm_wrapper_sw.h"
#include "adpcm_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"



void
reset_wrapper ()
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x00000000);

  adpcm(input, output);
}



int
encode_wrapper (int i1, int i2)
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x1);
  input.write(i1);
  input.write(i2);

  adpcm(input, output);

  return output.read();
}


void
decode_wrapper (int inputp, int *xout1, int *xout2)
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x2);
  input.write(inputp);

  adpcm(input, output);

  *xout1 = output.read();
  *xout2 = output.read();
}
