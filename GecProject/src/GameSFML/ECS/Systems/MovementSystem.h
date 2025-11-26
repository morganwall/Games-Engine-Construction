#pragma once
#include "System.h"

// Handles Entity Movement.
class MovementSystem : public System
{
	ECSManager& m_ECS; // Reference to the ECSManager.

public:
	// System Update.
	void Update(float deltaTime);
	// Move to destination.
	void MoveTo(EntityID& curEntity, float deltaTime);

	// Constructor.
	MovementSystem(ECSManager& ecs) : m_ECS(ecs) {}
};