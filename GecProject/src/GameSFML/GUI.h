#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Vector2.h"
#include "GameMetrics.h"
#include "Color.h"
#include "TextureManager.h"
#include "ECS/ECSManager.h"

// Gui class, using ImGui.
class GUI
{
	Window* m_Window{ nullptr }; // Target render window pointer.
	GameMetrics* m_Metrics{ nullptr }; // Game metrics class pointer.
	TextureManager* m_TextureManager{ nullptr }; // Texture manager pointer.
	ECSManager* m_ECS{ nullptr }; // Pointer to the ecs manager.

	sf::Clock m_UIClock{}; // Clock used for ImGui.
	int m_TextureSelectedIndex{ 0 }; // The currently selected Texture ListBox index.
	EntityID m_TexturePreviewEntity{}; // The entity used for the preview texture.
	size_t m_NumTextures{ 0 }; // Number of loaded textures.
	int m_EntitySelectedIndex{ 0 }; // The currently selected Entity ListBox index.
	size_t m_NumEntities{ 0 }; // Number of active entities from the ECS.

	// Window/Tab Bools.
	bool m_ShowMetrics{ true }; // Is the metrics window open.
	bool m_ShowDemoWnd{ false }; // Show ImGui demo window.

	// ImGui Settings.
	Color m_MetricsColor{ 1.0f, 1.0f, 1.0f, 1.0f }; // Colour of the metrics text.

public:
	// Initialise the Gui.
	bool Init(Window* window, GameMetrics* metrics, ECSManager* ecs, TextureManager* textureManager);
	// Draw the Gui.
	void Draw();
	// Render ImGui.
	void Render();
	// Cleanup the Gui.
	void Cleanup();

	// Constructor.
	GUI() {}
	// Destructor.
	~GUI() {}
};