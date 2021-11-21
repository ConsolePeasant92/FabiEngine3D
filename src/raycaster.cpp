#include "raycaster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::min;
using std::max;

Raycaster::Raycaster(RenderBus& renderBus, TerrainEntityManager& terrainManager)
	:
	_renderBus(renderBus),
	_terrainManager(terrainManager)
{

}

void Raycaster::update(ivec2 cursorPosition)
{
	// Update raycasting
	_cursorRay = _calculateCursorRay(cursorPosition);

	// Update cursor pointing on terrain
	if(_isTerrainPointingEnabled)
	{
		if(_terrainManager.getSelectedTerrain() != nullptr)
		{
			_terrainPoint = _calculateTerrainPoint();
		}
		else
		{
			_terrainPoint = fvec3(-1.0f);
		}
	}
	else
	{
		_terrainPoint = fvec3(-1.0f);
	}
}

void Raycaster::setTerrainPointingEnabled(bool enabled)
{
	_isTerrainPointingEnabled = enabled;
}

void Raycaster::setTerrainPointingDistance(float distance)
{
	_terrainPointingDistance = distance;
}

void Raycaster::setTerrainPointingPrecision(float precision)
{
	_terrainPointingPrecision = precision;
}

const bool Raycaster::isTerrainPointingEnabled() const
{
	return _isTerrainPointingEnabled;
}

const float Raycaster::getTerrainPointingDistance() const
{
	return _terrainPointingDistance;
}

const float Raycaster::getTerrainPointingPrecision() const
{
	return _terrainPointingPrecision;
}

const Ray Raycaster::getCursorRay() const
{
	return _cursorRay;
}

const fvec3 Raycaster::getTerrainPoint() const
{
	return _terrainPoint;
}

// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
const float Raycaster::calculateRayBoxIntersectionDistance(Ray ray, Box box) const
{
	/*
		Initial formula: point = (origin + distance) * direction
		Rearranged formula: distance = (point - origin) / direction
		Final formula: distance = (point - origin) * (1 / direction)
	*/

	// Check if ray is invalid
	if(ray.getDirection() == fvec3(0.0f))
	{
		return -1.0f;
	}

	// Small performance optimization
	const fvec3 inverseRayDirection = (fvec3(1.0f) / ray.getDirection());

	// Calculate box points
	float minX = (box.getPosition().x - box.getLeft());
	float maxX = (box.getPosition().x + box.getRight());
	float minY = (box.getPosition().y - box.getBottom());
	float maxY = (box.getPosition().y + box.getTop());
	float minZ = (box.getPosition().z - box.getBack());
	float maxZ = (box.getPosition().z + box.getFront());

	// Calculates distances
	float minDistanceX = ((minX - ray.getPosition().x) * inverseRayDirection.x);
	float maxDistanceX = ((maxX - ray.getPosition().x) * inverseRayDirection.x);
	float minDistanceY = ((minY - ray.getPosition().y) * inverseRayDirection.y);
	float maxDistanceY = ((maxY - ray.getPosition().y) * inverseRayDirection.y);
	float minDistanceZ = ((minZ - ray.getPosition().z) * inverseRayDirection.z);
	float maxDistanceZ = ((maxZ - ray.getPosition().z) * inverseRayDirection.z);

	// Calculate intersections
	float minIntersectionDistance = max(max(min(minDistanceX, maxDistanceX), min(minDistanceY, maxDistanceY)), min(minDistanceZ, maxDistanceZ));
	float maxIntersectionDistance = min(min(max(minDistanceX, maxDistanceX), max(minDistanceY, maxDistanceY)), max(minDistanceZ, maxDistanceZ));

	// AABB is behind camera
	if(maxIntersectionDistance < 0.0f)
	{
		return -1.0f;
	}

	// No intersection
	if(minIntersectionDistance > maxIntersectionDistance)
	{
		return -1.0f;
	}

	// Intersection
	return minIntersectionDistance;
}

const Ray Raycaster::_calculateCursorRay(ivec2 cursorPosition) const
{
	fvec2 screenCoords = Tools::convertFromScreenCoords(cursorPosition);
	fvec2 ndcCoords = Math::convertToNDC(screenCoords);
	fvec4 clipCoords = fvec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	fvec4 viewCoords = _convertToViewSpace(clipCoords);
	fvec3 worldCoords = _convertToWorldSpace(viewCoords);

	return Ray(_renderBus.getCameraPosition(), Math::normalize(worldCoords));
}

const fvec4 Raycaster::_convertToViewSpace(fvec4 clipCoords) const
{
	mat44 invertedProjection = Math::invertMatrix(_renderBus.getProjectionMatrix());
	fvec4 viewCoords = (invertedProjection * clipCoords);

	return fvec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

const fvec3 Raycaster::_convertToWorldSpace(fvec4 viewCoords) const
{
	mat44 invertedView = Math::invertMatrix(_renderBus.getViewMatrix());
	fvec4 worldCoords = (invertedView * viewCoords);

	return fvec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

const fvec3 Raycaster::getPointOnRay(Ray ray, float distance) const
{
	return (ray.getPosition() + (ray.getDirection() * distance));
}

const bool Raycaster::_isUnderTerrain(float distance) const
{
	// Scale ray
	fvec3 scaledRay = getPointOnRay(_cursorRay, distance);

	// Retrieve height
	auto selectedTerrain = _terrainManager.getSelectedTerrain();
	float terrainHeight = _terrainManager.getPixelHeight(
		selectedTerrain->getID(),
		scaledRay.x + (selectedTerrain->getSize() / 2.0f),
		scaledRay.z + (selectedTerrain->getSize() / 2.0f));

	// Return
	return (scaledRay.y < terrainHeight);
}

const fvec3 Raycaster::_calculateTerrainPoint() const
{
	// Temporary values
	float distance = 0.0f;

	// Try to find point on terrain
	while(distance < _terrainPointingDistance)
	{
		// Intersected with terrain
		if(_isUnderTerrain(distance))
		{
			// Calculate point on terrain
			distance -= (_terrainPointingPrecision / 2.0f);
			fvec3 endPoint = getPointOnRay(_cursorRay, distance);

			// Check if selected point is inside the terrain size
			auto selectedTerrain = _terrainManager.getSelectedTerrain();
			if(_terrainManager.isInside(
				selectedTerrain->getID(),
				endPoint.x + (selectedTerrain->getSize() / 2.0f),
				endPoint.z + (selectedTerrain->getSize() / 2.0f)))
			{
				return endPoint;
			}
			else
			{
				break;
			}
		}
		else
		{
			distance += _terrainPointingPrecision;
		}
	}

	return fvec3(-1.0f);
}