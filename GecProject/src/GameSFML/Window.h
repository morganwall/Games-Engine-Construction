#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Color.h"

class Window
{
	// Window Information.
	sf::RenderWindow m_Window; // The SFML render window.
	std::string m_Title{ "Main Window" }; // The window title.
	Vector2<unsigned int> m_Size{ 1280, 720 }; // The window size.

	// DeltaTime.
	sf::Clock m_DeltaTimeClock{}; // Clock used for calculating delta time.
	float m_DeltaTime{ 0.0f }; // Delta Time.

public:
	// Initialise the window variables and create the sfml render window.
	bool Init(const std::string& title = std::string("Main Window"), const Vector2<unsigned int>& size = {1280, 720})
	{
		m_Title = title;
		m_Size = size;

		m_Window.create(sf::VideoMode(m_Size.x, m_Size.y), m_Title); // Create the sfml render window.

		return true;
	}
	// Display to the window.
	void Display()
	{
		m_Window.display();
	}
	// Clears the window.
	void Clear(const Color& clearColor = { 0.0f, 0.0f, 0.0f, 1.0f })
	{
		// Convert the Color from Float to Int.
		sf::Color sfColor
		{
			static_cast<sf::Uint8>(255 * clearColor.r), static_cast<sf::Uint8>(255 * clearColor.g), 
			static_cast<sf::Uint8>(255 * clearColor.b), static_cast<sf::Uint8>(255 * clearColor.a)
		};

		m_Window.clear(sfColor);
	}
	// Check if the window is open.
	bool IsOpen()
	{
		return m_Window.isOpen();
	}
	// Close the window.
	void Close()
	{
		m_Window.close();
	}
	// Update deltaTime.
	void Update()
	{
		m_DeltaTime = m_DeltaTimeClock.restart().asSeconds(); // This will give us the elapsed time, and will reset the clock.
	}

	// Get the SFML Render Window.
	sf::RenderWindow& GetSFWindow()
	{
		return m_Window;
	}
	// Return deltaTime.
	float& GetDeltaTime()
	{
		return m_DeltaTime;
	}

	Window() {}
	~Window() {}
};