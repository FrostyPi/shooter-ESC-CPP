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
	for (auto e : m_entitiesToAdd)
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
	removeDeadEntities(m_entities);

	// remove dead entities from each vector in the entity map
	// C++17 way of iterating through [key, value] pairs in a map
	for (auto & [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
}

void EntityManager::removeDeadEntities(EntityVec & vec)
{

	//for (size_t i = 0; i < vec.size();) {
	//	if (!vec[i]->isActive()) {
	//		vec[i] = vec[vec.size() - 1];
	//		vec.pop_back();
	//	}
	//	else {
	//		i++;
	//	}
	//}
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity> entity) { return !entity->isActive(); }), vec.end());
	//int i = 0;
	//for (auto e : vec)
	//{

	//	if (!e->isActive())
	//	{
	//		m_entitiesToRemove[i] = e;
	//		//m_entitiesToRemove.push_back(e);
	//	}
	//	i++;
	//}

	//for (auto & [index, enTitty] : m_entitiesToRemove)
	//{

	//	//FIGURE THIS OUT
	//	//vec.erase
	//}
	// ok fucking yolo 


	/*for (auto i : vec) 
	{asdasdasdas
		//std::cout << i << " ";fsadfasdasdasdsadasdasd
	}*/
	// TODO: remove all dead entities from the input vector
	//		 this is called by the update() function
	//auto new_end = std::remove_if(vec.begin(), vec.end(), [&](const std::shared_ptr<Entity> & e) { return !e->isActive(); });

	//vec.erase(new_end, end(vec));
	// OK NEVERMIND DOESNT FCUKIGN WORK
	// SEEMS TO COMPILE AND LINK, TEST W LIFESPAN 
	// 
	// 
	// 
	//vec.erase(std::remove_if(vec.begin(), vec.end(), [](Entity entity) { return !entity.isActive(); }), vec.end());
	//TEST THIS SOMEHOW?
	// vec.erase(std::remove_if(vec.begin(), vec.end() - 1, [](const std::shared_ptr<Entity> e) { return !e->isActive(); }), vec.end());
	//vec.erase(std::remove_if(vec.begin(), vec.end() - 1, [](const std::shared_ptr<Entity> e) { return !e->isActive(); }), vec.begin());
	//for (auto e : vec)
	//{	
	//	if (!e->isActive())
	//	{

	//		//remove from vec, perhaps try std::remove_if
	//		// CONSIDER concurrent iterator modification, this should be the only function where this may happen.
	//	}
	//}
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