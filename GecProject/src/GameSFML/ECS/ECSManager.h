#pragma once
#include <queue>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <typeindex> // https://cplusplus.com/reference/typeindex/type_index/
#include <functional> // Used for std::function.
#include "Entity.h"
#include "ComponentStore.h"

#include "Components/Component.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/MovementComponent.h"
#include "Components/BoundingBoxComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/GridComponent.h"
#include "Components/InputComponent.h"

#include "Systems/System.h"
#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/GridSystem.h"

class ECSManager // Manages creation, destruction, and interaction with entities and components. This class probably could've been split into three different classes.
{
	std::queue<EntityID> m_InactiveEntityIDs{}; // A queue of all currently inactive entity IDs. Using a queue, as both pop and push operations are really fast.
										  // Inactive IDs are added when active entities are destroyed.
	std::vector<Entity> m_Entities{}; // A vector of the entities. Using a vector, as they're contiguous, which makes them better for caching.
	size_t m_NumActiveEntities{ 0 }; // The number of currently active entities.
	EntityID m_PlayerEntity{ 0 }; // The player entity. Just an easier way to keep track of which entity is the player. Should hopefully just be 0 anyway.

	ComponentID m_NumActiveComponents{ 0 }; // The number of active components. Used for getting the next component ID.
	std::unordered_map<std::type_index, BaseComponentStore*> m_ComponentStores; // A map off all the component stores. Using type_index as the key, as it's the best way to get the different class types here.
	std::unordered_map<std::type_index, ComponentID> m_ComponentIDs; // A map of all the componentIDs, with the component type as the key.

	std::unordered_map<std::type_index, System*> m_Systems; // A map of all the systems, with the system type as key.

	// Get the ComponentStore for a specific type.
	template <class T>
	ComponentStore<T>* GetComponentStore()
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the type of the ComponentStore. Needed as m_ComponentStores is a map of the base class.

	#ifdef _DEBUG
		assert(m_ComponentStores.find(type) != m_ComponentStores.end() && "No ComponentStore for the given Type!"); // Check that there's a store for the current type.
	#endif

		return static_cast<ComponentStore<T>*>(m_ComponentStores[type]); // Static cast the ComponentStore from the base class, to the correct class, and then return it. Needed due to the map using the base class.
	}

	// When an Entity's ComponentIDs signature changes, check if it needs to be added to any systems.
	void EntityComponentsChanged(EntityID entityID);

public:
	std::unordered_map<std::type_index, std::function<Component& (EntityID)>> m_ComponentGetters; // A map of all the component getters. // TODO: Make this private and add a getter.

	// Creates and adds a new entity.
	EntityID NewEntity();
	// Removes and destroys an entity. Takes in the ID of the target entity.
	void RemoveEntity(EntityID id);
	// Gets an entity by it's ID.
	Entity& GetEntity(EntityID id)
	{
	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(id < m_Entities.size() && "Invalid ID!"); // Check that id is valid.
	#endif // _DEBUG

		return m_Entities[id];
	}
	// Get the number of active entities.
	size_t GetNumEntities() { return m_NumActiveEntities; }
	// Get the player entity.
	EntityID GetPlayerEntity() { return m_PlayerEntity; }
	// Set the player entity.
	void SetPlayerEntity(EntityID id) { m_PlayerEntity = id; }

	// Create a new component. Also creates a new ComponentStorage for it.
	template <class T>
	void NewComponent()
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the type of the new component. Used as the key in the map later.

	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(m_ComponentStores.find(type) == m_ComponentStores.end() && "The given Component Type Already Exists!"); // Check that the new type doesn't already exist, by checking if it already has a ComponentStore.
	#endif // _DEBUG
		m_ComponentStores[type] = new ComponentStore<T>(); // Create a new ComponentStore, with the template, and add it to the map.

	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(m_ComponentIDs.find(type) == m_ComponentIDs.end() && "The given Component Type Already Exists!"); // Check that the new type doesn't already exist, by checking if it already has a ComponentStore.
	#endif // _DEBUG
		m_ComponentIDs[type] = m_NumActiveComponents++; // Add the new component type to the ID map, along with the next ID.

		// Initialize the component getter.
		m_ComponentGetters[type] = [this](EntityID entityID)->Component& // Lambda function. Lambda functions are used to create anonymous functions.
		{																 // I've never really used them, but it's the only solution I could find to my issue.
			return this->GetComponent<T>(entityID);
		};
	}
	// Add a component to an entity.
	template <class T>
	void AddComponent(EntityID entityID, T component)
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the type of the component that we're adding.

	#ifdef _DEBUG // Check that we're in Debug mode.
		assert(m_ComponentIDs.find(type) != m_ComponentIDs.end() && "Invalid Component!"); // Check that the component exists.
	#endif // _DEBUG

		Entity& curEntity{ GetEntity(entityID) }; // Get the current entity.
		curEntity.SetComponentBit(m_ComponentIDs[type], true); // Set the component bit, the same as the ID, to true.

		EntityComponentsChanged(entityID); // Update the entity with all the systems.

		GetComponentStore<T>()->Add(entityID, component); // Add the new component to the ComponentStore.
	}
	// Remove a component from an entity.
	template <class T>
	void RemoveComponent(EntityID entityID)
	{
		std::type_index type{ GetEntity(entityID) }; // Get the type of the component that we're removing.

	#ifdef _DEBUG // Check that we're in Debug mode.
		assert(m_ComponentIDs.find(type) != m_ComponentIDs.end() && "Invalid Component!"); // Check that the component exists.
	#endif // _DEBUG

		Entity& curEntity{ GetEntity(entityID) }; // Get the current entity.
		curEntity.SetComponentBit(m_ComponentIDs[type], false); // Set the component bit to false.

		EntityComponentsChanged(entityID);

		GetComponentStore<T>()->Remove(entityID);
	}
	// Check if an entity has a compnent.
	template <class T>
	bool HasComponent(EntityID entityID)
	{
		return GetComponentStore<T>()->Has(entityID); // Check if the entity has a specific component within the ComponentStores.
	}
	// Get an entity's component.
	template <class T>
	T& GetComponent(EntityID entityID)
	{
		return GetComponentStore<T>()->Get(entityID); // Return an entity's component from the ComponentStores.
	}
	// Get a component's ID.
	template <class T>
	ComponentID GetComponentID()
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the Component's type.

	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(m_ComponentIDs.find(type) != m_ComponentIDs.end() && "Invalid Component Type!"); // Check that the component type is valid.
	#endif // _DEBUG

		return m_ComponentIDs[type]; // Return the component's ID.
	}
	// Get a component's signature.
	template <class T>
	Signature GetComponentSignature()
	{
		ComponentID curID{ GetComponentID<T>() }; // Get the ID of the current component.

		Signature curSignature; // Create a new signature.
		return curSignature.set(curID, true); // Set the bit, which is at the index of the curID, to true. Then return the new signature.
	}
	// Get component type from ID.
	std::type_index GetComponentType(ComponentID id)
	{
		for (auto& entry : m_ComponentIDs) // Loop through all of the component IDs.
		{
			if (entry.second == id) // Check that the IDs match.
				return entry.first; // Return the type of the component.
		}

		return std::type_index(typeid(void)); // Return void if the component ID isn't found.
	}
    // Get component type, from the ID, and return it as a string.
    std::string GetComponentTypeString(ComponentID id)
    {
		std::string typeString{ GetComponentType(id).name() }; // Get the component type as a string.
		const std::string prefix = "class "; // The prefix that we want to remove from the string.

		return typeString.substr(prefix.length()); // Return the type string, with the prefix removed.
    }

	// Create a new system.
	template <class T, class... Args>
	void NewSystem(Args&&... args)
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the type of the new system. Used as the key in the map later.

	#ifdef _DEBUG // Check if we're in Debug mode.
		assert(m_Systems.find(type) == m_Systems.end() && "The given System Type Already Exists!"); // Check that the system doesn't already exist.
	#endif // _DEBUG

		m_Systems[type] = new T(std::forward<Args>(args)...); // Add the next system to the Systems map, with the system type as the key. Pass args with std::forward.
	}
	// Get a reference to a system from the map.
	template <class T>
	T& GetSystem()
	{
		std::type_index type{ std::type_index(typeid(T)) }; // Get the type of the system.

	#ifdef _DEBUG // Check that we're in Debug mode.
		assert(m_Systems.find(type) != m_Systems.end() && "Invalid System!"); // Check that the system is valid.
	#endif // _DEBUG

		return *static_cast<T*>(m_Systems[type]); // Have to static_cast here, as all systems are stored with the base class in the map.
	}

	ECSManager();
	~ECSManager()
	{
		// Cleanup all ComponentStores.
		for (auto& entry : m_ComponentStores) // Loop through all of the ComponentStores.
			delete entry.second; // Delete the ComponentStore.
		m_ComponentStores.clear(); // Clear the map.

		// Cleanup all Systems.
		for (auto& entry : m_Systems) // Loops through all of the Systems.
			delete entry.second; // Delete the System.
		m_Systems.clear();
	}
};