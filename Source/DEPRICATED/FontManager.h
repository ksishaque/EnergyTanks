/*!
\file   FontManager.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-6-2022
\brief
        Functions for managing fonts.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>

#include "ISystem.h"


class FontManager : public ISystem {
    private:
        // Holds all state information relevant to a character as loaded using FreeType.
        struct Character {
            unsigned int TextureID; // ID handle of the glyph texture
            glm::ivec2   Size;      // size of glyph
            glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
            unsigned int Advance;   // horizontal offset to advance to next glyph
        };

    public:
        /*!
        \fn     void initialize()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function initializes the font manager.
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
        void update(float dt) override;


        /*!
        \fn     void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function shuts down and cleans up the font manager.
        */
        void shutdown() override;

        /*!
        \fn     static FontManager* getInstance()
        \return Singleton instance of the font manager system
        \brief
                This function accesses the singleton instance of the font manager system, creating it if needed.
        */
        static FontManager* getInstance();


    private:
        /*!
        \fn     FontManager()
        \par    This function has no parameters.
        \return The new texture manager
        \brief
                This function constructs a font manager.
        */
        FontManager();

        /*!
        \fn     ~FontManager()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destructs a font manager.
        */
        ~FontManager();


        // instance of font manager
        static FontManager* instance;

        std::map<char, Character> charactersMap;
};

