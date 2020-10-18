#pragma once

#include "base_entity_manager.hpp"

class WaterEntityManager final : public BaseEntityManager
{
public:
	WaterEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~WaterEntityManager() = default;

	WaterEntity* getEntity(const string& ID) override;
	WaterEntity* getSelectedWater();

	const vector<WaterEntity*> getEntities();

	void selectWater(const string& ID);
	void addWaterEntity(const string& ID);
	void generateModel(const string& ID);
	void update() override;

private:
	string _selectedID = "";
};