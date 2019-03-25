#ifndef MOTION_H
#define MOTION_H

/* #include "config.h"  */
/* #include "global.h" */
/* #include "getvlc.h" */ 



void Initialize_Buffer_wrapper ();
void
motion_vectors_wrapper (int PMV[2][2][2], int dmvector[2], int motion_vertical_field_select[2][2],
		  int s, int motion_vector_count, int mv_format, int h_r_size,
		  int v_r_size, int dmv, int mvscale);

#endif
