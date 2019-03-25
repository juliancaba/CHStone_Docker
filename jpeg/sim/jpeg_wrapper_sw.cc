#include "jpeg_wrapper_sw.h"
#include "jpeg_wrapper_hw.h"
#include <stdio.h>
#include <stdlib.h>     /* atoll */

#include "hls_stream.h"

#include "jpeg.h"

void jpeg_read_wrapper (int *OutData_image_width, int *OutData_image_height)
{
  hls::stream<unsigned int> input;
  hls::stream<unsigned int> output;
    
  // for(int i=0; i != JPEGSIZE; i+=4)
  //   input.write((read_buf[i]<<24) | (read_buf[i+1]<<16) | (read_buf[i+2]<<8) | read_buf[i+3]);
  input.write(1);   
  jpeg(input, output);

  *OutData_image_width = output.read();
  *OutData_image_height = output.read();
  
  // for(int i=0; i != RGB_NUM; i++){
  //   for(int j=0; j != BMP_OUT_SIZE; j+=4){
  //     unsigned char *ptr;
  //     int aux = output.read();
  //     ptr=(unsigned char *) &aux;
  //     OutData_comp_buf[i][j+3] = *ptr++;
  //     OutData_comp_buf[i][j+2] = *ptr++;
  //     OutData_comp_buf[i][j+1] = *ptr++;
  //     OutData_comp_buf[i][j+0] = *ptr++;
  //   }
  // }
}
