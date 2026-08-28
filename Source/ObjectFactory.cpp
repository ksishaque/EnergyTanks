/*!
\file   ObjectFactory.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-15-2022
\brief
        Functions for reading a .JSON file and using RapidJSON to parse it into a game object.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/


#pragma warning(push)
#pragma warning(disable:33010)
#pragma warning(disable:26451)
#pragma warning(disable:26495)
#include "rapidjson/document.h"
#pragma warning(pop)
#include "readFile.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "ActionList.h"
#include "ActionNodeIncludes.h"
#include "BehaviorAgreeButton.h"
#include "BehaviorBullet.h"
#include "BehaviorConfirmIcon.h"
#include "BehaviorControlsBlocker.h"
#include "BehaviorDisplayControlKey.h"
#include "BehaviorDisplayFullscreen.h"
#include "BehaviorDisplayMultiMonitor.h"
#include "BehaviorDisplayPowerUp.h"
#include "BehaviorHealth.h"
#include "BehaviorMap.h"
#include "BehaviorOptionSelector.h"
#include "BehaviorOptionTrack.h"
#include "BehaviorPlayer.h"
#include "BehaviorPopup.h"
#include "BehaviorPowerUp.h"
#include "BehaviorShield.h"
#include "BehaviorText.h"
#include "BehaviorTeamButton.h"
#include "BehaviorUniversalButton.h"
#include "BehaviorWall.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "MenuOption.h"
#include "MeshManager.h"
#include "ObjectContainer.h"
#include "ParticleGenerator.h"
#include "Physics.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "SoundSystem.h"
#include "Sprite.h"
#include "StringTables.h"
#include "TextureManager.h"
#include "Trace.h"
#include "ObjectFactory.h"

using rapidjson::Document;
using rapidjson::Value;

/*!
\fn     static bool getGLFWKey(Value &val, int &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for the parsed key code
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a valid GLFW key code.
*/
static bool getGLFWKey(Value &val, int &ans){

	//	Check `key`
	if(!val.IsString()) return false;

	//	Variable: `key` as a c-style string of characters
	const char *keyString = val.GetString();

	//	Check for basic single-character keys
	if(val.GetStringLength() == 1){

		//	Chuck uppercase keys
		if(*keyString >= ' ' && *keyString < 'a' && invalid.find(*keyString) == std::string::npos){

			//	Set `ans`
			ans = (int) *keyString;
			
			//	Return
			return true;
		}
	
		//	Check for lowercase keys
		if(*keyString > '`' && *keyString < '{'){

			//	Set `ans`
			ans = (int) *keyString;
	
			//	Convert to uppercase
			ans += (int) 'A';
			ans -= (int) 'a';
			
			//	Return
			return true;
		}

		//	Return if the string was invalid
		return false;
	}

	//	Check for other keys
	try{

		//	Check key table
		ans = keyTable.at(std::string(keyString));

		//	Return
		return true;
	}
	catch(const std::out_of_range&){

		//	Return
		return false;
	}
}

/*!
\fn     static GameObject::Type getObjectType(Value &val)
\param  val
          rapidJSON value to parse
\return Parsed object type
\brief
        This function parses a rapidJSON value into a valid object type.
*/
static GameObject::Type getObjectType(Value &val){

	//	Check `val`
	if(!val.IsString()) return GameObject::Type::Invalid;

	//	Variable: `val` as a c-style string of characters
	const char *valString = val.GetString();

	//	Check for other keys
	try{

		//	Check key table and return
		return typeTable.at(std::string(valString));

	}
	catch(const std::out_of_range&){

		//	Return
		return GameObject::Type::Invalid;

	}

}

/*!
\fn     static bool getGraphicsLayer(Value &val, GraphicsUnit::Type &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for parsed type
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a valid graphics unit type.
*/
static bool getGraphicsLayer(Value &val, GraphicsUnit::Type &ans){

	//	Check for string
	if(val.IsString()){

		//	Variable: `val` as a c-style string of characters
		const char *valString = val.GetString();
		
		//	Check `layerTable`
		try{

			//	Retrieve from `layerTable`
			ans = layerTable.at(std::string(valString));

			//	Return
			return true;

		}
		catch(const std::out_of_range&){
		
			//	Set invalid case
			ans = GraphicsUnit::Type::guInvalid;

			//	Return
			return false;

		}

	}

	//	Set invalid case and return
	ans = GraphicsUnit::Type::guInvalid;
	return false;

}

/*!
\enum   GraphicsLoadTypes
          Types of viable graphics loading methods
\var    BASIC
          Basic draw
\var    TEXT
          Text draw
\var    GLOW
          Glow effect
*/
enum GraphicsLoadType{BASIC, TEXT, GLOW, TEST};

/*!
\var    graphicsTable
          Map containing conversion from strings to valid graphics loading types.
*/
static const std::map<std::string, GraphicsLoadType> graphicsTable = {
#ifdef _DEBUG
	{"TEST", GraphicsLoadType::TEST},
#endif
	{"Basic", GraphicsLoadType::BASIC},
	{"Text", GraphicsLoadType::TEXT},
	{"Glow", GraphicsLoadType::GLOW}
};

/*!
\fn     static bool getGraphicsType(Value &val, GraphicsLoadType &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for parsed type
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a valid graphics unit type.
*/
static bool getGraphicsType(Value &val, GraphicsLoadType &ans){

	//	Check for string
	if(val.IsString()){

		//	Variable: `val` as a c-style string of characters
		const char *valString = val.GetString();
		
		//	Check `layerTable`
		try{

			//	Retrieve from `layerTable`
			ans = graphicsTable.at(std::string(valString));

			//	Return
			return true;

		}
		catch(const std::out_of_range&){
		
			//	Set invalid case
			ans = GraphicsLoadType::BASIC;

			//	Return
			return false;

		}

	}

	//	Set invalid case and return
	ans = GraphicsLoadType::BASIC;
	return false;

}

/*!
\fn     static bool getControlType(Value &val, ControlUnit::ControlType &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for parsed type
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a valid control type.
*/
static bool getControlType(Value &val, ControlUnit::ControlType &ans){

	//	Check for string
	if(val.IsString()){

		//	Variable: `val` as a c-style string of characters
		const char *valString = val.GetString();
		
		//	Check `controlTable`
		try{

			//	Retrieve from `controlTable`
			ans = controlTable.at(std::string(valString));

			//	Return
			return true;

		}
		catch(const std::out_of_range&){
		
			//	Set invalid case
			ans = ControlUnit::ControlType::MAX;

			//	Return
			return false;

		}

	}

	//	Set invalid case and return
	ans = ControlUnit::ControlType::MAX;
	return false;

}

/*!
\fn     static bool getKeyState(Value &val, ControlManager::KeyState &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for parsed state
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a valid key state.
*/
static bool getKeyState(Value &val, ControlManager::KeyState &ans){

	//	Check for string
	if(val.IsString()){

		//	Variable: `val` as a c-style string of characters
		const char *valString = val.GetString();
		
		//	Check `keyStateTable`
		try{

			//	Retrieve from `keyStateTable`
			ans = keyStateTable.at(std::string(valString));

			//	Return
			return true;

		}
		catch(const std::out_of_range&){

			//	Return
			return false;

		}

	}

	//	Return
	return false;

}

/*!
\fn     static bool getSliderType(Value &val,BehaviorDisplayFloatBar::FloatType &ans)
\param  val
          rapidJSON value to parse
\param  ans
          Output reference for parsed typs
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value into a slider type.
*/
static bool getSliderType(Value &val, BehaviorDisplayFloatBar::FloatType &ans){

	//	Check for string
	if(val.IsString()){

		//	Variable: `val` as a c-style string of characters
		const char *valString = val.GetString();
		
		//	Check `sliderTypeTable`
		try{

			//	Retrieve from `sliderTypeTable`
			ans = sliderTypeTable.at(std::string(valString));

			//	Return
			return true;

		}
		catch(const std::out_of_range&){

			//	Return
			return false;

		}

	}

	//	Return
	return false;

}

/*!
\fn     static bool getGLMVec3(Value &val, glm::vec3 &ans, float z)
\param  val
          rapidJSON value to parse
\param  ans
          vector to place the parsed values into
\param  z
          default z value to assume
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value as a GLM vector.
*/
static bool getGLMVec3(Value &val, glm::vec3 &ans, float z){
	
	//	Check for object
	if(val.IsObject()){
	
		//	Variable: `val` as a rapidJSON object
		rapidjson::GenericObject<false, Value> valObj = val.GetObject();
	
		//	Check for x, y and z as floats
		if(valObj.HasMember("x") && valObj["x"].IsFloat() && valObj.HasMember("y") && valObj["y"].IsFloat()){

			//	Get x and y from valObj
			ans.x = valObj["x"].GetFloat();
			ans.y = valObj["y"].GetFloat();
			if(valObj.HasMember("z") && valObj["z"].IsFloat()) ans.z = valObj["z"].GetFloat();
			else ans.z = z;

			//	Return
			return true;
		}
	}

	//	Check for array
	else if(val.IsArray()){
	
		//	Variable: `val` as a rapidJSON object
		rapidjson::GenericArray<false, Value> valArr = val.GetArray();
	
		//	Check for x, y and z
		if(valArr.Capacity() > 1 && valArr[0].IsFloat() && valArr[1].IsFloat()){

			//	Get x, y and z from valObj
			ans.x = valArr[0].GetFloat();
			ans.y = valArr[1].GetFloat();
			if(valArr.Capacity() > 2 && valArr[2].IsFloat()) ans.z = valArr[2].GetFloat();
			else ans.z = z;

			//	Return
			return true;
		}
	}

	//	Return if `val` is invalid
	return false;
}

/*!
\fn     static bool getColor(Value &val, glm::vec4 &rgba, float &team)
\param  val
          rapidJSON value to parse
\param  rgba
          Output reference to place the parsed rgba values into
\param  teamColor
          Output reference to place team color value into
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value as an rgba color vector and a team color value.
*/
static bool getColor(Value &val, glm::vec4 &rgba, float &team){
	
	//	Check for object
	if(val.IsObject()){
	
		//	Variable: `val` as a rapidJSON object
		rapidjson::GenericObject<false, Value> valObj = val.GetObject();
	
		//	Check for r, g and b as floats
		if(valObj.HasMember("r") && valObj["r"].IsFloat() && valObj.HasMember("g") && valObj["g"].IsFloat() && valObj.HasMember("b") && valObj["b"].IsFloat()){

			//	Get r, g and b from valObj
			rgba.r = valObj["r"].GetFloat();
			rgba.g = valObj["g"].GetFloat();
			rgba.b = valObj["b"].GetFloat();

			//	Check for a
			if(valObj.HasMember("a") && valObj["a"].IsFloat()) rgba.a = valObj["a"].GetFloat();

			//	Check for t
			if(valObj.HasMember("t") && valObj["t"].IsFloat()) team = valObj["t"].GetFloat();

			//	Return
			return true;

		}

	}

	//	Check for array
	else if(val.IsArray()){
	
		//	Variable: `val` as a rapidJSON object
		rapidjson::GenericArray<false, Value> valArr = val.GetArray();
	
		//	Check for r, g and b
		if(valArr.Capacity() > 2 && valArr[0].IsFloat() && valArr[1].IsFloat() && valArr[2].IsFloat()){

			//	Get r, g and b from valObj
			rgba.r = valArr[0].GetFloat();
			rgba.g = valArr[1].GetFloat();
			rgba.b = valArr[2].GetFloat();

			//	Check for a
			if(valArr.Capacity() > 3 && valArr[3].IsFloat()) rgba.a = valArr[3].GetFloat();

			//	Check for t
			if(valArr.Capacity() > 4 && valArr[4].IsFloat()) team = valArr[4].GetFloat();

			//	Return
			return true;

		}

	}

	//	Check for just team color
	else if(val.IsFloat()){

		//	Set team color
		team = val.GetFloat();

		//	Return
		return true;

	}

	//	Return if `val` is invalid
	return false;
}

/*!
\fn     static bool getActionList(Value &val, ActionList *list)
\param  val
          RapidJSON value to parse
\param  list
          Action list to edit
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value as a GLM vector.
*/
static bool getActionList(Value &val, ActionList *list);

/*!
\fn     static bool getAction(Value &val, ActionNode *ans)
\param  val
          RapidJSON value to parse
\param  ans
          Return pointer for new action node
\return If `val` was successfully parsed
\brief
        This function parses a rapidJSON value as an action node.
*/
static ActionNode * getAction(Value &val){
	if(val.IsObject()){
	
		//	Variable: `val` as a rapidJSON object
		rapidjson::GenericObject<false, Value> valObj = val.GetObject();

		//	Check format
		if(!(valObj.HasMember("type") && valObj["type"].IsString())) return nullptr;

		//	Variable: type of action being made
		std::string type(valObj["type"].GetString());
	
		//	Create function actions
		if(type == "function"){

			//	Check format
			if(!(valObj.HasMember("function") && valObj["function"].IsString())) return nullptr;

			//	Variable: function for action
			std::string fn(valObj["function"].GetString());

			//	Parse function name
			if(fn == "restartGame") return new FunctionActionNode<ActionFunctionVoid>(restartGame);
			else if(fn == "shutdownGame") return new FunctionActionNode<ActionFunctionVoid>(shutdownGame);
			else if(fn == "musicVolumeUp") return new FunctionActionNode<ActionFunctionDt>(increaseMusicVolume);
			else if(fn == "musicVolumeDown") return new FunctionActionNode<ActionFunctionDt>(decreaseMusicVolume);
			else if(fn == "sfxVolumeUp") return new FunctionActionNode<ActionFunctionDt>(increaseSfxVolume);
			else if(fn == "sfxVolumeDown") return new FunctionActionNode<ActionFunctionDt>(decreaseSfxVolume);
			else if(fn == "die") return new FunctionActionNode<ActionFunctionObj>(die);
			else if(fn == "closeGame") return new FunctionActionNode<ActionFunctionVoid>(closeGame);
			else return nullptr;

		}
	
		//	Create changestate actions
		if(type == "changestate"){

			//	Check format
			if(!(valObj.HasMember("to") && valObj["to"].IsString())) return nullptr;

			//	Create action
			return changeGamestate(valObj["to"].GetString());

		}

		//	Create teamloss conditional actions
		if(type == "checkTeamLoss"){

			//	Check format
			if(!(valObj.HasMember("team") && valObj["team"].IsInt())) return nullptr;

			//	Create action
			return checkTeamLoss((GameObject::Team) valObj["team"].GetInt());

		}

		//	Create playsound actions
		if(type == "playSound"){

			//	Check format
			if(!(valObj.HasMember("sound") && valObj["sound"].IsString())) return nullptr;

			//	Create action without `paused`
			return playSoundAct(std::string(valObj["sound"].GetString()), valObj.HasMember("Paused"));

		}

		//	Create generateParticles actions
		if (type == "generateParticles") {

			//	Check format
			if (!(valObj.HasMember("particleType") && valObj["particleType"].IsString())) return nullptr;

			//	Create action
			return generateParticlesAct(std::string(valObj["particleType"].GetString()));

		}

		//	Create fading actions
		if(type == "fade"){

			//	Check format
			if(!(valObj.HasMember("from") && valObj["from"].IsFloat() && valObj.HasMember("to") && valObj["to"].IsFloat() && valObj.HasMember("time") && valObj["time"].IsFloat())) return nullptr;

			//	Create action
			return fade(valObj["from"].GetFloat(), valObj["to"].GetFloat(), valObj["time"].GetFloat());

		}

		//	Create blank actions
#ifdef DEBUG_SYSTEM
		if(type == "blank") Trace::error("OUTDATED ACTION NODE: REMOVE BLANK ACTION");
#endif

		//	Create waiting actions
		if(type == "sleep"){

			//	Check format
			if(!(valObj.HasMember("time") && valObj["time"].IsFloat())) return nullptr;

			//	Create action
			return sleep(valObj["time"].GetFloat());

		}

		//	Create texture loading actions
		if(type == "loadTexture"){

			//	Check format
			if(!(valObj.HasMember("texture") && valObj["texture"].IsString())) return nullptr;

			//	Create action without `paused`
			return loadTextureAct(valObj["texture"].GetString());

		}

		//	Create team color cycling actions
		if(type == "incTeamCol"){

			//	Check format
			if(!(valObj.HasMember("team") && valObj["team"].IsInt() && valObj.HasMember("ratio") && valObj["ratio"].IsFloat())) return nullptr;

			//	Create action without `paused`
			return incrementTeamColor(valObj["team"].GetInt(), valObj["ratio"].GetFloat());

		}

		//	Create object loading actions
		if(type == "create"){

			//	Check format
			if(!(valObj.HasMember("name") && valObj["name"].IsString())) return nullptr;

			//	Create action
			return newObjAct(valObj["name"].GetString(), valObj.HasMember("global"));

		}

		//	Create object killing actions
		if(type == "destroy"){

			//	Check format
			if(!(valObj.HasMember("name") && valObj["name"].IsString())) return nullptr;

			//	Create action
			return killObjAct(valObj["name"].GetString());

		}

		//	Create timed actions
		if(type == "timed"){

			//	Variable: Sublist to use for the timed list
			ActionList *list = new ActionList();

			//	Check format and parse `list`
			if(!(valObj.HasMember("time") && valObj["time"].IsFloat() && valObj.HasMember("list") && getActionList(valObj["list"], list))) return nullptr;

			//	Create action
			return timedAct(list, valObj["time"].GetFloat());

		}

		//	Create color setting actions
		if(type == "setColor"){

			//	Check format for explicit
			if(valObj.HasMember("r") && valObj["r"].IsFloat() && valObj.HasMember("g") && valObj["g"].IsFloat() && valObj.HasMember("b") && valObj["b"].IsFloat() && valObj.HasMember("a") && valObj["a"].IsFloat()) return  setColorAct(valObj["r"].GetFloat(), valObj["g"].GetFloat(), valObj["b"].GetFloat(), valObj["a"].GetFloat());

			//	Check format for array
			if(valObj.HasMember("color") && valObj["color"].IsArray() && valObj["color"].Size() > 3 && valObj["color"][0].IsFloat() && valObj["color"][1].IsFloat() && valObj["color"][2].IsFloat() && valObj["color"][3].IsFloat()) return setColorAct(valObj["color"][0].GetFloat(), valObj["color"][1].GetFloat(), valObj["color"][2].GetFloat(), valObj["color"][3].GetFloat());

			//	Return failed case
			return nullptr;

		}

		//	Create repeating actions
		if(type == "repeat"){

			//	Variable: Sublist to use for the timed list
			ActionList *list = new ActionList();

			//	Check format and parse `list`
			if(!(valObj.HasMember("list") && getActionList(valObj["list"], list))) return nullptr;

			//	Create action
			return repeatAct(list);

		}

		//	Create lingering actions
		if(type == "linger") return linger();

		//	Create pop up opening actions
		if(type == "openPopup"){

			//	Check format
			if(!(valObj.HasMember("name") && valObj["name"].IsString())) return nullptr;

			//	Create action
			return openPopup(valObj["name"].GetString());

		}

		//	Create pop up closing actions
		if(type == "closePopup"){

			//	Check for `name`
			if(valObj.HasMember("name")){
				
				//	Check format
				if(!valObj["name"].IsString()) return nullptr;

				//	Create action
				return closePopup(valObj["name"].GetString());

			}

			//	Create action
			return closeThisPopup();

		}

		//	Create selecting actions
		if(type == "selOption"){

			//	Check format
			if(!(valObj.HasMember("to") && valObj["to"].IsInt())) return nullptr;

			//	Create action
			return selectOption(valObj["to"].GetInt());

		}

		//	Create clicking actions
		if(type == "click") return clickAct();

		//	Create reloading actions
		if(type == "reload"){

			//	Variable: Sublist to use for the timed list
			ActionList *list = new ActionList();

			//	Check format and parse `list`
			if(!(valObj.HasMember("list") && getActionList(valObj["list"], list))) return nullptr;

			//	Create action
			return reloadAct(list);

		}

		//	Create full screen setting actions
		if(type == "fullscreen") return fullscreenAct(true);
		if(type == "windowed") return fullscreenAct(false);

		//	Create selecting actions
		if(type == "monitor"){

			//	Check format
			if(!(valObj.HasMember("inc") && valObj["inc"].IsInt())) return nullptr;

			//	Create action
			return monitorChange(valObj["inc"].GetInt());

		}

		//	Create full screen check actions
		if(type == "fullscreenCheck") return fullscreenCheck;

		//	Create multi monitor check actions
		if(type == "monitorCheck") return monitorCheck;

		//	Create moving actions
		if(type == "transform"){

			//	Check format
			if(!(valObj.HasMember("time") && valObj["time"].IsFloat())) return nullptr;

			//	Variable: Return value / moving action created
			TransformAction *ans;

			//	Check for coefficients
			if(valObj.HasMember("equation")){

				//	Check format
				if(!valObj["equation"].IsArray()) return nullptr;

				//	Variable: List of coefficients
				std::vector<float> cos;

				//	Parse `cos`
				for(Value &coVal : valObj["equation"].GetArray()){

					//	Check format
					if(!coVal.IsFloat()) return nullptr;

					//	Add to `cos`
					cos.push_back(coVal.GetFloat());

				}

				//	Create action
				ans = transformActCo(valObj["time"].GetFloat(), cos);

			}
			else ans = transformAct(valObj["time"].GetFloat());

			//	Variable: Temporary variable for outputs
			glm::vec3 temp;
			
			//	Edit members
			if(valObj.HasMember("translation") && getGLMVec3(valObj["translation"], temp, 1)) ans -> setTranslation(temp);
			if(valObj.HasMember("scale") && getGLMVec3(valObj["scale"], temp, 0)) ans -> setScale(temp);
			if(valObj.HasMember("rotation") && valObj["rotation"].IsFloat()) ans -> setRotation(valObj["rotation"].GetFloat());

			//	Return
			return ans;

		}

		//	Create branching actions
		if(type == "branch"){

			//	Variable: Sublist to use for the branched list
			ActionList *list = new ActionList();

			//	Check format and parse `list`
			if(!(valObj.HasMember("list") && getActionList(valObj["list"], list))) return nullptr;

			//	Create action
			return branchAct(list);

		}

		//	Create button activating actions
		if(type == "button"){

			//	Check format
			if(!(valObj.HasMember("name") && valObj["name"].IsString())) return nullptr;

			//	Create action
			return buttonPressAct(valObj["name"].GetString());

		}

		//	Create intial display actions
		if(type == "initialControlDisplay") return initialDisplayCheck;

		//	Create lockstate actions
		if(type == "lockState") return lockGamestate(!valObj.HasMember("unlock"));

		//	Create pause actions
		if(type == "pause") return pauseAct;
		if(type == "unpause") return unpauseAct;

		//	Create object setting actions
		if(type == "find"){

			//	Check format
			if(!(valObj.HasMember("name") && valObj["name"].IsString())) return nullptr;

			//	Create action
			return setObjectAct(valObj["name"].GetString());

		}

		//	Create random actions
		if(type == "random"){

			//	Check format
			if(!(valObj.HasMember("lists") && valObj["lists"].IsArray())) return nullptr;

			//	Variable: Return value / moving action created
			RandomConstantAction *ans = randomAct;

			//	Parse random pool
			for(Value &listVal : valObj["lists"].GetArray()){

				//	Variable: Sublist to add to random pool
				ActionList *list = new ActionList();

				//	Check format and parse `list`
				if(!getActionList(listVal, list)) return nullptr;

				//	Add `list`
				ans -> addPossibility(list);

			}

			//	Return
			return ans;

		}

	}

	return nullptr;
}

/*!
\fn     static bool getActionList(Value &val, ActionList *list)
\param  val
          val
\param  list
          list
\brief  See above
*/
static bool getActionList(Value &val, ActionList *list){

	//	Check for array
	if(!val.IsArray()) return false;
	
	//	Add each action
	for(Value &actionVal : val.GetArray()){

		//	Variable: action to add to the action list
		ActionNode *action = getAction(actionVal);

		//	Check for `action`
		if(action == nullptr)
#ifdef DEBUG_SYSTEM
			Trace::error("Action could not be deserialized");
#else
			assert("Deserialization error");
#endif

		//	Add `action` to the list
		else list -> add(action);
	}

	//	Return
	return true;
}

/*!
\fn     void parseObject(Value &info, ObjectManager &obj)
\param  info
          rapidJSON value to parse from
\param  obj
          object to parse to
\brief
        This function parses a rapidJSON value to edit a game object.
*/
void parseObject(Value &info, GameObject &obj){
	
	//	Parse type info
	if(info.HasMember("id")) obj.setType(getObjectType(info["id"]));

	//	Parse team info
	if(info.HasMember("team") && info["team"].IsInt()){
		
		//	Variable: Team information
		int team = info["team"].GetInt();

		//	Check and add team
		if(team < -1 || team > 1){
#ifdef DEBUG_SYSTEM
			if(Trace::error("\"team\" could not be parsed"))
#endif
				team = 0;
		}
		else obj.setTeam((GameObject::Team) info["team"].GetInt());
	}

	//	Remove transformation
	if(info.HasMember("- transformation")) obj.remove(ComponentTypeEnum::cTransform);

	//	Parse tranformation
	if(info.HasMember("transformation")){

		//	Check format
		if(!info["transformation"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"transformation\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		trans: transformation to edit
		data: data about the transformation to edit
		*/
		Transform *trans = dynamic_cast<Transform *>(obj.get(ComponentTypeEnum::cTransform));
		rapidjson::GenericObject<false, Value> data = info["transformation"].GetObj();

		//	Check `trans`
		if(trans == nullptr){
			trans = new Transform();
			obj.add(trans);
		}
		
		//	Variable: placeholder vector for return value of `getGLMVec3()`
		glm::vec3 vec;

		//	Edit `translation`
		if(data.HasMember("translation")){

			//	Check format
			if(!getGLMVec3(data["translation"], vec, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"translation\" (transform) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `translation`
			trans -> setTranslation(vec);
		}

		//	Edit `scale`
		if(data.HasMember("scale")){
	
			//	Check format
			if(!getGLMVec3(data["scale"], vec, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"scale\" (transform) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `scale`
			trans -> setScale(vec);
		}

		//	Edit `rotation`
		if(data.HasMember("rotation")){
	
			//	Check format
			if(!data["rotation"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"rotation\" (transform) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `rotation`
			trans -> setRotatePos(data["rotation"].GetFloat());
		}
	}

	//	Remove sprite
	if(info.HasMember("- sprite")) obj.remove(ComponentTypeEnum::cSprite);

	//	Parse sprite
	if(info.HasMember("sprite")){
		
		//	Check format
		if(!info["sprite"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"sprite\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		spr: sprite to edit
		data: data about the sprite to edit
		*/
		Sprite *spr = dynamic_cast<Sprite *>(obj.get(ComponentTypeEnum::cSprite));
		rapidjson::GenericObject<false, Value> data = info["sprite"].GetObj();

		//	Check `spr`
		if(spr == nullptr){
			spr = new Sprite();
			obj.add(spr);
		}

		//	Edit `graphics`
		if(data.HasMember("graphics")){

			//	Clear the existing graphics list
			spr -> clearGraphics();
				
			//	Check format
			if(!data["graphics"].IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"graphics\" (sprite) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Add graphics units
			for(Value &graphicsData : data["graphics"].GetArray()) if(graphicsData.IsObject()){

				/*	Variables:
				type: Type of loading method
				mesh: Type of mesh to use
				texture: Texture to use
				layer: Layer on which to draw
				trans: Transformation of offset
				scale: Scale of offset
				rot: Rotation of offset
				col: Color of texture
				*/
				GraphicsLoadType type;
				Mesh *mesh;
				GraphicsUnit::Type layer;
				Texture *texture = nullptr;
				glm::vec3 trans(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f);
				float rot = 0, team = 0;
				glm::vec4 col(1.0f, 1.0f, 1.0f, 1.0f);

				//	Edit `type`
				if(graphicsData.HasMember("type")){

					//	Parse `type`
					if(!getGraphicsType(graphicsData["type"], type))
#ifdef DEBUG_SYSTEM
						Trace::error("\"type\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif

				}
				else type = GraphicsLoadType::BASIC;

				//	Edit `mesh`
				if(graphicsData.HasMember("mesh")){

					//	Check format
					if(!graphicsData["mesh"].IsString())
#ifdef DEBUG_SYSTEM
						Trace::error("\"mesh\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif

					//	Get `mesh`
					if(!MeshManager::getInstance() -> getMesh((MeshManager::MeshType) (*graphicsData["mesh"].GetString()), mesh))
#ifdef DEBUG_SYSTEM
						Trace::error("\"mesh\" (sprite) is not a valid mesh type");
#else
						assert("Deserialization error!");
#endif
				}
				else{

					//	Variable: Default mesh type, based on loading type
					MeshManager::MeshType meshType;

					//	Get default mesh types
					switch(type){
						case GraphicsLoadType::TEXT:
							meshType = MeshManager::MeshType::text;
							break;
						case GraphicsLoadType::GLOW:
							meshType = MeshManager::MeshType::circle;
							break;
						default:
							meshType = MeshManager::MeshType::single;
					}

					//	Load default mesh
					if(!MeshManager::getInstance() -> getMesh(meshType, mesh))
#ifdef DEBUG_SYSTEM
						Trace::error("Default mesh is not a valid mesh type");
#else
						assert("Deserialization error!");
#endif

				}

				//	Edit `layer`
				if(graphicsData.HasMember("layer")){

					//	Parse `layer`
					if(!getGraphicsLayer(graphicsData["layer"], layer))
#ifdef DEBUG_SYSTEM
						Trace::error("\"layer\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif

				}
				else{

					//	Get default layer types
					switch(type){
						case GraphicsLoadType::TEXT:
							layer = GraphicsUnit::Type::guText;
							break;
						case GraphicsLoadType::GLOW:
							layer = GraphicsUnit::Type::guGlow2;
							break;
						default:
#ifdef _DEBUG
							layer = GraphicsUnit::Type::guTest;
#else
							layer = GraphicsUnit::Type::guInvalid;
#endif
					}
				}

				//	Edit `texture`
				if(graphicsData.HasMember("texture")){

					//	Check format
					if(!graphicsData["texture"].IsString())
#ifdef DEBUG_SYSTEM
						Trace::error("\"texture\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif
				
					//	Set `texture`
					texture = &TextureManager::getTexture(graphicsData["texture"].GetString());

				}

				//	Check for offset
				if(graphicsData.HasMember("offset")){

					//	Check format
					if(!graphicsData["offset"].IsObject())
#ifdef DEBUG_SYSTEM
						Trace::error("\"offset\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif

					//	Variable: Data about the offset
					Value &offData = graphicsData["offset"].GetObject();

					//	Edit `trans`
					if(offData.HasMember("translation")) if(!getGLMVec3(offData["translation"], trans, 0))
#ifdef DEBUG_SYSTEM
						Trace::error("\"translation\" (offset) could not be parsed");
#else
						assert("Deserialization error!");
#endif

					//	Edit `scale`
					if(offData.HasMember("scale")) if(!getGLMVec3(offData["scale"], scale, 0))
#ifdef DEBUG_SYSTEM
						Trace::error("\"scale\" (offset) could not be parsed");
#else
						assert("Deserialization error!");
#endif

					//	Edit `rot`
					if(offData.HasMember("rotation")){
	
						//	Check format
						if(!offData["rotation"].IsFloat())
#ifdef DEBUG_SYSTEM
							Trace::error("\"rotation\" (offset) could not be parsed");
#else
							assert("Deserialization error!");
#endif
			
						//	Set `rot`
						rot = offData["rotation"].GetFloat();

					}

				}

				//	Edit `col`
				if(graphicsData.HasMember("color")) if(!getColor(graphicsData["color"], col, team))
#ifdef DEBUG_SYSTEM
					Trace::error("\"color\" (sprite) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Create and add graphics based on type
				if(type == GraphicsLoadType::TEXT){
				
					//	Check "text"
					if(!(graphicsData.HasMember("text") && graphicsData["text"].IsString()))
#ifdef DEBUG_SYSTEM
						Trace::error("\"text\" (sprite) could not be parsed");
#else
						assert("Deserialization error!");
#endif

					//	Variable: Text to display
					std::string text = graphicsData["text"].GetString();

					//	Load default font if needed
					if(texture == nullptr) texture = &TextureManager::getTexture("font");

					//	Center the text
					trans.x -= (text.length() - 1) * 0.25f * scale.x;

					//	Add graphics units
					for(char c : text){

						//	Relocate `c`
						c -= ' ';

						//	Create and add graphics
						spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, layer, texture, ((float) c) / 96, 0, trans, scale, rot, col), team);

						//	Shift the text
						trans.x += 0.5f * scale.x;

					}

				}
				else if(type == GraphicsLoadType::GLOW){
				
					//	Check "strength"
					if(graphicsData.HasMember("strength")){

						//	Check format
						if(!graphicsData["strength"].IsFloat())
#ifdef DEBUG_SYSTEM
							Trace::error("\"strength\" (sprite) could not be parsed");
#else
							assert("Deserialization error!");
#endif

						//	Set "strength"
						scale *= graphicsData["strength"].GetFloat();

					}

					//	Make inner circle
					for(float r = 0.125f; r < 1.0625f; r += 0.125f) spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, (GraphicsUnit::Type) ((int) (layer) + 1), nullptr, 0, 0, trans, scale * r, 0, glm::vec4(1, 1, 1, 0.03125f)));

					//	Make outer circle
					col.a /= 32;
					for(float r = 0.125f; r < 2.0625f; r += 0.125f) spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, layer, nullptr, 0, 0, trans, scale * r, 0, col), team);

					//	Make back circle
					col.a *= 4;
					for(float r = 2.125f; r < 3.0625f; r += 0.125f) spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guGlow3, nullptr, 0, 0, trans, scale * r, 0, col), team);

				}
				else spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, layer, texture, 0, 0, trans, scale, rot, col), team);

			}

		}

	}

	//	Remove physics
	if(info.HasMember("- physics")) obj.remove(ComponentTypeEnum::cPhysics);

	//	Parse physics
	if(info.HasMember("physics")){

		//	Check format
		if(!info["physics"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"physics\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		phys: physics to edit
		data: data about the physics to edit
		*/
		Physics *phys = dynamic_cast<Physics *>(obj.get(ComponentTypeEnum::cPhysics));
		rapidjson::GenericObject<false, Value> data = info["physics"].GetObj();

		//	Check `phys`
		if(phys == nullptr){
			phys = new Physics();
			obj.add(phys);
		}
		
		//	Variable: placeholder vector for return value of `getGLMVec3()`
		glm::vec3 vec = glm::vec3{0, 0, 0};

		//	Edit `velocity`
		if(data.HasMember("velocity")){

			//	Check format
			if(!getGLMVec3(data["velocity"], vec, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"velocity\" (physics) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `velocity`
			phys -> setVelocity(vec);
		}
		else if(data.HasMember("rotated velocity")){

			//	Check format
			if(!getGLMVec3(data["rotated velocity"], vec, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"rotated velocity\" (physics) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `velocity` according to rotation
			phys -> setRotatedVelocity(vec);
		}

		//	Edit `acceleration`
		if(data.HasMember("acceleration")){

			//	Check format
			if(!getGLMVec3(data["acceleration"], vec, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"acceleration\" (physics) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `acceleration`
			phys -> setAcceleration(vec);
		}

		//	Edit `velocityRotate`
		if(data.HasMember("rotational velocity")){

			//	Check format
			if(!data["rotational velocity"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"rotational velocity\" (physics) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `velocityRotate` as rotational velcity
			phys -> setVelocityRotate(data["rotational velocity"].GetFloat());
		}

		//	Update old transform to avoid collisions
		phys -> updateOldTrans();
	}

	//	Remove action list
	if(info.HasMember("- action list")) obj.remove(ComponentTypeEnum::cActionList);

	//	Parse action list
	if(info.HasMember("action list")){

		//	Variable: action list to edit
		ActionList *list = dynamic_cast<ActionList *>(obj.get(ComponentTypeEnum::cActionList));

		//	Check `list`
		if(list == nullptr){
			list = new ActionList();
			obj.add(list);
		}

		//	Check format
		if(!getActionList(info["action list"], list))
#ifdef DEBUG_SYSTEM
			Trace::error("\"action list\" could not be parsed");
#else
			assert("Deserialization error!");
#endif
	}

	//	Remove collider
	if(info.HasMember("- collider")) obj.remove(ComponentTypeEnum::cCollider);

	//	Remove circle collider
	if(info.HasMember("- circle collier") && dynamic_cast<CircleCollider *>(obj.get(ComponentTypeEnum::cCollider))) obj.remove(ComponentTypeEnum::cCollider);

	//	Parse circle collider
	if(info.HasMember("circle collider")){

		//	Check format
		if(!info["circle collider"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"circle collider\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		col: circle collider to edit
		data: data about the collider to edit
		*/
		CircleCollider *col = dynamic_cast<CircleCollider *>(obj.get(ComponentTypeEnum::cCollider));
		rapidjson::GenericObject<false, Value> data = info["circle collider"].GetObj();

		//	Check `col`
		if(col == nullptr){
			col = new CircleCollider();
			obj.add(col);
		}

		//	Edit `radius`
		if(data.HasMember("radius")){

			//	Check format
			if(!data["radius"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"radius\" (circle collider) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `radius`
			col -> setRadius(data["radius"].GetFloat());
		}
	}

	//	Remove line collider
	if(info.HasMember("- line collier") && dynamic_cast<LineCollider *>(obj.get(ComponentTypeEnum::cCollider))) obj.remove(ComponentTypeEnum::cCollider);

	//	Parse line collider
	if(info.HasMember("line collider")){

		//	Check format
		if(!info["line collider"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"line collider\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		col: line collider to edit
		data: data about the collider to edit
		*/
		LineCollider *col = dynamic_cast<LineCollider *>(obj.get(ComponentTypeEnum::cCollider));
		rapidjson::GenericObject<false, Value> data = info["line collider"].GetObj();

		//	Check `col`
		if(col == nullptr){
			col = new LineCollider();
			obj.add(col);
		}

		//	Edit lines
		if(data.HasMember("lines")){

			//	Check format
			if(!data["lines"].IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"lines\" (line collider) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Clear current line data
			col -> clearSegments();
			
			//	Add each line
			for(Value &lineData : data["lines"].GetArray()){

				//	Check format
				if(!(lineData.IsArray() && lineData.Capacity() == 2))
#ifdef DEBUG_SYSTEM
					Trace::error("line data (line collider) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				/*	Variables:
				vec1: placeholder vector for return value of `getGLMVec3()`
				vec2: placeholder vector for return value of `getGLMVec3()`
				*/
				glm::vec3 vec1 = glm::vec3{0, 0, 0}, vec2 = glm::vec3{0, 0, 0};

				//	Check format
				if(!(getGLMVec3(lineData.GetArray()[0], vec1, 1) && getGLMVec3(lineData.GetArray()[1], vec2, 1)))
#ifdef DEBUG_SYSTEM
					Trace::error("line data (line collider) could not be parsed");
#else
					assert("Deserialization error!");
#endif
				
				//	Add line
				col -> addSegment(vec1, vec2);
			}
		}
	}

	//	Remove box collider
	if (info.HasMember("- box collier") && dynamic_cast<BoxCollider*>(obj.get(ComponentTypeEnum::cCollider))) obj.remove(ComponentTypeEnum::cCollider);

	//	Parse box collider
	if (info.HasMember("box collider")) {

		//	Check format
		if (!info["box collider"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"box collider\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		col: box collider to edit
		data: data about the collider to edit
		*/
		BoxCollider* col = dynamic_cast<BoxCollider*>(obj.get(ComponentTypeEnum::cCollider));
		rapidjson::GenericObject<false, Value> data = info["box collider"].GetObj();

		//	Check `col`
		if (col == nullptr) {
			col = new BoxCollider();
			obj.add(col);
		}

		//	Edit `height`
		if (data.HasMember("height")) {

			//	Check format
			if (!data["height"].IsInt())
#ifdef DEBUG_SYSTEM
				Trace::error("\"height\" (box collider) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `height`
			col->setHeight(data["height"].GetInt());
		}
		//	Edit `width`
		if (data.HasMember("width")) {

			//	Check format
			if (!data["width"].IsInt())
#ifdef DEBUG_SYSTEM
				Trace::error("\"width\" (box collider) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `radius`
			col->setWidth(data["width"].GetInt());
		}
	}

	//	Remove behavior
	if(info.HasMember("- behavior")) obj.remove(ComponentTypeEnum::cBehavior);

	//	Remove player behavior
	if(info.HasMember("- player behavior") && dynamic_cast<BehaviorPlayer *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse player behavior
	if(info.HasMember("player behavior")){

		//	Check format
		if(!info["player behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"player behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhp: behavior to edit
		data: data about the player behavior to edit
		*/
		BehaviorPlayer *bhp = dynamic_cast<BehaviorPlayer *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["player behavior"].GetObj();

		//	Check `bhp`
		if(bhp == nullptr){
			bhp = new BehaviorPlayer();
			obj.add(bhp);
		}
		
		//	Edit `cooldown`
		if(data.HasMember("cooldown")){

			//	Check format
			if(!(data.HasMember("cooldown") && data["cooldown"].IsFloat()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"cooldown\" (player behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `cooldown`
			bhp -> setCooldown(data["cooldown"].GetFloat());

		}
		
		//	Edit `fore`
		if(data.HasMember("forward")){

			//	Check format
			if(!(data.HasMember("forward") && data["forward"].IsFloat()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"forward\" (player behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `fore`
			bhp -> setFore(data["forward"].GetFloat());

		}
		
		//	Edit `back`
		if(data.HasMember("backward")){

			//	Check format
			if(!(data.HasMember("backward") && data["backward"].IsFloat()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"backward\" (player behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `back`
			bhp -> setBack(data["backward"].GetFloat());

		}
		
		//	Edit `turn`
		if(data.HasMember("turn")){

			//	Check format
			if(!(data.HasMember("turn") && data["turn"].IsFloat()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"turn\" (player behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `turn`
			bhp -> setTurn(data["turn"].GetFloat());

		}
		
#ifdef BEHAVIOR_PLAYER_UNIQUE_SHOOT_SOUND
		if(data.HasMember("sound")){

			//	Check format
			if(!(data.HasMember("sound") && data["sound"].IsString())) Trace::error("\"sound\" (player behavior) could not be parsed");

			//	Set `sound`
			bhp -> setShootSound(data["sound"].GetString());
		}
#endif

	}

	//	Remove bullet behavior
	if(info.HasMember("- bullet behavior") && dynamic_cast<BehaviorBullet *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse bullet behavior
	if(info.HasMember("bullet behavior")){

		//	Check format
		if(!info["bullet behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"bullet behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the bullet behavior to edit
		*/
		BehaviorBullet *bhb = dynamic_cast<BehaviorBullet *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["bullet behavior"].GetObj();

		//	Check `bhb`
		if(bhb == nullptr){
			bhb = new BehaviorBullet();
			obj.add(bhb);
		}

		//	Edit `timer`
		if(data.HasMember("time")){

			//	Check format
			if(!data["time"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"time\" (bullet behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `timer`
			bhb -> setTimer(data["time"].GetFloat());
		}
	}

	//	Remove health behavior
	if(info.HasMember("- health behavior") && dynamic_cast<BehaviorHealth *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse health behavior
	if(info.HasMember("health behavior")){

		//	Check format
		if(!info["health behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"health behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the health behavior to edit
		*/
		BehaviorHealth *bhh = dynamic_cast<BehaviorHealth *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["health behavior"].GetObj();

		//	Check `bhh`
		if(bhh == nullptr){
			bhh = new BehaviorHealth();
			obj.add(bhh);
		}

		//	Edit `regenTime`
		if(data.HasMember("time")){

			//	Check format
			if(!data["time"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"time\" (health behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `regenTime`
			bhh -> setTimer(data["time"].GetFloat());
		}

		//	Edit `shieldNumber`
		if(data.HasMember("count")){

			//	Check format
			if(!data["count"].IsInt())
#ifdef DEBUG_SYSTEM
				Trace::error("\"count\" (health behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `shieldNumber`
			bhh -> setShieldNum(data["count"].GetInt());
		}


		//	Edit `texture`
		//if(data.HasMember("texture")){

		//	//	Check format
		//	if(!data["texture"].IsString()) Trace::error("\"texture\" (sprite) could not be parsed");

		//	//	Set `texture`
		//	bhh -> setTexture(TextureManager::getTexture(data["texture"].GetString()));

		//}

	}



	//	Remove button behavior
	if(info.HasMember("- button behavior") && dynamic_cast<BehaviorButton *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse button behavior
	if(info.HasMember("button behavior"))
#ifdef DEBUG_SYSTEM
		Trace::error("Specify what kind of button");
#else
		assert("Deserialization error!");
#endif

	//	Remove agreement button behavior
	if(info.HasMember("- agree button behavior") && dynamic_cast<BehaviorAgreeButton *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse agreement button behavior
	if(info.HasMember("agree button behavior")){

		//	Check format
		if(!info["agree button behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"agree button behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorAgreeButton *bhb = dynamic_cast<BehaviorAgreeButton *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["agree button behavior"].GetObj();

		//	Check `bhb`
		if(bhb == nullptr){
			bhb = new BehaviorAgreeButton();
			obj.add(bhb);
		}

		//	Edit `list`
		if(data.HasMember("list")){

			//	Variable: temporary pointer for return values
			ActionList *list = bhb -> getAction();

			//	Check format
			if(!getActionList(data["list"], list))
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (agree button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

		}

		//	Edit `buffTime`
		if(data.HasMember("buffer")){

			//	Check format
			if(!data["buffer"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"buffer\" (agree button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `buffTime`
			bhb -> setBuffer(data["buffer"].GetFloat());

		}

		//	Check format of `name`
		if(!(data.HasMember("name") && data["name"].IsString()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"name\" (agree button behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `name`
		bhb -> setDecName(data["name"].GetString());

		//	Edit `confirmSound`
		if(data.HasMember("confirm")){

			//	Check format
			if(!data["confirm"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"confirm\" (team button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `confirmSound`
			bhb -> setConfirmSound(data["confirm"].GetString());

		}

		//	Edit `denySound`
		if(data.HasMember("deny")){

			//	Check format
			if(!data["deny"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"deny\" (team button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `denySound`
			bhb -> setDenySound(data["deny"].GetString());

		}

	}

	//	Remove team button behavior
	if(info.HasMember("- team button behavior") && dynamic_cast<BehaviorTeamButton *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse team button behavior
	if(info.HasMember("team button behavior")){

		//	Check format
		if(!info["team button behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"team button behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorTeamButton *bhb = dynamic_cast<BehaviorTeamButton *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["team button behavior"].GetObj();

		//	Check `bhb`
		if(bhb == nullptr){
			bhb = new BehaviorTeamButton();
			obj.add(bhb);
		}

		//	Edit `list`
		if(data.HasMember("list")){

			//	Variable: temporary pointer for return values
			ActionList *list = bhb -> getAction();

			//	Check format
			if(!getActionList(data["list"], list))
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (team button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

		}

		//	Check format of `name`
		if(!(data.HasMember("name") && data["name"].IsString()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"name\" (team button behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `name`
		bhb -> setDecName(data["name"].GetString());

		//	Edit `confirmSound`
		if(data.HasMember("confirm")){

			//	Check format
			if(!data["confirm"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"confirm\" (team button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `confirmSound`
			bhb -> setConfirmSound(data["confirm"].GetString());

		}

		//	Edit `denySound`
		if(data.HasMember("deny")){

			//	Check format
			if(!data["deny"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"deny\" (team button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `denySound`
			bhb -> setDenySound(data["deny"].GetString());

		}

	}

	//	Remove text behavior
	if (info.HasMember("- text behavior") && dynamic_cast<BehaviorText*>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse text behavior
	if (info.HasMember("text behavior")) {

		//	Check format
		if (!info["text behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"text behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bht: behavior to edit
		data: data about the text behavior to edit
		*/
		BehaviorText* bht = dynamic_cast<BehaviorText*>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["text behavior"].GetObj();

		if (bht == nullptr) {
			bht = new BehaviorText();
			obj.add(bht);
		}

		glm::vec3 vec1, vec2;
		if (data.HasMember("translation") && data.HasMember("scale"))
		{
			if (!getGLMVec3(data["translation"], vec1, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"translation\" (transform) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			if (!getGLMVec3(data["scale"], vec2, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"scale\" (transform) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			bht->setTrans(vec1, vec2);
		}

		if (data.HasMember("type"))
		{

			if (!data["type"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"type\" (text behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			std::string textType = data["type"].GetString();
			if (textType == "SfxVolume")
			{
				float& volume = SoundSystem::getInstance()->getSfxVol();
				bht->setText(volume);
			}
			if (textType == "MusicVolume")
			{
				float& volume = SoundSystem::getInstance()->getMusicVol();
				bht->setText(volume);
			}
		}

	}

	//	Remove shield behavior
	if(info.HasMember("- shield behavior")) if(dynamic_cast<BehaviorShield *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse shield behavior
	if(info.HasMember("shield behavior")){

		//	Variable: behavior to check for
		BehaviorShield *bhs = dynamic_cast<BehaviorShield *>(obj.get(ComponentTypeEnum::cBehavior));
		      
		//	Check `bhs`
		if(bhs == nullptr){
			bhs = new BehaviorShield();
			obj.add(bhs);
		}
	}

	if (info.HasMember("- powerup behavior")) if (dynamic_cast<BehaviorPowerUp*>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	if (info.HasMember("powerup behavior"))
	{

		BehaviorPowerUp* bhpu = dynamic_cast<BehaviorPowerUp*>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["powerup behavior"].GetObj();
		if (bhpu == nullptr)
		{
			bhpu = new BehaviorPowerUp();
			obj.add(bhpu);
		}

		if (data.HasMember("type"))
		{
			if (!static_cast<PowerUp::powerType>(data["type"].IsInt()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"type\" (powerup behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			bhpu->setPower(static_cast<PowerUp::powerType>(data["type"].GetInt()));
		}
		if (data.HasMember("respawn time"))
		{
			if (!static_cast<PowerUp::powerType>(data["respawn time"].IsFloat()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"respawn time\" (powerup behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			bhpu->respawnTime = data["respawn time"].GetFloat();
		}
		if (data.HasMember("ammo"))
		{
			if (!static_cast<PowerUp::powerType>(data["ammo"].IsInt()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"ammo\" (powerup behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			bhpu->setPower(static_cast<PowerUp::powerType>(data["ammo"].GetInt()));
		}

	}

	//	Remove map behavior
	if(info.HasMember("- map behavior") && dynamic_cast<BehaviorMap *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse map behavior
	if(info.HasMember("map behavior")){

		//	Variable: behavior to check for
		BehaviorMap *bhm = dynamic_cast<BehaviorMap *>(obj.get(ComponentTypeEnum::cBehavior));

		//	Check `bhm`
		if(bhm == nullptr){
			bhm = new BehaviorMap();
			obj.add(bhm);
		}
	}

	//	Remove wall behavior
	if(info.HasMember("- wall behavior") && dynamic_cast<BehaviorWall *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse wall behavior
	if(info.HasMember("wall behavior")){

		//	Check format
		if(!info["wall behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"wall behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorWall *bhw = dynamic_cast<BehaviorWall *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["wall behavior"].GetObj();

		//	Check `bhb`
		if(bhw == nullptr){
			bhw = new BehaviorWall();
			obj.add(bhw);
		}

		//	Edit `list`
		if(data.HasMember("list") && data["list"].IsArray()) for(rapidjson::Value &wallData : data["list"].GetArray()){

			//	Check format
			if(!wallData.IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (wall) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Variable: `walldata` as an array
			rapidjson::GenericArray<false, Value> wall = wallData.GetArray();

			//	Check format
			if(wall.Capacity() != 2)
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (wall) could not be parsed");
#else
				assert("Deserialization error!");
#endif
		
			/*	Variables:
			head: Start coordinates of the wall
			tail: End coordinates of the wall
			*/
			glm::vec3 head, tail;

			//	Get `head`
			if(!getGLMVec3(wall[0], head, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"head\" (wall) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Get `tail`
			if(!getGLMVec3(wall[1], tail, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"tail\" (wall) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Add `wall`
			bhw -> addWall(head, tail);
		}
	}

	//	Remove key behavior
	if(info.HasMember("- key behavior") && dynamic_cast<BehaviorPlayer *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse key behavior
	if(info.HasMember("key behavior")){

		//	Check format
		if(!info["key behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"key\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bub: behavior to edit
		data: data about the player behavior to edit
		*/
		BehaviorUniversalButton *bub = dynamic_cast<BehaviorUniversalButton *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["key behavior"].GetObj();

		//	Check `bhp`
		if(bub == nullptr){

			//	Create a new behavior
			bub = new BehaviorUniversalButton();
			obj.add(bub);

		}

		//	Variable: placeholder integer for return value of `getGLFWKey()`
		int key = -1;

		//	Edit `key`
		if(data.HasMember("key")){

			//	Check format
			if(!getGLFWKey(data["key"], key))
#ifdef DEBUG_SYSTEM
				Trace::error("\"key\" (key behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
			
			//	Set `key`
			bub -> setButton(key);

		}

		//	Check for "released"
		if(data.HasMember("released")){

			//	Check format
			if(!data["released"].IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"released\" (key behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
	
			//	Add each action
			for(Value &actionVal : data["released"].GetArray()){

				//	Variable: action to add to the action list
				ActionNode *action = getAction(actionVal);

				//	Check for `action`
				if(action == nullptr)
#ifdef DEBUG_SYSTEM
					Trace::error("Action could not be deserialized");
#else
					assert("Deserialization error!");
#endif

				//	Add `action` to the list
				else bub -> addAction(action, 2);

			}

		}

		//	Check for "pressed"
		if(data.HasMember("pressed")){

			//	Check format
			if(!data["pressed"].IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"pressed\" (key behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
	
			//	Add each action
			for(Value &actionVal : data["pressed"].GetArray()){

				//	Variable: action to add to the action list
				ActionNode *action = getAction(actionVal);

				//	Check for `action`
				if(action == nullptr)
#ifdef DEBUG_SYSTEM
					Trace::error("Action could not be deserialized");
#else
					assert("Deserialization error!");
#endif

				//	Add `action` to the list
				else bub -> addAction(action, 1);

			}

		}

		//	Check for "held"
		if(data.HasMember("held")){

			//	Check format
			if(!data["held"].IsArray())
#ifdef DEBUG_SYSTEM
				Trace::error("\"held\" (key behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif
	
			//	Add each action
			for(Value &actionVal : data["held"].GetArray()){

				//	Variable: action to add to the action list
				ActionNode *action = getAction(actionVal);

				//	Check for `action`
				if(action == nullptr)
#ifdef DEBUG_SYSTEM
					Trace::error("Action could not be deserialized");
#else
					assert("Deserialization error!");
#endif

				//	Add `action` to the list
				else bub -> addAction(action, 2);

			}

		}

	}

	//	Remove confirm icon behavior
	if(info.HasMember("- confirm icon behavior") && dynamic_cast<BehaviorConfirmIcon *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse confirm icon behavior
	if(info.HasMember("confirm icon behavior")){

		//	Check format
		if(!info["confirm icon behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"confirm icon behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorConfirmIcon *bhc = dynamic_cast<BehaviorConfirmIcon *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["confirm icon behavior"].GetObj();

		//	Check `bhc`
		if(bhc == nullptr){
			bhc = new BehaviorConfirmIcon();
			obj.add(bhc);
		}

		//	Edit `target`
		if(data.HasMember("target")){

			//	Check format
			if(!data["target"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"target\" (button behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `target`
			bhc -> setTarget(data["target"].GetString());

		}

	}

	//	Remove pop up behavior
	if(info.HasMember("- popup behavior") && dynamic_cast<BehaviorPopup *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse pop up behavior
	if(info.HasMember("popup behavior") && dynamic_cast<BehaviorPopup *>(obj.get(ComponentTypeEnum::cBehavior)) == nullptr){

		//	Check format
		if(!info["popup behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"popup behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhp: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorPopup *bhp = dynamic_cast<BehaviorPopup *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["popup behavior"].GetObj();

		//	Check `bhp`
		if(bhp == nullptr){
			bhp = new BehaviorPopup();
			obj.add(bhp);
		}

		//	Edit `openActions`
		if(data.HasMember("open")){

			//	Variable: Temporary pointer for return values
			ActionList *list = new ActionList();

			//	Check format
			if(!getActionList(data["open"], list))
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (pop up behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `openActions`
			bhp -> setOpenActions(list);

		}

		//	Edit `closeActions`
		if(data.HasMember("close")){

			//	Variable: Temporary pointer for return values
			ActionList *list = new ActionList();

			//	Check format
			if(!getActionList(data["close"], list))
#ifdef DEBUG_SYSTEM
				Trace::error("\"list\" (pop up behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `closeActions`
			bhp -> setCloseActions(list);

		}

		//	Edit `pawsable`
		bhp -> setPAWSable(!data.HasMember("unpausable"));

	}

	//	Remove keybind display behavior
	if(info.HasMember("- keybind display behavior") && dynamic_cast<BehaviorDisplayControlKey *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse keybind display behavior
	if(info.HasMember("keybind display behavior")){

		//	Check format
		if(!info["keybind display behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"keybind display behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorDisplayControlKey *bhd = dynamic_cast<BehaviorDisplayControlKey *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["keybind display behavior"].GetObj();

		//	Check `bhd`
		if(bhd == nullptr){
			bhd = new BehaviorDisplayControlKey();
			obj.add(bhd);
		}

		//	Variable: Return variable for function call
		ControlUnit::ControlType target = ControlUnit::ControlType::INVALID;

		//	Edit `target`
		if(!(data.HasMember("target") && getControlType(data["target"], target)))
#ifdef DEBUG_SYSTEM
			Trace::error("\"target\" (keybind display behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `target`
		bhd -> setTarget(target);

		//	Edit `fonts`
		if(data.HasMember("ASCII")){

			//	Check format
			if(!data["ASCII"].IsObject())
#ifdef DEBUG_SYSTEM
				Trace::error("\"ASCII\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Variable: Object containing information about the font
			rapidjson::GenericObject<false, Value> font = data["ASCII"].GetObject();

			//	Check format
			if(!(font.HasMember("font") && font["font"].IsString()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"ASCII\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			/*	Variables:
			texture: Texture to set
			size: Size of font
			*/
			Texture *texture = &TextureManager::getTexture(font["font"].GetString());
			float size = 1;

			//	Parse `size`
			if(font.HasMember("size")){
				
				//	Check format
				if(!font["size"].IsFloat())
#ifdef DEBUG_SYSTEM
					Trace::error("\"size\" (keybind display behavior: ASCII) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Edit `size`
				size = font["size"].GetFloat();

			}

			//	Set `fonts`
			bhd -> setFont(0, texture, size);

		}
		if(data.HasMember("extra")){

			//	Check format
			if(!data["extra"].IsObject())
#ifdef DEBUG_SYSTEM
				Trace::error("\"extra\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Variable: Object containing information about the font
			rapidjson::GenericObject<false, Value> font = data["extra"].GetObject();

			//	Check format
			if(!(font.HasMember("font") && font["font"].IsString()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"extra\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			/*	Variables:
			texture: Texture to set
			size: Size of font
			*/
			Texture *texture = &TextureManager::getTexture(font["font"].GetString());
			float size = 1;

			//	Parse `size`
			if(font.HasMember("size")){
				
				//	Check format
				if(!font["size"].IsFloat())
#ifdef DEBUG_SYSTEM
					Trace::error("\"size\" (keybind display behavior: extra) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Edit `size`
				size = font["size"].GetFloat();

			}

			//	Set `fonts`
			bhd -> setFont(1, texture, size);

		}
		if(data.HasMember("controller")){

			//	Check format
			if(!data["controller"].IsObject())
#ifdef DEBUG_SYSTEM
				Trace::error("\"controller\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Variable: Object containing information about the font
			rapidjson::GenericObject<false, Value> font = data["controller"].GetObject();

			//	Check format
			if(!(font.HasMember("font") && font["font"].IsString()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"controller\" (keybind display behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			/*	Variables:
			texture: Texture to set
			size: Size of font
			*/
			Texture *texture = &TextureManager::getTexture(font["font"].GetString());
			float size = 1;

			//	Parse `size`
			if(font.HasMember("size")){
				
				//	Check format
				if(!font["size"].IsFloat())
#ifdef DEBUG_SYSTEM
					Trace::error("\"size\" (keybind display behavior: controller) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Edit `size`
				size = font["size"].GetFloat();

			}

			//	Set `fonts`
			bhd -> setFont(2, texture, size);

		}

		//	Edit `layer`
		if(data.HasMember("layer")){

			//	Variable: Return variable for function call
			GraphicsUnit::Type layer;

			//	Parse `layer`
			if(!getGraphicsLayer(data["layer"], layer))
#ifdef DEBUG_SYSTEM
				Trace::error("\"layer\" (sprite) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `layer`
			bhd -> setLayer(layer);

		}

	}

	//	Remove menu behavior
	if(info.HasMember("- menu behavior") && dynamic_cast<BehaviorOptionTrack *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse menu behavior
	if(info.HasMember("menu behavior")){

		//	Check format
		if(!info["menu behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"menu behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bot: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorOptionTrack *bot = dynamic_cast<BehaviorOptionTrack *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["menu behavior"].GetObj();

		//	Check `bot`
		if(bot == nullptr){
			bot = new BehaviorOptionTrack();
			obj.add(bot);
		}

		//	Check for `options`
		if(!(data.HasMember("options") && data["options"].IsArray()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"options\" (menu) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Variable: Options to set
		std::vector<MenuOption *> ops;

		//	Parse each option
		for(Value &opData : data["options"].GetArray()){

			//	Check format
			if(!opData.IsObject())
#ifdef DEBUG_SYSTEM
				Trace::error("\"options\" (menu) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Variable: Option to add
			MenuOption *op = new MenuOption();

			//	Add to `ops`
			ops.push_back(op);

			//	Check for `actions`
			if(!(opData.HasMember("actions") && opData["actions"].IsArray()))
#ifdef DEBUG_SYSTEM
				Trace::error("\"actions\" (menu : options) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Parse each action
			for(Value &actData : opData["actions"].GetArray()){

				/*	Variables:
				type: Control type to set to
				state: Key state to set to
				act: Action to set
				*/
				ControlUnit::ControlType type;
				ControlManager::KeyState state;
				ActionList *act = new ActionList();

				//	Check format and parse values
				if(!(actData.HasMember("type") && getControlType(actData["type"], type) && actData.HasMember("state") && getKeyState(actData["state"], state) && actData.HasMember("list") && getActionList(actData["list"], act)))
#ifdef DEBUG_SYSTEM
					Trace::error("\"action\" (menu : option) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Set action
				op -> setAction(type, state, act);

			}

			/*	Variables:
			trans: Translation to set
			scale: Scale to set
			rot: Rotation to set
			*/
			glm::vec3 trans = {0, 0, 1}, scale = {1, 1, 1};
			float rot = 0;

			//	Parse `trans`
			if(opData.HasMember("translation")) if(!getGLMVec3(opData["translation"], trans, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"translation\" (menu : options) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Parse `scale`
			if(opData.HasMember("scale")) if(!getGLMVec3(opData["scale"], scale, 0))
#ifdef DEBUG_SYSTEM
				Trace::error("\"scale\" (menu : options) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Parse `rot`
			if(opData.HasMember("rotation")){
				
				//	Check format
				if(!opData["rotation"].IsFloat())
#ifdef DEBUG_SYSTEM
					Trace::error("\"rotation\" (menu : options) could not be parsed");
#else
					assert("Deserialization error!");
#endif

				//	Edit `rot`
				rot = opData["rotation"].GetFloat();

			}

			//	Set transformation
			op -> setTransform(trans, scale, rot);

		}

		//	Set `options`
		bot -> setOptions(ops);

	}

	//	Remove selector behavior
	if(info.HasMember("- selector behavior") && dynamic_cast<BehaviorConfirmIcon *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse selector behavior
	if(info.HasMember("selector behavior")){

		//	Check format
		if(!info["selector behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"selector behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bos: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorOptionSelector *bos = dynamic_cast<BehaviorOptionSelector *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["selector behavior"].GetObj();

		//	Check `bos`
		if(bos == nullptr){
			bos = new BehaviorOptionSelector();
			obj.add(bos);
		}

		//	Check format
		if(!(data.HasMember("priority") && data["priority"].IsInt()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"priority\" (selector behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `priority`
		bos -> setPriority(data["priority"].GetInt());

		//	Edit `optionInit`
		if(data.HasMember("menu")){

			//	Check format
			if(!data["menu"].IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("\"menu\" (selector behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `optionInit`
			bos -> setOption(data["menu"].GetString());

		}

	}

	//	Remove display mode signifier behavior
	if(info.HasMember("- fullscreen icon behavior") && dynamic_cast<BehaviorDisplayFullscreen *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse display mode signifier behavior
	if(info.HasMember("fullscreen icon behavior")){

		//	Check format
		if(!info["fullscreen icon behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"fullscreen icon behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorDisplayFullscreen *bdf = dynamic_cast<BehaviorDisplayFullscreen *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["fullscreen icon behavior"].GetObj();

		//	Check `bhc`
		if(bdf == nullptr){
			bdf = new BehaviorDisplayFullscreen();
			obj.add(bdf);
		}

		//	Edit `fullColor`
		if(data.HasMember("fullscreen")){

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = {0, 0, 0, 1};
			float temp;

			//	Check format
			if(!getColor(data["fullscreen"], col, temp))
#ifdef DEBUG_SYSTEM
				Trace::error("\"fullscreen\" (fullscreen icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `fullColor`
			bdf -> setFullscreenColor(col);

		}

		//	Edit `winColor`
		if(data.HasMember("windowed")){

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = {0, 0, 0, 1};
			float temp;

			//	Check format
			if(!getColor(data["windowed"], col, temp))
#ifdef DEBUG_SYSTEM
				Trace::error("\"windowed\" (fullscreen icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `winColor`
			bdf -> setWindowedColor(col);

		}

	}

	//	Remove display mode signifier behavior
	if (info.HasMember("- powerup icon behavior") && dynamic_cast<BehaviorDisplayPowerUp*>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse display mode signifier behavior
	if (info.HasMember("powerup icon behavior")) {

#ifdef NEW_PU_DISPLAY

		//	Variable: behavior to edit
		BehaviorDisplayPowerUp* bdp = dynamic_cast<BehaviorDisplayPowerUp*>(obj.get(ComponentTypeEnum::cBehavior));

		//	Check `bdp`
		if (bdp == nullptr) {
			bdp = new BehaviorDisplayPowerUp();
			obj.add(bdp);
		}

#else

		//	Check format
		if (!info["powerup icon behavior"].IsObject()) Trace::error("\"powerup icon behavior\" could not be parsed");

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorDisplayPowerUp* bdp = dynamic_cast<BehaviorDisplayPowerUp*>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["powerup icon behavior"].GetObj();

		//	Check `bhc`
		if (bdp == nullptr) {
			bdp = new BehaviorDisplayPowerUp();
			obj.add(bdp);
		}

		//	Edit `fullColor`
		if (data.HasMember("active color")) {

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = { 0, 0, 0, 1 };
			float temp;

			//	Check format
			if (!getColor(data["active color"], col, temp)) Trace::error("\"active color\" (fullscreen icon behavior) could not be parsed");

			//	Set `fullColor`
			bdp->setPowerUpColor(col);

		}

		//	Edit `winColor`
		if (data.HasMember("dead color")) {

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = { 0, 0, 0, 1 };
			float temp;

			//	Check format
			if (!getColor(data["dead color"], col, temp)) Trace::error("\"dead color\" (fullscreen icon behavior) could not be parsed");

			//	Set `winColor`
			bdp->setDeadColor(col);

		}

		//	Edit `key`
		if (data.HasMember("key")) {

			//	Check format
			if (!data["key"].IsInt()) Trace::error("\"key\" (health behavior) could not be parsed");

			//	Set `key`
			bdp->setKey(data["key"].GetInt());
		}

#endif

	}

	//	Remove monitor count signifier behavior
	if(info.HasMember("- monitor icon behavior") && dynamic_cast<BehaviorDisplayMultiMonitor *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse monitor count signifier behavior
	if(info.HasMember("monitor icon behavior")){

		//	Check format
		if(!info["monitor icon behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"monitor icon behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorDisplayMultiMonitor *bdm = dynamic_cast<BehaviorDisplayMultiMonitor *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["monitor icon behavior"].GetObj();

		//	Check `bhc`
		if(bdm == nullptr){
			bdm = new BehaviorDisplayMultiMonitor();
			obj.add(bdm);
		}

		//	Edit `fullColor`
		if(data.HasMember("multi")){

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = {0, 0, 0, 1};
			float temp;

			//	Check format
			if(!getColor(data["multi"], col, temp))
#ifdef DEBUG_SYSTEM
				Trace::error("\"multi\" (monitor icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `fullColor`
			bdm -> setMultiColor(col);

		}

		//	Edit `winColor`
		if(data.HasMember("single")){

			/*	Variables:
			col: Color variable to store output
			temp: Temporary variable to store output
			*/
			glm::vec4 col = {0, 0, 0, 1};
			float temp;

			//	Check format
			if(!getColor(data["single"], col, temp))
#ifdef DEBUG_SYSTEM
				Trace::error("\"single\" (monitor icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `winColor`
			bdm -> setSingleColor(col);

		}

	}

	//	Remove slider icon behavior
	if(info.HasMember("- slider icon behavior") && dynamic_cast<BehaviorDisplayFloatBar *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse slider icon behavior
	if(info.HasMember("slider icon behavior")){

		//	Check format
		if(!info["slider icon behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"slider icon behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bhb: behavior to edit
		data: data about the button behavior to edit
		*/
		BehaviorDisplayFloatBar *bds = dynamic_cast<BehaviorDisplayFloatBar *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["slider icon behavior"].GetObj();

		//	Check `bhc`
		if(bds == nullptr){
			bds = new BehaviorDisplayFloatBar();
			obj.add(bds);
		}

		//	Edit `center`
		if(data.HasMember("translation")){

			//	Variable: Center of the slider bar
			glm::vec3 cen;

			//	Check format
			if(!getGLMVec3(data["translation"], cen, 1))
#ifdef DEBUG_SYSTEM
				Trace::error("\"translation\" (slider icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `center`
			bds -> setTranslation(cen);

		}

		//	Edit `range`
		if(data.HasMember("range")){

			//	Check format
			if(!data["range"].IsFloat())
#ifdef DEBUG_SYSTEM
				Trace::error("\"range\" (slider icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `range`
			bds -> setRange(data["range"].GetFloat());

		}

		//	Edit `type`
		if(data.HasMember("type")){

			//	Variable: Type of float to display
			BehaviorDisplayFloatBar::FloatType type;

			//	Check format
			if(!getSliderType(data["type"], type))
#ifdef DEBUG_SYSTEM
				Trace::error("\"type\" (slider icon behavior) could not be parsed");
#else
				assert("Deserialization error!");
#endif

			//	Set `type`
			bds -> setValue(type);

		}

	}

	//	Remove selector behavior
	if(info.HasMember("- jammer behavior") && dynamic_cast<BehaviorControlsBlocker *>(obj.get(ComponentTypeEnum::cBehavior))) obj.remove(ComponentTypeEnum::cBehavior);

	//	Parse selector behavior
	if(info.HasMember("jammer behavior")){

		//	Check format
		if(!info["jammer behavior"].IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("\"jammer behavior\" could not be parsed");
#else
			assert("Deserialization error!");
#endif

		/*	Variables:
		bos: behavior to edit
		data: data about the jammer behavior to edit
		*/
		BehaviorControlsBlocker *bcb = dynamic_cast<BehaviorControlsBlocker *>(obj.get(ComponentTypeEnum::cBehavior));
		rapidjson::GenericObject<false, Value> data = info["jammer behavior"].GetObj();

		//	Check `bcb`
		if(bcb == nullptr){
			bcb = new BehaviorControlsBlocker();
			obj.add(bcb);
		}

		//	Check format
		if(!(data.HasMember("priority") && data["priority"].IsInt()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"priority\" (selector behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `priority`
		bcb -> setPriority(data["priority"].GetInt());

		//	Check format
		if(!(data.HasMember("time") && data["time"].IsFloat()))
#ifdef DEBUG_SYSTEM
			Trace::error("\"time\" (selector behavior) could not be parsed");
#else
			assert("Deserialization error!");
#endif

		//	Set `time`
		bcb -> setTime(data["time"].GetFloat());

	}

}

/*!
\fn     static void parseFromState(ObjectContainer &man, bool forced, const char *name, const char *fldr)
\param  man
          Object container to parse to
\param  forced
          If editable objects should be forcefully reset
\param  name
          Name of the object to parse
\param  fldr
          Name of the folder(s) to search
\return Nothing
\brief
        This function parses an object from a folder and adds it to an object container.
*/
static void parseFromState(ObjectContainer &man, bool forced, const char *name, const char *fldr){

	//	Trace for debug
#ifdef DEBUG_SYSTEM
	Trace::message("- %s", name);
#endif

	/*	Variables:
	obj: Object in `man` to edit
	objJson: Contents of the .JSON file
	*/
	GameObject *obj = man.findObject(name);
	const char *objJson = nullptr;

	//	Check if `obj` is there
	if(obj && !forced){
        
		//  Variable: Name of the .JSON file
		char objJsonName[256];

		//	Read in edit object .JSON file
		sprintf_s(objJsonName, 256, "Data/Json/Objects/%s/%s - e.json", fldr, name);
#ifdef DEBUG_SYSTEM
		Trace::message("Edit file");
#endif

		//	Read the contents of the .JSON file
		objJson = readWholeFile(objJsonName);

	}

	//	Check if the read was successful
	if(objJson && *objJson) obj -> setDestroyed(false);

	//	Create a new object if there is none
	else{

		//	Cleanup
		delete[] objJson;
        
		//  Variable: Name of the .JSON file
		char objJsonName[256];

		//	Read in new object .json file
		sprintf_s(objJsonName, 256, "Data/Json/Objects/%s/%s - n.json", fldr, name);
#ifdef DEBUG_SYSTEM
		Trace::message("New file");
#endif

		//	Read the contents of the .JSON file
		objJson = readWholeFile(objJsonName);

		//	Variable: If the base object was made with no new animation
		bool aniSkip = objJson == nullptr || *objJson == '\0';

		//  If there is no "new" file, then load the base file instead
		if(aniSkip){

			//	Cleanup
			delete[] objJson;

			//	Read the base .JSON file
			sprintf_s(objJsonName, 256, "Data/Json/Objects/%s/%s.json", fldr, name);
			objJson = readWholeFile(objJsonName);
#ifdef DEBUG_SYSTEM
			Trace::message("Base file");
#endif

		}

		//	Create new and add to `man`
		if(objJson && *objJson){

			//	Create new object
			obj = new GameObject();

			//	Set name
			if(!aniSkip) obj -> setName(std::string(name) + " - n");
			else obj -> setName(name);

			//	Add to `man`
			man.addObject(obj);

		}
		else obj = nullptr;

	}

	//  Check for `obj`
	if(obj){

		//	Variable: objJsonDoc: RapidJSON document of the .JSON file
		Document objJsonDoc;

		//	Parse `objJson` and cleanup
		objJsonDoc.Parse(objJson);
		delete[] objJson;

		//  Check for valid format
		if(!objJsonDoc.IsObject())
#ifdef DEBUG_SYSTEM
			Trace::error("Object \"%s\" for \"%s\" could not be parsed", name, fldr);
#else
			assert("Deserialization error!");
#endif

		//	Parse `obj`
		parseObject(objJsonDoc, *obj);

	}

}

/*!
\fn     void parseManager(ObjectManager &man, bool forced)
\param  man
          manager
\param  forced
          reset
\brief  See ObjectFactory.h
*/
void parseManager(ObjectContainer &man, bool forced){
	
#ifdef DEBUG_SYSTEM
	Trace::message("loading state %s", man.getName().c_str());
#endif

	//	Variable: Name of the .JSON file
	char jsonName[256];

	//	Read in new object .json file
	sprintf_s(jsonName, 256, "Data/Json/Objects/%s/- state.json", man.getName().c_str());

	/*	Variables:
	json: Contents of the .JSON file
	jsonDoc: RapidJSON document holding the information from 'json'
	*/
	const char *json = readWholeFile(jsonName);
	Document jsonDoc;

    //  Parse 'json' and check for proper format
    jsonDoc.Parse(json);
	delete[] json;
	if(!(jsonDoc.IsObject() && jsonDoc.HasMember("local") && jsonDoc["local"].IsArray()))
#ifdef DEBUG_SYSTEM
		Trace::error("\"- state.json\" for gamestate \"%s\" could not be parsed", man.getName().c_str());
#else
		assert("Deserialization error!");
#endif

	//	Delete every object already in the manager
	for(GameObject *obj : man.getObjectList()) obj -> setDestroyed();

	//	Trace for debug
#ifdef DEBUG_SYSTEM
	Trace::message("Local:");
#endif
    
    //  Read local game objects from list
    for(Value &objFile : jsonDoc["local"].GetArray()) if(objFile.IsString()) parseFromState(man, forced, objFile.GetString(), man.getName().c_str());
    
    //  Read global game objects from list
    if(jsonDoc.HasMember("global")) for(Value &objFile : jsonDoc["global"].GetArray()) if(objFile.IsString()) parseFromState(man, forced, objFile.GetString(), "-");

}

/*!
\fn     void parseObject(ObjectContainer &man, const std::string &name, bool g)
\param  man
          manager
\param  name
          objectName
\param  g
          global
\brief  See ObjectFactory.h
*/
void parseObject(ObjectContainer &man, const std::string &name, bool g){

	//	Variable: Name of the .JSON file
	char jsonName[256];

	//	Trace for debug
#ifdef DEBUG_SYSTEM
	Trace::message("Load %s", name.c_str());
#endif

	//	Read in new object .json file
	if(g) sprintf_s(jsonName, 256, "Data/Json/Objects/-/%s.json", name.c_str());
	else sprintf_s(jsonName, 256, "Data/Json/Objects/%s/%s.json", man.getName().c_str(), name.c_str());

	/*	Variables:
	json: Contents of the .JSON file
	jsonDoc: RapidJSON document holding the information from 'json'
	*/
	const char *json = readWholeFile(jsonName);
	Document jsonDoc;

    //  Parse 'json'
    jsonDoc.Parse(json);
	delete[] json;

	//  Check for valid format and ID
	if(!jsonDoc.IsObject())
#ifdef DEBUG_SYSTEM
		Trace::error("Object \"%s\" for \"%s\" could not be parsed", name.c_str(), man.getName().c_str());
#else
		assert("Deserialization error!");
#endif

	//	Variable: New object to parse and add
	GameObject *obj = new GameObject();

	//	Parse `obj` and add to `man`
	obj -> setName(name);
	parseObject(jsonDoc, *obj);
	man.addObject(obj);

}

/*!
\fn     GameObject *parseObject(const std::string &name)
\param  name
          objectName
\brief  See ObjectFactory.h
*/
GameObject *parseObject(const std::string &name){

	//	Variable: Name of the .JSON file
	char jsonName[256];

	//	Trace for debug
#ifdef DEBUG_SYSTEM
	Trace::message("Load %s", name.c_str());
#endif

	//	Read in new object .json file
	sprintf_s(jsonName, 256, "Data/Json/Objects/-/%s.json", name.c_str());

	/*	Variables:
	json: Contents of the .JSON file
	jsonDoc: RapidJSON document holding the information from 'json'
	*/
	const char *json = readWholeFile(jsonName);
	Document jsonDoc;

    //  Parse 'json'
    jsonDoc.Parse(json);
	delete[] json;

	//  Check for valid format and ID
	if(!jsonDoc.IsObject())
#ifdef DEBUG_SYSTEM
		Trace::error("Object \"%s\" could not be parsed", name.c_str());
#else
		assert("Deserialization error");
#endif

	//	Variable: New object to parse and add
	GameObject *obj = new GameObject();

	//	Parse `obj` and add to `man`
	obj -> setName(name);
	parseObject(jsonDoc, *obj);

	//	Return
	return obj;

}




//	VVV Luke's Code Here VVV

/*!
\fn     std::map<std::string,std::string> parseSounds(const char *json)
\param  json
          json
\brief
        See ObjectFactory.h
*/
std::map<std::string,std::queue<std::string>> parseSounds(const char *json) {
	//	Variable: RapidJSON document holding the information from 'json'
	Document jsonDoc;

    //  Parse 'json' and check for array format
    jsonDoc.Parse(json);

    //	Variable: return value parsed from `json`
    // First will be the input for when use sound, Second is the sound file name
    std::map<std::string, std::queue<std::string>> soundFiles;

	//	Check 'jsonDoc'
	if(!jsonDoc.IsObject()){
#ifdef DEBUG_SYSTEM
		Trace::error("Sound files could not be parsed");
#endif
		return soundFiles;
	}

	//	Parse document
	for(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &soundGroup : jsonDoc.GetObject()){
		std::string soundName = soundGroup.name.GetString();
		if(!soundGroup.value.IsArray())
#ifdef DEBUG_SYSTEM
			Trace::error("Sound files for %s group could not be parsed", soundName);
#else
			assert("Deserialization error");
#endif
		for(Value &sound : soundGroup.value.GetArray()){
			if(!sound.IsString())
#ifdef DEBUG_SYSTEM
				Trace::error("Sound file for %s group could not be parsed", soundGroup.name.GetString());
#else
				assert("Deserialization error");
#endif
			soundFiles[soundName].push(std::string(sound.GetString()) + ".wav");
		}
	}
#if 0
    // bullet shoot
    if (jsonDoc.HasMember("shooting") && jsonDoc["shooting"].IsString()) {
        soundFiles.insert({"shooting", jsonDoc["shooting"].GetString()});
    }
    // background music
    if (jsonDoc.HasMember("music") && jsonDoc["music"].IsString()) {
        soundFiles.insert({ "music", jsonDoc["music"].GetString()});
    }
    // bullet bounce
    if (jsonDoc.HasMember("bullet bounce") && jsonDoc["bullet bounce"].IsString()) {
        soundFiles.insert({ "bullet bounce", jsonDoc["bullet bounce"].GetString() });
    }
    // bullet hit shield
    if (jsonDoc.HasMember("shield") && jsonDoc["shield"].IsString()) {
        soundFiles.insert({ "shield", jsonDoc["shield"].GetString() });
    }
    // tank destroyed
    if (jsonDoc.HasMember("destroy") && jsonDoc["destroy"].IsString()) {
        soundFiles.insert({ "destroy", jsonDoc["destroy"].GetString() });
    }
    // end of round
    if (jsonDoc.HasMember("round end") && jsonDoc["round end"].IsString()) {
        soundFiles.insert({ "round end", jsonDoc["round end"].GetString() });
    }
#endif
	//	Return
	return soundFiles;
}