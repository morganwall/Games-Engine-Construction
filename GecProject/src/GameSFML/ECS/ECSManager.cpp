#include "ECSManager.h"

void ECSManager::EntityComponentsChanged(EntityID entityID)
{
	const Signature& curSignature{ GetEntity(entityID).GetComponents() }; // Get a reference to the entity's signature.

	for (auto& entry : m_Systems) // Loop through all of the Systems.
	{
		System* curSystem{ entry.second }; // The current system pointer.
		const Signature& curSystemSignature{ curSystem->GetSignature() }; // Get the signature of the current system.
		
																	   // Use Bitwise AND to check that the entity signature has the required
																	   // system signature bits. Then check the result of the AND, is equal to
		if ((curSignature & curSystemSignature) == curSystemSignature) // the system's signature.
			curSystem->AddEntity(entityID); // Add the entity to the System's entity vector.
		else // If the system doesn't, or no longer matches the system's signature.
			curSystem->RemoveEntity(entityID); // Remove the entity from the System's entity vector.
	}
}

EntityID ECSManager::NewEntity()
{
	EntityID curID; // Will store the ID we'll return.

	if (!m_InactiveEntityIDs.empty()) // Check if we have any inactive IDs.
	{
		curID = m_InactiveEntityIDs.front(); // Get the first ID from the queue.
		m_InactiveEntityIDs.pop(); // Remove the ID we just got, from the queue.
	}
	else // If we don't have any inactive IDs.
	{
		curID = EntityID(m_Entities.size()); // Creates a new ID based on the current size of the entity vector.
		m_Entities.push_back(Entity{ curID }); // Push a new entity, with the new ID, to the back of the entity vector.
	}

	m_NumActiveEntities++; // Increase the number of active entities.
	return curID; // Return the ID of the newly created entity.
}

void ECSManager::RemoveEntity(EntityID entityID)
{
#ifdef _DEBUG // Check if we're in Debug mode.
	assert(entityID < m_Entities.size() && "Invalid ID!"); // Check that id is valid.
#endif // _DEBUG

	for (auto& curCompStore : m_ComponentStores) // Loop through all componentStores for the current entity.
	{
		if (curCompStore.second->Has(entityID)) // Check if the entity has the current component.
			curCompStore.second->Remove(entityID); // Remove the entity's components from the component store.
	}

	m_InactiveEntityIDs.push(entityID); // Push id to the inactiveEntityIDs queue.
	m_Entities[entityID].SetComponents(Signature()); // Reset the component bitset signature.
	EntityComponentsChanged(entityID); // Update all systems, making sure that the entity gets removed from their entity vectors.

	m_NumActiveEntities--; // Decrease the number of active entities.
}

ECSManager::ECSManager()
{

}