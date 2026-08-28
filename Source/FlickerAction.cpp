/*!
\file   FlickerAction.cpp
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "General.h"
#include "Sprite.h"

#include "FlickerAction.h"

/*!
\fn     FlickerAction::FlickerAction(int chance)
\param  
\brief  See FlickerAction.h
*/
FlickerAction::FlickerAction(int chance) : chance(chance){}

/*!
\fn     void FlickerAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FlickerAction::operator()(GameObject *obj, float dt){

	//	Roll for flicker
	if(obj && randomInteger(chance) == 0){

		//	Variable: Sprite of `obj`
		Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

		//	Check `spr`
		if(spr) spr -> setColor(0.5f, 0.5f, 0.5f, 1);

	}

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     FlickerAction *FlickerAction::clone() const
\brief  See FlickerAction.h
*/
FlickerAction *FlickerAction::clone() const{

	//	Variable: return value / clone of `this`
	FlickerAction *ans = new FlickerAction(chance);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}