/*
*	Rubiks´s Cube solver by Gerrit Hinrichs 06.2024
*   github.com/snech99
*
* 	example cubes
*/
#include "cube.h"

#ifndef EXAMPLE_CUBES_H
#define EXAMPLE_CUBES_H

int bsp_cube_01[54];
int bsp_cube_02[54];
int bsp_cube_03[54];
int bsp_cube_04[54];
int bsp_cube_05[54];
int bsp_cube_fin[54];


void set_bsp_01 ()
{
    bsp_cube_01[0] = white;			bsp_cube_01[27] = red;
	bsp_cube_01[1] = white;			bsp_cube_01[28] = red;
	bsp_cube_01[2] = white;			bsp_cube_01[29] = red;
	bsp_cube_01[3] = white;			bsp_cube_01[30] = yellow;
	bsp_cube_01[4] = white;			bsp_cube_01[31] = green;
	bsp_cube_01[5] = white;			bsp_cube_01[32] = yellow;
	bsp_cube_01[6] = white;			bsp_cube_01[33] = blue;
	bsp_cube_01[7] = white;			bsp_cube_01[34] = orange;
	bsp_cube_01[8] = white;			bsp_cube_01[35] = red;

	bsp_cube_01[9] = orange;		bsp_cube_01[36] = green;
	bsp_cube_01[10] = yellow;		bsp_cube_01[37] = red;
	bsp_cube_01[11] = yellow;		bsp_cube_01[38] = yellow;
	bsp_cube_01[12] = red;			bsp_cube_01[39] = orange;
	bsp_cube_01[13] = yellow;		bsp_cube_01[40] = orange;
	bsp_cube_01[14] = blue;			bsp_cube_01[41] = green;
	bsp_cube_01[15] = orange;		bsp_cube_01[42] = green;
	bsp_cube_01[16] = orange;		bsp_cube_01[43] = green;		
	bsp_cube_01[17] = yellow;		bsp_cube_01[44] = blue;

	bsp_cube_01[18] = yellow;		bsp_cube_01[45] = green;
	bsp_cube_01[19] = blue;			bsp_cube_01[46] = green;
	bsp_cube_01[20] = blue;			bsp_cube_01[47] = blue;
	bsp_cube_01[21] = yellow;		bsp_cube_01[48] = orange;
	bsp_cube_01[22] = red;			bsp_cube_01[49] = blue;
	bsp_cube_01[23] = green;		bsp_cube_01[50] = blue;
	bsp_cube_01[24] = orange;		bsp_cube_01[51] = red;
	bsp_cube_01[25] = blue;			bsp_cube_01[52] = red;
	bsp_cube_01[26] = orange;		bsp_cube_01[53] = green;
}

void set_bsp_02 ()
{
    bsp_cube_02[0] = white;			bsp_cube_02[27] = orange;
	bsp_cube_02[1] = yellow;		bsp_cube_02[28] = red;
	bsp_cube_02[2] = orange;		bsp_cube_02[29] = red;
	bsp_cube_02[3] = red;			bsp_cube_02[30] = blue;
	bsp_cube_02[4] = white;			bsp_cube_02[31] = green;
	bsp_cube_02[5] = green;			bsp_cube_02[32] = blue;
	bsp_cube_02[6] = green;			bsp_cube_02[33] = green;
	bsp_cube_02[7] = white;			bsp_cube_02[34] = yellow;
	bsp_cube_02[8] = yellow;		bsp_cube_02[35] = blue;

	bsp_cube_02[9] = yellow;		bsp_cube_02[36] = yellow;
	bsp_cube_02[10] = yellow;		bsp_cube_02[37] = blue;
	bsp_cube_02[11] = blue;			bsp_cube_02[38] = red;
	bsp_cube_02[12] = orange;		bsp_cube_02[39] = orange;
	bsp_cube_02[13] = yellow;		bsp_cube_02[40] = orange;
	bsp_cube_02[14] = green;		bsp_cube_02[41] = blue;
	bsp_cube_02[15] = white;		bsp_cube_02[42] = orange;
	bsp_cube_02[16] = white;		bsp_cube_02[43] = orange;		
	bsp_cube_02[17] = white;		bsp_cube_02[44] = yellow;

	bsp_cube_02[18] = red;			bsp_cube_02[45] = green;
	bsp_cube_02[19] = red;			bsp_cube_02[46] = green;
	bsp_cube_02[20] = blue;			bsp_cube_02[47] = green;
	bsp_cube_02[21] = white;		bsp_cube_02[48] = red;
	bsp_cube_02[22] = red;			bsp_cube_02[49] = blue;
	bsp_cube_02[23] = white;		bsp_cube_02[50] = green;
	bsp_cube_02[24] = red;			bsp_cube_02[51] = orange;
	bsp_cube_02[25] = orange;		bsp_cube_02[52] = yellow;
	bsp_cube_02[26] = white;		bsp_cube_02[53] = blue;
}

void set_bsp_03 ()
{
    bsp_cube_03[0] = orange;		bsp_cube_03[27] = green;
	bsp_cube_03[1] = blue;			bsp_cube_03[28] = orange;
	bsp_cube_03[2] = orange;		bsp_cube_03[29] = yellow;
	bsp_cube_03[3] = orange;		bsp_cube_03[30] = red;
	bsp_cube_03[4] = red;			bsp_cube_03[31] = blue;
	bsp_cube_03[5] = blue;			bsp_cube_03[32] = white;
	bsp_cube_03[6] = green;			bsp_cube_03[33] = white;
	bsp_cube_03[7] = yellow;		bsp_cube_03[34] = red;
	bsp_cube_03[8] = yellow;		bsp_cube_03[35] = yellow;

	bsp_cube_03[9] =  white;		bsp_cube_03[36] = orange;
	bsp_cube_03[10] = orange;		bsp_cube_03[37] = green;
	bsp_cube_03[11] = orange;		bsp_cube_03[38] = white;
	bsp_cube_03[12] = yellow;		bsp_cube_03[39] = yellow;
	bsp_cube_03[13] = green;		bsp_cube_03[40] = yellow;
	bsp_cube_03[14] = blue;			bsp_cube_03[41] = green;
	bsp_cube_03[15] = red;			bsp_cube_03[42] = blue;
	bsp_cube_03[16] = blue;			bsp_cube_03[43] = red;		
	bsp_cube_03[17] = red;			bsp_cube_03[44] = blue;

	bsp_cube_03[18] = green;		bsp_cube_03[45] = red;
	bsp_cube_03[19] = white;		bsp_cube_03[46] = green;
	bsp_cube_03[20] = yellow;		bsp_cube_03[47] = blue;
	bsp_cube_03[21] = orange;		bsp_cube_03[48] = yellow;
	bsp_cube_03[22] = orange;		bsp_cube_03[49] = white;
	bsp_cube_03[23] = white;		bsp_cube_03[50] = white;
	bsp_cube_03[24] = green;		bsp_cube_03[51] = blue;
	bsp_cube_03[25] = red;			bsp_cube_03[52] = green;
	bsp_cube_03[26] = red;			bsp_cube_03[53] = white;
}

void set_bsp_04 ()
{
    bsp_cube_04[0] = red;			bsp_cube_04[27] = orange;
	bsp_cube_04[1] = red;			bsp_cube_04[28] = yellow;
	bsp_cube_04[2] = yellow;		bsp_cube_04[29] = blue;
	bsp_cube_04[3] = orange;		bsp_cube_04[30] = white;
	bsp_cube_04[4] = red;			bsp_cube_04[31] = blue;
	bsp_cube_04[5] = blue;			bsp_cube_04[32] = blue;
	bsp_cube_04[6] = yellow;		bsp_cube_04[33] = yellow;
	bsp_cube_04[7] = green;			bsp_cube_04[34] = white;
	bsp_cube_04[8] = white;			bsp_cube_04[35] = orange;

	bsp_cube_04[9] = green;			bsp_cube_04[36] = white;
	bsp_cube_04[10] = orange;		bsp_cube_04[37] = yellow;
	bsp_cube_04[11] = green;		bsp_cube_04[38] = white;
	bsp_cube_04[12] = white;		bsp_cube_04[39] = red;
	bsp_cube_04[13] = green;		bsp_cube_04[40] = yellow;
	bsp_cube_04[14] = white;		bsp_cube_04[41] = yellow;
	bsp_cube_04[15] = blue;			bsp_cube_04[42] = yellow;
	bsp_cube_04[16] = blue;			bsp_cube_04[43] = green;		
	bsp_cube_04[17] = orange;		bsp_cube_04[44] = orange;

	bsp_cube_04[18] = red;			bsp_cube_04[45] = blue;
	bsp_cube_04[19] = green;		bsp_cube_04[46] = orange;
	bsp_cube_04[20] = blue;			bsp_cube_04[47] = red;
	bsp_cube_04[21] = orange;		bsp_cube_04[48] = red;
	bsp_cube_04[22] = orange;		bsp_cube_04[49] = white;
	bsp_cube_04[23] = green;		bsp_cube_04[50] = red;
	bsp_cube_04[24] = white;		bsp_cube_04[51] = green;
	bsp_cube_04[25] = blue;			bsp_cube_04[52] = yellow;
	bsp_cube_04[26] = red;			bsp_cube_04[53] = green;
}

void set_bsp_05 ()
{
    bsp_cube_05[0] = blue;			bsp_cube_05[27] = orange;
	bsp_cube_05[1] = orange;		bsp_cube_05[28] = red;
	bsp_cube_05[2] = orange;		bsp_cube_05[29] = green;
	bsp_cube_05[3] = white;			bsp_cube_05[30] = red;
	bsp_cube_05[4] = white;			bsp_cube_05[31] = green;
	bsp_cube_05[5] = green;			bsp_cube_05[32] = green;
	bsp_cube_05[6] = green;			bsp_cube_05[33] = white;
	bsp_cube_05[7] = orange;		bsp_cube_05[34] = white;
	bsp_cube_05[8] = blue;			bsp_cube_05[35] = yellow;

	bsp_cube_05[9] = green;			bsp_cube_05[36] = white;
	bsp_cube_05[10] = red;			bsp_cube_05[37] = yellow;
	bsp_cube_05[11] = orange;		bsp_cube_05[38] = orange;
	bsp_cube_05[12] = yellow;		bsp_cube_05[39] = red;
	bsp_cube_05[13] = yellow;		bsp_cube_05[40] = orange;
	bsp_cube_05[14] = white;		bsp_cube_05[41] = white;
	bsp_cube_05[15] = green;		bsp_cube_05[42] = red;
	bsp_cube_05[16] = orange;		bsp_cube_05[43] = yellow;		
	bsp_cube_05[17] = blue;			bsp_cube_05[44] = red;

	bsp_cube_05[18] = white;		bsp_cube_05[45] = yellow;
	bsp_cube_05[19] = blue;			bsp_cube_05[46] = blue;
	bsp_cube_05[20] = yellow;		bsp_cube_05[47] = red;
	bsp_cube_05[21] = yellow;		bsp_cube_05[48] = blue;
	bsp_cube_05[22] = red;			bsp_cube_05[49] = blue;
	bsp_cube_05[23] = blue;			bsp_cube_05[50] = green;
	bsp_cube_05[24] = white;		bsp_cube_05[51] = yellow;
	bsp_cube_05[25] = green;		bsp_cube_05[52] = orange;
	bsp_cube_05[26] = blue;			bsp_cube_05[53] = red;
}


void set_bsp_fin ()
{
    bsp_cube_fin[0] = red;			bsp_cube_fin[27] = green;
	bsp_cube_fin[1] = red;			bsp_cube_fin[28] = green;
	bsp_cube_fin[2] = red;			bsp_cube_fin[29] = green;
	bsp_cube_fin[3] = red;			bsp_cube_fin[30] = green;
	bsp_cube_fin[4] = red;			bsp_cube_fin[31] = green;
	bsp_cube_fin[5] = red;		    bsp_cube_fin[32] = green;
	bsp_cube_fin[6] = red;			bsp_cube_fin[33] = green;
	bsp_cube_fin[7] = red;			bsp_cube_fin[34] = green;
	bsp_cube_fin[8] = red;			bsp_cube_fin[35] = green;

	bsp_cube_fin[9] = blue;		    bsp_cube_fin[36] = yellow;
	bsp_cube_fin[10] = blue;		bsp_cube_fin[37] = yellow;
	bsp_cube_fin[11] = blue;		bsp_cube_fin[38] = yellow;
	bsp_cube_fin[12] = blue;		bsp_cube_fin[39] = yellow;
	bsp_cube_fin[13] = blue;		bsp_cube_fin[40] = yellow;
	bsp_cube_fin[14] = blue;		bsp_cube_fin[41] = yellow;
	bsp_cube_fin[15] = blue;		bsp_cube_fin[42] = yellow;
	bsp_cube_fin[16] = blue;		bsp_cube_fin[43] = yellow;		
	bsp_cube_fin[17] = blue;		bsp_cube_fin[44] = yellow;

	bsp_cube_fin[18] = orange;		bsp_cube_fin[45] = white;
	bsp_cube_fin[19] = orange;		bsp_cube_fin[46] = white;
	bsp_cube_fin[20] = orange;		bsp_cube_fin[47] = white;
	bsp_cube_fin[21] = orange;		bsp_cube_fin[48] = white;
	bsp_cube_fin[22] = orange;		bsp_cube_fin[49] = white;
	bsp_cube_fin[23] = orange;		bsp_cube_fin[50] = white;
	bsp_cube_fin[24] = orange;		bsp_cube_fin[51] = white;
	bsp_cube_fin[25] = orange;		bsp_cube_fin[52] = white;
	bsp_cube_fin[26] = orange;		bsp_cube_fin[53] = white;
}

#endif
