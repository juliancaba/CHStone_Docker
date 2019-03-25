#include <stdio.h>
#include <math.h>
#include "mips_wrapper_sw.h"
#include "rc-unity.h"
#include "unity.h"

/*
+--------------------------------------------------------------------------+
| * Test Vectors (added for CHStone)                                       |
|     A : input data                                                       |
|     outData : expected output data                                       |
+--------------------------------------------------------------------------+
*/

int A[8] = { 22, 5, -9, 3, -17, 38, 0, 11 };
const int outData[8] = { -17, -9, 0, 3, 5, 11, 22, 38 };


void setUp(void)
{
}

void tearDown(void)
{
}



void
test_mips()
{
  int out[8];
  int n_inst;

  n_inst = mips_wrapper(A, out);
  TEST_ASSERT_EQUAL(611, n_inst);
  for(int i=0; i!=8; i++)
    TEST_ASSERT_EQUAL(outData[i], out[i]);
}



