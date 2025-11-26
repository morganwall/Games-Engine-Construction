#pragma once
#include "Vector2.h"

// Not Used Yet. Just made for the ICA Specification.
class Rect
{
	Vector2<float> m_Position;
	Vector2<float> m_Size;

public:
	// Get position.
	Vector2<float>& GetPosition() { return m_Position; }
	// Get size.
	Vector2<float>& GetSize() { return m_Size; }
	// Set position.
	void SetPosition(Vector2<float> position) { m_Position = position; }
	// Set size.
	void SetSize(Vector2<float> size) { m_Size = size; }

	Rect() {}
	Rect(Vector2<float>& position, Vector2<float>& size) : m_Position(position), m_Size(size) {}
};