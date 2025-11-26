#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"

// Holds game metrics.
class GameMetrics
{
	sf::Clock m_Clock{}; // Clock used for calculating FPS and frame time.

	// Get the current FPS and FrameTime.
	void GetFPSandFrameTime();

public:
	unsigned int m_FrameCounter{ 0 }; // Used for calculating the FPS.
	float m_FPS{ 0.0f }; // Current FPS.
	float m_FrameTime{ 0.0f }; // Current frame time.
	float m_LastSampleTime{ 0.0f }; // Last time FPS was calculated.
	float m_UpdateTime{ 500.0f }; // Time it takes to update the game metrics (in ms).
	float m_MaxFPS{ 60.0f }; // The max FPS limit. Default is 60.0f.

	bool m_LimitFPS{ false }; // Limit the FPS.
	bool m_UpdateLimit{ false }; // Update the FPS limit.

	// Update Metrics.
	void Update(Window& window);

	GameMetrics() {}
	~GameMetrics() {}
};

// TODO: Make most vars private, with getters and setters.