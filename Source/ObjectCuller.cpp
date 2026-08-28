/*!
\fnile  ObjectCuller.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-13-2022
\brief
        Functions for creating and maintaining an object culler for the object manager
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <iterator>

#include "CollisionManager.h"
#include "GameObject.h"
#include "ObjectContainer.h"

#include "ObjectCuller.h"

using std::vector;

#define LINKED_LIST_MANAGERX

/*!
\fn     void ObjectCuller::update()
\param  dt
          dt
\brief  See ISystem.h
*/
void ObjectCuller::update(float &dt){
	cull();
}

/*!
\fn     void ObjectCuller::cull() const
\brief  See ObjectCuller.h
*/
void ObjectCuller::cull() const{

	//	Variable: iterator of the list
	vector<GameObject *>::iterator i = target.begin(); 

	//	Search for destroyed game objects
	while(i != target.end()){

		//	
		if((**i).isDestroyed()){

#ifdef LINKED_LIST_MANAGER
			//	Variable: next iterator after `i`
			vector<GameObject *>::iterator next = std::next(i);
#endif

			//	Delete the object
			delete *i;

			//	Remove `i`
			i = target.erase(i);

#ifdef LINKED_LIST_MANAGER
			//	Move to `next`
			i = next;
#endif

		}

		else ++i;
	}
}

/*!
\fn     ObjectCuller::ObjectCuller(ObjectManager *target)
\param  target
          target
\brief  See ObjectCuller.h
*/
ObjectCuller::ObjectCuller(ObjectContainer &target) : ISystem(sCuller), target(target.getObjectList()){
	target.setCuller(this);
}