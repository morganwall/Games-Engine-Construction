#include "ShapeRenderer2D.h"

void ShapeRenderer2D::DrawRectangle(Vector2<float> position, Vector2<float> size, Color colour)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(position.x, position.y);
	rectangle.setSize(sf::Vector2f(size.x, size.y));
	rectangle.setFillColor(colour);

	m_Window.GetSFWindow().draw(rectangle);
}

void ShapeRenderer2D::DrawCircle(Vector2<float> position, float radius, Color colour)
{
	sf::CircleShape circle;
	circle.setPosition(position.x, position.y);
	circle.setRadius(radius);
	circle.setFillColor(colour);
	m_Window.GetSFWindow().draw(circle);
}

void ShapeRenderer2D::DrawLine(Vector2<float> start, Vector2<float> end, Color colour)
{
	// Create vertex array.
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(start.x, start.y), colour),
		sf::Vertex(sf::Vector2f(end.x, end.y), colour)
	};

	m_Window.GetSFWindow().draw(line, 2, sf::Lines);
}