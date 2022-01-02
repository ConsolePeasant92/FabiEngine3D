#pragma once

#include "vertex_buffer.hpp"
#include "camera.hpp"
#include "billboard_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class BillboardEntityManager final
{
public:
	BillboardEntityManager(RenderBus& renderBus, Camera& camera);

	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID);

	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();
	shared_ptr<BillboardEntity> getEntity(const string& ID);

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _standingVertexBuffer;
	unordered_map<string, shared_ptr<BillboardEntity>> _entities;
	RenderBus& _renderBus;
	Camera& _camera;
};