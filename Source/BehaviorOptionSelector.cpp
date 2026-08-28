/*!
\file   BehaviorOptionSelector.cpp
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for managing the behavior of a player selector
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorOptionTrack.h"
#include "GameObject.h"
#include "MenuOption.h"
#include "ObjectContainer.h"

#include "BehaviorOptionSelector.h"

/*!
\fn     BehaviorOptionSelector::BehaviorOptionSelector()
\brief  See BehaviorOptionSelector.h
*/
BehaviorOptionSelector::BehaviorOptionSelector() : BehaviorControllable(), optionInit(""), i(0), dt(0), options(nullptr){}

/*!
\fn     BehaviorOptionSelector::BehaviorOptionSelector(const BehaviorOptionSelector &that)
\param  that
          source
\brief  See BehaviorOptionSelector.h
*/
BehaviorOptionSelector::BehaviorOptionSelector(const BehaviorOptionSelector &that) : BehaviorControllable(), i(0), dt(0), options(that.options){

	//	Check `option`
	if(options) optionInit = "";
	else optionInit = that.optionInit;

}

/*!
\fn     void BehaviorOptionSelector::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorOptionSelector::update(float dt){

	//	Save `dt`
	this -> dt = dt;

	//	Check `options`
	if(options == nullptr){

		//	Variable: Object parent of `this`
		GameObject *par = getParent();

		//	Check `par`
		if(par){

			//	Variable: Container containing `par`
			ObjectContainer *man = par -> getManager();

			//	Check `man`
			if(man){

				//	Variable: Object of the option selections
				GameObject *obj = man -> findObject(optionInit);

				//	Check `obj`
				if(obj){

					//	Set `options`
					options = dynamic_cast<BehaviorOptionTrack *>(obj -> get(ComponentTypeEnum::cBehavior));

					//	Check `options`
					if(options){

						//	Variable: Current option
						MenuOption *option = options -> getOption(i);

						//	Place at `option`
						if(option) option -> placeSelector(getParent());

					}

				}

			}

		}

	}

	//	Update parent
	BehaviorControllable::update(dt);

}

/*!
\fn     BehaviorOptionSelector *BehaviorOptionSelector::clone() const
\brief  See Component.h
*/
BehaviorOptionSelector *BehaviorOptionSelector::clone() const{
	return new BehaviorOptionSelector(*this);
}

/*!
\fn     void BehaviorOptionSelector::setOption(const std::string &name)
\param  name
          name
\brief  See BehaviorOptionSelector.h
*/
void BehaviorOptionSelector::setOption(const std::string &name){
	optionInit = name;
}

/*!
\fn     void actionCall(ControlType act, ControlManager::KeyState key)
\param  act
          action
\param  key
          keyState
\brief  See BehaviorControllable.h
*/
void BehaviorOptionSelector::actionCall(ControlUnit::ControlType act, ControlManager::KeyState key){

	//	Check `options`
	if(options == nullptr || act > CONTROL_UNIT_KEY_MAX) return;
	
	//	Variable: Current option
	MenuOption *option = options -> getOption(i);
	
	//	Select `option`
	if(option) option -> select(getParent(), act, key, dt);

}

/*!
\fn     void BehaviorOptionSelector::setOption(unsigned i)
\param  i
          option
\brief  See BehaviorOptionSelector.h
*/
void BehaviorOptionSelector::setOption(unsigned i){

	//	Set `i`
	this -> i = i;

	//	Check `options`
	if(options == nullptr) return;
	
	//	Variable: Current option
	MenuOption *option = options -> getOption(i);
	
	//	Place at `option`
	if(option) option -> placeSelector(getParent());

}

/*!
\fn     BehaviorOptionSelector::~BehaviorOptionSelector()
\brief  See BehaviorOptionSelector.h
*/
BehaviorOptionSelector::~BehaviorOptionSelector(){
	options = nullptr;
}