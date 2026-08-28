/*****************************************************************//**
 * \file   GameObject.cpp
 * \brief
 *
 * \author Luke Tseng
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#include "GameObject.h"
#include "Component.h"
#include "Trace.h"
#include "Renderer.h"
#include "CollisionManager.h"
#include "General.h"
#include "DebugSystem.h"

struct compareComponents {
	/**
	* operator
	*      function used in sort function to sort components
	* \param l
	*      first component
	* \param r
	*      second component
	* \return
	*      returns which one goes first
	*/
	bool operator()(Component* l, Component* r)
	{
		return(l->getType() < r->getType());
	}
};

GameObject::GameObject() :
destroyed(false),
manager(nullptr),
type(Invalid),
team(Neutral),
name("")
{
#ifdef DEBUG_SYSTEM
	Trace::message("CTOR: Game Object \"%s\" (%p)", name.c_str(), this);
#endif
}

GameObject::GameObject(const GameObject& gameObject) :
destroyed(false),
manager(gameObject.manager),
type(gameObject.type),
team(gameObject.team)
{
#ifdef DEBUG_SYSTEM
	Trace::message("CCTR: Game Object \"%s\" (%p)", name.c_str(), this);
#endif
	name = "~" + gameObject.name;
	for (Component* component : gameObject.components)
	{
		if (component)
		{
			add(component->clone());
		}
	}
}

GameObject::~GameObject()
{
#ifdef DEBUG_SYSTEM
	Trace::message("DTOR: Game Object \"%s\"", name.c_str());
#endif
	for (Component* component : components)
	{
		if (component)
		{
			delete component;
		}
	}
}

GameObject* GameObject::clone()
{
	return new GameObject(*this);
}

void GameObject::update(float dt)
{
    //updates every component
    for (Component* component : components)
    {
        if (component)
        {
            component->update(dt);
        }
    }

	//checks for debug draw
#ifdef DEBUG_SYSTEM
	if (DebugSystem::getInstance()->getFlag(DebugSystem::DebugFlag::DRAW))
	{
	    for (Component* c : components)
	    {
	        if (c)
	        {
	            c->debugDraw();
	        }
	    }
	}
#endif
}

void GameObject::add(Component* component)
{
	if (component)
	{
#ifdef DEBUG_SYSTEM
        if (has(component->getType()))
        {
            int result = remove(component->getType());
            if (result == 0)
            {
                Trace::message("Component to remove not found");
            }
        }
#endif
		//setting parent of compoent
		component->setParent(this);
		//adding component
		components.push_back(component);
		//sorting list of components
		std::sort(components.begin(), components.end(), pointerCompare<Component>);
	}
}

Component* GameObject::get(ComponentTypeEnum type)
{
	//binary search to find component of type and return it

	return componentSearch(type);
}

bool GameObject::has(ComponentTypeEnum type)
{
	//returns whether it can find component in components
	return (componentSearch(type) != NULL);
}

Component* GameObject::componentSearch(ComponentTypeEnum type) const
{
	return binarySearch<Component, std::vector<Component *>, ComponentTypeEnum>(components, [](Component* comp, ComponentTypeEnum type){
		return (int) comp -> getType() - (int) type;
	}, type);
}

bool GameObject::remove(ComponentTypeEnum type)
{
    int start = 0;
    int end = (int)components.size() - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (type == components[mid]->getType())
        {
			delete components[mid];
            components.erase(components.begin() + mid);
            return true;
        }
        else if (type > components[mid]->getType())
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return false;
}

void GameObject::setManager(ObjectContainer *man)
{
	manager = man;
}

const Component* GameObject::get(ComponentTypeEnum type) const
{
	//binary search to find component of type and return it

	return componentSearch(type);
}

ObjectContainer *GameObject::getManager()
{
	return manager;
}


void GameObject::setDestroyed(bool des)
{
    destroyed = des;
}

void GameObject::setType(GameObject::Type aType)
{
    type = aType;
}

GameObject::Type GameObject::getType()
{
    return type;
}

void GameObject::setTeam(Team aTeam)
{
    team = aTeam;
}

GameObject::Team GameObject::getTeam()
{
    return team;
}

void GameObject::setName(const std::string &aName)
{
    name = aName;
#ifdef DEBUG_SYSTEM
	Trace::message(" Game Object Renamed \"%s\" (%p)", name.c_str(), this);
#endif
}

std::string GameObject::getName()
{
    return name;
}

bool GameObject::checkName(std::string aName)
{
    if (name == aName)
    {
        return true;
    }
    return false;
}

bool GameObject::isDestroyed() const
{
    return destroyed;
}
