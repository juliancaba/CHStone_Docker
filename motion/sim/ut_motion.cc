#include <stdio.h>
#include <math.h>
#include "motion_wrapper_sw.h"
#include "unity.h"


/*
+--------------------------------------------------------------------------+
| * Test Vectors (added for CHStone)                                       |
|     inRdbfr, inPMV, inPMV : input data                                   |
|     outPMV, outmvfs : expected output data                               |
+--------------------------------------------------------------------------+
*/
#define Num 2048

int inPMV[2][2][2] = { {{45, 207}, {70, 41}}, {{4, 180}, {120, 216}} };
int inmvfs[2][2] = { {232, 200}, {32, 240} };
#ifdef __SYNTHESIS__
const int outPMV[2][2][2] = { {{1566, 206}, {70, 41}}, {{1358, 206}, {120, 216}} };
#else
const int outPMV[2][2][2] = { {{1566, 206}, {70, 41}}, {{1566, 206}, {120, 216}} };
#endif
const int outmvfs[2][2] = { {0, 200}, {0, 240} };



void setUp(void)
{
}

void tearDown(void)
{
}



void
test_motion()
{
    int i, j, k;
  int main_result;
  int PMV[2][2][2];
  int dmvector[2];
  int motion_vertical_field_select[2][2];
  int s, motion_vector_count, mv_format, h_r_size, v_r_size, dmv, mvscale;

      main_result = 0;
      int evalue = 0;
      //System_Stream_Flag = 0;
      s = 0;
      motion_vector_count = 1;
      mv_format = 0;
      h_r_size = 200;
      v_r_size = 200;
      dmv = 0;
      mvscale = 1;
      for (i = 0; i < 2; i++)
	{
	  dmvector[i] = 0;
	  for (j = 0; j < 2; j++)
	    {
	      motion_vertical_field_select[i][j] = inmvfs[i][j];
	      for (k = 0; k < 2; k++)
		PMV[i][j][k] = inPMV[i][j][k];
	    }
	}

      Initialize_Buffer_wrapper ();
      motion_vectors_wrapper (PMV, dmvector, motion_vertical_field_select, s,
		      motion_vector_count, mv_format, h_r_size, v_r_size, dmv,
		      mvscale);

      for (i = 0; i < 2; i++)
	for (j = 0; j < 2; j++)
	  {
	    TEST_ASSERT_EQUAL(motion_vertical_field_select[i][j], outmvfs[i][j]);
	    for (k = 0; k < 2; k++)
	      TEST_ASSERT_EQUAL(PMV[i][j][k], outPMV[i][j][k]);
	  }
}




