#include "CollisionSystem.h"
#include <iostream>
#include "../ECSManager.h"
#include "../../ShapeRenderer2D.h"

void CollisionSystem::Update(float deltaTime)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		TransformComponent& transform1{ m_ECS.GetComponent<TransformComponent>(curEntity) }; // Get the current entity's transform component.
		BoundingBoxComponent& boundingBox1{ m_ECS.GetComponent<BoundingBoxComponent>(curEntity) }; // Get the current entity's bounding box component.
		SpriteComponent& sprite1{ m_ECS.GetComponent<SpriteComponent>(curEntity) }; // Get the current entity's sprite component.

		boundingBox1.SetPosition(transform1.GetPosition()); // Make sure the bounding box stays with the entity.
		boundingBox1.SetSize
		(
			{
				sprite1.GetTexture().GetSize().x * transform1.GetScale().x,
				sprite1.GetTexture().GetSize().y * transform1.GetScale().y
			}
		); // Make sure the bounding box is the same size as the sprite.
		boundingBox1.SetRotation(transform1.GetRotation()); // Make sure the bounding box is the same rotation as the sprite. TODO: Fix this.

		if (m_Entities.size() == 1) // If there's only one entity within the system, return, as there's no possible collisions.
			return;

		for (EntityID otherEntity : m_Entities) // Loop through the entities again, as we need two entities to check for collision.
		{
			if (curEntity == otherEntity) // Skip the current check if the two entities are the same.
				continue;

			TransformComponent& transform2{ m_ECS.GetComponent<TransformComponent>(otherEntity) }; // Get the other entity's transform component.
			BoundingBoxComponent& boundingBox2{ m_ECS.GetComponent<BoundingBoxComponent>(otherEntity) }; // Get the other entity's bounding box component.


			boundingBox2.SetPosition(transform2.GetPosition()); // Make sure the bounding box stays with the entity. TODO: Add an optional offset to this.
			COLLISION_SIDE collision{ Box(boundingBox1, boundingBox2) }; // Check for collision between the two bounding boxes.
			
			switch (collision) // Switch on collision side.
			{
			case COLLISION_TOP:
				transform1.SetPosition({ transform1.GetPosition().x, transform2.GetPosition().y - boundingBox1.GetSize().y });
				boundingBox1.SetCollisionSide(COLLISION_TOP);
				break;
			case COLLISION_BOTTOM:
				transform1.SetPosition({ transform1.GetPosition().x, transform2.GetPosition().y + boundingBox2.GetSize().y });
				boundingBox1.SetCollisionSide(COLLISION_BOTTOM);
				break;
			case COLLISION_LEFT:
				transform1.SetPosition({ transform2.GetPosition().x - boundingBox1.GetSize().x, transform1.GetPosition().y });
				boundingBox1.SetCollisionSide(COLLISION_LEFT);
				break;
			case COLLISION_RIGHT:
				transform1.SetPosition({ transform2.GetPosition().x + boundingBox2.GetSize().x, transform1.GetPosition().y });
				boundingBox1.SetCollisionSide(COLLISION_RIGHT);
				break;

			default: // No collision.
				boundingBox1.SetCollisionSide(COLLISION_NONE);
				break;
			}
		}
	}
}

void CollisionSystem::Draw()
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		BoundingBoxComponent& boundingBox{ m_ECS.GetComponent<BoundingBoxComponent>(curEntity) }; // Get the current entity's bounding box component.

		if (boundingBox.GetShowBoundingBox()) // Check if we should show the bounding box.
			DrawBoundingBox(curEntity); // Draw the bounding box.
	}
}

COLLISION_SIDE CollisionSystem::Box(BoundingBoxComponent& box1, BoundingBoxComponent& box2)
{
	// Get the positions and sizes of the boxes.
	Vector2<float> box1Pos{ box1.GetPosition() };
	Vector2<float> box2Pos{ box2.GetPosition() };
	Vector2<float> box1Size{ box1.GetSize() };
	Vector2<float> box2Size{ box2.GetSize() };

	// Rather than checking first if the object is colliding, and then calculating which collision is the shortest, we can just calculate the overlap and then check if it's less than 0.
	// If they're all less than 0, then there's no overlap. If at least one of the side overlaps are greater than 0, then there's an overlap, and the smallest value is the side that's overlapping.
	float topOverlap{ (box1Pos.y + box1Size.y) - box2Pos.y };
	float bottomOverlap{ (box2Pos.y + box2Size.y) - box1Pos.y };
	float leftOverlap{ (box1Pos.x + box1Size.x) - box2Pos.x };
	float rightOverlap{ (box2Pos.x + box2Size.x) - box1Pos.x };

	if (topOverlap < 0 || bottomOverlap < 0 || leftOverlap < 0 || rightOverlap < 0) // All side overlaps are less than 0, meaning no collision.
		return COLLISION_NONE;

	float smallest{ std::min({topOverlap, bottomOverlap, leftOverlap, rightOverlap}) }; // Find the smallest overlap. The smallest value is the side that is overlapping.
	if (smallest == topOverlap)
		return COLLISION_TOP;
	if (smallest == bottomOverlap)
		return COLLISION_BOTTOM;
	if (smallest == leftOverlap)
		return COLLISION_LEFT;
	if (smallest == rightOverlap)
		return COLLISION_RIGHT;

	return COLLISION_NONE;
}

void CollisionSystem::DrawBoundingBox(EntityID entity)
{
	BoundingBoxComponent& boundingBox{ m_ECS.GetComponent<BoundingBoxComponent>(entity) }; // Get the entity's bounding box component.

	// Create Shape Renderer.
	ShapeRenderer2D shapeRenderer{ m_Window };

	// Create Bounding Box Outline with Lines.
	shapeRenderer.DrawLine
	(
		{ boundingBox.GetPosition().x, boundingBox.GetPosition().y }, 
		{ boundingBox.GetPosition().x + boundingBox.GetSize().x, boundingBox.GetPosition().y }, boundingBox.GetBoundingBoxColor()
	); // Top line.
	shapeRenderer.DrawLine
	(
		{ boundingBox.GetPosition().x, boundingBox.GetPosition().y + boundingBox.GetSize().y },
		{ boundingBox.GetPosition().x + boundingBox.GetSize().x, boundingBox.GetPosition().y + boundingBox.GetSize().y }, boundingBox.GetBoundingBoxColor()
	); // Bottom line.
	shapeRenderer.DrawLine
	(
		{ boundingBox.GetPosition().x, boundingBox.GetPosition().y },
		{ boundingBox.GetPosition().x, boundingBox.GetPosition().y + boundingBox.GetSize().y }, boundingBox.GetBoundingBoxColor()
	); // Left line.
	shapeRenderer.DrawLine
	(
		{ boundingBox.GetPosition().x + boundingBox.GetSize().x, boundingBox.GetPosition().y },
		{ boundingBox.GetPosition().x + boundingBox.GetSize().x, boundingBox.GetPosition().y + boundingBox.GetSize().y }, boundingBox.GetBoundingBoxColor()
	); // Right line.
}