#include "camera_collision_handler.hpp"

using std::make_shared;

CameraCollisionHandler::CameraCollisionHandler()
{
	_cameraBox = make_shared<Box>(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	clearCollisionWithTerrain();
	clearCollisionWithAabbs();
}

void CameraCollisionHandler::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void CameraCollisionHandler::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void CameraCollisionHandler::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void CameraCollisionHandler::setCameraBox(shared_ptr<Box> value)
{
	_cameraBox = value;
}

const bool CameraCollisionHandler::hasCollidedWithTerrain() const
{
	return _hasCollidedWithTerrain;
}

void CameraCollisionHandler::clearCollisionWithTerrain()
{
	_hasCollidedWithTerrain = false;
}

void CameraCollisionHandler::clearCollisionWithAabbs()
{
	_aabbCollisions.clear();
}

const vector<pair<string, DirectionType>> & CameraCollisionHandler::getCollisions() const
{
	return _aabbCollisions;
}