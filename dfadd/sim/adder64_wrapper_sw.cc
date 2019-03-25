#include "adder64_wrapper_sw.h"
#include "adder64_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"

union convertLL{
  unsigned int i[2];
  float64 ll;
};


float64
castOutput(int i1, int i2)
{
  union convertLL castingLL;
  castingLL.i[0] = i1;
  castingLL.i[1] = i2;

  return castingLL.ll;  
}

  
float64
adder64_wrapper(float64 a, float64 b)
{
  float64 _ret = 0x0UL;

  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;
  
  union convertLL castingLL;
  castingLL.ll = a;
  input.write(castingLL.i[0]);
  input.write(castingLL.i[1]);
  castingLL.ll = b;
  input.write(castingLL.i[0]);
  input.write(castingLL.i[1]);

  adder64(input, output);
  
  unsigned int ret1, ret2;
  ret1 = output.read();
  ret2 = output.read();

  float64 t1, t2;

  t1 = (float64)ret1;
  t2 = (float64)ret2;
  _ret = (t1<<32) | t2;
  
  return _ret;  
}

