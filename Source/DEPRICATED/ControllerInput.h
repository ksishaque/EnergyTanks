/*!
\file   ControllerInput.h
\author Khaled Ishaque
\date   2-24-2023
\brief
		Controller input.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class BehaviorPlayer;

bool detectController(const int glfwJoystickCode);

int moveWithController(int joystick);

void shootWithButton(int joystick);