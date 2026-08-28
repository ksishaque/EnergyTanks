/*!
\file   BehaviorOptionTrack.cpp
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for managing the behavior of a options track or menu
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "MenuOption.h"

#include "BehaviorOptionTrack.h"

/*!
\fn     BehaviorOptionTrack::BehaviorOptionTrack()
\param  cd
          cooldown
\param  fore
          forSpeed
\param  back
          backSpeed
\param  turn
          turnSpeed
\brief  See BehaviorOptionTrack.h
*/
BehaviorOptionTrack::BehaviorOptionTrack() : options(nullptr), size(0){}

/*!
\fn     BehaviorOptionTrack::BehaviorOptionTrack(const BehaviorOptionTrack &that)
\param  that
          source
\brief  See BehaviorOptionTrack.h
*/
BehaviorOptionTrack::BehaviorOptionTrack(const BehaviorOptionTrack &that) : size(that.size){

	//	Copy `options`
	if(that.options){

		//	Create `options`
		options = new MenuOption *[size];

		//	Clone each option
		for(unsigned i = 0; i < size; i += 1) options[i] = new MenuOption(*(that.options[i]));

	}
	else options = nullptr;

}

/*!
\fn     BehaviorOptionTrack *BehaviorOptionTrack::clone() const
\brief  See Component.h
*/
BehaviorOptionTrack *BehaviorOptionTrack::clone() const{
	return new BehaviorOptionTrack(*this);
}

/*!
\fn    BehaviorOptionTrack::~BehaviorOptionTrack()
\brief See BehaviorOptionTrack.h
*/
BehaviorOptionTrack::~BehaviorOptionTrack(){
	for(unsigned i = 0; i < size; i += 1) delete options[i];
}

/*!
\fn     void BehaviorOptionTrack::setOptions(const std::vector<MenuOption *> &ops)
\param  ops
          options
\brief  See BehaviorOptionTrack.h
*/
void BehaviorOptionTrack::setOptions(const std::vector<MenuOption *> &ops){

	//	Delete previous options
	for(unsigned i = 0; i < size; i += 1) delete options[i];

	//	Set `size`
	size = (unsigned) ops.size();

	//	Create `options`
	options = new MenuOption *[size];

	//	Move each option
	for(unsigned i = 0; i < size; i += 1) options[i] = ops[i];

}

/*!
\fn     MenuOption *BehaviorOptionTrack::getOption(unsigned i)
\param  i
          option
\brief  See BehaviorOptionTrack.h
*/
MenuOption *BehaviorOptionTrack::getOption(unsigned i){
	return options[i];
}
