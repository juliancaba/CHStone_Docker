#include "adpcm_wrapper_hw.h"
#include "adpcm.h"
#include <stdio.h>


void
adpcm(hls::stream<unsigned int> &slave,
      hls::stream<unsigned int> &master)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=slave
#pragma HLS INTERFACE axis port=master

  unsigned int op;

  op=slave.read();

  if (op==1){ //encode
    int aux = encode(slave.read(), slave.read());
    master.write(aux);
  }
  else {
    if(op==2){ //decode
      int o1, o2;
      decode(slave.read(),&o1,&o2);
      master.write(o1);
      master.write(o2);
    }
    else{
      reset();
    }
  }  
}
