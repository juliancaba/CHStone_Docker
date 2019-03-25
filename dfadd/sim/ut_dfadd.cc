#include <stdio.h>
#include <math.h>
#include "rc-unity.h"
#include "unity.h"
#include "adder64_wrapper_sw.h"


void setUp(void)
{
}

void tearDown(void)
{
}


#define N 46
const float64 a_input[N] = {
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x4000000000000000ULL,	/* 2.0 */
  0x4000000000000000ULL,	/* 2.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF8000000000000ULL,	/* 1.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF8000000000000ULL,	/* 1.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xC000000000000000ULL,	/* -2.0 */
  0xC000000000000000ULL,	/* -2.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0xBFF8000000000000ULL,	/* -1.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0x8000000000000000ULL,	/* -0.0 */
  0xBFF8000000000000ULL,	/* -1.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF8000000000000ULL,	/* 1.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x4000000000000000ULL,	/* 2.0 */
  0xFFF0000000000000ULL,	/* -inf */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0xBFF8000000000000ULL,	/* -1.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xC000000000000000ULL		/* -2.0 */
};

const float64 b_input[N] = {
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF8000000000000ULL,	/* 1.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x4000000000000000ULL,	/* 2.0 */
  0x4000000000000000ULL,	/* 2.0 */
  0x7FF0000000000000ULL,	/* inf */
  0x7FF0000000000000ULL,	/* inf */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0xBFF8000000000000ULL,	/* -1.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xC000000000000000ULL,	/* -2.0 */
  0xC000000000000000ULL,	/* -2.0 */
  0xFFF0000000000000ULL,	/* -inf */
  0xFFF0000000000000ULL,	/* -inf */
  0x8000000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xFFF0000000000000ULL,	/* -inf */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xC000000000000000ULL,	/* -2.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFF0000000000000ULL,	/* -1.0 */
  0x8000000000000000ULL,	/* -0.0 */
  0xBFF8000000000000ULL,	/* -1.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x4000000000000000ULL,	/* 2.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x0000000000000000ULL,	/* 0.0 */
  0x3FF8000000000000ULL		/* 1.5 */
};

const float64 z_output[N] = {
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x4000000000000000ULL,	/* 2.0 */
  0x400C000000000000ULL,	/* 3.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x4000000000000000ULL,	/* 2.0 */
  0x400C000000000000ULL,	/* 3.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x0000000000000000ULL,	/* 0.0 */
  0x4004000000000000ULL,	/* 2.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xC000000000000000ULL,	/* -2.0 */
  0xC00C000000000000ULL,	/* -3.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xC000000000000000ULL,	/* -2.0 */
  0xC00C000000000000ULL,	/* -3.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0x8000000000000000ULL,	/* -0.0 */
  0xC004000000000000ULL,	/* -2.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF8000000000000ULL,	/* nan */
  0x0000000000000000ULL,	/* 0.0 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFE0000000000000ULL,	/* -0.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF8000000000000ULL,	/* nan */
  0x0000000000000000ULL,	/* 0.0 */
  0x7FF8000000000000ULL,	/* nan */
  0x7FF0000000000000ULL,	/* inf */
  0x3FF0000000000000ULL,	/* 1.0 */
  0x3FE0000000000000ULL,	/* 0.5 */
  0xFFF8000000000000ULL,	/* nan */
  0xFFF0000000000000ULL,	/* -inf */
  0xBFF0000000000000ULL,	/* -1.0 */
  0xBFE0000000000000ULL		/* -0.5 */
};



void
test_a_inf_b_1_z_inf()
{  
  float64 result = adder64_wrapper(a_input[1],b_input[1]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[1]);
}

void
test_a_2_b_0_z_2()
{  
  float64 result = adder64_wrapper(a_input[2],b_input[2]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[2]);
}

void
test_a_2_b_1p5_z_3p5()
{  
  float64 result = adder64_wrapper(a_input[3],b_input[3]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[3]);
}

void
test_a_1_b_nan_z_nan()
{  
  float64 result = adder64_wrapper(a_input[4],b_input[4]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[4]);
}

void
test_a_0_b_inf_z_inf()
{  
  float64 result = adder64_wrapper(a_input[5],b_input[5]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[5]);
}

void
test_a_0_b_2_z_2()
{  
  float64 result = adder64_wrapper(a_input[6],b_input[6]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[6]);
}

void
test_a_1p5_b_2_z_3p5()
{  
  float64 result = adder64_wrapper(a_input[7],b_input[7]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[7]);
}

void
test_a_nan_b_inf_z_nan()
{  
  float64 result = adder64_wrapper(a_input[8],b_input[8]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[8]);
}

void
test_a_inf_b_inf_z_inf()
{  
  float64 result = adder64_wrapper(a_input[9],b_input[9]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[9]);
}

void
test_a_0_b_0_z_0()
{  
  float64 result = adder64_wrapper(a_input[10],b_input[10]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[10]);
}

void
test_a_1p5_b_1_z_2p5()
{  
  float64 result = adder64_wrapper(a_input[11],b_input[11]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[11]);
}

void
test_a_nan_b_n1_z_nan()
{  
  float64 result = adder64_wrapper(a_input[12],b_input[12]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[12]);
}

void
test_a_ninf_b_n1_z_ninf()
{  
  float64 result = adder64_wrapper(a_input[13],b_input[13]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[13]);
}

void
test_a_n2_b_n0_z_n2()
{  
  float64 result = adder64_wrapper(a_input[14],b_input[14]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[14]);
}

void
test_a_n2_b_n1p5_z_n3p5()
{  
  float64 result = adder64_wrapper(a_input[15],b_input[15]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[15]);
}

void
test_a_n1_b_nan_z_nan()
{  
  float64 result = adder64_wrapper(a_input[16],b_input[16]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[16]);
}

void
test_a_n1_b_ninf_z_ninf()
{  
  float64 result = adder64_wrapper(a_input[17],b_input[17]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[17]);
}

void
test_a_n0_b_n2_z_n2()
{  
  float64 result = adder64_wrapper(a_input[18],b_input[18]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[18]);
}

void
test_a_n1p5_b_n2_z_n3p5()
{  
  float64 result = adder64_wrapper(a_input[19],b_input[19]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[19]);
}

void
test_a_nan_b_ninf_z_nan()
{  
  float64 result = adder64_wrapper(a_input[20],b_input[20]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[20]);
}

void
test_a_ninf_b_ninf_z_ninf()
{  
  float64 result = adder64_wrapper(a_input[21],b_input[21]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[21]);
}

void
test_a_n0_b_ninf_z_n0()
{  
  float64 result = adder64_wrapper(a_input[22],b_input[22]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[22]);
}

void
test_a_n1p5_b_n1_z_n2p5()
{  
  float64 result = adder64_wrapper(a_input[23],b_input[23]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[23]);
}

void
test_a_inf_b_ninf_z_nan()
{  
  float64 result = adder64_wrapper(a_input[25],b_input[25]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[25]);
}

void
test_a_1_b_n1_z_0()
{  
  float64 result = adder64_wrapper(a_input[26],b_input[26]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[26]);
}


void
test_a_1_b_ninf_z_ninf()
{  
  float64 result = adder64_wrapper(a_input[28],b_input[28]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[28]);
}

void
test_a_0_b_n1_z_n1()
{  
  float64 result = adder64_wrapper(a_input[29],b_input[29]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[29]);
}

void
test_a_1p5_b_n2_z_n0p5()
{  
  float64 result = adder64_wrapper(a_input[30],b_input[30]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[30]);
}


void
test_a_inf_b_n1_z_inf()
{  
  float64 result = adder64_wrapper(a_input[32],b_input[32]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[32]);
}

void
test_a_1_b_n0_z_1()
{  
  float64 result = adder64_wrapper(a_input[33],b_input[33]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[33]);
}

void
test_a_2_b_n1p5_z_0p5()
{  
  float64 result = adder64_wrapper(a_input[34],b_input[34]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[34]);
}

void
test_a_ninf_b_nan_z_nan()
{  
  float64 result = adder64_wrapper(a_input[35],b_input[35]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[35]);
}

void
test_a_ninf_b_inf_z_nan()
{  
  float64 result = adder64_wrapper(a_input[36],b_input[36]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[36]);
}

void
test_a_n1_b_1_z_0()
{  
  float64 result = adder64_wrapper(a_input[37],b_input[37]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[37]);
}

void
test_a_n1_b_inf_z_inf()
{  
  float64 result = adder64_wrapper(a_input[39],b_input[39]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[39]);
}

void
test_a_n0_b_1_z_1()
{  
  float64 result = adder64_wrapper(a_input[40],b_input[40]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[40]);
}

void
test_a_n1p5_b_2_z_0p5()
{  
  float64 result = adder64_wrapper(a_input[41],b_input[41]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[41]);
}


void
test_a_ninf_b_1_z_ninf()
{  
  float64 result = adder64_wrapper(a_input[43],b_input[43]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[43]);
}

void
test_a_n1_b_0_z_n1()
{  
  float64 result = adder64_wrapper(a_input[44],b_input[44]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[44]);
}

void
test_a_n2_b_1p5_z_n0p5()
{  
  float64 result = adder64_wrapper(a_input[45],b_input[45]);
  TEST_ASSERT_EQUAL_INT64(result, z_output[45]);
}
