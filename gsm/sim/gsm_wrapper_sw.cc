#include "gsm_wrapper_sw.h"
#include "gsm_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"

void
Gsm_LPC_Analysis_wrapper (word s[N], word LARc[M])
{
  int head1, head2;
  float _ret;

  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  int i;
  for(i=0; i != N; i+=2)
    input.write((s[i]<<16) | (s[i+1] & 0xFFFF));
  
  gsm(input, output);

  int tmp;
  for(i=0; i != N; i+=2){
    tmp = output.read();
    s[i] = (tmp >>16)&0xFFFF;
    s[i+1] = tmp;
  }
  
  for(i=0; i != M; i+=2){
    tmp = output.read();
    LARc[i] = (tmp >>16) & 0xFFFF;
    LARc[i+1] = tmp;
  }
}
