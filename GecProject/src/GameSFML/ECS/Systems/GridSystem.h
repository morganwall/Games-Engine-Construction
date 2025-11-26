#pragma once
#include "System.h"
#include "../Components/GridComponent.h"
#include "../../Window.h"
#include "../../TextureManager.h"

class GridSystem : public System
{
	Window& m_Window; // Reference to the Window.
	ECSManager& m_ECS; // Reference to the ECSManager.
	TextureManager& m_TextureManager; // Reference to the TextureManager.

public:
	// System Update.
	void Update(float deltaTime);
	// Draw the grid.
	void Draw();
	// On Left Click.
	void OnLeftClick(const Vector2<int>& mousePos);

	GridSystem(Window& window, ECSManager& ecs, TextureManager& textureManager) : m_Window(window), m_ECS(ecs), m_TextureManager(textureManager) {}
};