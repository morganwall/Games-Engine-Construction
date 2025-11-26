#pragma once
#include "Component.h"
#include <vector>
#include <imgui.h>
#include "../../Vector2.h"

class AnimationComponent : public Component
{
	std::vector<Texture2D*> m_Frames; // Vector of the frame texture references.
	size_t m_NumFrames{ 0 }; // The number of frames in the animation.
	unsigned int m_CurrentFrame{ 0 }; // The current frame of the animation.
	float m_Timer{ 0.0f }; // The timer for the animation.
	float m_UpdateDelay{ 250.0f }; // The delay between each frame update.
	bool m_Loop{ true }; // Should the animation loop.
	bool m_Enabled{ true }; // Should the animation be enabled.

public:
	// ImGui elements for the AnimationComponent.
	void OnGui() override
	{
		ImGui::Checkbox("Enabled", &m_Enabled);
		ImGui::Checkbox("Loop", &m_Loop);
		ImGui::Text("Number of Frames: %d", m_NumFrames);
		ImGui::Text("Current Frame: %d", m_CurrentFrame);
		ImGui::Text("Timer: %.2f", m_Timer);
		ImGui::DragFloat("Update Delay", &m_UpdateDelay, 0.1f);
	}

	// Add a frame to the animation.
	void AddFrame(Texture2D* frame)
	{
		m_Frames.push_back(frame); // Push frame to the frames vector.
		m_NumFrames++; // Increment the number of frames.
	}
	// Add several frames to the animation.
	void AddFrames(std::vector<Texture2D*> frames)
	{
		for (auto& frame : frames) // Loop through all of the frames.
			AddFrame(frame); // Add the frame to the animation.
	}
	// Get frames.
	std::vector<Texture2D*> GetFrames() { return m_Frames; }
	// Get number of frames.
	size_t GetNumFrames() { return m_NumFrames; }
	// Get the current frame.
	unsigned int GetCurrentFrame() { return m_CurrentFrame; }
	// Get the timer.
	float GetTimer() { return m_Timer; }
	// Get the update delay.
	float GetUpdateDelay() { return m_UpdateDelay; }
	// Get loop.
	bool GetLoop() { return m_Loop; }
	// Get enabled.
	bool GetEnabled() { return m_Enabled; }
	// Set number of frames.
	void SetNumFrames(unsigned int numFrames) { m_NumFrames = numFrames; }
	// Set the current frame.
	void SetCurrentFrame(unsigned int currentFrame) { m_CurrentFrame = currentFrame; }
	// Set the timer.
	void SetTimer(float timer) { m_Timer = timer; }
	// Set the update delay.
	void SetUpdateDelay(float updateTime) { m_UpdateDelay = updateTime; }
	// Set loop.
	void SetLoop(bool loop) { m_Loop = loop; }
	// Set enabled.
	void SetEnabled(bool enabled) { m_Enabled = enabled; }

	AnimationComponent() {}
	AnimationComponent(std::vector<Texture2D*> frames, bool loop) : m_Frames(frames), m_Loop(loop)
	{
		m_NumFrames = m_Frames.size(); // Set the number of frames.
	}
};