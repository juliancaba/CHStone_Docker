#include "aes_wrapper_sw.h"
#include "aes_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"

void
encrypt_wrapper (int statemt[N], int key[N], int AESType)
{
  int it;
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x1);
  for(it = 0; it != N; it++)
    input.write(statemt[it]);
  for(it = 0; it != N; it++)
    input.write(key[it]);
  input.write(AESType);

  aes(input, output);

  for(it = 0; it != N; it++)
    statemt[it] = output.read();
}

void
decrypt_wrapper (int statemt[N], int key[N], int AESType)
{
  int it;
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;

  input.write(0x2);
  for(it = 0; it != N; it++)
    input.write(statemt[it]);
  for(it = 0; it != N; it++)
    input.write(key[it]);
  input.write(AESType);
  
  aes(input, output);

  for(it = 0; it != N; it++)
    statemt[it] = output.read();
}
