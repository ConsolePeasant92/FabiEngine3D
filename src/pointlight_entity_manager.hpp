#pragma once

#include "pointlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class PointlightEntityManager final
{
public:
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<PointlightEntity>>& getEntities();

	shared_ptr<PointlightEntity> getEntity(const string& ID);

	static inline const unsigned int MAX_LIGHT_COUNT = 64;

private:
	unordered_map<string, shared_ptr<PointlightEntity>> _entities;
};