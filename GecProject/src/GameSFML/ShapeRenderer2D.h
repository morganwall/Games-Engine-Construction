#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Color.h"
#include "Window.h"

class ShapeRenderer2D
{
	Window& m_Window; // Reference to the window.

public:
	// Draw a rectangle.
	void DrawRectangle(Vector2<float> position, Vector2<float> size, Color colour);
	// Draw a circle.
	void DrawCircle(Vector2<float> position, float radius, Color colour);
	// Draw a line.
	void DrawLine(Vector2<float> start, Vector2<float> end, Color colour);

	ShapeRenderer2D(Window& window) : m_Window(window) {};
};