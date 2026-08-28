/*!
\file   ColorWheel.h
\author Kevin Shin
\date   3-16-2023
\brief
		Functions for incrementing bold, saturated colors around a color wheel.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glm/glm.hpp>

/*!
\fn     void incrementColor(glm::vec4 &color, float dc)
\param  color
          Color to increment
\param  dc
          Change in color, measured in 60 degree units around the color wheel (i.e. a value of 6 is one full rotation)
\return Nothing
\brief
        This function increments a color around a color wheel.
*/
void incrementColor(glm::vec4 &color, float dc);

/*!
\fn     void incrementColor(glm::vec3 &color, float dc)
\param  color
          Color to increment
\param  dc
          Change in color, measured in 60 degree units around the color wheel (i.e. a value of 6 is one full rotation)
\return Nothing
\brief
        This function increments a color around a color wheel.
*/
void incrementColor(glm::vec3 &color, float dc);

/*!
\fn     float evaluateColor(const glm::vec4 &color)
\param  color
          Color to evluate
\return Nothing
\brief
        This function finds the float corresponding to a color.
*/
float evaluateColor(const glm::vec4 &color);