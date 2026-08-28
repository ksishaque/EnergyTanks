/*!
\file   General.cpp
\author Kevin Shin
\date   11-11-2022
\brief
		Functions for general use
\par    Copyright � 2022 DigiPen, All rights reserved.
\par    NOTE: Due to templatized functions, this file is excluded from being built, and is instead included in General.h.
*/

#pragma once

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <random>

#include "Trace.h"

#include "General.h"

static bool randomSeedSet = false;

/*!
\fn     int randomInteger(int max, int min)
\param  max
          max
\param  min
          min
\brief  See General.h
*/
int randomInteger(int max, int min){
	
	//	Check if a random seed has been set
	if(!randomSeedSet){

		//	Set a random seed
		srand(0);
		randomSeedSet = true;

	}

	//	Generate and return a random value
	int temp1 = rand();
	double temp = temp1 / (double) RAND_MAX;
	temp *= max - min;
	temp += min;
	return (int) temp;

}

/*!
\fn     void checkGLError()
\param  info
          info
\brief  See General.h
*/
void checkGLError(const char *info){

    //	Get the current error value
    GLenum error = glGetError();

    //	Check if there is an error
#ifdef DEBUG_SYSTEM
    if(error != GL_NO_ERROR) Trace::error("OpenGL error (%s): %u", info, error);
#endif

}

/*!
\fn     bool quadraticFormula(float a, float b, float c, float &ans, bool minus)
\param  a
          a
\param  b
          b
\param  c
          c
\brief  See General.h
*/
bool quadraticFormula(float a, float b, float c, float &ans, bool minus){

	//	Variable: Discriminant of the equation
	float dis = (b * b) - (4 * a * c);

	//	Check `dis`
	if(dis < 0) return false;

	//	Check for linear equation
	if(a == 0){

		//	Check for flat line
		if(b == 0) return false;

		//	Calculate
		ans = -c;
		ans /= b;

		//	Return
		return true;

	}

	//	Calculate the half-range
	ans = glm::sqrt(dis);

	//	Check if half-range should be subtracted
	if(minus) ans *= -1;
	if(a < 0) ans *= -1;

	//	Calculate `ans`
	ans -= b;
	ans /= 2;
	ans /= a;

	//	Return
	return true;

}