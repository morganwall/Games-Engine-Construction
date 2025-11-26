#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ECS/Systems/InputSystem.h"

class EventHandler
{
    Window* m_Window{ nullptr }; // Window pointer.
    sf::Event m_CurrentEvent{}; // The current SFML window event.
	InputSystem* m_InputSystem{ nullptr }; // Input system pointer.

public:
	// Process SFML and ImGui Events. Returns False by Default, and True to Exit.
	bool Process()
	{
        sf::RenderWindow* sfWindow{ &m_Window->GetSFWindow() }; // Get the SFML Window.

        // Poll Event.
        while (sfWindow->pollEvent(m_CurrentEvent)) // Loop while we have polled events to process.
        {
            // Process ImGui Events.
            ImGui::SFML::ProcessEvent(*sfWindow, m_CurrentEvent);

            // Process SFML Events.
            switch (m_CurrentEvent.type) // Switch on the event type.
            {
            case sf::Event::Closed:
                return true;

            case sf::Event::MouseButtonPressed: // Mouse button pressed.
				m_InputSystem->MouseButtonDown(m_CurrentEvent.mouseButton);
				break;
			case sf::Event::MouseButtonReleased: // Mouse button released.
				m_InputSystem->MouseButtonUp(m_CurrentEvent.mouseButton);
				break;

            default:
                break;
            }
        }

        return false;
	}
    // Initialise the Event Handler.
    bool Init(Window* window, InputSystem* inputSystem)
    {
        m_Window = window;
		m_InputSystem = inputSystem;

        return true;
    }

	EventHandler() {}
    ~EventHandler() {}
};