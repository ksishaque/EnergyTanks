/*!
\file   Particle.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-19-2022
\brief
        A particle is a tiny 2D quad that have a short lifespan.
        Particles are used to create game effects.

\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "General.h"
#include "Window.h"
#include "Particle.h"
#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"
#include "Mesh.h"
#include "MeshManager.h"
#include "ObjectManager.h"
#include "TeamSystem.h"
#include "ColorWheel.h"

/*!
\fn  Particle()
\brief
        The particle constructor.
*/
Particle::Particle()
    : duration(0.0f),
      position(0.0f),
      rotation(0.0f),
      velocity(0.0f),
	  color(1.0f, 1.0f, 1.0f),
	  alpha(1.0f),
      pType(Particle::Emission),
      scale(0.0f),
	  frameTimeout(-1.0)
{
}

/*!
\fn  ~Particle()
\brief
        The particle destructor.
*/
Particle::~Particle() {
}

/*!
\fn     float getType()
\par    This function has no parameters.
\return `particle type`
\brief
		This function returns the particle type.
*/
Particle::Type Particle::getType() {
	return pType;
}

/*!
\fn     void setType(Type particleType)
\param  value
			The value to be set.
\brief
		This function sets the particle type
*/

void Particle::setType(Type particleType) {
	pType = particleType;
}

/*!
\fn     float getLifespan()
\par    This function has no parameters.
\return `lifespan`
\brief
        This function returns the lifespan.
*/
float Particle::getLifespan() {
    return this->duration;
}

/*!
\fn     void setLifespan(float value)
\param  value
            The value to be set.
\brief
        This function sets the lifespan
*/
void Particle::setLifespan(float value) {
    this->duration = value;
}


/*!
\fn     glm::vec3 getPosition()
\par    This function has no parameters.
\return `position`
\brief
        This function returns the position.
*/
glm::vec3 Particle::getPosition() {
    return this->position;
}

/*!
\fn     void setPosition(glm::vec3 vec)
\param  vec
            The position to be set.
\brief
        This function sets the position.
*/
void Particle::setPosition(glm::vec3 vec) {
    this->position = vec;
}

/*!
\fn     float getRotation()
\par    This function has no parameters.
\return `rotation`
\brief
        This function returns the rotation.
*/
float Particle::getRotation() {
    return this->rotation;
}

/*!
\fn     void setRotation(float value)
\param  value
            The rotation to be set.
\brief
        This function sets the rotation.
*/
void Particle::setRotation(float value) {
    this->rotation = value;
}

/*!
\fn     glm::vec3 getVelocity()
\par    This function has no parameters.
\return `velocity`
\brief
        This function returns the velocity.
*/
glm::vec3 Particle::getVelocity() {
    return this->velocity;
}

/*!
\fn     void setVelocity(glm::vec3 vec)
\param  vec
            The velocity to be set.
\brief
        This function sets the velocity.
*/
void Particle::setVelocity(glm::vec3 vec) {
	this->velocity = vec;
}

/*!
\fn     glm::vec3 getScale()
\par    This function has no parameters.
\return `velocity`
\brief
		This function returns the scale.
*/
glm::vec3 Particle::getScale() {
	return this->scale;
}

/*!
\fn     void setScale(glm::vec3 vec)
\param  vec
			The scale to be set.
\brief
		This function sets the scale.
*/
void Particle::setScale(glm::vec3 vec) {
	this->scale = vec;
}

/*!
\fn		float getAlpha()
\return `alpha`
\brief
		This function gets the alpha.
*/
float Particle::getAlpha() {
	return alpha;
}

/*!
\fn     void setAlpha(float newAlpha)
\param  newAlpha
		  The alpha of the texture.
\brief
		This function sets the alpha of the texture.
*/
void Particle::setAlpha(float newAlpha) {
	alpha = newAlpha;
}

/*!
\fn     glm::vec3 getColor()
\par    This function has no parameters.
\return `color`
\brief
		This function returns the color applied to the texture.
*/
glm::vec3 Particle::getColor() {
	return this->color;
}

/*!
 \fn     void setColor(glm::vec3 vec)
 \param  vec
		   The color to be set.
 \brief
		 This function sets the color applied to the texture.
 */
void Particle::setColor(glm::vec3 vec) {
	this->color = vec;
}

#if 0
/*!
\fn     unsigned int getFrameIndex()
\par    This function has no parameters.
\return `index`
\brief
		This function returns the current texture frame index.
*/
unsigned int Particle::getFrameIndex() {
	return frameIndex;
}

/*!
\fn     void setFrameIndex(unsigned int index)
\param  index
		  The current texture frame index.
\brief
		This function sets the current texture frame index.
*/
void Particle::setFrameIndex(unsigned int index) {
	frameIndex = index;
}
#endif

/*!
\fn     float getFrameTimeout()
\par    This function has no parameters.
\return `float`
\brief
		This function returns the texture frame timeout.
*/
float Particle::getFrameTimeout() {
	return frameTimeout;
}

/*!
\fn     void setFrameTimeout(float timeout)
\param  timeout
		  The frame timeout to be set. Determines when texture
		  frames are changed.
\brief
		This function sets the texture frame timeout.
*/
void Particle::setFrameTimeout(float timeout) {
	frameTimeout = timeout;
}

/*!
\fn     void spawn(GameObject* emitter, Type particleType)
\param  emitter
            The particle emitter.
\param  particleType
            The particle type.
\brief
        This function spawns particle.
*/
void Particle::spawn(GameObject* emitter, Type particleType, ParticleInfo pInfo) {
	glm::vec3 scale = pInfo.scale;
	glm::vec4 color = pInfo.color;
	float frameduration = pInfo.frameduration;

    setLifespan(pInfo.lifespan > 0 ? pInfo.lifespan : DEFAULT_LIFE_SPAN);

	Physics* ePhysics;
	Transform* eTransform;

	if (emitter) {
		ePhysics = dynamic_cast<Physics*>(emitter->get(ComponentTypeEnum::cPhysics));
		eTransform = dynamic_cast<Transform*>(emitter->get(ComponentTypeEnum::cTransform));
	}
	else {
		// In the case of no emitter, particle type determines physics and transform.
		ePhysics = new Physics();
		eTransform = new Transform(glm::vec3(0), glm::vec3(0), 0.0f);
	}

	setType(particleType);
	setColor(glm::vec3(color)); // default color from Particles.json
	setAlpha(color.a);

	glm::vec3 teamColor = (emitter) ? 
		TeamSystem::getInstance()->getColor(emitter->getTeam()) :
		glm::vec3(pInfo.color);

	if (particleType == Particle::Tracks) {
		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());
		setVelocity(ePhysics->getVelocity() * 0.0f);
		setScale(scale);
		//setColor(teamColor);
	}
	else if (particleType == Particle::Explosion) {
		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());
		setVelocity(glm::vec3(randomInteger(500,-500) * 1.0f, randomInteger(500, -500) * 1.0f, 0.0f));
		setScale(scale);
		setColor(teamColor);
	}
	else if (particleType == Particle::Emission) {
		const double particlePositionX = eTransform->getTranslation().x - (ePhysics->getVelocity().x * 0.07);
		const double particlePositionY = eTransform->getTranslation().y - (ePhysics->getVelocity().y * 0.07);
		setPosition(glm::vec3(particlePositionX, particlePositionY, 0));

		setRotation(eTransform->getRotation());

		const float emVelX = ePhysics->getVelocity().x * 0.5f;
		const float emVelY = ePhysics->getVelocity().y * 0.5f;
		setVelocity(glm::vec3(emVelX + randomInteger(120, -120), emVelY + randomInteger(120, -120), 0.0f));

		setScale(scale);
		setColor(teamColor);
	}
	else if (particleType == Particle::Defense) {
		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());
		/*
		setVelocity(ePhysics->getVelocity() * 1.0f);
		/*/
		setVelocity({0, 0, 0});
		//*/
		setScale(scale);
		setColor(teamColor);
	}
	else if (particleType == Particle::BulletTrail) {
		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());
		setVelocity(ePhysics->getVelocity() * 0.0f);
		setScale(scale);
		setColor(teamColor);
	}
	else if (particleType == Particle::BounceSparks) {

		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());

		const float emVelX = ePhysics->getVelocity().x * -0.2f;
		const float emVelY = ePhysics->getVelocity().y * -0.2f;
		setVelocity(glm::vec3(emVelX + randomInteger(120, -120), emVelY + randomInteger(120, -120), 0.0f));

		int newScale = randomInteger(static_cast<int>(scale.x * 1.5), static_cast<int>(scale.x * 0.5));
		glm::vec3 randomScale = glm::vec3(newScale, newScale, scale.z);
		setScale(randomScale);
		
		glm::vec3 sparksColor = TeamSystem::getInstance()->getColor(emitter->getTeam());
		//setColor(sparksColor);
	}
	else if (particleType == Particle::ShieldSparks) {
		setPosition(eTransform->getTranslation());
		setRotation(eTransform->getRotation());

		const float emVelX = ePhysics->getVelocity().x * -0.2f;
		const float emVelY = ePhysics->getVelocity().y * -0.2f;
		setVelocity(glm::vec3(emVelX + randomInteger(120, -120), emVelY + randomInteger(120, -120), 0.0f));

		int newScale = randomInteger(static_cast<int>(scale.x * 1.25), static_cast<int>(scale.x * 0.75));
		glm::vec3 randomScale = glm::vec3(newScale, newScale, scale.z);
		setScale(randomScale);

		glm::vec3 sparksColor = TeamSystem::getInstance()->getColor(emitter->getTeam());
		setColor(sparksColor);
	}
	else if (particleType == Particle::Confetti) {
		int winWidth = Window::getInstance()->getWidth();
		int winHeight = Window::getInstance()->getHeight();
		int posX = randomInteger(winWidth / 2, -(winWidth / 2));
		int posY = randomInteger(winHeight / 2, winHeight / 4);
		int velX = randomInteger(20, 0);
		int velY = randomInteger(-80, -120);
		/*
		int scaleX = randomInteger(static_cast<int>(scale.x * 1.2), static_cast<int>(scale.x * 0.8));
		int scaleY = randomInteger(static_cast<int>(scale.y * 1.2), static_cast<int>(scale.y * 0.8));
		glm::vec3 randomScale = glm::vec3(scaleX, scaleY, scale.z);
		/*/
		float scaleVar = (float) randomInteger(4, 1);
		scaleVar *= scaleVar;
		scaleVar /= 16;
		scaleVar += 0.4375f;
		glm::vec3 randomScale = glm::vec3(scaleVar * scale.x, scaleVar * scale.y, scale.z);
		//*/

		/*
		float colorR = randomInteger(255, 100) / 255.0f;
		float colorG = randomInteger(255, 100) / 255.0f;
		float colorB = randomInteger(255, 100) / 255.0f;
		glm::vec3 randomColor = glm::vec3(colorR, colorG, colorB);
		/*/
		float colorVal = static_cast<float>(randomInteger(24));
		colorVal /= 6;
		glm::vec3 randomColor = glm::vec3(1.0f, 0.0f, 0.0f);
		incrementColor(randomColor, colorVal);
		randomColor /= 2;
		randomColor += glm::vec3(0.5f, 0.5f, 0.5f);
		//*/

		setPosition(glm::vec3(posX, posY, 1));
		setRotation(eTransform->getRotation() + randomInteger(90, 0));
		setVelocity(glm::vec3(velX, velY, 0));
		setScale(randomScale);
		setColor(randomColor);

		frameTimeout = randomInteger((int) (frameduration * 64.0f)) * 0.015625f;
		if(frameTimeout == 0) frameTimeout = frameduration;
	}
}

/*!
\fn     void despawn()
\brief
        This function despawns particle.
*/
void Particle::despawn() {
    setLifespan(0.0f);
    setPosition(glm::vec3(0.0f));
    setRotation(0.0f);
    setVelocity(glm::vec3(0.0f));
	//setFrameIndex(0);
	setFrameTimeout(-1.0f);
}


