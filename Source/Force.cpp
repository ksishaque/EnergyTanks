/*!
\file   Force.cpp
\author Kevin Shin
\date   3-9-2023
\brief
        Functions for creating and managing a knockback force.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "Force.h"

/*!
\fn     Force::Force(const glm::vec3 &n, float s, float t)
\param  n
          direction
\param  s
          magnitude
\param  t
          time
\brief  See Force.h
*/
Force::Force(const glm::vec3 &n, float s, float t) : vel(n * s), time(1), dtScale(1){

	//	Check `t`
	if(t <= 0) time = 0;
	else dtScale /= t;

}

/*!
\fn     bool Force::apply(glm::vec3 &trans, float &r, float dt)
\param  trans
          translation
\param  r
          velocityEffect
\param  dt
          dt
\brief  See Force.h
*/
bool Force::apply(glm::vec3 &trans, float &r, float dt){

	//	Check `time`
	if(time <= 0){

		//	Delete `this`
		delete this;

		//	Return
		return true;

	}

	//	Apply force to `trans` and `r`
	trans += vel * time * dt;
	r *= 1 - time;

	//	Update `time`
	time -= dt *  dtScale;

	//	Return
	return false;

}