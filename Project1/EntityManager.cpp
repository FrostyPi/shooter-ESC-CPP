#include "EntityManager.h"
#include <iostream>
//1:00:14
EntityManager::EntityManager()
{

}

void EntityManager::update()
{
	//TODO: add entities from m_entitiesToAdd to the proper location(s)
	//		- add them to the vector of all entities //
	//		- add them to the vector inside the map, with the tag as a key
	for (auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);

		//if key doesn't exist, create a new EntityVec to store the entity e
		if (m_entityMap.find(e->tag()) == m_entityMap.end()) {
		
			m_entityMap[e->tag()] = EntityVec(); 
			
		}

		 //Push the bullet entity into the vector associated with the "bullet" key
		m_entityMap[e->tag()].push_back(e);
		
	}

	m_entitiesToAdd.clear();

	// remove dead entities from the vector of all entities
	

	// remove dead entities from each vector in the entity map
	// C++17 way of iterating through [key, value] pairs in a map
	for (auto & [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
	removeDeadEntities(m_entities);
}

void EntityManager::removeDeadEntities(EntityVec & vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity> entity) { return !entity->isActive(); }), vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
}

const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string & tag) 
{
	return m_entityMap[tag];
}