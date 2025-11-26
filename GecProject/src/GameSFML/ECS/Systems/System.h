#pragma once
#include <vector>
#include "../Entity.h"

class ECSManager; // ECSManager forward declaration.

class System // Base system class.
{
protected:
	Signature m_Signature; // A signature of the components needed for an entity to use this system.
	std::vector<EntityID> m_Entities; // A vector of all entities that have this system.

public:
	// Add an entity, to the entities vector, to be processed by the system.
	void AddEntity(EntityID entityID)
	{
		m_Entities.push_back(entityID); // Push the entityID to the back of the vector.
	}
	// Remove an entity from the entities vector.
	void RemoveEntity(EntityID entityID)
	{
		m_Entities.erase(
			std::remove(m_Entities.begin(), m_Entities.end(), entityID), // std::remove moves all entities, with entityID, to the end of the vector.
			m_Entities.end()
		); // Remove entities with entityID from the vector.
	}
	// Set the system's signature.
	void SetSignature(Signature signature)
	{
		m_Signature = signature;
	}
	// Get a reference to the system's signature.
	Signature& GetSignature()
	{
		return m_Signature;
	}

	virtual ~System() {}
};