/*!
\file   FadeAction.cpp
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "Sprite.h"

#include "FadeAction.h"

/*!
\fn     FadeAction::FadeAction(float from, float to, float t)
\param  from
          from
\param  to
          to
\param  t
          time
\brief  See FadeAction.h
*/
FadeAction::FadeAction(float from, float to, float t) : SequentialAction(), alpha(from), to(to), da((to - from) / t){}

/*!
\fn     void FadeAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FadeAction::operator()(GameObject *obj, float dt){

	//	Check object
	if(obj == nullptr) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Iterate `alpha`
	alpha += da * dt;

	//	Check if `to` has been reached
	if((da >= 0 && alpha >= to) || (da <= 0 && alpha <= to)){

		//	Set alpha
		spr -> setColor(1, 1, 1, to);

		//	Set as completed
		completed(obj, (alpha - to) / da);

	}

	//	Set alpha
	else spr -> setColor(1, 1, 1, alpha);

}

/*!
\fn     FadeAction *FadeAction::clone() const
\brief  See ActionNode.h
*/
FadeAction *FadeAction::clone() const{

	//	Variable: return value / clone of `this`
	FadeAction *ans = new FadeAction(alpha, to, (to - alpha) / da);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}