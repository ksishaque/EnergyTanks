/*!
\file InputController.h
\author Khaled S. Ishaque
        Kevin Shin
\date 9-23-2022
\brief
    Header file for object movement with keyboard
\par Copyright © 2022 DigiPen, All rights reserved.
*/

#include "Physics.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"

#define GLFW_INCLUDE_NONE

#include "Window.h"

#if 0
/*!
\fn     float inputsPlayer1Vertical(GLFWwindow* window, float valueUD);
\param  window
            Screen where the inputs are being taken to show output
        player1
            The game object that houses the 1st player
\return nothing
\brief
        Does actions based on what the first player inputted for buttons
*/
void inputsPlayer1Vertical(GLFWwindow* window, GameObject* player1);
/*!
\fn     float inputsPlayer1horizontal(GLFWwindow* window, float valueLR);
\param  window
            Screen where the inputs are being taken to show output
        player1
            The game object that houses the 1st player
\return nothing
\brief
        Does actions based on what the first player inputted for buttons
*/
void inputsPlayer1Horizontal(GLFWwindow* window, GameObject* player1);

/*!
\fn     void inputsPlayer2(GLFWwindow* window, float& valueUD, float& valueLR);
\param  window
            Screen where the inputs are being taken to show output
\param  physics
            Physics for the inputs to affect
\param  up
            Key code for up input
\param  down
            Key code for down input
\param  left
            Key code for left input
\param  right
            Key code for right input
\return nothing
\brief
        Does actions based on what the player inputted for buttons
*/
void inputsPlayer2(GLFWwindow* window, Physics *physics, int up, int down, int left, int right);
#endif