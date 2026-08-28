/*!
\fnile  ObjectManager.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-13-2022
\brief
        Functions for creating and maintaining a game object manager
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ObjectFactory.h"
#include "ObjectCuller.h"
#include "Trace.h"

#include "ObjectManager.h"

using std::vector;
using std::string;

/*!
\fn     void ObjectManager::update()
\param  dt
          dt
\brief  See ObjectManager.h
*/
void ObjectManager::update(float &dt){

	//	Check if the system is active
	if(!isActive()) return;

	//	Update every object
	for(GameObject *object : objects) object -> update(dt);
	for(GameObject *foreigner : foreigners) foreigner -> update(dt);

	//	Reload the gamestate if necessary
	if(loadLock && !stateLock){

		//	Clear `addQueue`
		while(!addQueue.empty()){

			//	Clear each object
			delete addQueue.front();

			//	Remove the object from the queue
			addQueue.pop();

		}
		
		//	Load new gamestate
		parseManager(*this, loadReset);

		//	Cull old gamestate
		culler -> cull();

		//	Unlock `loadLock` and `loadReset`
		loadLock = false;
		loadReset = false;

	}

	//	Add objects in `addQueue`
	while(!addQueue.empty()){

		//	Add object to `objects`
		objects.push_back(addQueue.front());

		//	Set as parent
		addQueue.front() -> setManager(this);

		//	Remove the object from the queue
		addQueue.pop();

	}

}

/*!
\var    DEFAULT_MATRIX
          See ObjectManager.h
*/
const glm::mat4 ObjectManager::DEFAULT_MATRIX = glm::mat4(1
);

/*!
\fn     ObjectManager::ObjectManager(const std::string &name)
\param  name
          name
\brief  See ObjectManager.h
*/
ObjectManager::ObjectManager(const std::string &name) : ObjectContainer(), name(name), loadLock(false), loadReset(false), stateLock(false), foreigners(){
	matrix = &DEFAULT_MATRIX;
}

/*!
\fn     const string &ObjectManager::getName() const
\brief  See ObjectManager.h
*/
const string &ObjectManager::getName() const{
	return name;
}

/*!
\fn     void ObjectManager::changeState(const string &name)
\param  name
          stateName
\brief  See ObjectManager.h
*/
void ObjectManager::changeState(const string &name){

	//	Set `name`
	this -> name = name;

	//	Load new state
	loadLock = true;

}

/*!
\fn     void ObjectManager::changeState()
\brief  See ObjectManager.h
*/
void ObjectManager::changeState(){

	//	Reload state
	loadLock = true;

	//	Reload existing objects
	loadReset = true;

}

/*!
\fn     ObjectManager *ObjectManager::getInstance()
\brief  See ObjectManager.h
*/
ObjectManager *ObjectManager::getInstance(){

	//	Check `instance`
	if(instance == nullptr)
#ifdef DEBUG_SYSTEM
		if(Trace::error("No object manager"))
#endif
			instance = new ObjectManager("Title");

	//	Return
	return instance;
}

/*!
\fn     void ObjectManager::closeInstance()
\brief  See ObjectManager.h
*/
void ObjectManager::closeInstance(){
	delete instance;
}

/*!
\fn     ObjectManager *ObjectManager::getInstance(const string &name)
\param  name
          name
\brief  See ObjectManager.h
*/
ObjectManager *ObjectManager::getInstance(const string &name){

	//	Check and delete `instance`
	delete instance;

	//	Create new instance
	instance = new ObjectManager(name);

	//	Return
	return instance;
}

/*!
\var    ObjectManager::instance
\brief  See ObjectManager.h
*/
ObjectManager *ObjectManager::instance = nullptr;

/*!
\fn     void ObjectManager::initialize()
\brief  See ISystem.h
*/
void ObjectManager::initialize(){

	//	Check if the system is already active
	if(isActive()) return;

	//	Initialize the system
	ISystem::initialize();

	//	Load current gamestate
	changeState();

	//	Make sure `foreigners` is clear
	foreigners.clear();

}

/*!
\fn     void ObjectManager::addForeignObject(GameObject *obj)
\param  obj
          object
\brief  See ObjectManager.h
*/
void ObjectManager::addForeignObject(GameObject *obj){
	if(obj) foreigners.push_back(obj);
}

/*!
\fn     void ObjectManager::removeForeignObject(GameObject *obj)
\param  obj
          object
\brief  See ObjectManager.h
*/
void ObjectManager::removeForeignObject(GameObject *obj){

	//	Check `obj`
	if(obj == nullptr) return;

	//	Variable: Iterator to find `obj`
	std::vector<GameObject *>::iterator it = foreigners.begin();

	//	Find `it`
	while(*it != obj){
		
		//	Iterate `it`
		++it;

		//	Check for end
		if(it == foreigners.end()) return;

	}

	//	Remove `it`
	foreigners.erase(it);

}

/*!
\fn     void ObjectManager::lockState(bool lock)
\param  lock
          lock
\brief  See ObjectManager.h
*/
void ObjectManager::lockState(bool lock){
	stateLock = lock;
}