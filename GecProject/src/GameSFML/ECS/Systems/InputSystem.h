#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../../Window.h"

// Handles Entity Input.
class InputSystem : public System
{
	Window& m_Window; // Reference to the window
	ECSManager& m_ECS; // Reference to the ECSManager.

public:
	// Process mouse button down events.
	void MouseButtonDown(const sf::Event::MouseButtonEvent& event);
	// Process mouse button up events.
	void MouseButtonUp(const sf::Event::MouseButtonEvent& event);

	// Constructor.
	InputSystem(Window& window, ECSManager& ecs) : m_Window(window), m_ECS(ecs) {}
};