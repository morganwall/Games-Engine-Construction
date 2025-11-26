#include "RenderSystem.h"
#include "../ECSManager.h"

void RenderSystem::Update(float deltaTime)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		TransformComponent& transform{ m_ECS.GetComponent<TransformComponent>(curEntity) }; // Get the current entity's transform component.
		SpriteComponent& sprite{ m_ECS.GetComponent<SpriteComponent>(curEntity) }; // Get the current entity's sprite component.

		sprite.GetSprite().setPosition(transform.GetPosition().x, transform.GetPosition().y); // Update the sprite with the entity's transform position.
		sprite.GetSprite().setRotation(transform.GetRotation()); // Update the sprite with the entity's transform rotation.
		sprite.GetSprite().setScale(transform.GetScale().x, transform.GetScale().y); // Update the sprite with the entity's transform scale.
	}
}

void RenderSystem::Draw()
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		SpriteComponent& sprite{ m_ECS.GetComponent<SpriteComponent>(curEntity) }; // Get the current entity's sprite component.
		m_Window.GetSFWindow().draw(sprite.GetSprite()); // Draw the sprite.
	}
}