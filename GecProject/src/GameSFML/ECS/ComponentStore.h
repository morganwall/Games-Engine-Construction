#pragma once
#include <unordered_map>
#include "Entity.h"

using ComponentID = uint8_t;

class BaseComponentStore
{
public:
	virtual void Remove(EntityID entityID) = 0; // Define the Remove function as a pure virtual function, so that it can be called outside of the class.
	virtual bool Has(EntityID entityID) = 0; // Define the Has function as a pure virtual function, so that it can be called outside of the class.

	virtual ~BaseComponentStore() {}
};

// Stores all components of the same type.
template <class T>
class ComponentStore : public BaseComponentStore
{
	std::unordered_map<EntityID, T> m_Components; // Stores all of the components, with their entityID as the key.

public:
	// Add a component to the map, with the entityID as the key.
	void Add(EntityID entityID, const T& component)
	{
	#ifdef _DEBUG // Check if we're in debug.
		assert(m_Components.find(entityID) == m_Components.end() && "The Entity Already has the Component!"); // Check that the entity doesn't have the component, by checking that we're at the end of the map.
	#endif // _DEBUG

		m_Components[entityID] = component; // Add the component to the map, with the entityID as the key.
	}

	// Remove a component from the map.
	void Remove(EntityID entityID) override
	{
	#ifdef _DEBUG // Check if we're in debug.
		assert(m_Components.find(entityID) != m_Components.end() && "The Entity does not have the Compnent!"); // Check that the entity has the component, by checking that we're not at the end of the map.
	#endif // _DEBUG

		m_Components.erase(entityID); // Remove the entry with the entityID key.
	}

	// Get a component from the map.
	T& Get(EntityID entityID)
	{
	#ifdef _DEBUG // Check if we're in debug.
		assert(m_Components.find(entityID) != m_Components.end() && "The Entity does not have the Compnent!"); // Check that the entity has the component, by checking that we're not at the end of the map.
	#endif // _DEBUG

		return m_Components[entityID]; // Return the component with the entityID.
	}

	// Check if an entity has a component.
	bool Has(EntityID entityID) override
	{
		return m_Components.find(entityID) != m_Components.end(); // Check if the entity has the component.
	}
};