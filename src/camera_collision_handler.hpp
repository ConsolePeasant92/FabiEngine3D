#pragma once

#include "aabb_entity.hpp"
#include "camera.hpp"
#include "raycaster.hpp"
#include "camera_collision_detector.hpp"
#include "terrain_entity_manager.hpp"
#include "box.hpp"
#include "direction_order.hpp"

class CameraCollisionHandler final
{
public:
	// VOID
	void update(const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, TerrainEntityManager& terrainManager, Camera& camera, Raycaster& raycaster);
	void setCameraBox(const Box& box);
	void enableCameraAabbResponse(bool x, bool y, bool z);
	void disableCameraAabbResponse();
	void enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableCameraTerrainResponse();

	// BOOL
	const bool isCameraUnderTerrain() const;
	const bool isCameraAabbResponseEnabled() const;
	const bool isCameraTerrainResponseEnabled() const;

private:
	// VOID
	const bool _handleCollision(Direction direction, const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, Camera& camera) const;

	// FVEC3
	fvec3 _lastCameraPosition = fvec3(0.0f);

	// FLOAT
	float _cameraTerrainHeight = 0.0f;
	float _cameraTerrainSpeed = 0.0f;

	// BOOL
	bool _isCameraAabbResponseEnabled = false;
	bool _isCameraAabbResponseEnabledX = false;
	bool _isCameraAabbResponseEnabledY = false;
	bool _isCameraAabbResponseEnabledZ = false;
	bool _isCameraTerrainResponseEnabled = false;
	bool _isCameraUnderTerrain = false;

	// Miscellaneous
	CameraCollisionDetector _collisionDetector;
	DirectionOrder _responseDirectionOrder = DirectionOrder::XYZ;
	Box _cameraBox = Box(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
};