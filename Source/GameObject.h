/*****************************************************************//**
 * \file   GameObject.h
 * \brief  
 * 
 * \author Luke Tseng
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/

#pragma once
#include <vector>
#include <algorithm>
#include <string>

typedef class Component Component, * ComponentPtr;
typedef enum class ComponentTypeEnum ComponentTypeEnum;

class GameObject;

#include "Component.h"

class ObjectContainer;

class GameObject
{
public:
	enum Type
	{
		Player, Bullet, Wall, Map, Shield, Health, Button, Powerup, Visual, Miscelaneous, Invalid
	};
    
    enum Team
    {
        Left = -1, Neutral = 0, Right = 1
    };

	/**
	 * Default constructor
	 * 
	 */
	GameObject();
	/**
	 * Copy constructor
	 * 
	 * \param gameObject GameObject to copy
	 */
	GameObject(const GameObject& gameObject);
	/**
	 * Destructor
	 * 
	 */
	~GameObject();
	/**
	 * Clones GameObject
	 * 
	 * \return Cloned GameObject 
	 */
	GameObject* clone();

	/**
	 * Updates every component of the GameObject
	 * 
	 * \param dt Speed of the frame
	 */
	void update(float dt);
	/**
	 * Sets an object manager for gameObject
	 * \param manager Object manager to be set as `GameObject::manager`
	 */
	void setManager(ObjectContainer *manager);
	/**
	 * Gets an object manager for gameObject
	 * 
	 * \return Manager of the game object
	 */
	ObjectContainer *getManager();
	/**
	 * Adds component to gameObject
	 * \param component Component to add
	 */
	void add(Component* component);
	/**
	 * Getting component pointer from gameobject
	 * \param type component type to get
	 * \return component pointer
	 */
	Component* get(ComponentTypeEnum type);
	/**
	 * Getting component pointer from gameobject
	 * \param type component type to get
	 * \return component pointer
	 */
	const Component* get(ComponentTypeEnum type) const;
    /**
     * uses binary search to find component index and removes from vector
     * 
     * \param type Finds component of type
     * \return 1 if removed successfully 0 if not found
     */
    bool remove(ComponentTypeEnum type);
	/**
	 * Checking if gameobject contains a type of component
	 * \param type checking type of component
	 * \return whether gameobject has the type of component
	 */
	bool has(ComponentTypeEnum type);
    /**
     * Sets the game object's destroyed bool
     * \param des setting the isDestroyed bool true or false
     */
    void setDestroyed(bool des = true);
    /**
     * Gets the game object's destroyed bool
	 * 
	 * \return destroyed state of the game object
     */
    bool isDestroyed() const;

    /**
     * Sets the game object's type
     * 
     * \param Type to set object to
     */
    void setType(Type aType);
    /**
     * Gets the game object's type
     * 
     * \return Type of the object
     */
    Type getType();
    /**
    * Sets the game object's team
    * 
    * \param Team to set object to
    */
    void setTeam(Team aTeam);
    /**
     * Gets the game object's Team
     * 
     * \return Team of the object
     */
    Team getTeam();
    /**
    * Sets the game object's name
    * 
    * \param Name to set object to
    */
    void setName(const std::string &aName);
    /**
     * Gets the game object's Name
     * 
     * \return Name of the object
     */
    std::string getName();
    /**
    * Checks if name matches string
    * 
    * \return True if it matches, false if not
    */
    bool checkName(std::string aName);

private:
    std::string name;
    Team team;
	bool destroyed;
	std::vector<Component*> components;
    Type type;
	/**
	 * The object manager storing the game object
	 */
	ObjectContainer *manager;
	/**
	 * Uses binary search to find component
	 * 
	 * \param type Finds component of type
	 * \return component ptr
	 */
	Component *componentSearch(ComponentTypeEnum type) const;


};
