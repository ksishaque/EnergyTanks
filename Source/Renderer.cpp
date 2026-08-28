/*!
\file   Renderer.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
        Luke Tseng   (luke.tseng\@digipen.edu)
\date   9-21-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "glad/glad.h"
#include <glfw/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager.h"
#include "Trace.h"
#include "General.h"
#include "ParticleGenerator.h"
#include "GraphicsUnit.h"
#include "Window.h"
#include "Renderer.h"

Renderer* Renderer::instance = nullptr;


/*!
\fn  Renderer* getInstance()
\param none
\brief
        See Renderer.h
*/
Renderer* Renderer::getInstance() {
    if (instance == nullptr) {
        instance = new Renderer();
    }
    return instance;
}

/*!
\fn  static void closeInstance()
\param none
\brief
        See Renderer.h
*/
void Renderer::closeInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

/*!
\fn  Renderer()
\param none
\brief
        See Renderer.h
*/
Renderer::Renderer() : ISystem(sRender) {
}

/*!
\fn  ~Renderer()
\param none
\brief
        See Renderer.h
*/
Renderer::~Renderer() {
}

/*!
\fn  void addToList(Sprite* sprite)
\param sprite
            The sprite to add to renderer queue.
\brief
        See Renderer.h
*/
void Renderer::addToList(GraphicsUnit* graphicsUnit) {
    if (instance == nullptr) {
#ifdef DEBUG_SYSTEM
        Trace::message("Renderer instance is NULL");
#endif
        return;
    }
    renderQueue.push_back(graphicsUnit);
}

/*!
\fn  void removeFromList(Sprite* sprite)
\param sprite
            The sprite to remove from renderer queue.
\brief
        See Renderer.h
*/
void Renderer::removeFromList(GraphicsUnit* graphicsUnit) {
    if (instance == nullptr) {
#ifdef DEBUG_SYSTEM
        Trace::message("Renderer instance is NULL");
#endif
        return;
    }
    renderQueue.remove(graphicsUnit);
}

/*!
\fn  void initialize()
\param none
\brief
        See Renderer.h
*/
void Renderer::initialize() {
    // Create variables for the size of the window
    //const int width = 1920, height = 1080;

    // *** Set up initial graphics settings and objects *******************************************

    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGLError("Renderer");

    // Disable culling (triangles seen from behind will be drawn)
    glDisable(GL_CULL_FACE);
    checkGLError("Renderer");

    // Enable blending for normal transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/*!
\fn  void update(float dt)
\param dt
        The dt.
\brief
        See Renderer.h
*/
void Renderer::update(float& dt) {
    
    // Clear the background
    glClear(GL_COLOR_BUFFER_BIT);
    checkGLError("Renderer");

    // Draw each sprite in the render queue.
    renderQueue.sort(pointerCompare<GraphicsUnit>);
    std::list<GraphicsUnit*>::iterator it;
    for (it = renderQueue.begin(); it != renderQueue.end(); ++it) {
        GraphicsUnit* gu = *it;
        Draw(gu);
    }
	renderQueue.clear();
    
    // Draw particles.
    ParticleGenerator::getInstance()->draw(dt);
}

/*! 
\fn  void Draw(Sprite* spr)
\param spr
        The sprite.
\brief
        See Renderer.h
*/
void Renderer::Draw(GraphicsUnit* gu) {
    if (gu == nullptr) {
        return;
    }

    gu->draw(Window::getInstance() -> getScale());
}


/*!
\fn  void shutdown()
\param none
\brief
        See Renderer.h
*/
void Renderer::shutdown() {
    if (isActive()) {
        ISystem::shutdown();
        renderQueue.clear();
    }
}
