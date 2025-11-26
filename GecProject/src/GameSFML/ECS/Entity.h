#pragma once
#include <cstdint>
#include <bitset>
#include <cassert>
#include <limits.h>

const uint8_t MAX_COMPONENTS{ 64 }; // The max number of components that a single entity can have. 64 is close to the most I can do.
using Signature = std::bitset<MAX_COMPONENTS>; // Bitset signature, with the max size being the max number of components an entity can have.
using EntityID = uint16_t; // uint16_t gives a max value of 65535, which should be enough entities for my game engine.

class Entity
{
	EntityID m_ID{ 0 }; // The entity's ID.
	std::bitset<MAX_COMPONENTS> m_Components{}; // A bitset signature of the components that the current entity has.

public:
	// Return the bitset signature of the entity's current components.
	Signature GetComponents() { return m_Components; }
	// Set the entity ID.
	void SetID(EntityID id) 
	{
	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(id < std::numeric_limits<EntityID>::max() && "ID is Greater than Max!"); // Check that the ID doesn't exceed the max;
	#endif // _DEBUG
		m_ID = id;
	}
	// Set a single bit in the component bitset signature.
	void SetComponentBit(int index, bool value)
	{
	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(index < MAX_COMPONENTS && "Invalid Index!"); // Check that the index is valid.
	#endif // _DEBUG
		m_Components.set(index, value);
	}
	// Set the entire component bitset signature.
	void SetComponents(Signature components) { m_Components = components; }

	Entity() {}
	Entity(EntityID id) : m_ID(id) {}
	~Entity() {}
};