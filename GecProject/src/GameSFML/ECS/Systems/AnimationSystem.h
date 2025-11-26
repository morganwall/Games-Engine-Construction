#pragma once
#include "System.h"
//include "../Components/AnimationComponent.h"

class AnimationSystem : public System
{
	ECSManager& m_ECS; // Reference to the ECSManager.

public:
	// System Update.
	void Update(float deltaTime);

	AnimationSystem(ECSManager& ecs) : m_ECS(ecs) {}
};