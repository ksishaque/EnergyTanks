/*!
\file   BehaviorPopup.cpp
\author Kevin Shin
\date   3-25-2023
\brief
        Functions for managing the behavior of a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"
#include "ActivatePopupAction.h"
#include "GameObject.h"
#include "HidePopupAction.h"
#include "PauseSystem.h"
#include "PopupObjectList.h"
#include "ObjectCuller.h"

#include "BehaviorPopup.h"

/*!
\fn     BehaviorPopup::BehaviorPopup()
\brief  See BehaviorPopup.h
*/
BehaviorPopup::BehaviorPopup() : Behavior(), visible(false), active(false), opening(false), toClose(false), pawsable(true), passiveList(nullptr), activeList(nullptr), activeCuller(nullptr), openActions(nullptr), closeActions(nullptr), currentActions(new ActionList()), trans(nullptr){}

/*!
\fn     BehaviorPopup::BehaviorPopup(const BehaviorPopup &that)
\param  that
          source
\brief  See BehaviorPopup.h
*/
BehaviorPopup::BehaviorPopup(const BehaviorPopup &that) : Behavior(), visible(true), active(false), opening(false), toClose(false), pawsable(true), passiveList(nullptr), activeList(nullptr), activeCuller(nullptr), openActions(that.openActions -> clone()), closeActions(that.closeActions -> clone()), currentActions(new ActionList()), trans(nullptr){}

/*!
\fn     void BehaviorPopup::update(float dt)
\param  dt
          dt
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::update(float dt){

	//	Attempt to set `trans`
	if(trans == nullptr){

		//	Variable: Parent of the behavior
		GameObject *par = getParent();

		//	Set `trans` if possible
		if(par) trans = dynamic_cast<Transform *>(par -> get(ComponentTypeEnum::cTransform));

	}

	//	Check `pawsable`
	if(!pawsable) dt = PauseSystem::getInstance() -> getDt();

	//	Check if `visible`
	if(visible){

		//	Update `currentActions`
		currentActions -> update(dt);

		//	Update transformation matrix
		if(trans) trans -> updateMatrix();

		//	Update `activeList` and activeCuller`
		if(active && activeList && activeCuller){

			//	Update `activeList and `activeCuller`
			activeList -> update(dt);
			activeCuller -> update(dt);

		}
		
		//	Display `passiveList`
		if(passiveList) passiveList -> update(dt);

		//	Check `toClose`
		if(toClose){

			//	Close
			close();

			//	Reset `toClose`
			toClose = false;

		}

	}

}

/*!
\fn     BehaviorPopup *BehaviorPopup::clone() const
\brief  See Component.h
*/
BehaviorPopup *BehaviorPopup::clone() const{
	return new BehaviorPopup(*this);
}

/*!
\fn     void BehaviorPopup::setParent(GameObject *par)
\param  par
          parent
\brief  See Compenent.h
*/
void BehaviorPopup::setParent(GameObject *par){

	//	Set `cParent`
	Component::setParent(par);

	//	Shutdown old object lists
	if(passiveList) passiveList -> shutdown();
	if(activeList) activeList -> shutdown();

	//	Delete old object lists
	delete passiveList;
	delete activeList;

	//	Create new object lists
	passiveList = new PopupObjectList(this, true);
	activeList = new PopupObjectList(this, false);

	//	Create new culler
	activeCuller = new ObjectCuller(*activeList);

	//	Set parent for `currentActions`
	currentActions -> setParent(par);

	//	Set `trans` to be reupdated
	trans = nullptr;

}

/*!
\fn     BehaviorPopup::~BehaviorPopup()
\brief  See BehaviorPopup.h
*/
BehaviorPopup::~BehaviorPopup(){
	
	//	Shutdown object lists
	if(passiveList) passiveList -> shutdown();
	if(activeList) activeList -> shutdown();

	//	Delete object list
	delete passiveList;
	delete activeList;

	//	Delete action lists
	delete openActions;
	delete closeActions;
	delete currentActions;

}

/*!
\fn     void BehaviorPopup::open()
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::open(){

	//	Check `opening`
	if(opening){

		//	Refresh `activeList`, if applicable
		if(active){

			//	Shutdown
			activeList -> shutdown();

			//	Reinitialize
			activeList -> initialize();

		}

		//	Return
		return;

	}

	//	Set `opening`
	opening = true;

	//	Set `openActions`
	currentActions -> clear();
	currentActions -> add(openActions);
	currentActions -> add(new ActivatePopupAction(this));

	//	Make visible
	visible = true;
	passiveList -> initialize();

}

/*!
\fn     void BehaviorPopup::activate()
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::activate(){

	//	Clear `currentActions`
	currentActions -> clear();

	//	Set `active`
	active = true;

	//	Initialize `activeList`
	activeList -> initialize();

}

/*!
\fn     void BehaviorPopup::close()
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::close(){

	//	Check `opening`
	if(!opening) return;

	//	Set `opening`
	opening = false;

	//	Set `closeActions`
	currentActions -> clear();
	currentActions -> add(closeActions);
	currentActions -> add(new HidePopupAction(this));

	//	Deactivate
	active = false;
	activeList -> shutdown();

}

/*!
\fn     void BehaviorPopup::hide()
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::hide(){

	//	Clear `currentActions`
	currentActions -> clear();

	//	Set `visible`
	visible = false;
	passiveList -> shutdown();

}

/*!
\fn     void BehaviorPopup::setOpenActions(ActionList *list)
\par    list
          actions
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::setOpenActions(ActionList *list){

	//	Clear previous
	delete openActions;

	//	Set new
	openActions = list;

}

/*!
\fn     void BehaviorPopup::setCloseActions(ActionList *list)
\par    list
          actions
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::setCloseActions(ActionList *list){

	//	Clear previous
	delete closeActions;

	//	Set new
	closeActions = list;

}

/*!
\fn     void BehaviorPopup::settoClose()
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::setToClose(){
	toClose = true;
}

/*!
\fn     void BehaviorPopup::setPAWSable(bool state)
\param  state
          pawsable
\brief  See BehaviorPopup.h
*/
void BehaviorPopup::setPAWSable(bool state){
	pawsable = state;
}