#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

#include "Entity.hpp"

class GuiEntity : public Entity
{
public:
	GuiEntity()  = default;
	~GuiEntity() = default;

	// Model matrix
	void updateModelMatrix();

	// Texture & color
	void setDiffuseMap(GLuint diffuseMap);
	void setColor(vec3 color);
	void setMirroredHorizontally(bool val);
	void setMirroredVertically(bool val);

	// Transformation
	void setTranslation(vec2 val);
	void setRotation(float val);
	void setScaling(vec2 val);
	void translate(vec2 val, float delta);
	void rotate(float val, float delta);
	void scale(vec2 val, float delta);

	// Texture & color
	const GLuint getDiffuseMap() const;
	const vec3 getColor() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;

	// Transformation
	const mat4 getModelMatrix() const;
	const vec2 getTranslation() const;
	const float getRotation() const;
	const vec2 getScaling() const;

	// Other
	void setDepthEntity(bool val);
	const bool isDepthEntity() const;

private:
	mat4 p_modelMatrix = mat4(1.0f);

	GLuint p_diffuseMap = 0;

	vec3 p_color = vec3(1.0f);

	vec2  p_translation = vec2(0.0f);
	float p_rotation    = 0.0f;
	vec2  p_scaling     = vec2(1.0f);

	bool p_mirroredHorizontally = false;
	bool p_mirroredVertically   = false;
	bool p_isDepthEntity        = false;
};