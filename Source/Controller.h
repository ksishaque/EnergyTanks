/*!
\file   Controller.h
\author Kevin Shin
\date   3-27-2023
\brief
        Functions for creating and managing a controller
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class Controller;

#include "ControlManager.h"
#include "ControlUnit.h"

#define CONTROLLER_THRESHOLD_STICK 0.3f
#define CONTROLLER_THRESHOLD_TRIGGER 0

/*!
\struct ControllerAxisInit
\brief
        Initializer values for `ControllerAxis`
*/
struct ControllerAxisInit{

	/*!
	\var    index
	         Axis index to check
	*/
	int index;

	/*!
	\var    threshold
	          Axis value to use as threshold
	*/
	float threshold;

	/*!
	\var    multi
	          Value multiplier to use while checking
	*/
	float multi;

};

/*!
\class  Controller
\brief
        Listener for a game controller
*/
class Controller{
	public:

		/*!
		\fn     Controller(int joystick)
		\param  joystick
		          Joystick ID to link to
		\return Newly constructed controller
		\brief
		        This function constructs a new controller.
		*/
		Controller(int joystick);

		/*!
		\fn     ~Controller()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a controller.
		*/
		~Controller();

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates a controller.
		*/
		void update(float dt);

		/*!
		\fn     void setUnit(ControlUnit *unit)
		\param  unit
		          Control unit to set
		\return Nothing
		\brief
		        This function mutates the control unit that a controller is using.
		*/
		void setUnit(ControlUnit *unit);

		/*!
		\fn     void manualCall(ControlManager::KeyState state)
		\param  state
		          Key state to manually call
		\return Nothing
		\brief
		        This function manually replicates any buttons call if the button is pressed.
		*/
		void manualCall(ControlManager::KeyState state);

	private:

		/*!
		\class  ControllerInput
		\brief
		        Input manager for a single controller input
		*/
		class ControllerInput{
			public:

				/*!
				\fn     ControllerInput(int joystick)
				\param  joystick
				          Joystick ID to link to
				\return Newly constructed input manager
				\brief
				        This function constructs a new input manager.
				*/
				ControllerInput(int joystick);

				/*!
				\fn     ControlManager::KeyState getState()
				\par    This function has no parameters.
				\return Current state of the input.
				\brief
				        This function updates a controller input.
				*/
				ControlManager::KeyState getState();

				/*!
				\fn!    bool getPrevious()
				\par    This function has no parameters
				\return `previous`
				\brief
				        This function accesses information about if the button was recently pressed.
				*/
				bool getPrevious();

			protected:

				/*!
				\fn     virtual bool survey() const
				\par    This function has no parameters
				\return If the input is currently "pressed"
				\brief
				        This function determines if an input is "pressed".
				*/
				virtual bool survey() const = 0;

				/*!
				\var    joystick
				          Joystick ID that was linked
				*/
				int joystick;

			private:

				/*!
				\var    previous
				          If the button was previously "pressed"
				*/
				bool previous;

		};

		/*!
		\class  ControllerButton
		\brief
		        Input manager for a controller button
		*/
		class ControllerButton : public ControllerInput{
			public:

				/*!
				\fn     ControllerButton(int index, int joystick)
				\param  index
				          Index of button to manage
				\param  joystick
				          Joystick ID to link to
				\return Newly constructed input manager
				\brief
				        This function constructs a new input manager.
				*/
				ControllerButton(int index, int joystick);

			private:

				/*!
				\fn     bool survey() const override
				\brief  See Controller.h
				*/
				bool survey() const override;

				/*!
				\var    index
				          Button index to check
				*/
				int index;

		};

		/*!
		\class  ControllerAxis
		\brief
		        Input manager for a controller axis
		*/
		class ControllerAxis : public ControllerInput{
			public:

				/*!
				\fn     ControllerAxis(const ControllerAxisInit &info, int joystick)
				\param  info
				          Information about how to survey
				\param  joystick
				          Joystick ID to link to
				\return Newly constructed input manager
				\brief
				        This function constructs a new input manager.
				*/
				ControllerAxis(const ControllerAxisInit &info, int joystick);

			private:

				/*!
				\fn     bool survey() const override
				\brief  See Controller.h
				*/
				bool survey() const override;

				/*!
				\var    info
				         Information about axis to check
				*/
				const ControllerAxisInit &info;

		};

		/*!
		\var    inputs
		          Input managers for each button
		*/
		ControllerInput **inputs;

		/*!
		\var    unit
		          Control unit that is taking inputs from the controller
		*/
		ControlUnit *unit;

		/*!
		\fn     void outputCall(ControlUnit::ControlType output, bool current, bool previous, ControlUnit *unit)
		\param  output
		          Output control to simulate
		\param  state
		          Key state to simulate
		\return Nothing
		\brief
		        This function sends an output call depending on the situation and output type.
		*/
		void outputCall(ControlUnit::ControlType output, ControlManager::KeyState state);

};