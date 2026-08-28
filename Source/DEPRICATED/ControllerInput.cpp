/*!
\file   ControllerInput.cpp
\author Khaled Ishaque
\date   2-24-2023
\brief
		Controller input.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "ControllerInput.h"

#include "BehaviorPlayer.h"
#include "Trace.h"

bool detectController(const int glfwJoystickCode) {
	//check if gamepad is present
	int controllerPresent = glfwJoystickPresent(glfwJoystickCode);
#ifdef DEBUG_SYSTEM
	Trace::message("Status of GamePad: %i", controllerPresent);
#endif
	//found a controller
	if (controllerPresent == 1) {
		//get number of controllable axes/buttons
		int axesCount;
		const float* axes = glfwGetJoystickAxes(glfwJoystickCode, &axesCount);
		//DEBUG: display current controller's stick and trigger values
#ifdef DEBUG_SYSTEM
		Trace::message("\nLeft Stick = X: %f, Y: %f.\n Right Stick = X: %f, Y: %f.\n Left Trigger: %f.\n Right Trigger: %f.\n", axes[0], axes[1], axes[2], axes[3], axes[4], axes[5]);
#endif
		//get current buttons available
		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(glfwJoystickCode, &buttonCount);
		//DEBUG: display what button is pressed and released
		//Down Face Button
		if (buttons[0] == GLFW_PRESS) {
			Trace::message("Pressed Button A");
		}
		else if (buttons[0] == GLFW_RELEASE) {
			Trace::message("Released Button A");
		}
		//Right Face Button
		if (buttons[1] == GLFW_PRESS) {
			Trace::message("Pressed Button B");
		}
		else if (buttons[1] == GLFW_RELEASE) {
			Trace::message("Released Button B");
		}
		//Left Face Button
		if (buttons[2] == GLFW_PRESS) {
			Trace::message("Pressed Button X");
		}
		else if (buttons[2] == GLFW_RELEASE) {
			Trace::message("Released Button X");
		}
		//Up Face Button
		if (buttons[3] == GLFW_PRESS) {
			Trace::message("Pressed Button Y");
		}
		else if (buttons[3] == GLFW_RELEASE) {
			Trace::message("Released Button Y");
		}
		//Left Bumper
		if (buttons[4] == GLFW_PRESS) {
			Trace::message("Pressed Bumper L ");
		}
		else if (buttons[4] == GLFW_RELEASE) {
			Trace::message("Released Bumper L ");
		}
		//Right Bumper
		if (buttons[5] == GLFW_PRESS) {
			Trace::message("Pressed Bumper R ");
		}
		else if (buttons[5] == GLFW_RELEASE) {
			Trace::message("Released Bumper R ");
		}
		//Test others
		if (buttons[6] == GLFW_PRESS) {
			Trace::message("6: View");
		}
		if (buttons[7] == GLFW_PRESS) {
			Trace::message("7: Menu");
		}
		if (buttons[8] == GLFW_PRESS) {
			Trace::message("8: Left Stick");
		}
		if (buttons[9] == GLFW_PRESS) {
			Trace::message("9: Right Stick");
		}
		if (buttons[10] == GLFW_PRESS) {
			Trace::message("10: Up");
		}
		if (buttons[11] == GLFW_PRESS) {
			Trace::message("11: Right");
		}
		if (buttons[12] == GLFW_PRESS) {
			Trace::message("12: Down");
		}
		if (buttons[13] == GLFW_PRESS) {
			Trace::message("13: Left");
		}
		Trace::message("Button Count: %d", buttonCount);
		return true;
	}
	return false;
}

int moveWithController(int joystick) {
	//check if gamepad is present
	int controllerPresent = glfwJoystickPresent(joystick);
	//presence check for above
	if (controllerPresent == 1) {
		//get axes and triggers
		int axesCount;
		const float* axes = glfwGetJoystickAxes(joystick, &axesCount);
		//check if left stick is being moved
		//left and right
		if (axes[0] >= 0.2) { //0.2 test value
			return 1;
		}
		else if (axes[0] <= -0.2) { //-0.2 test value
			return -1;
		}
		else {
			return 0;
		}
		//up and down
		if (axes[1] >= 0.2) {
			return -1;
		}
		else if (axes[1] <= -0.2) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//can't read gamepad
	return -1;
}

void shootWithButton(int joystick) {
	int controllerPresent = glfwJoystickPresent(joystick);
	if (controllerPresent == 1) {
		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(joystick, &buttonCount);
	}
}