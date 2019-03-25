#include "aes_wrapper_hw.h"
#include "aes.h"
#include <stdio.h>


void
aes(hls::stream<unsigned int> &slave,
    hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master
#pragma HLS INLINE off

  unsigned int op;
  static int statemt[N];  
  static int key[N];
  static int AESType;  

  op=slave.read();

  for(int it=0; it != N; it++)
    statemt[it] = slave.read();
  for(int it=0; it != N; it++)
    key[it] = slave.read();
  AESType = slave.read();

  if (op==1) //encrypt
    encrypt(statemt, key, AESType);
  else
    decrypt(statemt, key, AESType);
      
  for(int it=0; it != N; it++)
    master.write(statemt[it]);
}
