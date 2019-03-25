#include "hls_casting.h"



union IEEE754_double_precision{
  unsigned char c[8];
  unsigned short s[4];
  unsigned int i[2];
  double d;
  long long ll;
};

union IEEE754_single_precision {
  unsigned int i;
  float f;
};



// Enteros
short
toShort(unsigned char c1, unsigned char c2)
{
  short aux;
  
#ifdef __SYNTHESIS__
  aux = (c2<<8) | c1;
#else
  aux = (c1<<8) | c2;
#endif
  
  return aux;
}

int
toInt(unsigned char c1, unsigned char c2, 
      unsigned char c3, unsigned char c4)
{
  int aux;
  
#ifdef __SYNTHESIS__
  aux = (c4<<24)|(c3<<16)|(c2<<8)|c1;
#else
  aux = (c1<<24)|(c2<<16)|(c3<<8)|c4;
#endif
  
  return aux;
}

int
toInt(unsigned short s1, unsigned short s2)
{  
  int aux;
  
  aux = (s1<<16)|s2;
  
// #ifdef __SYNTHESIS__
//   aux = (s2<<16)|s1;
// #else
//   aux = (s1<<16)|s2;
// #endif
  
  return aux;
}

long long
toLongLong(unsigned char c1, unsigned char c2, 
	   unsigned char c3, unsigned char c4,
	   unsigned char c5, unsigned char c6, 
	   unsigned char c7, unsigned char c8)
{
  long long aux, l1, l2, l3, l4, l5, l6, l7, l8;

  l1 = (long long)c1;
  l2 = (long long)c2;
  l3 = (long long)c3;
  l4 = (long long)c4;
  l5 = (long long)c5;
  l6 = (long long)c6;
  l7 = (long long)c7;
  l8 = (long long)c8;
  
#ifdef __SYNTHESIS__
  aux = (l8<<56) | (l7<<48) | (l6<<40) | (l5<<32) | (l4<<24) | (l3<<16) | (l2<<8) | l1;
#else
  aux = (l1<<56) | (l2<<48) | (l3<<40) | (l4<<32) | (l5<<24) | (l6<<16) | (l7<<8) | l8;
#endif
  
  return aux;
}

long long
toLongLong(unsigned short s1, unsigned short s2, 
	   unsigned short s3, unsigned short s4)
{
  long long aux, l1, l2, l3, l4;

  l1 = (long long)s1;
  l2 = (long long)s2;
  l3 = (long long)s3;
  l4 = (long long)s4;
  
#ifdef __SYNTHESIS__
  aux = (l4<<48) | (l3<<32) | (l2<<16) | l1;
#else
  aux = (l1<<48) | (l2<<32) | (l3<<16) | l4;
#endif
  
  return aux;
}


long long
toLongLong(unsigned int i1, unsigned int i2)
{
  long long aux, l1, l2;

  l1 = (long long)i1;
  l2 = (long long)i2;
  
#ifdef __SYNTHESIS__
    aux = (l2<<32) | l1;
#else
    aux = (l1<<32) | l2;
#endif
   
  return aux;
}





// -----------
//  -- IEEE754
// ------------
float
toFloat(unsigned char c1, unsigned char c2, 
	unsigned char c3, unsigned char c4)
{
  union IEEE754_single_precision castingIEEE754_sp;
#ifdef __SYNTHESIS__
  castingIEEE754_sp.i = (c4<<24)|(c3<<16)|(c2<<8)|c1;
#else
  castingIEEE754_sp.i = (c1<<24)|(c2<<16)|(c3<<8)|c4;
#endif
  return castingIEEE754_sp.f;
}

float
toFloat(unsigned short s1, unsigned short s2)
{
  union IEEE754_single_precision castingIEEE754_sp;
#ifdef __SYNTHESIS__
  castingIEEE754_sp.i = (s2<<16)|s1;
#else
  castingIEEE754_sp.i = (s1<<16)|s2;
#endif
  return castingIEEE754_sp.f;
}

float
toFloat(unsigned int i1)
{
  union IEEE754_single_precision castingIEEE754_sp;
  castingIEEE754_sp.i = i1;
  return castingIEEE754_sp.f;
}


double
toDouble(unsigned char c1, unsigned char c2, 
	 unsigned char c3, unsigned char c4,
	 unsigned char c5, unsigned char c6, 
	 unsigned char c7, unsigned char c8)
{
  union IEEE754_double_precision castingIEEE754_dp;
#ifdef __SYNTHESIS__
  castingIEEE754_dp.i[1] = (c8<<24)|(c7<<16)|(c6<<8)|c5;
  castingIEEE754_dp.i[0] = (c4<<24)|(c3<<16)|(c2<<8)|c1;
#else
  castingIEEE754_dp.i[1] = (c1<<24)|(c2<<16)|(c3<<8)|c4;
  castingIEEE754_dp.i[0] = (c5<<24)|(c6<<16)|(c7<<8)|c8;
#endif
  return castingIEEE754_dp.d; 
  
}

double
toDouble(unsigned short s1, unsigned short s2, 
	 unsigned short s3, unsigned short s4)
{
  union IEEE754_double_precision castingIEEE754_dp;
#ifdef __SYNTHESIS__
  castingIEEE754_dp.i[1] = (s4<<16)|s3;
  castingIEEE754_dp.i[0] = (s2<<16)|s1;
#else
  castingIEEE754_dp.i[1] = (s1<<16)|s2;
  castingIEEE754_dp.i[0] = (s3<<16)|s4;
#endif
  return castingIEEE754_dp.d; 
  
}

double
toDouble(unsigned int i1, unsigned int i2)
{
  union IEEE754_double_precision castingIEEE754_dp;
#ifdef __SYNTHESIS__
  castingIEEE754_dp.i[0] = i1;
  castingIEEE754_dp.i[1] = i2;
#else
  castingIEEE754_dp.i[1] = i1;
  castingIEEE754_dp.i[0] = i2;
#endif
  return castingIEEE754_dp.d; 
  
}


void
toSequence8_float(float n, unsigned char bytes[4])
{
  union IEEE754_single_precision castingIEEE754_sp;
  castingIEEE754_sp.f = n;
  bytes[3] = (castingIEEE754_sp.i >> 24) & 0xFF;
  bytes[2] = (castingIEEE754_sp.i >> 16) & 0xFF;
  bytes[1] = (castingIEEE754_sp.i >> 8) & 0xFF;
  bytes[0] = castingIEEE754_sp.i & 0xFF;
}

void
toSequence16_float(float n, unsigned short words[2])
{
  union IEEE754_single_precision castingIEEE754_sp;
  castingIEEE754_sp.f = n;
  words[1] = (castingIEEE754_sp.i >> 16) & 0xFFFF;
  words[0] = castingIEEE754_sp.i & 0xFFFF;
}

void
toSequence32_float(float n, unsigned int words[1])
{
  union IEEE754_single_precision castingIEEE754_sp;
  castingIEEE754_sp.f = n;
  words[0] = castingIEEE754_sp.i;
}


void
toSequence8_double(double n, unsigned char bytes[8])
{
  union IEEE754_double_precision castingIEEE754_dp;
  castingIEEE754_dp.d = n;
  bytes[3] = (castingIEEE754_dp.ll >> 56) & 0xFF;
  bytes[2] = (castingIEEE754_dp.ll >> 48) & 0xFF;
  bytes[1] = (castingIEEE754_dp.ll >> 40) & 0xFF;
  bytes[0] = (castingIEEE754_dp.ll >> 32) & 0xFF;
  bytes[7] = (castingIEEE754_dp.ll >> 24) & 0xFF;
  bytes[6] = (castingIEEE754_dp.ll >> 16) & 0xFF;
  bytes[5] = (castingIEEE754_dp.ll >> 8) & 0xFF;
  bytes[4] = castingIEEE754_dp.ll & 0xFF;
}

void
toSequence16_double(double n, unsigned short words[4])
{
  union IEEE754_double_precision castingIEEE754_dp;
  castingIEEE754_dp.d = n;
  words[1] = (castingIEEE754_dp.ll >> 48) & 0xFFFF;
  words[0] = (castingIEEE754_dp.ll >> 32) & 0xFFFF;
  words[3] = (castingIEEE754_dp.ll >> 16) & 0xFFFF;
  words[2] = castingIEEE754_dp.ll & 0xFFFF;
}

void
toSequence32_double(double n, unsigned int words[2])
{
  union IEEE754_double_precision castingIEEE754_dp;
  castingIEEE754_dp.d = n;
  words[0] = (castingIEEE754_dp.ll >> 32) & 0xFFFFFFFF;
  words[1] = castingIEEE754_dp.ll & 0xFFFFFFFF;
}


