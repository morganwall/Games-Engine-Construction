#include "AnimationSystem.h"
#include "../ECSManager.h"

void AnimationSystem::Update(float deltaTime)
{
	for (EntityID curEntity : m_Entities) // Loop through all the system's entities.
	{
		// Get components.
		AnimationComponent& animation{ m_ECS.GetComponent<AnimationComponent>(curEntity) }; // Get the current entity's animation component.
		if (!animation.GetEnabled()) // Check if the animation is enabled.
			continue; // If it isn't, continue.

		SpriteComponent& sprite{ m_ECS.GetComponent<SpriteComponent>(curEntity) }; // Get the current entity's sprite component.

		// Check that the animation has frames.
		if (animation.GetFrames().empty()) // Check if the animation has no frames.
		{
			animation.SetEnabled(false); // Disable the animation.
			continue; // Continue if there are no frames.
		}

		// Reset frame counter if needed.
		if (animation.GetCurrentFrame() >= animation.GetNumFrames()) // Check if we're already at the last frame.
		{
			animation.SetCurrentFrame(0); // Reset the frame counter.

			// Check if the animation should loop.
			if (!animation.GetLoop())
				animation.SetEnabled(false); // Disable the animation if it shouldn't loop.
		}

		// Update the texture.
		sprite.SetTexture(*animation.GetFrames()[animation.GetCurrentFrame()]); // Set the sprite's texture to the current frame's texture.

		// Update the timer.
		animation.SetTimer(animation.GetTimer() + deltaTime); // Increment the timer.
		if (animation.GetTimer() < animation.GetUpdateDelay() / 1000.0f) // Check if we've not passed the update interval. Divide by 1000 to convert from milliseconds to seconds.
			continue; // Continue if we haven't passed the update interval.

		animation.SetTimer(0.0f); // Reset the timer.
		animation.SetCurrentFrame(animation.GetCurrentFrame() + 1); // Increment the frame counter.
	}
}