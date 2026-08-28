/*!
\file   BehaviorDisplayFullscreen.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a display mode signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "Sprite.h"
#include "Window.h"

#include "BehaviorDisplayFullscreen.h"

/*!
\fn     BehaviorDisplayFullscreen::BehaviorDisplayFullscreen()
\brief  See BehaviorDisplayFullscreen.h
*/
BehaviorDisplayFullscreen::BehaviorDisplayFullscreen() : Behavior(), fullColor(1, 1, 1, 1), winColor(0, 0, 0, 1){}

/*!
\fn     BehaviorDisplayFullscreen::BehaviorDisplayFullscreen(const BehaviorDisplayFullscreen &that)
\param  that
          source
\brief  See BehaviorDisplayFullscreen.h
*/
BehaviorDisplayFullscreen::BehaviorDisplayFullscreen(const BehaviorDisplayFullscreen &that) : Behavior(), fullColor(that.fullColor), winColor(that.winColor){}

/*!
\fn     void BehaviorDisplayFullscreen::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorDisplayFullscreen::update(float dt){

	//	Variable: Parent object
	GameObject *obj = getParent();

	//	Check `obj`
	if(obj == nullptr) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Set colors
	if(Window::getInstance() -> isFullscreen()) spr -> setColor(fullColor);
	else spr -> setColor(winColor);

}

/*!
\fn     BehaviorDisplayFullscreen *BehaviorDisplayFullscreen::clone() const
\brief  See Component.h
*/
BehaviorDisplayFullscreen *BehaviorDisplayFullscreen::clone() const{
	return new BehaviorDisplayFullscreen(*this);
}

/*!
\fn     void BehaviorDisplayFullscreen::setFullscreenColor(const glm::vec4 &col)
\param  col
          color
\brief  See BehaviorDisplayFullscreen.h
*/
void BehaviorDisplayFullscreen::setFullscreenColor(const glm::vec4 &col){
	fullColor = col;
}

/*!
\fn     void BehaviorDisplayFullscreen::setWindowedColor(const glm::vec4 &col)
\param  col
          color
\brief  See BehaviorDisplayFullscreen.h
*/
void BehaviorDisplayFullscreen::setWindowedColor(const glm::vec4 &col){
	winColor = col;
}