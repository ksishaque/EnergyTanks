/*!
\file   ControllerButtons.h
\author Kevin Shin
\date   1-13-2023
\brief
		Macros for defining control key buttons
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glfw/glfw3.h>

#define CTRL_KEY_BASE (GLFW_KEY_LAST + 10)
#define CTRL_KEY_A CTRL_KEY_BASE
#define CTRL_KEY_B (CTRL_KEY_BASE + 1)
#define CTRL_KEY_X (CTRL_KEY_BASE + 2)
#define CTRL_KEY_Y (CTRL_KEY_BASE + 3)
#define CTRL_KEY_UP (CTRL_KEY_BASE + 4)
#define CTRL_KEY_DOWN (CTRL_KEY_BASE + 5)
#define CTRL_KEY_LEFT (CTRL_KEY_BASE + 6)
#define CTRL_KEY_RIGHT (CTRL_KEY_BASE + 7)
#define CTRL_KEY_LS (CTRL_KEY_BASE + 8)
#define CTRL_KEY_RS (CTRL_KEY_BASE + 9)
#define CTRL_KEY_LB (CTRL_KEY_BASE + 10)
#define CTRL_KEY_RB (CTRL_KEY_BASE + 11)
#define CTRL_KEY_BACK (CTRL_KEY_BASE + 12)
#define CTRL_KEY_START (CTRL_KEY_BASE + 13)
#define CTRL_KEY_GUIDE (CTRL_KEY_BASE + 14)
#define CTRL_KEY_LS_UP (CTRL_KEY_BASE + 15)
#define CTRL_KEY_LS_DOWN (CTRL_KEY_BASE + 16)
#define CTRL_KEY_LS_LEFT (CTRL_KEY_BASE + 17)
#define CTRL_KEY_LS_RIGHT (CTRL_KEY_BASE + 18)
#define CTRL_KEY_RS_UP (CTRL_KEY_BASE + 19)
#define CTRL_KEY_RS_DOWN (CTRL_KEY_BASE + 20)
#define CTRL_KEY_RS_LEFT (CTRL_KEY_BASE + 21)
#define CTRL_KEY_RS_RIGHT (CTRL_KEY_BASE + 22)
#define CTRL_KEY_LT (CTRL_KEY_BASE + 23)
#define CTRL_KEY_RT (CTRL_KEY_BASE + 24)
#define CTRL_KEY_MAX (CTRL_KEY_BASE + 25)
#define CTRL_KEY_BUTTON_COUNT 15
#define CTRL_KEY_COUNT 25
#define CTRL_KEY_CROSS CTRL_KEY_A
#define CTRL_KEY_CIRCLE CTRL_KEY_B
#define CTRL_KEY_SQUARE CTRL_KEY_X
#define CTRL_KEY_TRIANGLE CTRL_KEY_Y