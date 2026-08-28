/*!
\file   ObjectFactory.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-15-2022
\brief
		Functions for reading a .JSON file and using RapidJSON to parse it into a game object.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <map>
#include <queue>
#include <string>

class GameObject;
class ObjectContainer;

/*!
\fn     void parseManager(ObjectContainer &manager, const std::string &name, bool global)
\param  manager
          object manager to parse to
\param  objectName
          Name of the object to parse
\param  global
          If the object should be loaded from the global folder
\return Nothing
\brief
        This function reads a .json file and parses a game object and adds it to the manager.
*/
void parseObject(ObjectContainer &manager, const std::string &objectName, bool global);

/*!
\fn     GameObject *parseManager(const std::string &name)
\param  objectName
          Name of the object to parse
\return Object parsed
\brief
        This function reads a .json file from the global folder and parses a game object.
*/
GameObject *parseObject(const std::string &objectName);

/*!
\fn     void parseManager(ObjectContainer &manager, bool reset)
\param  manager
          object manager to parse to
\param  reset
          If set objects should be forcefully reset
\return Nothing
\brief
        This function reads a .json file and parses a game object manager with the indicated game objects.
*/
void parseManager(ObjectContainer &manager, bool reset = false);

/*!
\fn     std::unordered_map<std::string, std::string> parseSounds(const char* json)
\param  json
          .JSON file, as a c-style string of characters
\return Map of the sound effect and the sound file name
\brief
        This function reads a .json file and creates a map of file names of the sound effect
*/
std::map<std::string, std::queue<std::string>> parseSounds(const char* json);