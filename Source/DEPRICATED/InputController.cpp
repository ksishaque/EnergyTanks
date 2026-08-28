/*!
\file InputController.cpp
\author Khaled S. Ishaque
\date 9-23-2022
\brief
    function definitions for object movement with keyboard
\par Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <GL/glew.h>
#include "SoundSystem.h"
#include "InputController.h"

#include <glfw/glfw3.h>
//to not type the same value over and over again
static float movementAmount = 300.0f;
static float rotationAmount = 90.0f;

/*!
 * @brief:
 * Allows player 1 to move vertically
 * @param:
 * window - the screen that will show the movement
 * player1 - the player game object to move
 * @return:
 * Nothing
 */
void inputsPlayer1Vertical(GLFWwindow* window, GameObject* player1)
{
    //get player's transform and physics
    Transform* p1Transform = dynamic_cast<Transform*>(player1->get(ComponentTypeEnum::cTransform));
    Physics* p1Physics = dynamic_cast<Physics*>(player1->get(ComponentTypeEnum::cPhysics));
    //physics and transform aren't garbage
    if (p1Physics != NULL && p1Transform != NULL)
    {
        float rotation = p1Transform->getRotation();
        glm::vec3 velocity = p1Physics->getVelocity();
        //move up
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            velocity.y = movementAmount;
            rotation = 0;
            p1Physics->setVelocity(velocity);
            p1Transform->setRotatePos(rotation);
        }
        //move down
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            velocity.y = -movementAmount;
            rotation = 180;
            p1Physics->setVelocity(velocity);
            p1Transform->setRotatePos(rotation);
        }
        //stand still
        else 
        {
            velocity.y = 0;
            p1Physics->setVelocity(velocity);
        }
    }
}

/*!
 * @brief:
 * Allows player 1 to move horizontally
 * @param:
 * window - the screen that will show the movement
 * player1 - the player game object to move
 * @return:
 * Nothing
 */
void inputsPlayer1Horizontal(GLFWwindow* window, GameObject* player1)
{
    //get player's transform and physics
    Transform* p1Transform = dynamic_cast<Transform*>(player1->get(ComponentTypeEnum::cTransform));
    Physics* p1Physics = dynamic_cast<Physics*>(player1->get(ComponentTypeEnum::cPhysics));
    //null check
    if (p1Physics != NULL && p1Transform != NULL)
    {
        float rotation = p1Transform->getRotation();
        glm::vec3 velocity = p1Physics->getVelocity();
        //move right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            velocity.x = movementAmount;
            rotation = -90;
            p1Physics->setVelocity(velocity);
            p1Transform->setRotatePos(rotation);
        }
        //move left
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            velocity.x = -movementAmount;
            rotation = 90;
            p1Physics->setVelocity(velocity);
            p1Transform->setRotatePos(rotation);
        }
        //stand still
        else
        {
            velocity.x = 0;
            p1Physics->setVelocity(velocity);
        }
    }
}
/*!
 * @brief:
 * Allows Player 2 to move on the screen
 * @param:
 * window - the screen that will show the movement
 * player2 - the player game object to move
 * @return:
 * Nothing
 */
void inputsPlayer2(GLFWwindow* window, GameObject* player2)
{
    Transform* p2Transform = dynamic_cast<Transform*>(player2->get(ComponentTypeEnum::cTransform));
    Physics* p2Physics = dynamic_cast<Physics*>(player2->get(ComponentTypeEnum::cPhysics));
    //null check
    if (p2Physics != NULL)
    {
        float rotation = p2Transform->getRotation();
        glm::vec3 velocity = p2Physics->getVelocity();
        //move up
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            velocity.y = movementAmount;
            rotation = 0;

        }
        //move down
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            velocity.y = -movementAmount;
            rotation = 180;
        }
        //no vertical movement
        else
        {
            velocity.y = 0;
        }
        //move left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            velocity.x = -movementAmount;
            rotation = 90;
        }
        //move right
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            velocity.x = movementAmount;
            rotation = -90;
        }
        //no horizontal movement
        else
        {
            velocity.x = 0;
        }
        //set direction and move
        p2Physics->setVelocity(velocity);
        p2Transform->setRotatePos(rotation);
    }
}

/*!
\fn     void inputsPlayer2
\param  win
          window
\param  phys
          physics
\param  up
          up
\param  dn
          downn
\param  lf
          left
\param  rt
          right
\brief  See InputController.h
*/
void inputsPlayer2(GLFWwindow* win, Physics* phys, int up, int dn, int lf, int rt) {

    //	Check parameters
    if (win == nullptr || phys == nullptr) return;

    /*	Variables:
    inFB: front-back input from window
        B: input state is going backwards
        N: input state is staying still
        F: input state is going forewards
    inLR: left-right input from window
        R: input state is going right
        S: input state is going straight
        L: input state is going left
    */
    //*
    enum FB { B = -1, N = 0, F = 1 } inFB = N;
    enum LR { R = -1, S = 0, L = 1 } inLR = S;
    /*/
    int inFB = 0;
    int inLR = 0;
    //*/

    //	Check and add inputs
    if (glfwGetKey(win, up) == GLFW_PRESS) inFB = (FB)(inFB + 1);
    if (glfwGetKey(win, dn) == GLFW_PRESS) inFB = (FB)(inFB - 1);
    if (glfwGetKey(win, lf) == GLFW_PRESS) inLR = (LR)(inLR + 1);
    if (glfwGetKey(win, rt) == GLFW_PRESS) inLR = (LR)(inLR - 1);

    //	Rotate according to `inLR`
    phys->setVelocityRotate(rotationAmount * inLR);

    //	Set movement
    if (inFB == N) phys->setVelocity(glm::vec3(0, 0, 0));
    else if (inFB > N) phys->setRotatedVelocity(glm::vec3(0, movementAmount, 0));
    else phys->setRotatedVelocity(glm::vec3(0, movementAmount * -0.8, 0));
}