/*!
\file   BehaviorDisplayControlKey.cpp
\author Kevin Shin
\date   3-22-2023
\brief
        Functions for managing the behavior of an agreement button confirmation icon
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include <map>

#include "ControllerButtons.h"
#include "MeshManager.h"
#include "Sprite.h"
#include "TeamSystem.h"
#include "TextureManager.h"

#include "BehaviorDisplayControlKey.h"

/*!
\fn     BehaviorDisplayControlKey::BehaviorDisplayControlKey()
\brief  See BehaviorDisplayControlKey.h
*/
BehaviorDisplayControlKey::BehaviorDisplayControlKey() : Behavior(), target(nullptr), preTarget(-1), type(ControlUnit::ControlType::INVALID), layer(GraphicsUnit::Type::guInvalid){
	
	//	Set values of `fonts`
	fonts[0] = &TextureManager::getTexture("font");
	fonts[1] = nullptr;
	fonts[2] = nullptr;
	
	//	Set values of `fontSizes`
	fontSizes[0] = 1;
	fontSizes[1] = 1;
	fontSizes[2] = 1;

}

/*!
\fn     BehaviorDisplayControlKey::BehaviorDisplayControlKey(const BehaviorDisplayControlKey &that)
\param  that
          source
\brief  See BehaviorDisplayControlKey.h
*/
BehaviorDisplayControlKey::BehaviorDisplayControlKey(const BehaviorDisplayControlKey &that) : BehaviorDisplayControlKey(){}

/*!
\var    CONTROL_ICON
          Map to translate keybinds to cooresponding textures and offsets
*/
static const std::map<int, std::pair<unsigned, unsigned>> CONTROL_ICONS{
	{GLFW_KEY_SPACE, {1, 0}},
	{GLFW_KEY_APOSTROPHE, {0, 7}},
	{GLFW_KEY_COMMA, {0, 12}},
	{GLFW_KEY_MINUS, {0, 13}},
	{GLFW_KEY_PERIOD, {0, 14}},
	{GLFW_KEY_SLASH, {0, 15}},
	{GLFW_KEY_0, {0, 16}},
	{GLFW_KEY_1, {0, 17}},
	{GLFW_KEY_2, {0, 18}},
	{GLFW_KEY_3, {0, 19}},
	{GLFW_KEY_4, {0, 20}},
	{GLFW_KEY_5, {0, 21}},
	{GLFW_KEY_6, {0, 22}},
	{GLFW_KEY_7, {0, 23}},
	{GLFW_KEY_8, {0, 24}},
	{GLFW_KEY_9, {0, 25}},
	{GLFW_KEY_SEMICOLON, {0, 27}},
	{GLFW_KEY_EQUAL, {0, 29}},
	{GLFW_KEY_A, {0, 33}},
	{GLFW_KEY_B, {0, 34}},
	{GLFW_KEY_C, {0, 35}},
	{GLFW_KEY_D, {0, 36}},
	{GLFW_KEY_E, {0, 37}},
	{GLFW_KEY_F, {0, 38}},
	{GLFW_KEY_G, {0, 39}},
	{GLFW_KEY_H, {0, 40}},
	{GLFW_KEY_I, {0, 41}},
	{GLFW_KEY_J, {0, 42}},
	{GLFW_KEY_K, {0, 43}},
	{GLFW_KEY_L, {0, 44}},
	{GLFW_KEY_M, {0, 45}},
	{GLFW_KEY_N, {0, 46}},
	{GLFW_KEY_O, {0, 47}},
	{GLFW_KEY_P, {0, 48}},
	{GLFW_KEY_Q, {0, 49}},
	{GLFW_KEY_R, {0, 50}},
	{GLFW_KEY_S, {0, 51}},
	{GLFW_KEY_T, {0, 52}},
	{GLFW_KEY_U, {0, 53}},
	{GLFW_KEY_V, {0, 54}},
	{GLFW_KEY_W, {0, 55}},
	{GLFW_KEY_X, {0, 56}},
	{GLFW_KEY_Y, {0, 57}},
	{GLFW_KEY_Z, {0, 58}},
	{GLFW_KEY_LEFT_BRACKET, {0, 59}},
	{GLFW_KEY_BACKSLASH, {0, 60}},
	{GLFW_KEY_RIGHT_BRACKET, {0, 61}},
	{GLFW_KEY_GRAVE_ACCENT, {0, 64}},
	{GLFW_KEY_WORLD_1, {1, 1}},
	{GLFW_KEY_WORLD_2, {1, 2}},
	{GLFW_KEY_ESCAPE, {1, 3}},
	{GLFW_KEY_ENTER, {1, 4}},
	{GLFW_KEY_TAB, {1, 5}},
	{GLFW_KEY_BACKSPACE, {1, 6}},
	{GLFW_KEY_INSERT, {1, 7}},
	{GLFW_KEY_DELETE, {1, 8}},
	{GLFW_KEY_RIGHT, {1, 9}},
	{GLFW_KEY_LEFT, {1, 10}},
	{GLFW_KEY_DOWN, {1, 11}},
	{GLFW_KEY_UP, {1, 12}},
	{GLFW_KEY_PAGE_UP, {1, 13}},
	{GLFW_KEY_PAGE_DOWN, {1, 14}},
	{GLFW_KEY_HOME, {1, 15}},
	{GLFW_KEY_END, {1, 16}},
	{GLFW_KEY_CAPS_LOCK, {1, 17}},
	{GLFW_KEY_SCROLL_LOCK, {1, 18}},
	{GLFW_KEY_NUM_LOCK, {1, 19}},
	{GLFW_KEY_PRINT_SCREEN, {1, 20}},
	{GLFW_KEY_PAUSE, {1, 21}},
	{GLFW_KEY_F1, {1, 22}},
	{GLFW_KEY_F2, {1, 23}},
	{GLFW_KEY_F3, {1, 24}},
	{GLFW_KEY_F4, {1, 25}},
	{GLFW_KEY_F5, {1, 26}},
	{GLFW_KEY_F6, {1, 27}},
	{GLFW_KEY_F7, {1, 28}},
	{GLFW_KEY_F8, {1, 29}},
	{GLFW_KEY_F9, {1, 30}},
	{GLFW_KEY_F10, {1, 31}},
	{GLFW_KEY_F11, {1, 32}},
	{GLFW_KEY_F12, {1, 33}},
	{GLFW_KEY_F13, {1, 34}},
	{GLFW_KEY_F14, {1, 35}},
	{GLFW_KEY_F15, {1, 36}},
	{GLFW_KEY_F16, {1, 37}},
	{GLFW_KEY_F17, {1, 38}},
	{GLFW_KEY_F18, {1, 39}},
	{GLFW_KEY_F19, {1, 40}},
	{GLFW_KEY_F20, {1, 41}},
	{GLFW_KEY_F21, {1, 42}},
	{GLFW_KEY_F22, {1, 43}},
	{GLFW_KEY_F23, {1, 44}},
	{GLFW_KEY_F24, {1, 45}},
	{GLFW_KEY_F25, {1, 46}},
	{GLFW_KEY_KP_0, {1, 47}},
	{GLFW_KEY_KP_1, {1, 48}},
	{GLFW_KEY_KP_2, {1, 49}},
	{GLFW_KEY_KP_3, {1, 50}},
	{GLFW_KEY_KP_4, {1, 51}},
	{GLFW_KEY_KP_5, {1, 52}},
	{GLFW_KEY_KP_6, {1, 53}},
	{GLFW_KEY_KP_7, {1, 54}},
	{GLFW_KEY_KP_8, {1, 55}},
	{GLFW_KEY_KP_9, {1, 56}},
	{GLFW_KEY_KP_DECIMAL, {1, 57}},
	{GLFW_KEY_KP_DIVIDE, {1, 58}},
	{GLFW_KEY_KP_MULTIPLY, {1, 59}},
	{GLFW_KEY_KP_SUBTRACT, {1, 60}},
	{GLFW_KEY_KP_ADD, {1, 61}},
	{GLFW_KEY_KP_ENTER, {1, 62}},
	{GLFW_KEY_KP_EQUAL, {1, 63}},
	{GLFW_KEY_LEFT_SHIFT, {1, 64}},
	{GLFW_KEY_LEFT_CONTROL, {1, 65}},
	{GLFW_KEY_LEFT_ALT, {1, 66}},
	{GLFW_KEY_LEFT_SUPER, {1, 67}},
	{GLFW_KEY_RIGHT_SHIFT, {1, 68}},
	{GLFW_KEY_RIGHT_CONTROL, {1, 69}},
	{GLFW_KEY_RIGHT_ALT, {1, 70}},
	{GLFW_KEY_RIGHT_SUPER, {1, 71}},
	{GLFW_KEY_MENU, {1, 72}},
	{CTRL_KEY_A, {2, 0}},
	{CTRL_KEY_B, {2, 1}},
	{CTRL_KEY_X, {2, 2}},
	{CTRL_KEY_Y, {2, 3}},
	{CTRL_KEY_UP, {2, 4}},
	{CTRL_KEY_DOWN, {2, 5}},
	{CTRL_KEY_LEFT, {2, 6}},
	{CTRL_KEY_RIGHT, {2, 7}},
	{CTRL_KEY_LS, {2, 8}},
	{CTRL_KEY_RS, {2, 9}},
	{CTRL_KEY_LB, {2, 10}},
	{CTRL_KEY_RB, {2, 11}},
	{CTRL_KEY_BACK, {2, 12}},
	{CTRL_KEY_START, {2, 13}},
	{CTRL_KEY_GUIDE, {2, 14}},
	{CTRL_KEY_LS_UP, {2, 15}},
	{CTRL_KEY_LS_DOWN, {2, 16}},
	{CTRL_KEY_LS_LEFT, {2, 17}},
	{CTRL_KEY_LS_RIGHT, {2, 18}},
	{CTRL_KEY_RS_UP, {2, 19}},
	{CTRL_KEY_RS_DOWN, {2, 20}},
	{CTRL_KEY_RS_LEFT, {2, 21}},
	{CTRL_KEY_RS_RIGHT, {2, 22}},
	{CTRL_KEY_LT, {2, 23}},
	{CTRL_KEY_RT, {2, 24}}
};

/*!
\fn     void BehaviorDisplayControlKey::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorDisplayControlKey::update(float dt){

	//	Variable: Parent object
	GameObject *obj = getParent();

	//	Check `obj`
	if(obj == nullptr) return;

	//	Get and set `target`
	if(type > ControlUnit::ControlType::INVALID && type < ControlUnit::ControlType::MAX){

		//	Set `target`
		target = TeamSystem::getInstance() -> getControls(obj -> getTeam()) -> getKeyReference(type);

		//	Unset `type`
		type = ControlUnit::ControlType::INVALID;

	}

	//	Check `target`
	if(target == nullptr || *target == preTarget) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Variable: Found icon pair
	std::pair<unsigned, unsigned> iconInfo;

	//	Attempt to find the key in `CONTROL_ICONS`
	try{

		//	Check `CONTROL_ICONS`
		iconInfo = CONTROL_ICONS.at(*target);

	}
	catch(const std::out_of_range&){

		//	Set defaults
		iconInfo.first = 0;
		iconInfo.second = 0;

	}

	//	Variable: Mesh to draw with
	Mesh *mesh;

	//	Get `mesh`
	if(!MeshManager::getInstance() -> getMesh(MeshManager::MeshType::text, mesh)) return;

	//	Set new graphics
	spr -> clearGraphics();
	spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, layer, fonts[iconInfo.first], iconInfo.second / 96.f, 0, 0, 0, 0, fontSizes[iconInfo.first], fontSizes[iconInfo.first], 1));

}

/*!
\fn     BehaviorDisplayControlKey *BehaviorDisplayControlKey::clone() const
\brief  See Component.h
*/
BehaviorDisplayControlKey *BehaviorDisplayControlKey::clone() const{
	return new BehaviorDisplayControlKey(*this);
}

/*!
\fn     void BehaviorDisplayControlKey::setTarget(ControlUnit::ControlType type)
\param  type
          type
\brief  See BehaviorDisplayControlKey.h
*/
void BehaviorDisplayControlKey::setTarget(ControlUnit::ControlType type){
	this -> type = type;
}

/*!
\fn     void BehaviorDisplayControlKey::setFont(unsigned i, Texture *font, float size)
\param  i
          i
\param  font
          font
\param  size
          size
\brief  See BehaviorDisplayControlKey.h
*/
void BehaviorDisplayControlKey::setFont(unsigned i, Texture *font, float size){

	//	Check `i`
	if(i > 2) return;

	//	Set `fonts`
	fonts[i] = font;

	//	Set `fontSizes`
	fontSizes[i] = size;

}

/*!
\fn     void BehaviorDisplayControlKey::setLayer(GraphicsUnit::Type layer)
\param  type
          type
\brief  See BehaviorDisplayControlKey.h
*/
void BehaviorDisplayControlKey::setLayer(GraphicsUnit::Type layer){
	this -> layer = layer;
}