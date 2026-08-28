/*!
\file   BehaviorDisplayMultiMonitor.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a monitor count signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "GameObject.h"
#include "Sprite.h"
#include "Window.h"

#include "BehaviorDisplayMultiMonitor.h"

/*!
\fn     BehaviorDisplayMultiMonitor::BehaviorDisplayMultiMonitor()
\brief  See BehaviorDisplayMultiMonitor.h
*/
BehaviorDisplayMultiMonitor::BehaviorDisplayMultiMonitor() : Behavior(), multiColor(1, 1, 1, 1), singleColor(0, 0, 0, 1){}

/*!
\fn     BehaviorDisplayMultiMonitor::BehaviorDisplayMultiMonitor(const BehaviorDisplayMultiMonitor &that)
\param  that
          source
\brief  See BehaviorDisplayMultiMonitor.h
*/
BehaviorDisplayMultiMonitor::BehaviorDisplayMultiMonitor(const BehaviorDisplayMultiMonitor &that) : Behavior(), multiColor(that.multiColor), singleColor(that.singleColor){}

/*!
\fn     void BehaviorDisplayMultiMonitor::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorDisplayMultiMonitor::update(float dt){

	//	Variable: Parent object
	GameObject *obj = getParent();

	//	Check `obj`
	if(obj == nullptr) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Variable: Number of monitors present
	int mons;

	//	Get `mons`
	GLFWmonitor **foo = glfwGetMonitors(&mons);

	//	Set colors
	//	Set colors
	if(Window::getInstance() -> isFullscreen() && mons > 1) spr -> setColor(multiColor);
	else spr -> setColor(singleColor);

}

/*!
\fn     BehaviorDisplayMultiMonitor *BehaviorDisplayMultiMonitor::clone() const
\brief  See Component.h
*/
BehaviorDisplayMultiMonitor *BehaviorDisplayMultiMonitor::clone() const{
	return new BehaviorDisplayMultiMonitor(*this);
}

/*!
\fn     void BehaviorDisplayMultiMonitor::setMultiColor(const glm::vec4 &col)
\param  col
          color
\brief  See BehaviorDisplayMultiMonitor.h
*/
void BehaviorDisplayMultiMonitor::setMultiColor(const glm::vec4 &col){
	multiColor = col;
}

/*!
\fn     void BehaviorDisplayMultiMonitor::setSingleColor(const glm::vec4 &col)
\param  col
          color
\param  team
          team
\brief  See BehaviorDisplayMultiMonitor.h
*/
void BehaviorDisplayMultiMonitor::setSingleColor(const glm::vec4 &col){
	singleColor = col;
}