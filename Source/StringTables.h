/*!
\file   StringTables.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   8-1-2023
\brief
        Maps for converting strings into enumeration values
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include <map>
#include <stdexcept>

#include "BehaviorDisplayFloatBar.h"
#include "ControlUnit.h"
#include "GameObject.h"
#include "GraphicsUnit.h"

/*!
\var    invalid
          list of invalid keys, as a c++-style string
*/
static const std::string invalid = "!\"#$%&()*+:<>?@^_";

/*!
\var    keyTable
          map containing conversions from strings to valid key codes
*/
static const std::map<std::string, int> keyTable = {

	//	Non US keys
	{"World1", GLFW_KEY_WORLD_1}, {"Global1", GLFW_KEY_WORLD_1},
	{"World2", GLFW_KEY_WORLD_2}, {"Global2", GLFW_KEY_WORLD_2},

	//	Escape
	{"Escape", GLFW_KEY_ESCAPE}, {"Esc", GLFW_KEY_ESCAPE},

	//	Enter
	{"Enter", GLFW_KEY_ENTER}, {"Ent", GLFW_KEY_ENTER}, {"Return", GLFW_KEY_ENTER},

	//	Tab
	{"Tab", GLFW_KEY_TAB},

	//	Backspace
	{"Backspace", GLFW_KEY_BACKSPACE}, {"Back", GLFW_KEY_BACKSPACE},

	//	Insert and Delete
	{"Insert", GLFW_KEY_INSERT}, {"Ins", GLFW_KEY_INSERT},
	{"Delete", GLFW_KEY_DELETE}, {"Del", GLFW_KEY_DELETE},

	//	D-Pad
	{"Right", GLFW_KEY_RIGHT},
	{"Left", GLFW_KEY_LEFT},
	{"Down", GLFW_KEY_DOWN},
	{"Up", GLFW_KEY_UP},

	//	Page Up and Down
	{"Page Up", GLFW_KEY_PAGE_UP}, {"PgUp", GLFW_KEY_PAGE_UP},
	{"Page Down", GLFW_KEY_PAGE_DOWN}, {"PgDn", GLFW_KEY_PAGE_DOWN},

	//	Home and End
	{"Home", GLFW_KEY_HOME}, {"Hm", GLFW_KEY_HOME},
	{"End", GLFW_KEY_END}, {"Terminate", GLFW_KEY_END},

	//	Locks
	{"Caps Lock", GLFW_KEY_CAPS_LOCK}, {"CapLk", GLFW_KEY_CAPS_LOCK},
	{"Scroll Lock", GLFW_KEY_SCROLL_LOCK}, {"ScrLk", GLFW_KEY_SCROLL_LOCK},
	{"Num Lock", GLFW_KEY_NUM_LOCK}, {"NumLk", GLFW_KEY_NUM_LOCK},

	//	Print
	{"Print Screen", GLFW_KEY_PRINT_SCREEN}, {"Print", GLFW_KEY_PRINT_SCREEN}, {"PrtScn", GLFW_KEY_PRINT_SCREEN},

	//	Pause
	{"PAWS", GLFW_KEY_PAUSE},

	//	Function keys
	{"F1", GLFW_KEY_F1},
	{"F2", GLFW_KEY_F2},
	{"F3", GLFW_KEY_F3},
	{"F4", GLFW_KEY_F4},
	{"F5", GLFW_KEY_F5},
	{"F6", GLFW_KEY_F6},
	{"F7", GLFW_KEY_F7},
	{"F8", GLFW_KEY_F8},
	{"F9", GLFW_KEY_F9},
	{"F10", GLFW_KEY_F10},
	{"F11", GLFW_KEY_F11},
	{"F12", GLFW_KEY_F12},
	{"F13", GLFW_KEY_F13},
	{"F14", GLFW_KEY_F14},
	{"F15", GLFW_KEY_F15},
	{"F16", GLFW_KEY_F16},
	{"F17", GLFW_KEY_F17},
	{"F18", GLFW_KEY_F18},
	{"F19", GLFW_KEY_F19},
	{"F20", GLFW_KEY_F20},
	{"F21", GLFW_KEY_F21},
	{"F22", GLFW_KEY_F22},
	{"F23", GLFW_KEY_F23},
	{"F24", GLFW_KEY_F24},
	{"F25", GLFW_KEY_F25},

	//	Keypad numbers
	{"K0", GLFW_KEY_KP_0},
	{"K1", GLFW_KEY_KP_1},
	{"K2", GLFW_KEY_KP_2},
	{"K3", GLFW_KEY_KP_3},
	{"K4", GLFW_KEY_KP_4},
	{"K5", GLFW_KEY_KP_5},
	{"K6", GLFW_KEY_KP_6},
	{"K7", GLFW_KEY_KP_7},
	{"K8", GLFW_KEY_KP_8},
	{"K9", GLFW_KEY_KP_9},

	//	Keypad Decimal
	{"K.", GLFW_KEY_KP_DECIMAL}, {"Decimal", GLFW_KEY_KP_DECIMAL},

	//	Keypad Add, Multiply, Subtract and Divide
	{"K/", GLFW_KEY_KP_DIVIDE}, {"Divide", GLFW_KEY_KP_DIVIDE},
	{"K*", GLFW_KEY_KP_MULTIPLY}, {"Multiply", GLFW_KEY_KP_MULTIPLY},
	{"K-", GLFW_KEY_KP_SUBTRACT}, {"Subtract", GLFW_KEY_KP_SUBTRACT},
	{"K+", GLFW_KEY_KP_ADD}, {"Add", GLFW_KEY_KP_ADD},

	//	Keypad Enter
	{"KEnter", GLFW_KEY_KP_ENTER}, {"KEnt", GLFW_KEY_KP_ENTER}, {"KReturn", GLFW_KEY_KP_ENTER},

	//	Keypad Equals
	{"K=", GLFW_KEY_KP_EQUAL}, {"Equal", GLFW_KEY_KP_EQUAL},

	//	Shifts
	{"LShift", GLFW_KEY_LEFT_SHIFT}, 
	{"RShift", GLFW_KEY_RIGHT_SHIFT},

	//	Control
	{"LControl", GLFW_KEY_LEFT_CONTROL}, {"LCtrl", GLFW_KEY_LEFT_CONTROL},
	{"RControl", GLFW_KEY_RIGHT_CONTROL}, {"RCtrl", GLFW_KEY_RIGHT_CONTROL},

	//	Alts
	{"LAlt", GLFW_KEY_LEFT_ALT}, 
	{"RAlt", GLFW_KEY_RIGHT_ALT},

	//	Super
	{"LSuper", GLFW_KEY_LEFT_SUPER}, 
	{"RSuper", GLFW_KEY_RIGHT_SUPER},

	//	Menu
	{"Menu", GLFW_KEY_MENU},

	//	Universal
	{"ALL", 0}

};

/*!
\var    typeTable
          map containing conversion from strings to valid game object types.
*/
static const std::map<std::string, GameObject::Type> typeTable = {
	{"p", GameObject::Type::Player}, {"Player", GameObject::Type::Player},
	{"b", GameObject::Type::Bullet}, {"Bullet", GameObject::Type::Bullet},
	{"w", GameObject::Type::Wall}, {"Wall", GameObject::Type::Wall},
	{"m", GameObject::Type::Map}, {"Map", GameObject::Type::Map},
	{"s", GameObject::Type::Shield}, {"Shield", GameObject::Type::Shield},
	{"h", GameObject::Type::Health}, {"Health", GameObject::Type::Health},
	{"t", GameObject::Type::Button}, {"Button", GameObject::Type::Button},
	{"u", GameObject::Type::Powerup}, {"Powerup", GameObject::Type::Powerup},
	{"v", GameObject::Type::Visual}, {"Visual", GameObject::Type::Visual},
	{"x", GameObject::Type::Miscelaneous}, {"Miscelaneous", GameObject::Type::Miscelaneous}
};

/*!
\var    layerTable
          Map containing conversion from strings to valid graphics unit layer types.
*/
static const std::map<std::string, GraphicsUnit::Type> layerTable = {
#ifdef _DEBUG
	{"TEST", GraphicsUnit::Type::guTest},
#endif

	{"CTRL: Background", GraphicsUnit::Type::guCtrlPopBackground},
	{"CTRL: Icon 1", GraphicsUnit::Type::guCtrlPopIcon1},
	{"CTRL: Icon 2", GraphicsUnit::Type::guCtrlPopIcon2},
	{"CTRL: Text", GraphicsUnit::Type::guCtrlPopText},

	{"HTPL: Background", GraphicsUnit::Type::guCtrlPopBackground},
	{"HTPL: Text", GraphicsUnit::Type::guCtrlPopText},

	{"OPTN: Background", GraphicsUnit::Type::guOptnPopBackground},
	{"OPTN: Icon", GraphicsUnit::Type::guOptnPopIcon},
	{"OPTN: Slider", GraphicsUnit::Type::guOptnPopSlider1},
	{"OPTN: Slider 1", GraphicsUnit::Type::guOptnPopSlider1},
	{"OPTN: Slider 2", GraphicsUnit::Type::guOptnPopSlider2},
	{"OPTN: Selector", GraphicsUnit::Type::guOptnPopSelector},
	{"OPTN: Text", GraphicsUnit::Type::guOptnPopText1},
	{"OPTN: Text 1", GraphicsUnit::Type::guOptnPopText1},
	{"OPTN: Text 2", GraphicsUnit::Type::guOptnPopText2},

	{"PALI: Background", GraphicsUnit::Type::guPaLiPopBackground},
	{"PALI: Icon", GraphicsUnit::Type::guPaLiPopIcon},

	{"PAWS: Background", GraphicsUnit::Type::guPawsPopBackground},
	{"PAWS: Icon", GraphicsUnit::Type::guPawsPopIcon},
	{"PAWS: Selector", GraphicsUnit::Type::guPawsPopSelector},
	{"PAWS: Text", GraphicsUnit::Type::guPawsPopText},

	{"SHUT: Background", GraphicsUnit::Type::guShutPopBackground},
	{"SHUT: Icon", GraphicsUnit::Type::guShutPopIcon},
	{"SHUT: Selector", GraphicsUnit::Type::guShutPopSelector},
	{"SHUT: Text", GraphicsUnit::Type::guShutPopText},

	{"Background", GraphicsUnit::Type::guBackground1},
	{"Background 1", GraphicsUnit::Type::guBackground1},
	{"Background 2", GraphicsUnit::Type::guBackground2},
	{"Background 3", GraphicsUnit::Type::guBackground3},
	{"Border", GraphicsUnit::Type::guBorder},
	{"Bullet", GraphicsUnit::Type::guBullet},
	{"Button", GraphicsUnit::Type::guButton1},
	{"Button 1", GraphicsUnit::Type::guButton1},
	{"Button 2", GraphicsUnit::Type::guButton2},
	{"Button 3", GraphicsUnit::Type::guButton3},
	{"Glow", GraphicsUnit::Type::guGlow2},
	{"Glow 1", GraphicsUnit::Type::guGlow1},
	{"Glow 2", GraphicsUnit::Type::guGlow2},
	{"Glow 3", GraphicsUnit::Type::guGlow3},
	{"Map Button", GraphicsUnit::Type::guMapButton1},
	{"Map Button 1", GraphicsUnit::Type::guMapButton1},
	{"Map Button 2", GraphicsUnit::Type::guMapButton2},
	{"Screen", GraphicsUnit::Type::guScreen},
	{"Shell", GraphicsUnit::Type::guShell},
	{"Shield", GraphicsUnit::Type::guShield1},
	{"Shield 1", GraphicsUnit::Type::guShield1},
	{"Shield 2", GraphicsUnit::Type::guShield2},
	{"Smoke", GraphicsUnit::Type::guSmoke},
	{"Spark", GraphicsUnit::Type::guSparks},
	{"Tank", GraphicsUnit::Type::guTank},
	{"Text", GraphicsUnit::Type::guText},
	{"Tracks", GraphicsUnit::Type::guTrack},
	{"Trail", GraphicsUnit::Type::guTrail},
	{"UI", GraphicsUnit::Type::guUI1},
	{"UI 1", GraphicsUnit::Type::guUI1},
	{"UI 2", GraphicsUnit::Type::guUI2},
	{"Wall", GraphicsUnit::Type::guWall1},
	{"Wall 1", GraphicsUnit::Type::guWall1},
	{"Wall 2", GraphicsUnit::Type::guWall2}
};

/*!
\var    controlTable
          Map containing conversion from strings to control key types.
*/
static const std::map<std::string, ControlUnit::ControlType> controlTable = {
	{"Up", ControlUnit::ControlType::UP},
	{"Down", ControlUnit::ControlType::DOWN},
	{"Left", ControlUnit::ControlType::LEFT},
	{"Right", ControlUnit::ControlType::RIGHT},
	{"First", ControlUnit::ControlType::FIRST},
	{"Shoot", ControlUnit::ControlType::FIRST},
	{"Confirm", ControlUnit::ControlType::FIRST},
	{"Second", ControlUnit::ControlType::SECOND},
	{"Pause", ControlUnit::ControlType::SECOND},
	{"Back", ControlUnit::ControlType::SECOND}
};

/*!
\var   keyStateTable
          Map containing conversion from strings to key states.
*/
static const std::map<std::string, ControlManager::KeyState> keyStateTable = {
	{"Pressed", ControlManager::KeyState::PRESSED},
	{"Held", ControlManager::KeyState::HELD},
	{"Released", ControlManager::KeyState::RELEASED}
};

/*!
\var   sliderTypeTable
          Map containing conversion from strings to slider target types.
*/
static const std::map<std::string, BehaviorDisplayFloatBar::FloatType> sliderTypeTable = {
	{"Music", BehaviorDisplayFloatBar::FloatType::MUSIC},
	{"SFX", BehaviorDisplayFloatBar::FloatType::SFX},
	{"Color", BehaviorDisplayFloatBar::FloatType::TEAM_COLOR}
};