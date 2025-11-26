#pragma once
#include <imgui.h>
#include "Component.h"
#include "../../Vector2.h"

// Determines an object's position, rotation, and scale.
class TransformComponent : public Component
{
	Vector2<float> m_Pos{ 0.0f, 0.0f }; // Position.
	float m_Rotation{ 0.0f }; // Rotation.
	Vector2<float> m_Scale{ 1.0f, 1.0f }; // Scale.

public:
	// ImGui elements for the TransformComponent.
	void OnGui() override
	{
		ImGui::DragFloat2("Position", &m_Pos.x, 0.1f);
		ImGui::DragFloat("Rotation", &m_Rotation, 0.1f);
		ImGui::DragFloat2("Scale", &m_Scale.x, 0.1f);
	}

	// Set the transform position.
	void SetPosition(Vector2<float> position) { m_Pos = position; }
	// Set the transform rotation.
	void SetRotation(float& rotation) { m_Rotation = rotation; }
	// Set the transform scale.
	void SetScale(Vector2<float>& scale) { m_Scale = scale; }
	// Get the transform position.
	Vector2<float>& GetPosition() { return m_Pos; }
	// Get the transform rotation.
	float& GetRotation() { return m_Rotation; }
	// Get the transform scale.
	Vector2<float>& GetScale() { return m_Scale; }

	TransformComponent() {}
	TransformComponent(Vector2<float> position, float rotation, Vector2<float> scale) : m_Pos(position), m_Rotation(rotation), m_Scale(scale) {}
};