/*!
\fnile  ObjectContainer.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   3-24-2023
\brief
        Functions for creating and maintaining a game object container
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ObjectFactory.h"
#include "ObjectCuller.h"
#include "Trace.h"

#include "ObjectContainer.h"

using std::vector;
using std::string;

/*!
\fn     void ObjectContainer::initialize()
\brief  See ObjectContainer.h
*/
void ObjectContainer::initialize(){

	//	Check if the system is already active
	if(isActive()) return;

	//	Initialize the system
	ISystem::initialize();

	//	Load current gamestate
	parseManager(*this);

}

/*!
\fn     void ObjectContainer::update()
\param  dt
          dt
\brief  See ObjectContainer.h
*/
void ObjectContainer::update(float &dt){

	//	Check if the system is active
	if(!isActive()) return;

	//	Update every object
	for(GameObject *object : objects) object -> update(dt);

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
\fn     void ObjectContainer::shutdown()
\brief  See ObjectContainer.h
*/
void ObjectContainer::shutdown(){

	//	Check if the system was active
	if(!isActive()) return;

	//	Shutdown the system
	ISystem::shutdown();

	//	Delete all objects

	for(GameObject *object : objects) delete object;
	objects.clear();

}

/*!
\fn     void ObjectContainer::addObject(GameObject *object)
\param  obj
          object
\brief  See ObjectContainer.h
*/
void ObjectContainer::addObject(GameObject *obj){
	if(obj) addQueue.push(obj);
}

/*!
\fn     ObjectContainer::ObjectContainer()
\param  name
          name
\brief  See ObjectContainer.h
*/
ObjectContainer::ObjectContainer() : ISystem(sObjMan), culler(nullptr), objects(), addQueue(), matrix(nullptr){}

/*!
\fn     const vector<GameObject *> &ObjectContainer::getObjectList() const
\brief  See ObjectContainer.h
*/
const vector<GameObject *> &ObjectContainer::getObjectList() const{
	return objects;
}

/*!
\fn     vector<GameObject *> &ObjectContainer::getObjectList()
\brief  See ObjectContainer.h
*/
vector<GameObject *> &ObjectContainer::getObjectList(){
	return objects;
}

/*!
\var    const GameObject *ObjectContainer::findObject(const std::string &name) const
\param  name
          name
\brief  See ObjectContainer.h
*/
const GameObject *ObjectContainer::findObject(const std::string &name) const{

	//	No order -> sequential search
	for(GameObject *object : objects) if(object -> checkName(name)) return object;

	//	Return
	return nullptr;
	
}

/*!
\var    GameObject *ObjectContainer::findObject(const std::string &name)
\param  name
          name
\brief  See ObjectContainer.h
*/
GameObject *ObjectContainer::findObject(const std::string &name){

	//	No order -> sequential search
	for(GameObject *object : objects) if(object -> checkName(name)) return object;

	//	Return
	return nullptr;
	
}

/*!
\var    void ObjectContainer::setCuller(const ObjectCuller *cul)
\param  cul
          culler
\brief  See ObjectContainer.h
*/
void ObjectContainer::setCuller(const ObjectCuller *cul){
	culler = cul;
}

/*!
\fn     void ObjectContainer::addObject(const std::string &name, bool g)
\param  name
          name
\param  g
          global
\brief  See ObjectContainer.h
*/
void ObjectContainer::addObject(const std::string &name, bool g){
	parseObject(*this, name, g);
}

/*!
\fn     const glm::mat4 &ObjectContainer::getViewMatrix() const
\brief  See ObjectContainer.h
*/
const glm::mat4 &ObjectContainer::getViewMatrix() const{

	//	Check `matrix`
#ifdef DEBUG_SYSTEM
	if(matrix == nullptr) Trace::error("Container %s without matrix!", getName());
#endif

	//	Return
	return *matrix;

}