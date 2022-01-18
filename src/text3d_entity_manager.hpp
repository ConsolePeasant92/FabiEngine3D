#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"
#include "text3d_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Text3dEntityManager final : public BaseEntityManager
{
public:
	Text3dEntityManager();

	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<Text3dEntity>>& getEntities();
	shared_ptr<Text3dEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _standingMesh;

	unordered_map<string, shared_ptr<Text3dEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
};