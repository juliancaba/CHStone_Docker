#ifndef WRAPPER_H
#define WRAPPER_H

#include "hls_stream.h"

void
sha(hls::stream<unsigned int> &slave,
    hls::stream<unsigned int> &master);

#endif
