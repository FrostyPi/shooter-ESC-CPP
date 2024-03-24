#pragma once
//1:00:15
#include "Entity.h"
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>>		EntityVec;
typedef std::map<std::string, EntityVec>			EntityMap;
typedef std::map<int, std::shared_ptr<Entity>>      EntityTBR;

class EntityManager
{
	EntityVec m_entities;
	EntityVec m_entitiesToAdd;

	EntityTBR m_entitiesToRemove;

	EntityMap m_entityMap;
	size_t    m_totalEntities = 0;

	void removeDeadEntities(EntityVec & vec);

public:

	EntityManager();

	void update();

	std::shared_ptr<Entity> addEntity(const std::string & tag);

	const EntityVec & getEntities();
	const EntityVec& getEntities(const std::string& tag);

};