/*!
\file   Particle.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-19-2022
\brief
        A particle is a tiny 2D quad that have a short lifespan.
        Particles are used to create game effects.

\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include <map>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "GraphicsUnit.h"

const float DEFAULT_LIFE_SPAN = 0.5f;

struct ParticleInfo {
	std::string id;
	std::string texture;
	glm::vec4 color = glm::vec4(0);
	glm::vec3 scale = glm::vec3(0);
	float lifespan = 0.0f;
	unsigned int count = 0;
	GraphicsUnit::Type layer = GraphicsUnit::Type::guInvalid;
	float frameduration = 0.0f;
};

class Particle {
    public:

        enum Type {
            Explosion,
            Tracks,
			Emission,
			Defense,
			BulletTrail,
			BounceSparks,
			ShieldSparks,
			Confetti
        };

		/*!
		\fn  ParticleTypeToString(Type e)
		\brief
				Convert Particle::Type to string.
		*/
		static constexpr const char* ParticleTypeToString(Type e) noexcept {
			switch (e) {
				case Type::Explosion:
					return "explosion";
				case Type::Emission:
					return "emission";
				case Type::Defense:
					return "defense";
				case Type::BulletTrail:
					return "bullettrail";
				case Type::BounceSparks:
					return "bouncesparks";
				case Type::ShieldSparks:
					return "shieldsparks";
				case Type::Confetti:
					return "confetti";
				case Type::Tracks:
				default:
					return "tracks";
			}
		}

		/*!
		\fn  StringToParticleType(Type e)
		\brief
				Convert string to Particle::Type.
		*/
		static const Type StringToParticleType(std::string s) noexcept {
			std::map<std::string, Type> table = {
				{"tracks", Tracks},
				{"explosion", Explosion},
				{"emission", Emission},
				{"defense", Defense},
				{"bullettrail", BulletTrail},
				{"bouncesparks", BounceSparks},
				{"shieldsparks", ShieldSparks},
				{"confetti", Confetti}
			};
			return table.at(s);
		};

        /*!
        \fn  Particle()
        \brief
                The particle constructor.
        */
        Particle();

        /*!
        \fn  ~Particle()
        \brief
                The particle destructor.
        */
        ~Particle();

		/*!
        \fn     Type getType()
        \par    This function has no parameters.
        \return `particle type`
        \brief
                This function returns the particle type.
        */
		Type getType();

		/*!
		\fn     void setType(Type particleType)
		\param  value
				  The value to be set.
		\brief
				This function sets the particle type.
		*/
		void setType(Type particleType);

        /*!
        \fn     float getLifespan()
        \par    This function has no parameters.
        \return `lifespan`
        \brief
                This function returns the lifespan.
        */
        float getLifespan();

        /*!
        \fn     void setLifespan(float value)
        \param  value
                  The value to be set.
        \brief
                This function sets the lifespan
        */
        void setLifespan(float value);

        /*!
        \fn     glm::vec3 getPosition()
        \par    This function has no parameters.
        \return `position`
        \brief
                This function returns the position.
        */
        glm::vec3 getPosition();

        /*!
        \fn     void setPosition(glm::vec3 vec)
        \param  vec
                  The position to be set.
        \brief
                This function sets the position.
        */
        void setPosition(glm::vec3 vec);

        /*!
        \fn     float getRotation()
        \par    This function has no parameters.
        \return `rotation`
        \brief
                This function returns the rotation.
        */
        float getRotation();

        /*!
        \fn     void setRotation(float value)
        \param  value
                  The rotation to be set.
        \brief
                This function sets the rotation.
        */
        void setRotation(float value);

        /*!
        \fn     glm::vec3 getVelocity()
        \par    This function has no parameters.
        \return `velocity`
        \brief
                This function returns the velocity.
        */
        glm::vec3 getVelocity();

        /*!
        \fn     void setVelocity(glm::vec3 vec)
        \param  vec
                  The velocity to be set.
        \brief
                This function sets the velocity.
        */
        void setVelocity(glm::vec3 vec);

		/*!
		\fn     glm::vec3 getScale()
		\par    This function has no parameters.
		\return `scale`
		\brief
				This function returns the scale.
		*/
		glm::vec3 getScale();

		/*!
		 \fn     void setScale(glm::vec3 vec)
		 \param  vec
				   The scale to be set.
		 \brief
				 This function sets the scale.
		 */
		void setScale(glm::vec3 vec);

		/*!
		\fn     float getAlpha()
		\par    This function has no parameters.
		\return `alpha`
		\brief
				This function returns the alpha of the texture.
		*/
		float getAlpha();

		/*!
		\fn     void setAlpha(float newAlpha)
		\param  newAlpha
				  The alpha of the texture.
		\brief
				This function sets the alpha of the texture.
		*/
		void setAlpha(float newAlpha);

		/*!
		\fn     Type getColor()
		\par    This function has no parameters.
		\return `color`
		\brief
				This function returns the color applied to the texture.
		*/
		glm::vec3 getColor();

		/*!
		 \fn     void setColor(glm::vec3 vec)
		 \param  vec
				   The color to be set.
		 \brief
				 This function sets the color applied to the texture.
		 */
		void setColor(glm::vec3 vec);

#if 0
		/*!
		\fn     unsigned int getFrameIndex()
		\par    This function has no parameters.
		\return `index`
		\brief
				This function returns the current texture frame index.
		*/
		unsigned int getFrameIndex();

		/*!
		\fn     void setFrameIndex(unsigned int index)
		\param  index
				  The current texture frame index.
		\brief
				This function sets the current texture frame index.
		*/
		void setFrameIndex(unsigned int index);
#endif

		/*!
		\fn     float getFrameTimeout()
		\par    This function has no parameters.
		\return `float`
		\brief
				This function returns the texture frame timeout.
		*/
		float getFrameTimeout();

		/*!
		\fn     void setFrameTimeout(float timeout)
		\param  timeout
				  The frame timeout to be set. Determines when texture
				  frames are changed.
		\brief
				This function sets the texture frame timeout.
		*/
		void setFrameTimeout(float timeout);

        /*!
        \fn     void spawn(GameObject* emitter, Type particleType)
        \param  emitter
                  The particle emitter.
        \param  particleType
                  The particle type.
		\param  pInfo
				  The particle info.
        \brief
                This function spawns particle.
        */
        void spawn(GameObject* emitter, Type particleType, ParticleInfo pInfo);

        /*!
        \fn     void despawn()
        \brief
                This function despawns particle.
        */
        void despawn();

    private:
		Type pType;

        /*!
        \var    duration
                  The duration of the particle.
        */
        float duration;

        /*!
        \var    position
                  The position of the particle.
        */
        glm::vec3 position;

        /*!
        \var    rotation
                  The rotation of the particle.
        */
        float rotation;

        /*!
        \var    velocity
                  The velocity of the particle.
        */
        glm::vec3 velocity;

		/*!
		\var    scale
				  The scale of the particle.
		*/
		glm::vec3 scale;

		/*!
		\var    alpha
				  The alpha value of the particle texture.
		*/
		float alpha;

		/*!
		\var    color
				  The color applies to the particle texture.
		*/
		glm::vec3 color;

		/*!
		\var    frameIndex
				  The index of current texture - if multi-texture is used.
		*/
		//unsigned int frameIndex;

		/*!
		\var    frameTimeout
				  Timout before switching to next texture - if multi-texture is used.
		*/
		float frameTimeout;
};
