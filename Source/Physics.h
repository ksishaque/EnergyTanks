/*!
\file Physics.h
\author Khaled S. Ishaque
\date 9-9-2022
\brief
    Header file for object physics class and functions in class
\par Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <vector>

typedef class Physics* PhysicsPtr;

class Force;

class Physics : public Component 
{
public:
    /*!
        \fn     Physics()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function creates a new physics class and set all values to 0
     */
	Physics(float translX = 0, float translY = 0, float translZ = 0, 
        float accelX = 0, float accelY = 0, float accelZ = 0, 
        float velX = 0, float velY = 0, float velZ = 0);
    /*!
        \fn     ~Physics()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destroys a physics class
     */
	~Physics();
    /*!
        \fn     Physics(const Physics& basePhysics)
        \par    basePhysics
                    Already made Physics class
        \return Nothing
        \brief
                This function creates a new physics class and copies it's values
                from basePhysics
     */
	Physics(const Physics& basePhysics);
    /*!
        \fn     void read(FILE* file)
        \par    file
                    an opened file to read values from
        \return Nothing
        \brief
                Reads values from a file and sets variables to values from file
     */
	void read(FILE* file);
    /*!
        \fn     glm::vec3 getAcceleration();
        \par    None
        \return A glm::vec3
        \brief
                This function gets the acceleration from a physics class and gives
                it to whatever function needs it
     */
    glm::vec3 getAcceleration();
    /*!
        \fn     glm::vec3 getOldTransl();
        \par    None
        \return A glm::vec3
        \brief
                This function gets the old translation from a physics class
                and gives it to whatever function needs it
     */
    glm::vec3 getOldTransl();
    /*!
        \fn     glm::vec3 getVelocity();
        \par    None
        \return A glm::vec3
        \brief
                This function gets the velocity from a physics class and gives
                it to whatever function needs it
     */
    glm::vec3 getVelocity();
    /*!
        \fn     float getRotateVelocity();
        \par    None
        \return A float
        \brief
                This function gets the rotational velocity from a
                physics class and gives it to whatever function needs it
     */
	float getRotateVelocity();
    /*!
        \fn     void accelerationSet(glm::vec3 newAccel)
        \par    newAccel
                    New acceleration vector for physics class
        \return Nothing
        \brief
                Sets acceleration vector to value given from parameter
     */
    void setAcceleration(glm::vec3 newAccel);
    /*!
        \fn     void setVelocity(glm::vec3 newVel)
        \par    newAccel
                    New velocity vector for physics class
        \return Nothing
        \brief
                Sets velocity vector to values given from parameter
     */
    void setVelocity(glm::vec3 newVel);
    /*!
        \fn     void velocityRotatenSet(float rotVel)
        \par    rotVel
                    New rotational velocity for physics class
        \return Nothing
        \brief
                Sets rotational velocity to values given from parameter
     */
    void setVelocityRotate(float rotVel);
    /*!
        \fn     void setRotatedVelocity(glm::vec3 newVel)
        \par    newVel
                    New velocity vector for physics class
        \return Nothing
        \brief
                Sets velocity vector to values given from parameter in the orientation of the object
     */
    void setRotatedVelocity(glm::vec3 newVel);
    /*!
        \fn     void updateOldTrans()
        \par    This function has no parameters
        \return Nothing
        \brief
                updates the old translation in the physics class
     */
    void updateOldTrans();
    /*!
        \fn     void setOldTrans(const glm::vec3& trans)
        \par    trans
		          Old translation to set
        \return Nothing
        \brief
                sets the old translation in the physics class
     */
    void setOldTrans(const glm::vec3& trans);
    /*!
        \fn     void addForce(const glm::vec3& dir, float mag, float time)
        \par    dir
		          Normalized vector indicating the direction of the force
		\par    mag
		          Initial magnitude of the force
		\par    time
		          Lifetime of the force
        \return Nothing
        \brief
                builds and adds a new force to the physics class
     */
    void addForce(const glm::vec3& dir, float mag = 300, float time = 0.5f);
    /*!
        \fn     void clearForces()
        \par    None
        \return Nothing
        \brief
                clears all forces on the physics class
     */
    void clearForces();
    /*!
        \fn     void update(float dt) override
        \par    dt
                    time from current frame to previous frame
        \return Nothing
        \brief
                updates the values in the physics class
     */
    void update(float dt) override;

    Component* clone() const override;
private:
    /*!
        \var    prevTranslation
                  vector of the object's previous translation
    */
    glm::vec3 prevTranslation;
    /*!
        \var    acceleration
                  vector of the object's acceleration
     */
    glm::vec3 acceleration;
    /*!
        \var    velocity
                  vector of the object's velocity
     */
    glm::vec3 velocity;
    /*!
        \var    velocityRotate
                  object's rotational velocity
     */
	float velocityRotate;
	//maybe float drag;
    /*!
        \var   forces
                  knockback forces acting on the object
     */
	std::vector<Force*> forces;
};