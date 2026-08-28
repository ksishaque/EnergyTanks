/*!
\file Collider.h
\author Khaled S. Ishaque
\date 9-27-2022
\brief
    Header file for object collider class and functions in class
*/

#pragma once

#include <glm/glm.hpp>

#include "Component.h"

struct BounceInfo;
class GraphicsUnit;

/*!
 * @brief:
 * Class type for a collider component
 */
class Collider : public Component
{
public:

	/*!
	 * @brief:
	 * Enum that houses the types of colliders that a game object
	 * could have
	 * 
	 */
	enum Type
	{
	    None,
	    circle,
	    line,
	    bounds,
	};
    /*!
    * @brief:
    * Default Constructor for Collider class
    * @param:
    * None
    * @return:
    * Nothing
    */
    Collider(Type colType = None);
    /*!
    * @brief:
    * Destructor for Collider class
    * @param:
    * None
    * @return:
    * Nothing
    */
    virtual ~Collider();
    /*!
    * @brief:
    * set the type of collider that the component is
    * @param:
    * colType - the type to assign the collider component
    * @return:
    * Nothing
    */
    void setType(Type type);
    /*!
    * @brief:
    * set the type of collider that the component is
    * @param:
    * colType - the type to assign the collider component
    * @return:
    * Nothing
    */
    Type getType();

    void debugDraw();

    virtual void draw() = 0;

    /*!
    * @brief:
    * Checks to see if any object's collider component is touching each other
    * @param:
    * collider1 - the first collider component to check the collision
    * info1 - the return reference for the displacement of the first collider
    * collider2 - the second collider component to check the collision
    * info2 - the return reference for the displacement of the second collider
    * @return:
    * TRUE if a collision was detected between the 2 colliders
    * FALSE if there is no collision happening between the 2 colliders
    */
    friend bool isColliding(Collider* collider1, BounceInfo& info1, Collider* collider2, BounceInfo& info2);

    void update(float dt) override;
    //Component* clone() const override;
private:
    /*!
     * @brief:
     * If Collider was added to CollisionManager
     */
    bool managerSet;
    /*!
     * @brief:
     * Type of Collider to check
     */
    Type type;
};