/*!
\file   Controller.cpp
\author Kevin Shin
\date   3-27-2023
\brief
        Functions for creating and managing a controller
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include <map>

#include "ActionList.h"
#include "ControllerButtons.h"
#include "ControlUnit.h"
#include "Trace.h"
#include "Window.h"

#include "Controller.h"

/*!
\var    GAMEPAD_BUTTON_CONVERSION
          Map containing translations from control manager index values to GLFW gamepad indices
*/
static const std::map<int, int> GAMEPAD_BUTTON_CONVERSION{
	{CTRL_KEY_A, GLFW_GAMEPAD_BUTTON_A},
	{CTRL_KEY_B, GLFW_GAMEPAD_BUTTON_B},
	{CTRL_KEY_X, GLFW_GAMEPAD_BUTTON_X},
	{CTRL_KEY_Y, GLFW_GAMEPAD_BUTTON_Y},
	{CTRL_KEY_LB, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER},
	{CTRL_KEY_RB, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER},
	{CTRL_KEY_BACK, GLFW_GAMEPAD_BUTTON_BACK},
	{CTRL_KEY_START, GLFW_GAMEPAD_BUTTON_START},
	{CTRL_KEY_GUIDE, GLFW_GAMEPAD_BUTTON_GUIDE},
	{CTRL_KEY_LS, GLFW_GAMEPAD_BUTTON_LEFT_THUMB},
	{CTRL_KEY_RS, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB},
	{CTRL_KEY_UP, GLFW_GAMEPAD_BUTTON_DPAD_UP},
	{CTRL_KEY_RIGHT, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT},
	{CTRL_KEY_DOWN, GLFW_GAMEPAD_BUTTON_DPAD_DOWN},
	{CTRL_KEY_LEFT, GLFW_GAMEPAD_BUTTON_DPAD_LEFT}
};

/*!
\var    GAMEPAD_AXIS_CONVERSION
          Map containing translations from control manager index values to `ControllerAxisInit`s
*/
static const std::map<int, ControllerAxisInit> GAMEPAD_AXIS_CONVERSION{
	{CTRL_KEY_LS_RIGHT, {GLFW_GAMEPAD_AXIS_LEFT_X, CONTROLLER_THRESHOLD_STICK, 1}},
	{CTRL_KEY_LS_LEFT, {GLFW_GAMEPAD_AXIS_LEFT_X, CONTROLLER_THRESHOLD_STICK, -1}},
	{CTRL_KEY_LS_UP, {GLFW_GAMEPAD_AXIS_LEFT_Y, CONTROLLER_THRESHOLD_STICK, -1}},
	{CTRL_KEY_LS_DOWN, {GLFW_GAMEPAD_AXIS_LEFT_Y, CONTROLLER_THRESHOLD_STICK, 1}},
	{CTRL_KEY_RS_RIGHT, {GLFW_GAMEPAD_AXIS_RIGHT_X, CONTROLLER_THRESHOLD_STICK, 1}},
	{CTRL_KEY_RS_LEFT, {GLFW_GAMEPAD_AXIS_RIGHT_X, CONTROLLER_THRESHOLD_STICK, -1}},
	{CTRL_KEY_RS_UP, {GLFW_GAMEPAD_AXIS_RIGHT_Y, CONTROLLER_THRESHOLD_STICK, -1}},
	{CTRL_KEY_RS_DOWN, {GLFW_GAMEPAD_AXIS_RIGHT_Y, CONTROLLER_THRESHOLD_STICK, 1}},
	{CTRL_KEY_LT, {GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, CONTROLLER_THRESHOLD_TRIGGER, 1}},
	{CTRL_KEY_RT, {GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, CONTROLLER_THRESHOLD_TRIGGER, 1}}
};

/*!
\var    GAMEPAD_AXIS_CONVERSION
          Map containing translations from control manager index values to `ControllerAxisInit`s
*/
static const ControlUnit::ControlType GAMEPAD_CONTROL_CONVERSION[] = {
	ControlUnit::ControlType::FIRST,
	ControlUnit::ControlType::FIRST,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::UP,
	ControlUnit::ControlType::DOWN,
	ControlUnit::ControlType::LEFT,
	ControlUnit::ControlType::RIGHT,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::SECOND,
	ControlUnit::ControlType::SECOND,
	ControlUnit::ControlType::SECOND,
	ControlUnit::ControlType::UP,
	ControlUnit::ControlType::DOWN,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::INVALID,
	ControlUnit::ControlType::LEFT,
	ControlUnit::ControlType::RIGHT,
	ControlUnit::ControlType::FIRST,
	ControlUnit::ControlType::FIRST
};

/*!
\fn     Controller::Controller(int js)
\param  js
          joystick
\brief  See Controller.h
*/
Controller::Controller(int js) : inputs(new ControllerInput*[CTRL_KEY_COUNT]), unit(nullptr){

	//	Initialize `claims` and `inputs` for buttons
	for(unsigned i = 0; i < CTRL_KEY_BUTTON_COUNT; i += 1) inputs[i] = new ControllerButton(GAMEPAD_BUTTON_CONVERSION.at(CTRL_KEY_BASE + i), js);

	//	Initialize `claims` and `inputs` for axes
	for(unsigned i = CTRL_KEY_BUTTON_COUNT; i < CTRL_KEY_COUNT; i += 1) inputs[i] = new ControllerAxis(GAMEPAD_AXIS_CONVERSION.at(CTRL_KEY_BASE + i), js);

}

/*!
\fn     Controller::~Controller()
\brief  See Controller.h
*/
Controller::~Controller(){

	//	Reset `unit`
	if(unit) unit -> setController(-1);

	//	Delete `inputs`
	for(unsigned i = 0; i < CTRL_KEY_COUNT; i += 1) delete inputs[i];
	delete[] inputs;

}

/*!
\fn     void Controller::update(float dt)
\param  dt
          dt
\brief  See Controller.h
*/
void Controller::update(float dt){

	//	Update all buttons
	for(unsigned i = 0; i < CTRL_KEY_COUNT; i += 1){

		//	Variable: Pressed/released state of the button
		ControlManager::KeyState state = inputs[i] -> getState();

		//	Call outputs
		outputCall(GAMEPAD_CONTROL_CONVERSION[i], state);
		if(state != ControlManager::KeyState::INVALID) ControlManager::getInstance() -> universalInput(state);

		//	Check for held
		if(inputs[i] -> getPrevious()){

			//	Call outputs
			outputCall(GAMEPAD_CONTROL_CONVERSION[i], ControlManager::KeyState::HELD);
			ControlManager::getInstance() -> universalInput(ControlManager::KeyState::HELD);

		}

	}
}

/*!
\fn     Controller::ControllerInput::ControllerInput(int js, ControlUnit::ControlType out)
\param  js
          joystick
\param  out
          output
\brief  See Controller.h
*/
Controller::ControllerInput::ControllerInput(int js) : joystick(js), previous(false){}

/*!
\fn     ControlManager::KeyState Controller::ControllerInput::getState)
\brief  See Controller.h
*/
ControlManager::KeyState Controller::ControllerInput::getState(){

	/*	Variables:
	cur: If the button was pressed
	ans: Return value; key state to return
	*/
	bool cur = survey();
	ControlManager::KeyState ans = ControlManager::KeyState::INVALID;

	//	Check `cur`
	if(cur && !previous) ans = ControlManager::KeyState::PRESSED;

	//	Check for `RELEASED`
	else if(!cur && previous) ans = ControlManager::KeyState::RELEASED;

	//	Update `previous`
	previous = cur;

	//	Return
	 return ans;

}

/*!
\fn     Controller::ControllerButton::ControllerButton(int i, int js, ControlUnit::ControlType out)
\param  i
          index
\param  js
          joystick
\param  out
          output
\brief  See Controller.h
*/
Controller::ControllerButton::ControllerButton(int i, int js) : ControllerInput(js), index(i){}

/*!
\fn     bool Controller::ControllerButton::survey()
\brief  See Controller.h
*/
bool Controller::ControllerButton::survey() const{

	//	Check for window focus
	if(!glfwGetWindowAttrib(Window::getInstance() -> getHandle(), GLFW_FOCUSED)) return false;

	//	Variable: Gamepad state to check
	GLFWgamepadstate state;

	//	Retrieve and check `state`
	if(!glfwGetGamepadState(joystick, &state)) return false;

	//	Check button state
	return state.buttons[index] == GLFW_PRESS;

}

/*!
\fn     Controller::ControllerAxis::ControllerAxis(const ControllerAxisInit &info, int js, ControlUnit::ControlType out)
\param  info
          info
\param  js
          joystick
\param  out
          output
\brief  See Controller.h
*/
Controller::ControllerAxis::ControllerAxis(const ControllerAxisInit &info, int js) : ControllerInput(js), info(info){}

/*!
\fn     bool Controller::ControllerAxis::survey()
\brief  See Controller.h
*/
bool Controller::ControllerAxis::survey() const{

	//	Check for window focus
	if(!glfwGetWindowAttrib(Window::getInstance() -> getHandle(), GLFW_FOCUSED)) return false;

	//	Variable: Gamepad state to check
	GLFWgamepadstate state;

	//	Retrieve and check `state`
	if(!glfwGetGamepadState(joystick, &state)) return false;

	//	Check button state
	return state.axes[info.index] * info.multi > info.threshold;

}

/*!
\fn     void setUnit(ControlUnit *u)
\param  unit
          Control unit to set
\return Nothing
\brief
        This function mutates the control unit that a controller is using.
*/
void Controller::setUnit(ControlUnit *u){

	//	Release all presses on previous `unit`
	manualCall(ControlManager::KeyState::RELEASED);
	//unit -> releaseController();

	//	Set new `unit`
	unit = u;

	//	Activate all presses on new `unit`
	for(unsigned i = 0; i < CTRL_KEY_COUNT; i += 1) if(inputs[i] -> getPrevious()) outputCall(GAMEPAD_CONTROL_CONVERSION[i], ControlManager::KeyState::PRESSED);

}

/*!
\fn     bool Controller::ControllerInput::getPrevious()
\brief  See Controller.h
*/
bool Controller::ControllerInput::getPrevious(){
	return previous;
}

/*!
\fn     void Controller::outputCall(ControlUnit::ControlType out, bool cur, bool prev, ControlUnit *u)
\param  out
          output
\param  cur
          current
\param  prev
          previous
\param  u
          unit
\brief  See Controller.h
*/
void Controller::outputCall(ControlUnit::ControlType output, ControlManager::KeyState state){

	//	Check `unit` and `state`
	if(state == ControlManager::KeyState::INVALID || unit == nullptr) return;

	//	Check for pressed inputs
	if(state == ControlManager::KeyState::PRESSED){

		//	Update axis for axis inputs
		if(output == ControlUnit::ControlType::UP) unit -> iterateAxisY(1);
		else if(output == ControlUnit::ControlType::DOWN) unit -> iterateAxisY(-1);
		else if(output == ControlUnit::ControlType::LEFT) unit -> iterateAxisX(1);
		else if(output == ControlUnit::ControlType::RIGHT) unit -> iterateAxisX(-1);

		//	Call `actionCall`
		unit -> actionCall(output, ControlManager::KeyState::PRESSED);

	}

	//	Check for released inputs
	else if(state == ControlManager::KeyState::RELEASED){

		//	Update axis for axis inputs
		if(output == ControlUnit::ControlType::UP) unit -> iterateAxisY(-1);
		else if(output == ControlUnit::ControlType::DOWN) unit -> iterateAxisY(1);
		else if(output == ControlUnit::ControlType::LEFT) unit -> iterateAxisX(-1);
		else if(output == ControlUnit::ControlType::RIGHT) unit -> iterateAxisX(1);

		//	Call `actionCall`
		unit -> actionCall(output, ControlManager::KeyState::RELEASED);

	}

	//	Check for held inputs
	if(state == ControlManager::KeyState::HELD && output > ControlUnit::ControlType::RIGHT && output < ControlUnit::ControlType::MAX) unit -> actionCall(output, ControlManager::KeyState::HELD);

}

/*!
\fn     void Controller::manualCall(ControlManager::KeyState state)
\param  state
          state
\brief  See Controller.h
*/
void Controller::manualCall(ControlManager::KeyState state){
	for(unsigned i = 0; i < CTRL_KEY_BUTTON_COUNT; i += 1) if(inputs[i] -> getPrevious()) outputCall(GAMEPAD_CONTROL_CONVERSION[i], state);
}