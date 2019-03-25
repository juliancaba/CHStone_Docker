#include <stdio.h>
#include <math.h>
#include "rc-unity.h"
#include "unity.h"
#include "multiplier64_wrapper_sw.h"



void setUp(void)
{
}

void tearDown(void)
{
}



#define N 20

const float64 a_input[N] = {
  0x7FF0000000000000ULL,	/* inf */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x4000000000000000ULL,	/* 2.0 */
  0x3FD0000000000000ULL,	/* 0.25 */
  0xC000000000000000ULL,	/* -2.0 */
  0xBFD0000000000000ULL,	/* -0.25 */
  0x4000000000000000ULL,	/* 2.0 */
  0xBFD0000000000000ULL,	/* -0.25 */
  0xC000000000000000ULL,	/* -2.0 */
  0x3FD0000000000000ULL,	/* 0.25 */
  0x0000000000000000ULL		/* 0.0 */
};

const float64 b_input[N] = {
  0x7FF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0x7FF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0x3FD0000000000000ULL,	/* 0.25 */
  0x4000000000000000ULL,	/* 2.0 */
  0xBFD0000000000000ULL,	/* -0.25 */
  0xC000000000000000ULL,	/* -2.0 */
  0xBFD0000000000000ULL,	/* -0.25 */
  0x4000000000000000ULL,	/* -2.0 */
  0x3FD0000000000000ULL,	/* 0.25 */
  0xC000000000000000ULL,	/* -2.0 */
  0x0000000000000000ULL		/* 0.0 */
};

const float64 z_output[N] = {
  0x7FF8000000000000ULL,	/* nan */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* inf */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x0000000000000000ULL,	/* 0.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0xBFE0000000000000ULL,	/* -0.5 */
  0xBFE0000000000000ULL,	/* -0.5 */
  0xBFE0000000000000ULL,	/* -0.5 */
  0xBFE0000000000000ULL,	/* -0.5 */
  0x0000000000000000ULL		/* 0.0 */
};

void
test_a_inf_b_nan_z_nan()
{  
  float64 result = multiplier64_wrapper(a_input[0],b_input[0]);
  TEST_ASSERT_EQUAL(result, z_output[0]);
}

void
test_a_nan_b_ninf_z_nan()
{  
  float64 result = multiplier64_wrapper(a_input[1],b_input[1]);
  TEST_ASSERT_EQUAL(result, z_output[1]);
}

void
test_a_inf_b_nan_z_nan2()
{  
  float64 result = multiplier64_wrapper(a_input[2],b_input[2]);
  TEST_ASSERT_EQUAL(result, z_output[2]);
}

void
test_a_inf_b_ninf_z_inf()
{  
  float64 result = multiplier64_wrapper(a_input[3],b_input[3]);
  TEST_ASSERT_EQUAL(result, z_output[3]);
}

void
test_a_1_b_nan_z_nan()
{  
  float64 result = multiplier64_wrapper(a_input[4],b_input[4]);
  TEST_ASSERT_EQUAL(result, z_output[4]);
}

void
test_a_0_b_inf_z_nan()
{  
  float64 result = multiplier64_wrapper(a_input[5],b_input[5]);
  TEST_ASSERT_EQUAL(result, z_output[5]);
}

void
test_a_1_b_inf_z_inf()
{  
  float64 result = multiplier64_wrapper(a_input[6],b_input[6]);
  TEST_ASSERT_EQUAL(result, z_output[6]);
}

void
test_a_0_b_1_z_0()
{  
  float64 result = multiplier64_wrapper(a_input[7],b_input[7]);
  TEST_ASSERT_EQUAL(result, z_output[7]);
}

void
test_a_n0_b_1_z_n0()
{  
  float64 result = multiplier64_wrapper(a_input[8],b_input[8]);
  TEST_ASSERT_EQUAL(result, z_output[8]);
}

void
test_a_1_b_0_z_0()
{  
  float64 result = multiplier64_wrapper(a_input[9],b_input[9]);
  TEST_ASSERT_EQUAL(result, z_output[9]);
}

void
test_a_1_b_n0_z_n0()
{  
  float64 result = multiplier64_wrapper(a_input[10],b_input[10]);
  TEST_ASSERT_EQUAL(result, z_output[10]);
}

void
test_a_2_b_025_z_05()
{  
  float64 result = multiplier64_wrapper(a_input[11],b_input[11]);
  TEST_ASSERT_EQUAL(result, z_output[11]);
}

void
test_a_025_b_2_z_05()
{  
  float64 result = multiplier64_wrapper(a_input[12],b_input[12]);
  TEST_ASSERT_EQUAL(result, z_output[12]);
}

void
test_a_n2_b_n025_z_05()
{  
  float64 result = multiplier64_wrapper(a_input[13],b_input[13]);
  TEST_ASSERT_EQUAL(result, z_output[13]);
}

void
test_a_n025_b_n2_z_05()
{  
  float64 result = multiplier64_wrapper(a_input[14],b_input[14]);
  TEST_ASSERT_EQUAL(result, z_output[14]);
}

void
test_a_2_b_n025_z_n05()
{  
  float64 result = multiplier64_wrapper(a_input[15],b_input[15]);
  TEST_ASSERT_EQUAL(result, z_output[15]);
}

void
test_a_n025_b_n2_z_n05()
{  
  float64 result = multiplier64_wrapper(a_input[16],b_input[16]);
  TEST_ASSERT_EQUAL(result, z_output[16]);
}

void
test_a_n2_b_025_z_n05()
{  
  float64 result = multiplier64_wrapper(a_input[17],b_input[17]);
  TEST_ASSERT_EQUAL(result, z_output[17]);
}

void
test_a_025_b_n2_z_n05()
{  
  float64 result = multiplier64_wrapper(a_input[18],b_input[18]);
  TEST_ASSERT_EQUAL(result, z_output[18]);
}

void
test_a_0_b_0_z_0()
{  
  float64 result = multiplier64_wrapper(a_input[19],b_input[19]);
  TEST_ASSERT_EQUAL(result, z_output[19]);
}






