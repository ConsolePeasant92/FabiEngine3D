#pragma once

#include "base_entity_manager.hpp"

class WaterEntityManager final : public BaseEntityManager
{
public:
	WaterEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();

	void selectWater(const string& ID);
	void createEntity(const string& ID);
	void loadMesh(const string& ID);
	void update() override;

private:
	string _selectedID = "";
};