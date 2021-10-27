#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp" 
#include "tools.hpp"

using std::make_shared;
using std::max;

const float bufferData[] =
{
	-0.5f,  1.0f, -0.5f,
	 0.5f,  1.0f, -0.5f,
	 0.5f,  0.0f, -0.5f,
	-0.5f,  0.0f, -0.5f,
	-0.5f,  1.0f, -0.5f,
	-0.5f,  1.0f,  0.5f,
	 0.5f,  1.0f,  0.5f,
	 0.5f,  0.0f,  0.5f,
	-0.5f,  0.0f,  0.5f,
	-0.5f,  1.0f,  0.5f,
	 0.5f,  1.0f,  0.5f,
	 0.5f,  1.0f, -0.5f,
	 0.5f,  0.0f, -0.5f,
	 0.5f,  0.0f,  0.5f,
	-0.5f,  0.0f,  0.5f,
	-0.5f,  0.0f, -0.5f
};

AabbEntityManager::AabbEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::AABB, meshLoader, textureLoader, renderBus),
	_renderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX, bufferData, static_cast<unsigned int>(sizeof(bufferData) / sizeof(float))))
{

}

shared_ptr<AabbEntity> AabbEntityManager::getEntity(const string& ID)
{
	auto result = _getAabbEntity(ID);

	if(result == nullptr)
	{
		Logger::throwError("AabbEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<AabbEntity>>& AabbEntityManager::getEntities()
{
	return _getAabbEntities();
}

void AabbEntityManager::createEntity(const string& ID)
{
	_createEntity(ID);
	getEntity(ID)->setRenderBuffer(_renderBuffer);
}

void AabbEntityManager::update()
{
	Logger::throwError("AabbEntityManager::update");
}

void AabbEntityManager::update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities, const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities)
{
	for(const auto& [keyID, entity] : _getAabbEntities())
	{
		// Update transformation
		entity->updateTransformation();

		// Check if AABB has parent
		if(entity->hasParent())
		{
			// Determine parent type
			if(entity->getParentType() == AabbParentType::MODEL_ENTITY)
			{
				// Try to find the parent entity
				auto foundPair = modelEntities.find(entity->getParentID());
				if(foundPair != modelEntities.end())
				{
					// Temporary values
					auto parentEntity = foundPair->second;

					// Model must not be level of detailed
					if(!parentEntity->isLevelOfDetailed())
					{
						// AABB must be allowed to follow parent
						if(entity->mustFollowParentTransformation())
						{
							// Retrieve maximum rotation & direction (based on parent rotation)
							Direction rotationDirection;
							Vec3 parentRotation = parentEntity->getBaseRotation();
							float rotation = 0.0f;
							if((parentRotation.x > parentRotation.y) && (parentRotation.x > parentRotation.z))
							{
								rotationDirection = Direction::X;
								rotation = parentRotation.x;
							}
							else if((parentRotation.y > parentRotation.x) && (parentRotation.y > parentRotation.z))
							{
								rotationDirection = Direction::Y;
								rotation = parentRotation.y;
							}
							else if((parentRotation.z > parentRotation.x) && (parentRotation.z > parentRotation.y))
							{
								rotationDirection = Direction::Z;
								rotation = parentRotation.z;
							}

							// Update size (based on parent size & AABB rotation)
							const Vec3 newAabbSize = (entity->getLocalSize() * parentEntity->getBaseSize());
							if(((rotation > 45.0f) && (rotation < 135.0f)) || ((rotation > 225.0f) && (rotation < 315.0f)))
							{
								// Determine rotation direction
								if(rotationDirection == Direction::X)
								{
									entity->setSize(Vec3(newAabbSize.x, newAabbSize.z, newAabbSize.y));
								}
								else if(rotationDirection == Direction::Y)
								{
									entity->setSize(Vec3(newAabbSize.z, newAabbSize.y, newAabbSize.x));
								}
								else if(rotationDirection == Direction::Z)
								{
									entity->setSize(Vec3(newAabbSize.y, newAabbSize.x, newAabbSize.z));
								}
							}
							else
							{
								entity->setSize(newAabbSize);
							}

							// Update position (based on parent position + rotation + size)
							Vec3 localPosition = (entity->getLocalPosition() * parentEntity->getBaseSize());
							float roundedRotation =
								(rotation > 45.0f && rotation < 135.0f) ? 90.0f : // 90 degrees rounded
								(rotation >= 135.0f && rotation <= 225.0f) ? 180.0f : // 180 degrees rounded
								(rotation > 225.0f && rotation < 315.0f) ? 270.0f : // 270 degrees rounded
								0.0f; // No rotation
							if(roundedRotation != 0.0f)
							{
								/*
								NOTE:
								X & Z directions are different, because the model is rotated around Vec3(0.0f) but is standing on Y 0.0f (local).
								The AABB is ALSO standing on Y 0.0f (local), so it needs a negative Y offset after the rotation.
								*/

								// Temporary values
								Matrix44 rotationMatrix = Matrix44(1.0f);
								Vec3 localOffset = Vec3(0.0f, (entity->getLocalSize().y / 2.0f), 0.0f);
								bool isMirrored = (roundedRotation == 180.0f);
								localPosition = (rotationDirection == Direction::Y) ? localPosition :
									(entity->getLocalPosition() + localOffset) * parentEntity->getBaseSize();
								float yOffset;

								// Determine rotation direction
								if(rotationDirection == Direction::X)
								{
									rotationMatrix = Math::createRotationMatrixX(Math::convertToRadians(roundedRotation));
									yOffset = -((isMirrored ? newAabbSize.y : newAabbSize.z) / 2.0f);
								}
								else if(rotationDirection == Direction::Y)
								{
									rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(roundedRotation));
									yOffset = 0.0f;
								}
								else if(rotationDirection == Direction::Z)
								{
									rotationMatrix = Math::createRotationMatrixZ(Math::convertToRadians(roundedRotation));
									yOffset = -((isMirrored ? newAabbSize.y : newAabbSize.x) / 2.0f);
								}

								// Apply rotation
								Vec4 result = rotationMatrix * Vec4(localPosition.x, localPosition.y, localPosition.z, 1.0f);
								entity->setPosition(parentEntity->getBasePosition() + Vec3(result.x, result.y + yOffset, result.z));
							}
							else // No rotation
							{
								entity->setPosition(parentEntity->getBasePosition() + localPosition);
							}
						}

						// Update visibility
						if(entity->mustFollowParentVisibility())
						{
							entity->setVisible(parentEntity->isVisible());
						}
					}
				}
				else
				{
					Logger::throwError("AabbEntityManager::update::1");
				}
			}
			else
			{
				// Try to find the parent entity
				auto foundPair = billboardEntities.find(entity->getParentID());
				if(foundPair != billboardEntities.end())
				{
					// Temporary values
					auto parentEntity = foundPair->second;

					// AABB must be allowed to follow parent
					if(entity->mustFollowParentTransformation())
					{
						const auto parentSize = parentEntity->getSize();
						auto newAabbSize = Vec3(parentSize.x, parentSize.y, 0.0f);

						// Retrieve absolute rotations
						const float rotationX = parentEntity->getRotation().x;
						const float rotationY = parentEntity->getRotation().y;
						const float rotationZ = parentEntity->getRotation().z;

						// Calculate reference rotation & convert it to 0-45 range
						float refRotationX = Math::calculateReferenceAngle(rotationX);
						float refRotationY = Math::calculateReferenceAngle(rotationY);
						float refRotationZ = Math::calculateReferenceAngle(rotationZ);
						refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
						refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
						refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

						// Determine direction to use
						if(refRotationX > refRotationY && refRotationX > refRotationZ)
						{
							const auto xSinRotation = fabsf(sinf(Math::convertToRadians(rotationX)));
							const auto xCosRotation = fabsf(cosf(Math::convertToRadians(rotationX)));
							newAabbSize.y = (xCosRotation * parentSize.y);
							newAabbSize.z = (xSinRotation * parentSize.y);
						}
						else if(refRotationY > refRotationX && refRotationY > refRotationZ)
						{
							const auto ySinRotation = fabsf(sinf(Math::convertToRadians(rotationY)));
							const auto yCosRotation = fabsf(cosf(Math::convertToRadians(rotationY)));
							newAabbSize.x = (yCosRotation * parentSize.x);
							newAabbSize.z = (ySinRotation * parentSize.x);
						}
						else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
						{
							const auto zSinRotation = fabsf(sinf(Math::convertToRadians(rotationZ)));
							const auto zCosRotation = fabsf(cosf(Math::convertToRadians(rotationZ)));
							newAabbSize.x = ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y));
							newAabbSize.y = ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y));
						}

						// AABB must still be a box (cannot be flat)
						newAabbSize.x = max(0.1f, newAabbSize.x);
						newAabbSize.y = max(0.1f, newAabbSize.y);
						newAabbSize.z = max(0.1f, newAabbSize.z);

						// Calculate Y offset, because rotation is around center while billboard is not centered
						float yOffset = -((newAabbSize.y - parentSize.y) / 2.0f);

						// Update size (based on parent rotation)
						entity->setSize(newAabbSize);

						// Update position (based on parent position + size)
						entity->setPosition(parentEntity->getPosition() + entity->getLocalPosition() + Vec3(0.0f, yOffset, 0.0f));
					}

					// Update visibility
					if(entity->mustFollowParentVisibility())
					{
						entity->setVisible(parentEntity->isVisible());
					}
				}
				else
				{
					Logger::throwError("AabbEntityManager::update::2");
				}
			}
		}

		// Update transformation matrix
		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}