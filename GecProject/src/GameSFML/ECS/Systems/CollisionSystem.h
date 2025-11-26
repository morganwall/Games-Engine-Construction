#pragma once
#include "System.h"
#include "../Components/BoundingBoxComponent.h"
#include "../../Window.h"

class CollisionSystem : public System
{
	ECSManager& m_ECS; // Reference to the ECSManager.
	Window& m_Window; // Reference to the window.

public:
	// System Update.
	void Update(float deltaTime);
	// System Draw.
	void Draw();
	// Box Collision.
	COLLISION_SIDE Box(BoundingBoxComponent& box1, BoundingBoxComponent& box2);
	// Draw Bouncing Box.
	void DrawBoundingBox(EntityID entity);

	// Constructor.
	CollisionSystem(ECSManager& ecs, Window& window) : m_ECS(ecs), m_Window(window) {}
};