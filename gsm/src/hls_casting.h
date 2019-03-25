#ifndef HLS_CASTING_H
#define HLS_CASTING_H



// Enteros
short toShort(unsigned char c1, unsigned char c2);

int
toInt(unsigned char c1, unsigned char c2, 
      unsigned char c3, unsigned char c4);
int
toInt(unsigned short s1, unsigned short s2);

long long
toLongLong(unsigned char c1, unsigned char c2, 
	   unsigned char c3, unsigned char c4,
	   unsigned char c5, unsigned char c6, 
	   unsigned char c7, unsigned char c8);
long long
toLongLong(unsigned short s1, unsigned short s2, 
	   unsigned short s3, unsigned short s4);
long long
toLongLong(unsigned int i1, unsigned int i2);



template <class T>
void
toSequence8_short(T n, unsigned char bytes[2])
{
  bytes[0] = (n >> 8) & 0xFF;
  bytes[1] = n & 0xFF;
}

template <class T>
void
toSequence8_int(T n, unsigned char bytes[4])
{
  bytes[0] = (n >> 24) & 0xFF;
  bytes[1] = (n >> 16) & 0xFF;
  bytes[2] = (n >> 8) & 0xFF;
  bytes[3] = n & 0xFF;
}



template <class T>
void
toSequence16_int(T n, unsigned short words[2])
{ 
  words[0] = (n >> 16) & 0xFFFF;
  words[1] = n & 0xFFFF; 
}


template <class T>
void
toSequence8_ll(T n, unsigned char bytes[8])
{
  bytes[0] = (n >> 56) & 0xFF;
  bytes[1] = (n >> 48) & 0xFF;
  bytes[2] = (n >> 40) & 0xFF;
  bytes[3] = (n >> 32) & 0xFF;
  bytes[4] = (n >> 24) & 0xFF;
  bytes[5] = (n >> 16) & 0xFF;
  bytes[6] = (n >> 8) & 0xFF;
  bytes[7] = n & 0xFF;
}


template <class T>
void
toSequence16_ll(T n, unsigned short words[4])
{  
  words[0] = (n >> 48) & 0xFFFF;
  words[1] = (n >> 32) & 0xFFFF;
  words[2] = (n >> 16) & 0xFFFF;
  words[3] = n & 0xFFFF;
}


template <class T>
void
toSequence32_ll(T n, unsigned int words[2])
{  
  words[0] = (n >> 32) & 0xFFFFFFFF;
  words[1] = n & 0xFFFFFFFF;
}


template <class T>
unsigned int
toSequence32_short(T s1, T s2)
{
  return (((s1<<16)&0xFFFF0000) | (s2&0xFFFF));
}


template <class T>
unsigned int
toSequence32_char(T c1, T c2, T c3, T c4)
{
  return (((c1<<24)&0xFF000000) | ((c2<<16)&0xFF0000) | ((c3<<8)&0xFF00) | (c4&0xFF));
}



// Dobles
float
toFloat(unsigned char c1, unsigned char c2, 
	unsigned char c3, unsigned char c4);
float
toFloat(unsigned short s1, unsigned short s2);
float
toFloat(unsigned int i1);

void
toSequence8_float(float n, unsigned char bytes[4]);
void
toSequence16_float(float n, unsigned short words[2]);
void
toSequence32_float(float n, unsigned int words[1]);

double
toDouble(unsigned char c1, unsigned char c2, 
	 unsigned char c3, unsigned char c4,
	 unsigned char c5, unsigned char c6, 
	 unsigned char c7, unsigned char c8);
double
toDouble(unsigned short s1, unsigned short s2, 
	 unsigned short s3, unsigned short s4);
double
toDouble(unsigned int i1, unsigned int i2);

void
toSequence8_double(double n, unsigned char bytes[8]);
void
toSequence16_double(double n, unsigned short words[4]);
void
toSequence32_double(double n, unsigned int words[2]);

#endif
