#include "blowfish_wrapper_sw.h"
#include "blowfish_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"

#define N 40

#define KEYSIZE 5200


void
BF_set_key_wrapper (int len, unsigned char *data)
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;
  
  input.write(0x1);
  input.write(len);
  
  for(int i=0; i != 8; i+=4)
    input.write((data[i]<<24) | (data[i+1]<<16) | (data[i+2]<<8) | data[i+3]);
    
  blowfish(input, output);
}


void BF_cfb64_encrypt_wrapper (unsigned char *in, unsigned char *out, long length,
		       unsigned char *ivec, int *num, int encrypt)
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;
  
  input.write(0x2);
  
  input.write(length);
  input.write(*num);
  input.write(encrypt);
  
  for(int i=0; i != N; i+=4)
    input.write((in[i]<<24) | (in[i+1]<<16) | (in[i+2]<<8) | in[i+3]);
      
  blowfish(input, output);
  
  for(int i=0; i != N; i+=4){
    unsigned char *ptr;
    int aux = output.read();
    ptr=(unsigned char *) &aux;
    out[i+3] = *ptr++;
    out[i+2] = *ptr++;
    out[i+1] = *ptr++;
    out[i+0] = *ptr++;
  }
}
