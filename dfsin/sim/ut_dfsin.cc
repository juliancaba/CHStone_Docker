#include <stdio.h>
#include <math.h>
#include "rc-unity.h"
#include "unity.h"
#include "sin64_wrapper_sw.h"


void setUp(void)
{
}

void tearDown(void)
{
}



#define N 36

const float64 a_input[N] = {
  0x0000000000000000ULL,	/*      0  */
  0x3fc65717fced55c1ULL,	/*   PI/18 */
  0x3fd65717fced55c1ULL,	/*   PI/9  */
  0x3fe0c151fdb20051ULL,	/*   PI/6  */
  0x3fe65717fced55c1ULL,	/*  2PI/9  */
  0x3febecddfc28ab31ULL,	/*  5PI/18 */
  0x3ff0c151fdb20051ULL,	/*   PI/3  */
  0x3ff38c34fd4fab09ULL,	/*  7PI/18 */
  0x3ff65717fced55c1ULL,	/*  4PI/9  */
  0x3ff921fafc8b0079ULL,	/*   PI/2  */
  0x3ffbecddfc28ab31ULL,	/*  5PI/9  */
  0x3ffeb7c0fbc655e9ULL,	/* 11PI/18 */
  0x4000c151fdb20051ULL,	/*  2PI/3  */
  0x400226c37d80d5adULL,	/* 13PI/18 */
  0x40038c34fd4fab09ULL,	/*  7PI/9  */
  0x4004f1a67d1e8065ULL,	/*  5PI/6  */
  0x40065717fced55c1ULL,	/*  8PI/9  */
  0x4007bc897cbc2b1dULL,	/* 17PI/18 */
  0x400921fafc8b0079ULL,	/*   PI    */
  0x400a876c7c59d5d5ULL,	/* 19PI/18 */
  0x400becddfc28ab31ULL,	/* 10PI/9  */
  0x400d524f7bf7808dULL,	/*  7PI/6  */
  0x400eb7c0fbc655e9ULL,	/* 11PI/9  */
  0x40100e993dca95a3ULL,	/* 23PI/18 */
  0x4010c151fdb20051ULL,	/*  8PI/6  */
  0x4011740abd996affULL,	/* 25PI/18 */
  0x401226c37d80d5adULL,	/* 13PI/9  */
  0x4012d97c3d68405bULL,	/*  3PI/2  */
  0x40138c34fd4fab09ULL,	/* 14PI/9  */
  0x40143eedbd3715b7ULL,	/* 29PI/18 */
  0x4014f1a67d1e8065ULL,	/* 15PI/9  */
  0x4015a45f3d05eb13ULL,	/* 31PI/18 */
  0x40165717fced55c1ULL,	/* 16PI/9  */
  0x401709d0bcd4c06fULL,	/* 33PI/18 */
  0x4017bc897cbc2b1dULL,	/* 17PI/9  */
  0x40186f423ca395cbULL         /* 35PI/18 */
};

const float64 z_output[N] = {
  0x0000000000000000ULL,	/*  0.000000 */
  0x3fc63a1a335aadcdULL,	/*  0.173648 */
  0x3fd5e3a82b09bf3eULL,	/*  0.342020 */
  0x3fdfffff91f9aa91ULL,	/*  0.500000 */
  0x3fe491b716c242e3ULL,	/*  0.642787 */
  0x3fe8836f672614a6ULL,	/*  0.766044 */
  0x3febb67ac40b2bedULL,	/*  0.866025 */
  0x3fee11f6127e28adULL,	/*  0.939693 */
  0x3fef838b6adffac0ULL,	/*  0.984808 */
  0x3fefffffe1cbd7aaULL,	/*  1.000000 */
  0x3fef838bb0147989ULL,	/*  0.984808 */
  0x3fee11f692d962b4ULL,	/*  0.939693 */
  0x3febb67b77c0142dULL,	/*  0.866026 */
  0x3fe883709d4ea869ULL,	/*  0.766045 */
  0x3fe491b81d72d8e8ULL,	/*  0.642788 */
  0x3fe00000ea5f43c8ULL,	/*  0.500000 */
  0x3fd5e3aa4e0590c5ULL,	/*  0.342021 */
  0x3fc63a1d2189552cULL,	/*  0.173648 */
  0x3ea6aedffc454b91ULL,	/*  0.000001 */
  0xbfc63a1444ddb37cULL,	/* -0.173647 */
  0xbfd5e3a4e68f8f3eULL,	/* -0.342019 */
  0xbfdffffd494cf96bULL,	/* -0.499999 */
  0xbfe491b61cb9a3d3ULL,	/* -0.642787 */
  0xbfe8836eb2dcf815ULL,	/* -0.766044 */
  0xbfebb67a740aae32ULL,	/* -0.866025 */
  0xbfee11f5912d2157ULL,	/* -0.939692 */
  0xbfef838b1ac64afcULL,	/* -0.984808 */
  0xbfefffffc2e5dc8fULL,	/* -1.000000 */
  0xbfef838b5ea2e7eaULL,	/* -0.984808 */
  0xbfee11f7112dae27ULL,	/* -0.939693 */
  0xbfebb67c2c31cb4aULL,	/* -0.866026 */
  0xbfe883716e6fd781ULL,	/* -0.766045 */
  0xbfe491b9cd1b5d56ULL,	/* -0.642789 */
  0xbfe000021d0ca30dULL,	/* -0.500001 */
  0xbfd5e3ad0a69caf7ULL,	/* -0.342021 */
  0xbfc63a23c48863ddULL         /* -0.173649 */
};


void
test_a_0_z_0()
{  
  float64 result = sin64_wrapper(a_input[0]);
  TEST_ASSERT_EQUAL(result, z_output[0]);
}
 
void
test_a_PI18_z_0p173648()
{  
  float64 result = sin64_wrapper(a_input[1]);
  TEST_ASSERT_EQUAL(result, z_output[1]);
}
 
void
test_a_PI9_z_0p342020()
{  
  float64 result = sin64_wrapper(a_input[2]);
  TEST_ASSERT_EQUAL(result, z_output[2]);
}
 
void
test_a_PI6_z_0p5()
{  
  float64 result = sin64_wrapper(a_input[3]);
  TEST_ASSERT_EQUAL(result, z_output[3]);
}
 
void
test_a_2PI9_z_0p642787()
{  
  float64 result = sin64_wrapper(a_input[4]);
  TEST_ASSERT_EQUAL(result, z_output[4]);
}
 
void
test_a_5PI18_z_0p766044()
{  
  float64 result = sin64_wrapper(a_input[5]);
  TEST_ASSERT_EQUAL(result, z_output[5]);
}
 
void
test_a_PI3_z_0p866025()
{  
  float64 result = sin64_wrapper(a_input[6]);
  TEST_ASSERT_EQUAL(result, z_output[6]);
}

void
test_a_7PI18_z_0p939693()
{  
  float64 result = sin64_wrapper(a_input[7]);
  TEST_ASSERT_EQUAL(result, z_output[7]);
}
 
void
test_a_4PI9_z_0p984808()
{  
  float64 result = sin64_wrapper(a_input[8]);
  TEST_ASSERT_EQUAL(result, z_output[8]);
}
 
void
test_a_PI2_z_1p0()
{  
  float64 result = sin64_wrapper(a_input[9]);
  TEST_ASSERT_EQUAL(result, z_output[9]);
}

void
test_a_5PI9_z_0p984808()
{  
  float64 result = sin64_wrapper(a_input[10]);
  TEST_ASSERT_EQUAL(result, z_output[10]);
}
 
void
test_a_11PI18_z_0p939693()
{  
  float64 result = sin64_wrapper(a_input[11]);
  TEST_ASSERT_EQUAL(result, z_output[11]);
}
 
void
test_a_2PI3_z_0p866026()
{  
  float64 result = sin64_wrapper(a_input[12]);
  TEST_ASSERT_EQUAL(result, z_output[12]);
}
 
void
test_a_13PI18_z_0p766045()
{  
  float64 result = sin64_wrapper(a_input[13]);
  TEST_ASSERT_EQUAL(result, z_output[13]);
}
 
void
test_a_7PI9_z_0p642788()
{  
  float64 result = sin64_wrapper(a_input[14]);
  TEST_ASSERT_EQUAL(result, z_output[14]);
}
 
void
test_a_5PI6_z_0p5()
{  
  float64 result = sin64_wrapper(a_input[15]);
  TEST_ASSERT_EQUAL(result, z_output[15]);
}
 
void
test_a_8PI9_z_0p342021()
{  
  float64 result = sin64_wrapper(a_input[16]);
  TEST_ASSERT_EQUAL(result, z_output[16]);
}

void
test_a_17PI18_z_0p173648()
{  
  float64 result = sin64_wrapper(a_input[17]);
  TEST_ASSERT_EQUAL(result, z_output[17]);
}
 
void
test_a_PI_z_0p000001()
{  
  float64 result = sin64_wrapper(a_input[18]);
  TEST_ASSERT_EQUAL(result, z_output[18]);
}
 
void
test_a_19PI18_z_n0p173647()
{  
  float64 result = sin64_wrapper(a_input[19]);
  TEST_ASSERT_EQUAL(result, z_output[19]);
}

void
test_a_10PI9_z_n0p342019()
{  
  float64 result = sin64_wrapper(a_input[20]);
  TEST_ASSERT_EQUAL(result, z_output[20]);
}
 
void
test_a_7PI6_z_n0p499999()
{  
  float64 result = sin64_wrapper(a_input[21]);
  TEST_ASSERT_EQUAL(result, z_output[21]);
}
 
void
test_a_11PI9_z_n0p642787()
{  
  float64 result = sin64_wrapper(a_input[22]);
  TEST_ASSERT_EQUAL(result, z_output[22]);
}
 
void
test_a_23PI18_z_n0p76044()
{  
  float64 result = sin64_wrapper(a_input[23]);
  TEST_ASSERT_EQUAL(result, z_output[23]);
}
 
void
test_a_8PI6_z_n0p866025()
{  
  float64 result = sin64_wrapper(a_input[24]);
  TEST_ASSERT_EQUAL(result, z_output[24]);
}
 
void
test_a_25PI18_z_n0p939692()
{  
  float64 result = sin64_wrapper(a_input[25]);
  TEST_ASSERT_EQUAL(result, z_output[25]);
}
 
void
test_a_13PI9_z_n0p984808()
{  
  float64 result = sin64_wrapper(a_input[26]);
  TEST_ASSERT_EQUAL(result, z_output[26]);
}

void
test_a_3PI2_z_n1p0()
{  
  float64 result = sin64_wrapper(a_input[27]);
  TEST_ASSERT_EQUAL(result, z_output[27]);
}
 
void
test_a_14PI9_z_n0p984808()
{  
  float64 result = sin64_wrapper(a_input[28]);
  TEST_ASSERT_EQUAL(result, z_output[28]);
}
 
void
test_a_29PI18_z_n0p939692()
{  
  float64 result = sin64_wrapper(a_input[29]);
  TEST_ASSERT_EQUAL(result, z_output[29]);
}

void
test_a_15PI9_z_n0p866026()
{  
  float64 result = sin64_wrapper(a_input[30]);
  TEST_ASSERT_EQUAL(result, z_output[30]);
}
 
void
test_a_31PI18_z_n0p766045()
{  
  float64 result = sin64_wrapper(a_input[31]);
  TEST_ASSERT_EQUAL(result, z_output[31]);
}
 
void
test_a_16PI9_z_n0p642789()
{  
  float64 result = sin64_wrapper(a_input[32]);
  TEST_ASSERT_EQUAL(result, z_output[32]);
}
 
void
test_a_33PI18_z_n0p500001()
{  
  float64 result = sin64_wrapper(a_input[33]);
  TEST_ASSERT_EQUAL(result, z_output[33]);
}
 
void
test_a_17PI9_z_n0p342021()
{  
  float64 result = sin64_wrapper(a_input[34]);
  TEST_ASSERT_EQUAL(result, z_output[34]);
}
 
void
test_a_35PI18_z_n0p173649()
{  
  float64 result = sin64_wrapper(a_input[35]);
  TEST_ASSERT_EQUAL(result, z_output[35]);
}
 
