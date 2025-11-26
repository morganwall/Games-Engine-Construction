#pragma once
#include <imgui.h>
#include <SFML/Graphics/Color.hpp>

// Stores all information for a colour.
class Color
{
public:
	float r{ 0.0f }, g{ 0.0f }, b{ 0.0f }, a{ 0.0f };

	// Convert from Color to an ImVec4.
	operator ImVec4()
	{
		return ImVec4(r, g, b, a);
	}
	// Convert from Color to float*.
	operator float* ()
	{
		return &r;
	}
	// Convert from Color to sf::Color.
	operator sf::Color()
	{
		return sf::Color(255 * int(r), 255 * int(g), 255 * int(b), 255 * int(a)); // Multiplying by 255, as sf::color uses ints and not floats.
	}

	Color() {}
	Color(float R, float G, float B, float A) : r(R), g(G), b(B), a(A) {}
	~Color () {}
};