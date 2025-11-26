#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../../Window.h"

// Handles updating and drawing sprites.
class RenderSystem : public System
{
	Window& m_Window; // Reference to the window.
	ECSManager& m_ECS; // Reference to the ECSManager.

public:
	// System update.
	void Update(float deltaTime);
	// Draw.
	void Draw();

	// Constructor.
	RenderSystem(Window& window, ECSManager& ecs) : m_Window(window), m_ECS(ecs) {}
};