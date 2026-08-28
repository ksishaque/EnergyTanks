/*!
\file   ParticleGenerator.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   11-19-2022
\brief
        Particle generator is responsible for generating particles
        that have a short lifespan.
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <cmath>
#include "rapidjson/document.h"
#include "readFile.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Trace.h"

#include "GraphicsUnit.h"
#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"
#include "Mesh.h"
#include "MeshManager.h"
#include "General.h"
#include "Window.h"
#include "StringTables.h"

using rapidjson::Document;

ParticleGenerator* ParticleGenerator::instance = nullptr;

/*!
\fn  ParticleGenerator* getInstance()
\param none
\brief
        See ParticleGenerator.h
*/
ParticleGenerator* ParticleGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new ParticleGenerator();
    }
    return instance;
}

/*!
\fn  static void closeInstance()
\param none
\brief
        See ParticleGenerator.h
*/
void ParticleGenerator::closeInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}


/*!
\fn     ParticleGenerator()
\par    This function has no parameters.
\return The new particle generator
\brief
        See ParticleGenerator.h
*/
ParticleGenerator::ParticleGenerator() : ISystem(sParticle) {
}

/*!
\fn     ~ParticleGenerator()
\par    This function has no parameters.
\return Nothing
\brief
        See ParticleGenerator.h
*/
ParticleGenerator::~ParticleGenerator() {
}

/*!
\fn void initialize()
\brief
        See ParticleGenerator.h
*/
void ParticleGenerator::initialize() {
    if (isActive()) {
        return;
    }
    ISystem::initialize();

	const char* jsonData = readWholeFile("Data/Json/Objects/Particles.json");

	Document jsonDoc;
	jsonDoc.Parse(jsonData);

	if (!jsonDoc.IsObject() || !jsonDoc.HasMember("particles")) {
		return;
	}

	if (jsonDoc.HasMember("maxParticles")) {
		maxParticles = jsonDoc["maxParticles"].GetInt();
	}

	if (jsonDoc.HasMember("particles") && jsonDoc["particles"].IsArray()) {
		for (auto& element : jsonDoc["particles"].GetArray()) {
			if (element.IsObject()) {
				rapidjson::GenericObject<false, rapidjson::Value> particleType = element.GetObject();
				if (particleType.HasMember("id") && particleType["id"].IsString()) {
					ParticleInfo pInfo;
					pInfo.id = particleType["id"].GetString();

					if (particleType.HasMember("texture") && particleType["texture"].IsString()) {
						pInfo.texture = particleType["texture"].GetString();
					}
					else {
						pInfo.texture = "NULL";
					}

					if (particleType.HasMember("color") && particleType["color"].IsArray() && particleType["color"].Size() > 3) {
						rapidjson::GenericArray<false, rapidjson::Value> colorArray = particleType["color"].GetArray();
						pInfo.color = glm::vec4(colorArray[0].GetFloat(), colorArray[1].GetFloat(), colorArray[2].GetFloat(), colorArray[3].GetFloat());
					}
					else {
						pInfo.color = {1, 1, 1, 1};
					}

					if (particleType.HasMember("scale") && particleType["scale"].IsArray() && particleType["scale"].Size() > 2) {
						rapidjson::GenericArray<false, rapidjson::Value> colorArray = particleType["scale"].GetArray();
						pInfo.scale = glm::vec3(colorArray[0].GetFloat(), colorArray[1].GetFloat(), colorArray[2].GetFloat());
					}
					else {
						pInfo.scale = {1, 1, 0};
					}

					if (particleType.HasMember("lifespan") && particleType["lifespan"].IsFloat()) {
						pInfo.lifespan = particleType["lifespan"].GetFloat();
					}
					else {
						pInfo.lifespan = 1;
					}

					if (particleType.HasMember("count") && particleType["count"].IsUint()) {
						pInfo.count = particleType["count"].GetUint();
					}
					else {
						pInfo.count = 1;
					}

					if (particleType.HasMember("layer") && particleType["layer"].IsString()) {
						try {
							pInfo.layer = layerTable.at(particleType["layer"].GetString());
						}
						catch (const std::out_of_range&) {
							pInfo.layer = GraphicsUnit::Type::guInvalid;
						}
					}
					else {
						pInfo.layer = GraphicsUnit::Type::guInvalid;
					}

					/*
					if (particleType.HasMember("textureframes")) {
						pInfo.textureframes = particleType["textureframes"].GetUint();
					}
					else {
						pInfo.textureframes = 1;
					}
					*/

					if (particleType.HasMember("frameduration")) {
						pInfo.frameduration = particleType["frameduration"].GetFloat();
					}
					else {
						pInfo.frameduration = 1.0f;
					}

					particleInfos[pInfo.id] = pInfo;
				}
			}
		}
	}
    
    //create instances of particles
    for (unsigned int i = 0; i < maxParticles; ++i) {
        particleQueue.push_back(new Particle());
    }

	delete [] jsonData;

}

/*!
\fn void update(float dt)
\param
    The delta time.
\brief
        See ParticleGenerator.h
*/
void ParticleGenerator::update(float& dt) {
    for (unsigned int i = 0; i < maxParticles; ++i) {
        Particle* particle = particleQueue[i];
		std::string typeInString = Particle::ParticleTypeToString(particle->getType());
		ParticleInfo pInfo = particleInfos[typeInString];

        if (particle->getLifespan() > 0.0f) {
            // decrease the duration timer on particle
            particle->setLifespan(particle->getLifespan() - dt);

            // set particle alpha and movement
			// for fade effect, use y = log5(x + 0.2) for x <= 1.5
			particle->setAlpha((particle->getLifespan() > 1.5f) ? particle->getAlpha() : log10(5 * (particle->getLifespan() + 0.2f)));

			glm::vec3 particlePosition = particle->getPosition();
			glm::vec3 particleVelocity = particle->getVelocity();
			particlePosition.x = (particleVelocity.x * dt) + particlePosition.x;
			particlePosition.y = (particleVelocity.y * dt) + particlePosition.y;
			particle->setPosition(particlePosition);
			
			// Create random movement on emission particles for drones / bullets.
			//if (particle->getType() == Particle::Emission && particle->getLifespan() < 0.42f) {
			//	particle->setVelocity(glm::vec3(randomInteger(-200, 200), randomInteger(-200, 200), 0.0f));
			//}

			// Update frameIndex if frameTimeout < 0.0f.
			if (particle->getFrameTimeout() > 0.0f) {
				particle->setFrameTimeout(particle->getFrameTimeout() - dt);
				if (particle->getFrameTimeout() < 0.0f) {
					//particle->setFrameIndex((particle->getFrameIndex() + 1) % pInfo.textureframes);
					float scale = (float) randomInteger(4, 1);
					scale *= scale;
					scale /= 16;
					scale += 0.4375f;
					particle->setScale({scale * pInfo.scale.x, scale * pInfo.scale.y, pInfo.scale.z});
					particle->setRotation(particle->getRotation() + 45);
					particle->setFrameTimeout(pInfo.frameduration);
				}
			}

        }
        else if (particle->getLifespan() <= 0.0f) {
            particle->despawn();
        }
    }

    // trace how many particles are in active use
    unsigned int count = 0;
    for (unsigned int j = 0; j < maxParticles; ++j) {
        Particle* particle = particleQueue[j];
        if (particle->getLifespan() > 0.0f) {
            count++;
        }
    }
#ifdef DEBUG_SYSTEM
    Trace::message("Num of Active Particles: %i", count);
#endif
}

/*!
\fn void shutdown()
\brief
        See ParticleGenerator.h
*/
void ParticleGenerator::shutdown() {
    //delete particles
    std::vector<Particle*>::iterator iter = particleQueue.begin();

    for (iter; iter < particleQueue.end(); ++iter) {
        delete *iter;
    }

	for (std::pair<Particle::Type, Sprite*> pair : particleSprites) {
		delete pair.second ->  getTransform();
		delete pair.second;
	}
}

/*!
\fn void spawnParticles(GameObject* emitter, Particle::Type pType)
\brief
        See ParticleGenerator.h
*/
void ParticleGenerator::spawnParticles(GameObject* emitter, Particle::Type pType) {

	std::string typeInString = Particle::ParticleTypeToString(pType);
	unsigned int numOfParticles = particleInfos[typeInString].count;

    for (unsigned int i = 0; i < numOfParticles; ++i) {
        Particle* newParticle = findUnusedParticle();
        if (newParticle) {
            newParticle->spawn(emitter, pType, particleInfos[typeInString]);
        }
    }
}

/*!
\fn void draw(float dt)
\brief
        Draws the particles.
*/
void ParticleGenerator::draw(float dt) {
    for (unsigned int j = 0; j < maxParticles; ++j) {
        Particle* particle = particleQueue[j];
        if (particle->getLifespan() > 0.0f) {

            Sprite* cranberry = getParticleSprite(particle->getType());
            if (cranberry) {
                Transform* transform = cranberry->getTransform();
                transform->setTranslation(particle->getPosition());
                transform->setRotatePos(particle->getRotation());
                transform->setScale(particle->getScale());

				/*
				unsigned int guSize = cranberry->getGraphicsListSize();

				// index is 0 if we only have one GU, else we use frameIndex.
				unsigned int guIndex = (guSize == 1) ? 0 : particle->getFrameIndex();
                
				GraphicsUnitMutable* gu = cranberry->getGraphics(guIndex); 
				if (gu) {
					gu->setTransformMatrix(&(transform->getMatrix()));
					gu->setTempColor(glm::vec4(particle->getColor(), particle->getAlpha()));
					gu->draw(Window::getInstance()->getScale());
				}
				/*/
				cranberry->setColor(particle->getColor().r, particle->getColor().g, particle->getColor().b, particle->getAlpha());
				cranberry->Draw();
				//*/
            }

        }
    }
}

/*!
\fn Particle* findUnusedParticle()
\brief
        See ParticleGenerator.h
*/
Particle* ParticleGenerator::findUnusedParticle() {
    // search for unused particle from last position.
    for (unsigned int i = lastSpawnPosition; i < maxParticles; ++i) {
        // search for unused particles.
        if (particleQueue[i]->getLifespan() <= 0.0f) {
            lastSpawnPosition = i;
            return particleQueue[i];
        }
    }

    // if unused particle not found, search from the beginning.
    for (unsigned int j = 0; j < lastSpawnPosition; ++j) {
        // search for unused particles.
        if (particleQueue[j]->getLifespan() <= 0.0f) {
            lastSpawnPosition = j;
            return particleQueue[j];
        }
    }

    // no unused particles left.
    return nullptr;
}

/*!
\fn Sprite* getParticleSprite(Particle::Type type)
\brief
        See ParticleGenerator.h
*/
Sprite* ParticleGenerator::getParticleSprite(Particle::Type type) {
    if (particleSprites[type] == nullptr) {
        // Create sprite for particle type.
        Sprite* cranberry = new Sprite();

        Transform* transform = new Transform(
            glm::vec3(0.0f), // translation
            glm::vec3(0.0f), // scale
            0.0f);           // rotation
        cranberry->setTransform(transform);

        Mesh* mesh;
        MeshManager::getInstance()->getMesh(MeshManager::MeshType::single, mesh);

		std::string typeInString = Particle::ParticleTypeToString(type);
		/*
		unsigned int frames = particleInfos[typeInString].textureframes;

		if (frames == 1) {
			Texture* texture = nullptr;
			texture = &TextureManager::getTexture(particleInfos[typeInString].texture);

			GraphicsUnitMutable* gu = makeGraphicsUnit(mesh, nullptr, GraphicsUnit::Type::guShield1, texture);
			cranberry->addToGraphics(gu);
			gu->setColor(particleInfos[typeInString].color);
		}
		else {
			// multiple frames.
			for (unsigned int i = 0; i < frames; ++i) {
				Texture* texture = nullptr;
				std::string textureName = particleInfos[typeInString].texture + std::to_string(i);
				texture = &TextureManager::getTexture(textureName);

				GraphicsUnitMutable* gu = makeGraphicsUnit(mesh, nullptr, GraphicsUnit::Type::guShield1, texture);
				cranberry->addToGraphics(gu);
				gu->setColor(particleInfos[typeInString].color);
			}
		}
		*/
		Texture* texture = nullptr;
		texture = &TextureManager::getTexture(particleInfos[typeInString].texture);

		GraphicsUnitMutable* gu = makeGraphicsUnit(mesh, nullptr, particleInfos[typeInString].layer, texture);
		cranberry->addToGraphics(gu);
		gu->setColor(particleInfos[typeInString].color);

        particleSprites[type] = cranberry;
    }

    return particleSprites[type];
}

