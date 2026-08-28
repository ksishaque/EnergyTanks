/*!
\file   ParticleGenerator.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-19-2022
\brief
        Particle generator is responsible for generating particles
        that have a short lifespan.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <map>
#include <vector>
#include "glm/glm.hpp"

#include "Particle.h"
#include "GameObject.h"
#include "Sprite.h"
#include "ISystem.h"


class ParticleGenerator : public ISystem {
    public:

        /*!
        \fn  ParticleGenerator* getInstance()
        \param none
        \brief
                Gets the instance of ParticleGenerator.
        */
        static ParticleGenerator* getInstance();

        /*!
        \fn  static void closeInstance()
        \param none
        \brief
                Closes the instance of ParticleGenerator.
        */
        static void closeInstance();

        /*!
        \fn void initialize()
        \brief
                The ParticleGenerator initialize.
        */
        void initialize() override;

        /*!
        \fn void update(float dt)
        \param
            The delta time.
        \brief
                The ParticleGenerator update.
        */
        void update(float& dt) override;

        /*!
        \fn void shutdown()
        \brief
                The ParticleGenerator shutdown.
        */
        void shutdown() override;

        /*!
        \fn void spawnParticles(GameObject* emitter, Particle::Type pType)
        \brief
                Spawns particles.
        */
        void spawnParticles(GameObject* emitter, Particle::Type pType);

        /*!
        \fn void draw(float dt)
        \brief
                Draws the particles.
        */
        void draw(float dt);

    private:
        /*!
        \fn     ParticleGenerator()
        \par    This function has no parameters.
        \return The new particle generator
        \brief
                This function constructs the particle generator.
        */
        ParticleGenerator();

        /*!
        \fn     ~ParticleGenerator()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destructs the particle generator.
        */
        ~ParticleGenerator();

        /*!
        \fn Particle* findUnusedParticle()
        \brief
                Finds an unused particle in particles vector.
        */
        Particle* findUnusedParticle();

        /*!
        \fn Sprite* getParticleSprite(Particle::Type type)
        \brief
                Finds the particle's sprite from its type.
                Create the sprite if not found.
        */
        Sprite* getParticleSprite(Particle::Type type);

    private:

        /*!
        \var    maxParticles
                  The max amount of particles able to be used at a time.
        */
        unsigned int maxParticles = 600;

        /*!
        \var    lastSpawnPosition
                  Tracks where the last spawned particle's position.
                  (to find unused particle)
        */
        unsigned int lastSpawnPosition = 0;

        // instance of particle generator
        static ParticleGenerator* instance;

        // The queue of particles
        std::vector<Particle*> particleQueue;

        // Store particle sprites
        std::map<Particle::Type, Sprite*> particleSprites;

		// Particles Info Vector
		std::map<std::string,ParticleInfo> particleInfos;
};
