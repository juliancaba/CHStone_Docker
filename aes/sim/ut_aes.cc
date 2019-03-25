#include <stdio.h>
#include <math.h>
#include "aes_wrapper_sw.h"
#include "unity.h"
#include "rc-unity.h"


int statemt[N] = {50,67,246,168,136,90,48,141,49,49,152,162,224,55,7,52};
int statemt_orig[N] = {50,67,246,168,136,90,48,141,49,49,152,162,224,55,7,52};
int key[N] = {43,126,21,22,40,174,210,166,171,247,21,136,9,207,79,60};
int out_statemt[N] = {0x39,0x25,0x84,0x1d,0x2,0xdc,0x9,0xfb,0xdc,0x11,0x85,0x97,0x19,0x6a,0xb,0x32};
int AESType=128128;


void setUp(void)
{
}

void tearDown(void)
{
}



void
test_aes_enc()
{
  encrypt_wrapper (statemt, key, AESType);

  for (int i = 0; i < 16; i++)
    TEST_ASSERT_EQUAL(statemt[i], out_statemt[i]);
}


void
test_aes_dec()
{
  decrypt_wrapper (out_statemt, key, AESType);

  for (int i = 0; i < 16; i++)
    TEST_ASSERT_EQUAL(out_statemt[i], statemt_orig[i]);

}


