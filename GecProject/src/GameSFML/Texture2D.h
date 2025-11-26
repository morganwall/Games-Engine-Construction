#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Texture2D
{
	Vector2<unsigned int> m_Size{ 32, 32 }; // The texture size.
	sf::Texture m_SFTexture; // The SFML texture.

public:
	// Returns the texture size.
	Vector2<unsigned int> GetSize() { return m_Size; }
	// Returns the sf::Texture.
	sf::Texture& GetSFTexture() { return m_SFTexture; }
	// Sets the sf::Texture.
	void SetSFTexture(sf::Texture texture) { m_SFTexture = texture; }
	// Sets the texture size.
	void SetSize(Vector2<unsigned int> size) { m_Size = size; }

	// Constructor.
	Texture2D() {}
	// Destructor.
	~Texture2D() {}
};