/*!
\file   Renderer.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-21-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

/*
#include "Engine.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "ReadFile.h"
#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"

// Using glfw for window handling
#include "Window.h"

// Using glm for math
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
*/

#include <list>

#include "ISystem.h"

struct GLFWwindow;
class GraphicsUnit;

class Renderer : public ISystem
{
private:
    /*!
    \var    windowHandle
              The GLFW window.
    */
    //GLFWwindow* windowHandle = nullptr;


public:

        /*!
        \fn  Renderer* getInstance()
        \param none
        \brief
                Gets the instance of renderer.
        */
        static Renderer* getInstance();

        /*!
        \fn  static void closeInstance()
        \param none
        \brief
                Closes the instance of renderer.
        */
        static void closeInstance();

        /*!
        \fn  void addToList(Sprite* sprite)
        \param sprite
                    The sprite to add to renderer queue.
        \brief
                Adds a sprite to the queue.
        */
        void addToList(GraphicsUnit* graphicsUnit);


        /*!
        \fn  void removeFromList(Sprite* sprite)
        \param sprite
                    The sprite to remove from renderer queue.
        \brief
                Removes a sprite to the queue.
        */
        void removeFromList(GraphicsUnit* graphicsUnit);

        /*!
        \fn void ResizeViewport(GLFWwindow* window, int width, int height)
        \param window
               The GLFW window
        \param width
               The width of the window.
        \param height
               The height of the window.
        \brief
                Resizes the images inside the window in accordance with the window size.
        */
        //void ResizeViewport(GLFWwindow* window, int width, int height);
		
        /*!
        \fn void Draw(Sprite *sprite)
        \param sprite
               The sprite of a game object.
        \brief
               Draws the specified sprite at the specified transformation.
        */
        void Draw(GraphicsUnit* graphicsUnit);

        /*!
        \fn void initialize()
        \brief
                The Renderer initialize.
        */
        void initialize() override;

        /*!
        \fn void update(float dt)
        \param
            The delta time.
        \brief
                The Renderer update.
        */
        void update(float& dt) override;

        /*!
        \fn void shutdown()
        \brief
                The Renderer shutdown.
        */
        void shutdown() override;

        private:

            /*!
            \fn  Renderer()
            \param none
            \brief
                    Constructor
            */
            Renderer();

            /*!
            \fn  ~Renderer()
            \param none
            \brief
                    Destructor
            */
            ~Renderer();


            std::list<GraphicsUnit*> renderQueue;
            static Renderer* instance;
};
