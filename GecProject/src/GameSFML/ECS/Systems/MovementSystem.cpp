#include "MovementSystem.h"
#include "../ECSManager.h"

void MovementSystem::Update(float deltaTime)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		MoveTo(curEntity, deltaTime); // Move the entity to the destination.
	}
}

void MovementSystem::MoveTo(EntityID& curEntity, float deltaTime)
{
	PhysicsComponent& physics{ m_ECS.GetComponent<PhysicsComponent>(curEntity) }; // Get the current entity's physics component.
	TransformComponent& transform{ m_ECS.GetComponent<TransformComponent>(curEntity) }; // Get the current entity's transform component.
	MovementComponent& movement{ m_ECS.GetComponent<MovementComponent>(curEntity) }; // Get the current entity's movement component.

	// Get the direction and distance to the destination.
	Vector2<float> direction{ movement.GetDestination() - transform.GetPosition() };
	float distance{ direction.Length() };

	if (distance > movement.GetMarginOfError()) // Check if we've reached the destination.
	{
		direction = direction.FastNormalize(); // Normalize the direction vector.
		Vector2<float> requiredVelocity{ direction * distance }; // Calculate the required velocity to travel towards the destination.

		transform.SetPosition
		(
			{
				transform.GetPosition().x += requiredVelocity.x * deltaTime,
				transform.GetPosition().y += requiredVelocity.y * deltaTime
			}
		); // Set the entity's position.
	}
	else
	{
		physics.SetVelocity({ 0.0f, 0.0f }); // Remove all velocity as we've reached the destination.
		transform.SetPosition(movement.GetDestination()); // Set the entity's position to the destination.
	}
}