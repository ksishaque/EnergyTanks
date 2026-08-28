/*!
\file   ShaderManager.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-1-2022
\brief
        Functions for managing shaders
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glad/glad.h>

#include "rapidjson/document.h"
#include "readFile.h"

#include "ShaderManager.h"
#include "Trace.h"

using rapidjson::Document;

ShaderManager* ShaderManager::instance = nullptr;

/*!
\fn     static ShaderManager* getInstance()
\return Singleton instance of the shader manager system
\brief
        This function accesses the singleton instance of the shader manager system, creating it if needed.
*/
ShaderManager* ShaderManager::getInstance() 
{
    if (instance == nullptr) {
        instance = new ShaderManager();
    }
    return instance;
}


/*!
\fn     static void closeInstance()
\brief
        This closes the singleton instance of the shader manager system.
*/
void ShaderManager::closeInstance()
{
    delete instance;
    instance = nullptr;
}


/*!
\fn     ShaderManager()
\par    This function has no parameters.
\return The new shader manager
\brief
        This function constructs a shader manager.
*/
ShaderManager::ShaderManager() : ISystem(sShaMan) 
{
}

/*!
\fn     ~ShaderManager()
\par    This function has no parameters.
\return Nothing
\brief
        This function destructs a shader manager.
*/
ShaderManager::~ShaderManager() 
{
}

/*!
\fn     void initialize()
\par    This function has no parameters.
\return Nothing
\brief
        This function initializes the shader manager.
*/
void ShaderManager::initialize() 
{
    if (isActive()) 
    {
        return;
    }
    ISystem::initialize();

    // Read the game JSON file.
    const char* jsonData = readWholeFile("Data/Json/graphics.json");

    Document jsonDoc;
    jsonDoc.Parse(jsonData);

    if (!jsonDoc.IsObject() || !jsonDoc.HasMember("shaders")) 
    {
        return;
    }

    if (jsonDoc.HasMember("shaders") && jsonDoc["shaders"].IsArray()) 
    {
        for (auto& element : jsonDoc["shaders"].GetArray()) {
            if (element.IsObject()) 
            {
                rapidjson::GenericObject<false, rapidjson::Value> shader = element.GetObject();
                if (shader.HasMember("name") && shader.HasMember("vertex") && shader.HasMember("fragment")) 
                {
                    const char* vertexFilePath = shader["vertex"].GetString();
                    const char* fragmentFilePath = shader["fragment"].GetString();
                    const char* name = shader["name"].GetString();
#ifdef DEBUG_SYSTEM
                    Trace::message(vertexFilePath);
                    Trace::message(fragmentFilePath);
#endif

                    loadShader(vertexFilePath, fragmentFilePath, (ShaderType) *name);
                }
            }
        }
    }

	delete [] jsonData;

}

/*!
\fn     void shutdown()
\par    This function has no parameters.
\return Nothing
\brief
        This function shuts down and cleans up the shader manager.
*/
void ShaderManager::shutdown() 
{
    if (isActive()) {
        ISystem::shutdown();
        for (auto iter : shadersMap)
        {
            GLuint shaderID = iter.second->getID();
            // Unload the shaders
            glDeleteProgram(shaderID);
            delete iter.second;
        }

        shadersMap.clear();
    }
}

/*!
\fn     void instanceLoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name);
\par    vertexShaderFile
            The vertex shader filename.
\par    fragmentShaderFile
            The fragment shader filename.
\par    name
            The name of the new shader program.
\brief
        This function loads a shader.
*/
void ShaderManager::instanceLoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name) 
{
    Shader* shader = new Shader();

    // Create the shader that displays textures
    if (shader) {
        shader->compile(vertexShaderFile, fragmentShaderFile);
        shadersMap[name] = shader;
    }
}

/*!
\fn     static void loadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name);
\par    vertexShaderFile
            The vertex shader filename.
\par    fragmentShaderFile
            The fragment shader filename.
\par    name
            The name of the new shader program.
\brief
        This function loads a shader.
*/
void ShaderManager::loadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name) 
{
    if (instance) 
    {
        instance->instanceLoadShader(vertexShaderFile, fragmentShaderFile, name);
    }
    else 
    {
#ifdef DEBUG_SYSTEM
        Trace::message("ShaderManager instance is NULL\n");
#endif
    }
}

/*!
\fn     Shader& instanceGetShader(ShaderType name)
\par    name
            The name
\brief
        This function retrieves a shader.
*/
Shader* ShaderManager::instanceGetShader(ShaderType name) 
{
    return (shadersMap[name]);
}

/*!
\fn     static Shader& getShader(ShaderType name)
\par    name
            The name
\brief
        This function retrieves a shader.
*/
Shader* ShaderManager::getShader(ShaderType name) 
{
    if (instance)
    {
        return instance->instanceGetShader(name);
    }
    return nullptr;
}
