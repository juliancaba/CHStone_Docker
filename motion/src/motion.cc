/*
+--------------------------------------------------------------------------+
| CHStone : a suite of benchmark programs for C-based High-Level Synthesis |
| ======================================================================== |
|                                                                          |
| * Collected and Modified : Y. Hara, H. Tomiyama, S. Honda,               |
|                            H. Takada and K. Ishii                        |
|                            Nagoya University, Japan                      |
|                                                                          |
| * Remark :                                                               |
|    1. This source code is modified to unify the formats of the benchmark |
|       programs in CHStone.                                               |
|    2. Test vectors are added for CHStone.                                |
|    3. If "main_result" is 0 at the end of the program, the program is    |
|       correctly executed.                                                |
|    4. Please follow the copyright of each benchmark program.             |
+--------------------------------------------------------------------------+
*/
/* motion.c, motion vector decoding                                         */

/* Copyright (C) 1996, MPEG Software Simulation Group. All Rights Reserved. */

/*
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any license fee or
 * royalty on an "as is" basis.  The MPEG Software Simulation Group disclaims
 * any and all warranties, whether express, implied, or statuary, including any
 * implied warranties or merchantability or of fitness for a particular
 * purpose.  In no event shall the copyright-holder be liable for any
 * incidental, punitive, or consequential damages of any kind whatsoever
 * arising from the use of these programs.
 *
 * This disclaimer of warranty extends to the user of these programs and user's
 * customers, employees, agents, transferees, successors, and assigns.
 *
 * The MPEG Software Simulation Group does not represent or warrant that the
 * programs furnished hereunder are free of infringement of any third-party
 * patents.
 *
 * Commercial implementations of MPEG-1 and MPEG-2 video, including shareware,
 * are subject to royalty fees to patent holders.  Many of these patents are
 * general enough such that they are unavoidable regardless of implementation
 * design.
 *
 */

#include "config.h"
#include "global.h"
//#include "getbits.c"
#include "getvlc.h"
//#include "getvlc.c"


/* private prototypes */
static void decode_motion_vector
_ANSI_ARGS_ ((int *pred, int r_size, int motion_code,
	      int motion_residualesidual, int full_pel_vector));

void
Initialize_Buffer ()
{
  ld_Incnt = 0;
  ld_Rdptr = ld_Rdbfr + 2048;
  ld_Rdmax = ld_Rdptr;
  ld_Bfr = 68157440;
  Flush_Buffer (0);		/* fills valid data into bfr */
}

/* ISO/IEC 13818-2 sections 6.2.5.2, 6.3.17.2, and 7.6.3: Motion vectors */
void
motion_vectors (int PMV[2][2][2], int dmvector[2],int motion_vertical_field_select[2][2],
		int s, int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale)
{
  if (motion_vector_count == 1)
    {
      if (mv_format == MV_FIELD && !dmv)
	{
	  motion_vertical_field_select[1][s] =
	    motion_vertical_field_select[0][s] = Get_Bits (1);
	}

      motion_vector (PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale,
		     0);

      /* update other motion vector predictors */
      PMV[1][s][0] = PMV[0][s][0];
      PMV[1][s][1] = PMV[0][s][1];
    }
  else
    {
      motion_vertical_field_select[0][s] = Get_Bits (1);

      motion_vector (PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale,
		     0);

      motion_vertical_field_select[1][s] = Get_Bits (1);

      motion_vector (PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale,
		     0);
    }
}

/* get and decode motion vector and differential motion vector 
   for one prediction */
void
motion_vector (int *PMV,  int *dmvector, int h_r_size,
	       int v_r_size,
	       int dmv,			/* MPEG-2 only: get differential motion vectors */
	       int mvscale,		/* MPEG-2 only: field vector in frame pic */
	       int full_pel_vector)	/* MPEG-1 only */
{
  int motion_code;
  int motion_residual;

  /* horizontal component */
  /* ISO/IEC 13818-2 Table B-10 */
  motion_code = Get_motion_code ();

  motion_residual = (h_r_size != 0
		     && motion_code != 0) ? Get_Bits (h_r_size) : 0;

  decode_motion_vector (&PMV[0], h_r_size, motion_code, motion_residual,
			full_pel_vector);

  if (dmv)
    dmvector[0] = Get_dmvector ();


  /* vertical component */
  motion_code = Get_motion_code ();
  motion_residual = (v_r_size != 0
		     && motion_code != 0) ? Get_Bits (v_r_size) : 0;

  if (mvscale)
    PMV[1] >>= 1;		/* DIV 2 */

  decode_motion_vector (&PMV[1], v_r_size, motion_code, motion_residual,
			full_pel_vector);

  if (mvscale)
    PMV[1] <<= 1;

  if (dmv)
    dmvector[1] = Get_dmvector ();

}

/* calculate motion vector component */
/* ISO/IEC 13818-2 section 7.6.3.1: Decoding the motion vectors */
/* Note: the arithmetic here is more elegant than that which is shown 
   in 7.6.3.1.  The end results (PMV[][][]) should, however, be the same.  */

static void
decode_motion_vector (int *pred,
		      int r_size, int motion_code, int motion_residual,
		      int full_pel_vector)	/* MPEG-1 (ISO/IEC 11172-1) support */
{
  int lim, vec;

  r_size = r_size % 32;
  lim = 16 << r_size;
  vec = full_pel_vector ? (*pred >> 1) : (*pred);

  if (motion_code > 0)
    {
      vec += ((motion_code - 1) << r_size) + motion_residual + 1;
      if (vec >= lim)
	vec -= lim + lim;
    }
  else if (motion_code < 0)
    {
      vec -= ((-motion_code - 1) << r_size) + motion_residual + 1;
      if (vec < -lim)
	vec += lim + lim;
    }
  *pred = full_pel_vector ? (vec << 1) : vec;
}


// getbits

/* initialize buffer, call once before first getbits or showbits */
int
read (unsigned char *s1, const unsigned char *s2, int n)
{
  unsigned char *p1;
  const unsigned char *p2;
  int n_tmp;
  
p1 = s1;
  p2 = s2;
  n_tmp = n;
  
while (n_tmp-- > 0)
    {
      *p1 = *p2;
      
p1++;
      
p2++;
    
}
  
return n;
}

void
Fill_Buffer ()
{
  int Buffer_Level;
  unsigned char *p;
  p = ld_Rdbfr;


  Buffer_Level = read (ld_Rdbfr, inRdbfr, 2048);
  ld_Rdptr = ld_Rdbfr;

  if (System_Stream_Flag)
    ld_Rdmax -= 2048;


  /* end of the bitstream file */
  if (Buffer_Level < 2048)
    {
      /* just to be safe */
      if (Buffer_Level < 0)
	Buffer_Level = 0;

      /* pad until the next to the next 32-bit word boundary */
      while (Buffer_Level & 3)
	ld_Rdbfr[Buffer_Level++] = 0;

      /* pad the buffer with sequence end codes */
      while (Buffer_Level < 2048)
	{
	  ld_Rdbfr[Buffer_Level++] = SEQUENCE_END_CODE >> 24;
	  ld_Rdbfr[Buffer_Level++] = SEQUENCE_END_CODE >> 16;
	  ld_Rdbfr[Buffer_Level++] = SEQUENCE_END_CODE >> 8;
	  ld_Rdbfr[Buffer_Level++] = SEQUENCE_END_CODE & 0xff;
	}
    }
}

unsigned int
Show_Bits (int N)
{
  return ld_Bfr >> (unsigned)(32-N)%32;
}


/* return next bit (could be made faster than Get_Bits(1)) */

unsigned int
Get_Bits1 ()
{
  return Get_Bits (1);
}


/* advance by n bits */

void
Flush_Buffer (int N)
{
  int Incnt;

#ifdef RAND_VAL 
	/* N is between 0 and 20 with realistic input sets, while it may become larger than the width of the integer type when using randomly generated input sets which are used in the contained input set. The following is to avoid this.  */
	ld_Bfr <<= (N%20);
#else
  ld_Bfr <<= N;
#endif
	
  Incnt = ld_Incnt -= N;

  if (Incnt <= 24)
    {
      if (ld_Rdptr < ld_Rdbfr + 2044)
	{
	  do
	    {
#ifdef RAND_VAL 
	/* N is between 0 and 20 with realistic input sets, while it may become larger than the width of the integer type when using randomly generated input sets which are used in the contained input set. The following is to avoid this.  */
	    	ld_Bfr |= *ld_Rdptr++ << ((24 - Incnt)%20);
#else
	    	ld_Bfr |= *ld_Rdptr++ << (24 - Incnt);
#endif
	    	Incnt += 8;
	    }
	  while (Incnt <= 24);
	}
      else
	{
	  do
	    {
	      if (ld_Rdptr >= ld_Rdbfr + 2048)
		Fill_Buffer ();
#ifdef RAND_VAL 
	/* N is between 0 and 20 with realistic input sets, while it may become larger than the width of the integer type when using randomly generated input sets which are used in the contained input set. The following is to avoid this.  */
	      ld_Bfr |= *ld_Rdptr++ << ((24 - Incnt)%20);
#else
	      ld_Bfr |= *ld_Rdptr++ << (24 - Incnt);
#endif
	      Incnt += 8;
	    }
	  while (Incnt <= 24);
	}
      ld_Incnt = Incnt;
    }
}


/* return next n bits (right adjusted) */

unsigned int
Get_Bits (int N)
{
  unsigned int Val;

  Val = Show_Bits (N);
  Flush_Buffer (N);

  return Val;
}



//getvlc

int
Get_motion_code ()
{
  int code;

  if (Get_Bits1 ())
    {
      return 0;
    }

  if ((code = Show_Bits (9)) >= 64)
    {
      code >>= 6;
      Flush_Buffer (MVtab0[code][1]);

      return Get_Bits1 ()? -MVtab0[code][0] : MVtab0[code][0];
    }

  if (code >= 24)
    {
      code >>= 3;
      Flush_Buffer (MVtab1[code][1]);

      return Get_Bits1 ()? -MVtab1[code][0] : MVtab1[code][0];
    }

  if ((code -= 12) < 0)
    return 0;

  Flush_Buffer (MVtab2[code][1]);
  return Get_Bits1 ()? -MVtab2[code][0] : MVtab2[code][0];
}

/* get differential motion vector (for dual prime prediction) */
int
Get_dmvector ()
{

  if (Get_Bits (1))
    {
      return Get_Bits (1) ? -1 : 1;
    }
  else
    {
      return 0;
    }
}



