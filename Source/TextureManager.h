/*!
\file   TextureManager.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-30-2022
\brief
        The texture manager.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <string>
#include <map>
#include "ISystem.h"
#include "Texture.h"

class TextureManager : public ISystem
{
    public:
        /*!
        \fn     void initialize()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function initializes the texture manager.
        */
        void initialize() override;

        /*!
        \fn     void update(float dt)
        \param  dt
                  time since previous frame
        \return Nothing
        \brief
                This function does nothing.
        */
        void update(float& dt) override;

        /*!
        \fn     static void loadTexture(const char* filename, bool alpha, std::string name)
        \par    filename
                    The filename
        \par    alpha
                    The alpha
        \par    name
                    The name
        \brief
                This function loads a texture.
        */
        static void loadTexture(const char* filename, bool alpha, std::string name);


        /*!
        \fn     static Texture getTexture(std::string name)
        \par    name
                    The name
        \brief
                This function retrieves a texture.
        */
        static Texture& getTexture(std::string name);


        /*!
        \fn     static void clear()
        \par    This function has no parameters.
        \brief
                This function clears all textures.
        */
        static void clear();

        /*!
        \fn     static size_t getCount()
        \return The count
        \brief
                This function returns the texture count.
        */
        static size_t getCount();
        
        /*!
        \fn     void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function shuts down and cleans up the texture manager.
        */
        void shutdown() override;
        /**
         * This function accesses the singleton instance of the texture manager system, creating it if needed.
         *
         * \return Singleton instance of the texture manager system
        */
        static TextureManager* getInstance();
        /**
         * This function closes and deletes the singleton instance of the texture manager system
         *
        */
        static void closeInstance();
    private:
        
        /*!
        \fn     void instanceLoadTexture(const char* filename, bool alpha)
        \par    filename
                    The filename
        \par    alpha
                    The alpha
        \brief
                This function loads a texture.
        */
        Texture* loadTextureFromAFile(const char* filename, bool alpha);
        

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
        void instanceLoadTexture(const char* filename, bool alpha, std::string name);


        /*!
        \fn     Texture instanceGetTexture(std::string name)
        \par    name
                    The name
        \brief
                This function retrieves a texture.
        */
        Texture& instanceGetTexture(std::string name);
        /*!
        \fn     int instanceGetCount()
        \return The count
        \brief
                This function returns the texture count.
        */
        size_t instanceGetCount();
        /*!
        \fn     void instanceClear()
        \brief
                This function clears all textures in the manager.
        */
        void instanceClear();
    private:
        /*!
        \fn     TextureManager()
        \par    This function has no parameters.
        \return The new texture manager
        \brief
                This function constructs a texture manager.
        */
        TextureManager();

        /*!
        \fn     ~TextureManager()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destructs a texture manager.
        */
        ~TextureManager();
        static TextureManager* instance;
        //list of textures
        std::map<std::string, Texture*> texturesMap;
};
