/*!
\file   ColorWheel.cpp
\author Kevin Shin
\date   3-16-2023
\brief
		Functions for incrementing bold, saturated colors around a color wheel.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ColorWheel.h"

/*!
\fn     static float incColVal(float *c, float dc)
\param  c
          Value to increment
\param  dc
          Value to increment by
\return Remaining amount of `dc`
\brief
        This function increments a specific color value.
*/
static float incColVal(float *c, float dc){

	//	Increment
	*c += dc;

	//	Variable: Return value / overflow
	float ans = 0;

	//	Check for `ans`
	if(*c > 1){

		//	Get `ans`
		ans = *c - 1;

		//	Clamp
		*c = 1;

	}
	else if(*c < 0){

		//	Get `ans`
		ans = *c;

		//	Clamp
		*c = 0;

	}

	//	Return
	return ans;

}

/*!
\fn     void incrementColor(glm::vec4 &col, float dc)
\param  colVec
          color
\param  dc
          dc
\brief  See ColorWheel.h
*/
void incrementColor(glm::vec4 &colVec, float dc){

	//	Check `dc`
	if(dc == 0) return;

	/*	Variables:
	col: RGB values of `colVec`, put in an array
	sect: Sector in which the color is currently in according to the following key (kept as an unsigned integer for convenience):
		0: [Red, Yellow)
		1: [Yellow, Green)
		2: [Green, Cyan)
		3: [Cyan, Blue)
		4: [Blue, Magenta)
		5: [Magenta, Red)
	*/
	float *(col[3]) = {&colVec.r, &colVec.g, &colVec.b};
	unsigned sect;

	//	Get `sect`
	if(*(col[2]) == 1){

		//	Eliminate sector 3
		if(*(col[1]) == 0){

			//	Catch magenta case
			if(*(col[0]) == 1) sect = 5;

			//	Sector 4
			else sect = 4;

		}

		//	Sector 3
		else if(*(col[0]) == 0) sect = 3;

		//	Invalid
		else return;

	}
	else if(*(col[1]) == 1){

		//	Sector 2
		if(*(col[0]) == 0) sect = 2;

		//	Sector 1
		else if(*(col[2]) == 0) sect = 1;

		//	Invalid
		else return;

	}
	else if(*(col[0]) == 1){

		//	Sector 0
		if(*(col[2]) == 0) sect = 0;

		//	Sector 5
		else if(*(col[1]) == 0) sect = 5;

		//	Invalid
		else return;

	}

	//	Invalid
	else return;

	//	Variable: Amount to change sect by, in case of overflow
	unsigned ds;

	//	Get `ds`
	if(dc > 0) ds = 1;
	else ds = 5;

	//	Increment `col`
	while(dc != 0){

		//	Increment a specific color value
		if(sect % 2 == 0) dc = incColVal(col[(7 - sect) % 3], dc);
		else dc = incColVal(col[(7 - sect) % 3], -dc) * -1;

		//	Update `sect`
		sect += ds;
		sect %= 6;

	}

}

/*!
\fn     void incrementColor(glm::vec3 &col, float dc)
\param  colVec
          color
\param  dc
          dc
\brief  See ColorWheel.h
*/
void incrementColor(glm::vec3 &colVec, float dc){

	//	Check `dc`
	if(dc == 0) return;

	/*	Variables:
	col: RGB values of `colVec`, put in an array
	sect: Sector in which the color is currently in according to the following key (kept as an unsigned integer for convenience):
		0: [Red, Yellow)
		1: [Yellow, Green)
		2: [Green, Cyan)
		3: [Cyan, Blue)
		4: [Blue, Magenta)
		5: [Magenta, Red)
	*/
	float *(col[3]) = {&colVec.r, &colVec.g, &colVec.b};
	unsigned sect;

	//	Get `sect`
	if(*(col[2]) == 1){

		//	Eliminate sector 3
		if(*(col[1]) == 0){

			//	Catch magenta case
			if(*(col[0]) == 1) sect = 5;

			//	Sector 4
			else sect = 4;

		}

		//	Sector 3
		else if(*(col[0]) == 0) sect = 3;

		//	Invalid
		else return;

	}
	else if(*(col[1]) == 1){

		//	Sector 2
		if(*(col[0]) == 0) sect = 2;

		//	Sector 1
		else if(*(col[2]) == 0) sect = 1;

		//	Invalid
		else return;

	}
	else if(*(col[0]) == 1){

		//	Sector 0
		if(*(col[2]) == 0) sect = 0;

		//	Sector 5
		else if(*(col[1]) == 0) sect = 5;

		//	Invalid
		else return;

	}

	//	Invalid
	else return;

	//	Variable: Amount to change sect by, in case of overflow
	unsigned ds;

	//	Get `ds`
	if(dc > 0) ds = 1;
	else ds = 5;

	//	Increment `col`
	while(dc != 0){

		//	Increment a specific color value
		if(sect % 2 == 0) dc = incColVal(col[(7 - sect) % 3], dc);
		else dc = incColVal(col[(7 - sect) % 3], -dc) * -1;

		//	Update `sect`
		sect += ds;
		sect %= 6;

	}

}

/*!
\fn     float evaluateColor(const glm::vec4 &col)
\param  col
          color
\brief  See ColorWheel.h
*/
float evaluateColor(const glm::vec4 &col){

	//	Find the sector
	if(col.b == 1){

		//	Sector 4
		if(col.g == 0) return 4 + col.r;

		//	Sector 3
		if(col.r == 0) return 4 - col.g;

	}
	else if(col.g == 1){

		//	Sector 2
		if(col.r == 0) return 2 + col.b;

		//	Sector 1
		if(col.b == 0) return 2 - col.r;

	}
	else if(col.r == 1){

		//	Sector 0
		if(col.b == 0) return col.g;

		//	Sector 5
		if(col.g == 0) return 6 - col.b;

	}

	//	Invalid
	return -1;

}