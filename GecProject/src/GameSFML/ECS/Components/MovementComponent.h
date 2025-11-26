#pragma once
#include <imgui.h>
#include "Component.h"

class MovementComponent : public Component
{
	Vector2<float> m_Destination{ 0.0f, 0.0f }; // Destination for movement.
	float m_MarginOfError{ 0.05f }; // Margin of error for destination.
	float m_MovementSpeed{ 500.0f }; // Movement speed.

public:
	// ImGui elements for the InputComponent.
	void OnGui() override
	{
		ImGui::DragFloat2("Destination", &m_Destination.x, 0.1f);
		ImGui::DragFloat("Margin of Error", &m_MarginOfError, 0.1f);
		ImGui::DragFloat("Movement Speed", &m_MovementSpeed, 0.1f);
	}

	// Set destination.
	void SetDestination(Vector2<float> destination) { m_Destination = destination; }
	// Set margin of error.
	void SetMarginOfError(float marginOfError) { m_MarginOfError = marginOfError; }
	// Set movement speed.
	void SetMovementSpeed(float movementSpeed) { m_MovementSpeed = movementSpeed; }
	// Get destination.
	Vector2<float>& GetDestination() { return m_Destination; }
	// Get margin of error.
	float& GetMarginOfError() { return m_MarginOfError; }
	// Get movement speed.
	float& GetMovementSpeed() { return m_MovementSpeed; }

	MovementComponent() {}
};