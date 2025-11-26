#pragma once
#include <imgui.h>
#include "Component.h"
#include "../../Vector2.h"

class PhysicsComponent : public Component
{
	Vector2<float> m_Velocity{ 0.0f, 0.0f }; // Velocity.

public:
	// ImGui elements for the PhysicsComponent.
	void OnGui() override
	{
		ImGui::DragFloat2("Velocity", &m_Velocity.x, 0.1f);
	}

	// Set the velocity.
	void SetVelocity(Vector2<float> velocity) { m_Velocity = velocity; }
	// Get the velocity.
	Vector2<float>& GetVelocity() { return m_Velocity; }

	PhysicsComponent() {}
	PhysicsComponent(Vector2<float> velocity) : m_Velocity(velocity) {}
};