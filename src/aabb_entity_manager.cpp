#include "aabb_entity_manager.hpp"
#include "render_storage.hpp"
#include "tools.hpp"

using std::make_shared;
using std::max;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, -0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	-0.5f, 0.0f, -0.5f,
	-0.5f, 1.0f, -0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, -0.5f
};

constexpr unsigned int centeredBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));
constexpr unsigned int standingBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));

AabbEntityManager::AabbEntityManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, standingBufferData, standingBufferDataCount))
{

}

void AabbEntityManager::inject(shared_ptr<ModelEntityManager> modelEntityManager)
{
	_modelEntityManager = modelEntityManager;
}

void AabbEntityManager::inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager)
{
	_quad3dEntityManager = quad3dEntityManager;
}

void AabbEntityManager::inject(shared_ptr<Text3dEntityManager> text3dEntityManager)
{
	_text3dEntityManager = text3dEntityManager;
}

const shared_ptr<AabbEntity> AabbEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<AabbEntity>> & AabbEntityManager::getEntities() const
{
	return _entities;
}

void AabbEntityManager::createEntity(const string & id, bool isCentered)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto entity = make_shared<AabbEntity>(id);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	entity->setCentered(isCentered);
	entity->setVisible(false);

	_entities.insert({id, entity});
}

void AabbEntityManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(entity->hasParent())
		{
			switch(entity->getParentType())
			{
				case AabbParentType::MODEL:
				{
					auto foundPair = _modelEntityManager->getEntities().find(entity->getParentId());

					if(foundPair == _modelEntityManager->getEntities().end())
					{
						abort();
					}

					auto parentEntity = foundPair->second;

					const auto newAabbSize = (entity->getLocalSize() * parentEntity->getBaseSize());
					const auto parentRotation = parentEntity->getBaseRotation();

					DirectionType rotationDirection;
					float rotation = 0.0f;
					if((parentRotation.x > parentRotation.y) && (parentRotation.x > parentRotation.z))
					{
						rotationDirection = DirectionType::X;
						rotation = parentRotation.x;
					}
					if((parentRotation.y > parentRotation.x) && (parentRotation.y > parentRotation.z))
					{
						rotationDirection = DirectionType::Y;
						rotation = parentRotation.y;
					}
					if((parentRotation.z > parentRotation.x) && (parentRotation.z > parentRotation.y))
					{
						rotationDirection = DirectionType::Z;
						rotation = parentRotation.z;
					}

					const bool is90Degrees = ((rotation > 45.0f) && (rotation < 135.0f));
					const bool is180Degrees = ((rotation >= 135.0f) && (rotation <= 225.0f));
					const bool is270Degrees = ((rotation > 225.0f) && (rotation < 315.0f));
					const float roundedRotation = (is90Degrees ? 90.0f : is180Degrees ? 180.0f : is270Degrees ? 270.0f : 0.0f);

					if(is90Degrees || is270Degrees)
					{
						if(rotationDirection == DirectionType::X)
						{
							entity->setBaseSize(fvec3(newAabbSize.x, newAabbSize.z, newAabbSize.y));
						}
						else if(rotationDirection == DirectionType::Y)
						{
							entity->setBaseSize(fvec3(newAabbSize.z, newAabbSize.y, newAabbSize.x));
						}
						else if(rotationDirection == DirectionType::Z)
						{
							entity->setBaseSize(fvec3(newAabbSize.y, newAabbSize.x, newAabbSize.z));
						}
					}
					else
					{
						entity->setBaseSize(newAabbSize);
					}

					if((roundedRotation == 0.0f) || entity->isCentered())
					{
						const fvec3 localPosition = (entity->getLocalPosition() * parentEntity->getBaseSize());
						entity->setBasePosition(parentEntity->getBasePosition() + localPosition);
					}
					else
					{
						fvec3 localPosition;
						if(rotationDirection == DirectionType::Y)
						{
							localPosition = (entity->getLocalPosition() * parentEntity->getBaseSize());
						}
						else
						{
							const fvec3 offset = fvec3(0.0f, (entity->getLocalSize().y * 0.5f), 0.0f);
							localPosition = (entity->getLocalPosition() + offset) * parentEntity->getBaseSize();
						}

						mat44 rotationMatrix;
						fvec3 rotationOffset;
						if(rotationDirection == DirectionType::X)
						{
							rotationMatrix = Mathematics::createRotationMatrixX(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.z) * 0.5f), 0.0f);
						}
						else if(rotationDirection == DirectionType::Y)
						{
							rotationMatrix = Mathematics::createRotationMatrixY(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f);
						}
						else if(rotationDirection == DirectionType::Z)
						{
							rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(roundedRotation));
							rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.x) * 0.5f), 0.0f);
						}

						auto rotatedLocalPosition = (rotationMatrix * fvec4(localPosition.x, localPosition.y, localPosition.z, 1.0f));
						rotatedLocalPosition += rotationOffset;
						entity->setBasePosition(parentEntity->getBasePosition() + rotatedLocalPosition);
					}

					if(!parentEntity->isVisible() || parentEntity->isFrozen())
					{
						entity->setVisible(false);
						entity->setCollisionResponsive(false);
						entity->setRaycastResponsive(false);
					}

					break;
				}
				case AabbParentType::QUAD3D:
				{
					auto foundPair = _quad3dEntityManager->getEntities().find(entity->getParentId());

					if(foundPair == _quad3dEntityManager->getEntities().end())
					{
						abort();
					}

					auto parentEntity = foundPair->second;

					const auto parentPosition = parentEntity->getPosition();
					const auto parentRotation = parentEntity->getRotation();
					const auto parentSize = parentEntity->getSize();

					float refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
					float refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
					float refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);
					refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
					refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
					refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

					fvec3 newAabbSize;
					if(refRotationX > refRotationY && refRotationX > refRotationZ)
					{
						const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
						const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
						newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
					}
					else if(refRotationY > refRotationX && refRotationY > refRotationZ)
					{
						const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
						const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));
						newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
					}
					else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
					{
						const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
						const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));
						newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
						newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
						newAabbSize.z = MIN_SIZE;
					}
					else
					{
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = MIN_SIZE;
					}

					auto newAabbPosition = (parentPosition + entity->getLocalPosition());
					if(!entity->isCentered())
					{
						newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
					}

					entity->setBasePosition(newAabbPosition);
					entity->setBaseSize(newAabbSize);

					if(!parentEntity->isVisible() || parentEntity->isFrozen())
					{
						entity->setVisible(false);
						entity->setCollisionResponsive(false);
						entity->setRaycastResponsive(false);
					}

					break;
				}
				case AabbParentType::TEXT3D:
				{
					auto foundPair = _text3dEntityManager->getEntities().find(entity->getParentId());

					if(foundPair == _text3dEntityManager->getEntities().end())
					{
						abort();
					}

					auto parentEntity = foundPair->second;

					const auto parentPosition = parentEntity->getPosition();
					const auto parentRotation = parentEntity->getRotation();
					const auto parentSize = parentEntity->getSize();

					float refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
					float refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
					float refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);
					refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
					refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
					refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

					fvec3 newAabbSize;
					if(refRotationX > refRotationY && refRotationX > refRotationZ)
					{
						const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
						const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
						newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
					}
					else if(refRotationY > refRotationX && refRotationY > refRotationZ)
					{
						const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
						const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));
						newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
					}
					else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
					{
						const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
						const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));
						newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
						newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
						newAabbSize.z = MIN_SIZE;
					}
					else
					{
						newAabbSize.x = max(MIN_SIZE, parentSize.x);
						newAabbSize.y = max(MIN_SIZE, parentSize.y);
						newAabbSize.z = MIN_SIZE;
					}

					auto newAabbPosition = (parentPosition + entity->getLocalPosition());
					if(!entity->isCentered())
					{
						newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
					}

					entity->setBasePosition(newAabbPosition);
					entity->setBaseSize(newAabbSize);

					if(!parentEntity->isVisible() || parentEntity->isFrozen())
					{
						entity->setVisible(false);
						entity->setCollisionResponsive(false);
						entity->setRaycastResponsive(false);
					}

					break;
				}
			}
		}

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}

void AabbEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void AabbEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool AabbEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool AabbEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}