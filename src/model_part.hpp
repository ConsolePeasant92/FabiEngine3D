#include "vertex_buffer.hpp"
#include "reflection_type.hpp"
#include "refraction_type.hpp"
#include "texture_buffer.hpp"

#include <string>

using std::string;

class ModelPart final
{
	friend class Model;

	shared_ptr<VertexBuffer> vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> diffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> emissionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> specularTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> reflectionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> refractionTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> normalTextureBuffer = nullptr;

	string diffuseMapPath = "";
	string emissionMapPath = "";
	string specularMapPath = "";
	string reflectionMapPath = "";
	string refractionMapPath = "";
	string normalMapPath = "";

	fmat44 transformation = fmat44(1.0f);

	fvec3 position = fvec3(0.0f);
	fvec3 rotation = fvec3(0.0f);
	fvec3 rotationOrigin = fvec3(0.0f);
	fvec3 size = fvec3(1.0f);
	fvec3 positionTarget = fvec3(0.0f);
	fvec3 rotationTarget = fvec3(0.0f);
	fvec3 sizeTarget = fvec3(1.0f);
	fvec3 color = fvec3(1.0f);
	fvec3 wireframeColor = fvec3(1.0f);

	float positionTargetSpeed = 0.0f;
	float rotationTargetSpeed = 0.0f;
	float sizeTargetSpeed = 0.0f;
	float reflectivity = 0.5f;
	float refractivity = 0.5f;
	float lightness = 1.0f;
	float specularShininess = 1.0f;
	float specularIntensity = 1.0f;
	float opacity = 1.0f;
	float emissionIntensity = 1.0f;
	float minAlpha = 1.0f;

	int textureRepeat = 1;

	bool isSpecular = false;
	bool isReflective = false;
	bool isRefractive = false;
	bool isWireframed = false;
	bool isBright = false;
	bool isFaceCulled = false;

	ReflectionType reflectionType = {};
	RefractionType refractionType = {};
};