/*!
\file   GenerateParticlesAction.cpp
\author Benedict Yau
\date   3-29-2023
\brief
		 Nodes in an action list that generate particles.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "Trace.h"
#include "ParticleGenerator.h"
#include "GenerateParticlesAction.h"

GenerateParticlesAction::GenerateParticlesAction(const std::string& pType) : ActionNode(), particleType(pType){}

void GenerateParticlesAction::operator()(GameObject* obj, float dt) {

	//	Trace message for debug
#ifdef DEBUG_SYSTEM
	Trace::message("Generate particles: %s", particleType);
#endif

	// Generate particles.
	ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
	particleGenerator->spawnParticles(nullptr, Particle::StringToParticleType(particleType));
	
	//	Recursive call to next
	ActionNode::operator()(obj, dt);
}

GenerateParticlesAction* GenerateParticlesAction::clone() const {

	//	Variable: return value / clone of `this`
	GenerateParticlesAction* ans = new GenerateParticlesAction(particleType);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;
}
