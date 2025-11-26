#include "InputSystem.h"
#include <iostream>
#include "../ECSManager.h"

void InputSystem::MouseButtonDown(const sf::Event::MouseButtonEvent& event)
{
	switch (event.button) // Switch on the button pressed.
	{
	case sf::Mouse::Left:
	#ifdef _DEBUG
		std::cout << "Left Mouse Button Down (x: " << event.x << ", y: " << event.y << ")\n";
	#endif // _DEBUG

		for (EntityID curEntity : m_Entities) // Loop through all of the system entities.
		{
			if (m_ECS.HasComponent<GridComponent>(curEntity)) // Check if the current entity has a grid component.
			{
				GridSystem& gridSystem{ m_ECS.GetSystem<GridSystem>() }; // Get the grid system.
				gridSystem.OnLeftClick({ event.x, event.y }); // Call OnLeftClick from the grid.
			}
		}
		break;
	case sf::Mouse::Right:
	#ifdef _DEBUG
		std::cout << "Right Mouse Button Down (x: " << event.x << ", y: " << event.y << ")\n";
	#endif // _DEBUG

		for (EntityID curEntity : m_Entities) // Loop through all of the system entities.
		{
			if (curEntity == m_ECS.GetPlayerEntity()) // Check if the current entity is the player.
			{
				MovementComponent& movement{ m_ECS.GetComponent<MovementComponent>(curEntity) }; // Get the movement component of the player.
				PhysicsComponent& physics{ m_ECS.GetComponent<PhysicsComponent>(curEntity) }; // Get the physics component of the player.
				SpriteComponent& sprite{ m_ECS.GetComponent<SpriteComponent>(curEntity) }; // Get the sprite component of the player.
				Vector2<float> spriteSize{ sprite.GetTexture().GetSize().x * sprite.GetSprite().getScale().x, sprite.GetTexture().GetSize().y * sprite.GetSprite().getScale().y }; // Size of the sprite.

				movement.SetDestination({ float(event.x - (spriteSize.x / 2.0f)), float(event.y - spriteSize.y / 2.0f) }); // Set the destination.
			}
		}
		break;

	default:
		break;
	}
}

void InputSystem::MouseButtonUp(const sf::Event::MouseButtonEvent& event)
{
	switch (event.button) // Switch on the button released.
	{
	case sf::Mouse::Left:
	#ifdef _DEBUG
		std::cout << "Left Mouse Button Up (x: " << event.x << ", y: " << event.y << ")\n";
	#endif // _DEBUG
		break;
	case sf::Mouse::Right:
	#ifdef _DEBUG
		std::cout << "Right Mouse Button Up (x: " << event.x << ", y: " << event.y << ")\n";
	#endif // _DEBUG
		break;

	default:
		break;
	}
}