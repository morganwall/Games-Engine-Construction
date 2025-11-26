#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include "Component.h"
#include "../../Texture2D.h"

class SpriteComponent : public Component
{
	sf::Sprite m_Sprite; // SFML sprite. TODO: Replace with something other than SFML sprite.
	Texture2D* m_Texture{ nullptr }; // Pointer to the texture.

public:
	// Set the sprite's texture.
	void SetTexture(Texture2D& texture)
	{
		m_Texture = &texture; // Set the texture.
		m_Sprite.setTexture(m_Texture->GetSFTexture()); // Sets the sprite's texture, with the sf::texture stored within the Texture2D.
	}
	// Gets the SFML sprite.
	sf::Sprite& GetSprite() { return m_Sprite; }
	// Gets the texture.
	Texture2D& GetTexture() { return *m_Texture; }

	SpriteComponent() {}
	// Constructor. Takes in a Texture2D, that can be gotten by doing TextureManager.GetTexture2D(textureKey).
	SpriteComponent(Texture2D& texture)
	{
		m_Texture = &texture; // Set the texture.
		SetTexture(*m_Texture); // Sets the sprite's texture, with the sf::texture stored within the Texture2D.
	}
};