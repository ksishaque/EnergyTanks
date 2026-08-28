/*!
\file   ShaderManager.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-1-2022
\brief
        Functions for managing shaders
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <map>
#include "ISystem.h"
#include "Shader.h"

class ShaderManager : public ISystem {
    public:

		/*!
		\enum   ShaderType
		          Type of shader, depending on what needs to be rendered
		\var    texture
		          Shader type for textured meshes
        \var    color
                  Shader type for solid colored meshes
		*/
		enum ShaderType{texture = 't', color = 'c'};

        /*!
        \fn     void initialize()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function initializes the shader manager.
        */
        void initialize() override;

        /*!
        \fn     void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function shuts down and cleans up the shader manager.
        */
        void shutdown() override;

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
        static void loadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name);

        /*!
        \fn     static Shader& getShader(ShaderType name)
        \par    name
                    The name
        \brief
                This function retrieves a texture.
        */
        static Shader* getShader(ShaderType name);

        /*!
        \fn     static ShaderManager* getInstance()
        \return Singleton instance of the shader manager system
        \brief
                This function accesses the singleton instance of the shader manager system, creating it if needed.
        */
        static ShaderManager* getInstance();


        /*!
        \fn     static void closeInstance()
        \brief
                This closes the singleton instance of the shader manager system.
        */
        static void closeInstance();


    private:
        /*!
        \fn     ShaderManager()
        \par    This function has no parameters.
        \return The new texture manager
        \brief
                This function constructs a shader manager.
        */
        ShaderManager();

        /*!
        \fn     ~ShaderManager()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destructs a shader manager.
        */
        ~ShaderManager();

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
        void instanceLoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, ShaderType name);

        /*!
        \fn     Shader& instanceGetShader(ShaderType name)
        \par    name
                    The name
        \brief
                This function retrieves a texture.
        */
        Shader* instanceGetShader(ShaderType name);

        // instance of shader manager
        static ShaderManager* instance;

        //list of shaders
        std::map<ShaderType, Shader*> shadersMap;
};

