#pragma once
#include <imgui.h>
#include "Component.h"
#include "../../Vector2.h"
#include "../../Color.h"

enum COLLISION_SIDE
{
	COLLISION_NONE = 0,
	COLLISION_TOP,
	COLLISION_BOTTOM,
	COLLISION_LEFT,
	COLLISION_RIGHT
};

class BoundingBoxComponent : public Component
{
	bool m_ShowBoundingBox{ false }; // Show the bounding box.
	Color m_BoundingBoxColor{ 1.0f, 1.0f, 1.0f, 1.0f }; // Colour of the bounding box.
	Vector2<float> m_Size{ 0.0f, 0.0f }; // Size of the bounding box.
	Vector2<float> m_Position{ 0.0f, 0.0f }; // Position of the bounding box.
	float m_Rotation{ 0.0f }; // Rotation of the bounding box.
	COLLISION_SIDE m_CollisionSide{ COLLISION_NONE }; // Collision side.

public:
	// ImGui elements for the BoundingBoxComponent.
	void OnGui() override
	{
		ImGui::Checkbox("Show Bounding Box", &m_ShowBoundingBox);
		ImGui::SameLine();
		ImGui::ColorEdit3("Colour##BoundingBox", m_BoundingBoxColor, ImGuiColorEditFlags_NoInputs); // Colour picker. No inputs.
		ImGui::DragFloat2("Position", &m_Position.x, 0.1f);
		ImGui::DragFloat2("Size", &m_Size.x, 0.1f);
		ImGui::DragFloat("Rotation", &m_Rotation, 0.1f);
		ImGui::Text("Collision Side: %d", m_CollisionSide);
	}

	// Set the bounding box show.
	void SetShowBoundingBox(bool show) { m_ShowBoundingBox = show; }
	// Set the bounding box colour.
	void SetBoundingBoxColor(Color colour) { m_BoundingBoxColor = colour; }
	// Set the bounding box size.
	void SetSize(Vector2<float> size) { m_Size = size; }
	// Set the bounding box position.
	void SetPosition(Vector2<float> position) { m_Position = position; }
	// Set the bounding box rotation.
	void SetRotation(float rotation) { m_Rotation = rotation; }
	// Set the collision side.
	void SetCollisionSide(COLLISION_SIDE side) { m_CollisionSide = side; }
	// Get the bounding box show.
	bool GetShowBoundingBox() { return m_ShowBoundingBox; }
	// Get the bounding box colour.
	Color& GetBoundingBoxColor() { return m_BoundingBoxColor; }
	// Get the bounding box size.
	Vector2<float>& GetSize() { return m_Size; }
	// Get the bounding box position.
	Vector2<float>& GetPosition() { return m_Position; }
	// Get the bounding box rotation.
	float GetRotation() { return m_Rotation; }
	// Get the collision side.
	COLLISION_SIDE& GetCollisionSide() { return m_CollisionSide; }

	BoundingBoxComponent() {}
	BoundingBoxComponent(Vector2<float> position, Vector2<float> size) : m_Position(position), m_Size(size) {}
};