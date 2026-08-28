/*!
\file   TextureManager.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        The texture manager.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

// Using stb image for image file loading

#pragma warning(push)
#pragma warning(disable:6262)
#pragma warning(disable:26451)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)
#include <glfw/glfw3.h>

#include <sstream>

#include "Trace.h"

#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

/*!
    \fn     TextureManager()
    \par    This function has no parameters.
    \return The new texture manager
    \brief
            This function constructs a texture manager.
*/
TextureManager::TextureManager() : ISystem(sTexMan)
{
}

/*!
\fn     ~TextureManager()
\par    This function has no parameters.
\return Nothing
\brief
        This function destructs a texture manager.
*/
TextureManager::~TextureManager() 
{  
}

/*!
\fn     void initialize()
\par    This function has no parameters.
\return Nothing
\brief
        This function initializes the texture manager.
*/
void TextureManager::initialize() 
{
	 if (isActive())
	 {
		  return;
	 }
	 ISystem::initialize();
	 /*
     bool alpha = true;
     loadTexture("./Data/Art/dum.png", alpha, "tank");
     loadTexture("./Data/Art/bullet.png", alpha, "bullet");
	 //*/
}

/*!
\fn     void update(float dt)
\param  dt
          time since previous frame
\return Nothing
\brief
        This function does nothing.
*/
void TextureManager::update(float& dt)
{
}

/*!
\fn     void loadTexture(const char* filename, bool alpha, std::string name)
\par    filename
            The filename
\par    alpha
            The alpha
\par    name
            The name
\brief
        This function loads a texture into the map.
*/
void TextureManager::instanceLoadTexture(const char* filename, bool alpha, std::string name) 
{
    Texture* texturePtr = loadTextureFromAFile(filename, alpha);
    if (texturePtr)
    {
        texturesMap[name] = texturePtr;
    }
}

/*!
\fn     Texture& TextureManager::instanceGetTexture(std::string name) 
\par    name
            The name
\brief
        This function retrieves a texture.
*/
Texture& TextureManager::instanceGetTexture(std::string name) 
{
	if(texturesMap[name] == nullptr){
		std::stringstream fileName;
		fileName << "./Data/Art/" << name << ".png";

		instanceLoadTexture(fileName.str().c_str(), true, name);
	}
    return *(texturesMap[name]);
}

/*!
\fn     int getCount()
\return The count
\brief
        This function returns the texture count.
*/
size_t TextureManager::instanceGetCount()
{
    return texturesMap.size();
}

/*!
\fn     void shutdown()
\par    This function has no parameters.
\return Nothing
\brief
        This function shuts down and cleans up the texture manager.
*/
void TextureManager::shutdown() 
{
	if (!isActive())
	{
		return;
	}
	ISystem::shutdown();
	instanceClear();
}

/*!
\fn     TextureManager* getInstance()
\par    This function has no parameters.
\return Singleton instance of the texture manager system
\brief
        This function accesses the singleton instance 
        of the texture manager system, creating it if needed.
*/
TextureManager* TextureManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}

/*!
\fn     TextureManager* closeInstance()
\par    This function has no parameters.
\brief
        This function closes and deletes the singleton instance 
        of the texture manager system
*/
void TextureManager::closeInstance()
{
    delete instance;
    instance = nullptr;
}

/*!
\fn     Texture* loadTextureFromAFile(const char* filename, bool alpha) 
\par    filename
            The filename
\par    alpha
            The alpha
\brief
        This function loads a texture.
*/
Texture* TextureManager::loadTextureFromAFile(const char* filename, bool alpha) 
{
    Texture* texture = new Texture();
    int width;
    int height;
    int numPerPixel;

    if (alpha == true) 
    {
        texture->setImageFormat(GL_RGBA);
        texture->setInternalFormat(GL_RGBA);
    }

    // Load the image data with stbi_load (RGBA format).
    unsigned char* image = stbi_load(filename, &width, &height, &numPerPixel, 4);
    if (image == NULL) 
    {
        return nullptr;
    }

    texture->generate(width, height, image);

    stbi_image_free(image);

    return texture;
}

/*!
\fn     void instanceLoadTexture(const char* filename, bool alpha, std::string name)
\par    filename
            The filename
\par    alpha
            The alpha
\par    name
            The name
\brief
        This function loads a texture. (instance)
*/
void TextureManager::loadTexture(const char* filename, bool alpha, std::string name)
{
    if (instance == nullptr)
    {
#ifdef DEBUG_SYSTEM
        Trace::message("TextureManager instance is NULL");
#endif
        return;
    }
    instance->instanceLoadTexture(filename, alpha, name);
}

/*!
\fn     static Texture getTexture(std::string name)
\par    name
            The name
\brief
        This function retrieves a texture.
*/
Texture& TextureManager::getTexture(std::string name)
{
    if (instance == nullptr)
    {
#ifdef DEBUG_SYSTEM
        Trace::message("TextureManager instance is NULL\n");
#endif
    }
    return instance->instanceGetTexture(name);
}

/*!
\fn     size_t getCount()
\return The count
\brief
        This function returns the texture count.
*/
size_t TextureManager::getCount()
{
    if (instance == nullptr)
    {
#ifdef DEBUG_SYSTEM
        Trace::message("TextureManager instance is NULL");
#endif
        return -1;
    }
    return instance->instanceGetCount();
}

/*!
\fn     static void clear()
\par    This function has no parameters.
\brief
        This function clears all textures.
*/
void TextureManager::clear()
{
    if (instance == nullptr)
    {
#ifdef DEBUG_SYSTEM
        Trace::message("TextureManager instance is NULL\n");
#endif
    }
    instance->instanceClear();
}

/*!
\fn     static void clear()
\par    This function has no parameters.
\brief
        This function clears all textures.
*/
void TextureManager::instanceClear()
{
    for (std::pair<std::string, Texture*> iter : texturesMap) 
    {
		if (iter.second)
		{
			unsigned int textureID = iter.second->getID();
			glDeleteTextures(1, &textureID);
		}
        delete iter.second;
    }

    texturesMap.clear();
}