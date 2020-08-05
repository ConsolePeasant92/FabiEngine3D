#pragma once

#include <GLEW\\glew.h>
#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

class ShaderBus final
{
public:
	ShaderBus() = default;

	// Textures
	void setSceneMap(GLuint val);
	void setSkyReflectionCubeMap(GLuint val);
	void setSceneReflectionMap(GLuint val);
	void setSceneRefractionMap(GLuint val);
	void setShadowMap(GLuint val);
	void setBloomMap(GLuint val);
	void setBloomedDofSceneMap(GLuint val);
	void setDepthMap(GLuint val);
	void setBlurMap(GLuint val);
	void setMotionBlurMap(GLuint val);

	// Matrices
	void setViewMatrix(const mat4 & val);
	void setProjectionMatrix(const mat4 & val);
	void setSkyRotationMatrix(const mat4 & val);
	void setShadowMatrix(const mat4 & val);

	// Vectors
	void setCameraPosition(vec3 val);
	void setAmbientLightColor(vec3 val);
	void setDirectionalLightPos(vec3 val);
	void setDirectionalLightColor(vec3 val);
	void setShadowAreaCenter(vec3 val);
	void setFogColor(vec3 val);

	// Floats
	void setAmbientLightIntensity(float val);
	void setDirectionalLightIntensity(float val);
	void setSpecularLightingIntensity(float val);
	void setFogMinDistance(float val);
	void setBloomIntensity(float val);
	void setBloomTreshold(float val);
	void setCameraYaw(float val);
	void setCameraPitch(float val);
	void setNearZ(float val);
	void setFarZ(float val);
	void setDofMinDistance(float val);
	void setSkyReflectionFactor(float val);
	void setSceneReflectionHeight(float val);
	void setSceneReflectionFactor(float val);
	void setShadowAreaSize(float val);

	// Integers
	void setBloomBlurSize(int val);

	// Booleans
	void setMsaaEnabled(bool val);
	void setAmbientLightingEnabled(bool val);
	void setDirectionalLightingEnabled(bool val);
	void setSpecularLightingEnabled(bool val);
	void setPointLightingEnabled(bool val);
	void setFogEnabled(bool val);
	void setLightMappingEnabled(bool val);
	void setSkyReflectionsEnabled(bool val);
	void setSceneReflectionsEnabled(bool val);
	void setBloomEnabled(bool val);
	void setWaterEffectsEnabled(bool val);
	void setSkyHdrEnabled(bool val);
	void setShadowsEnabled(bool val);
	void setDofEnabled(bool val);
	void setMotionBlurEnabled(bool val);
	void setWireframeRenderingEnabled(bool val);
	void setAabbFrameRenderingEnabled(bool val);
	void setDebugRenderingEnabled(bool val);
	void setShadowFrameRenderingEnabled(bool val);

	// Textures
	const GLuint getSceneMap()             const;
	const GLuint getSkyReflectionCubeMap() const;
	const GLuint getSceneReflectionMap()   const;
	const GLuint getSceneRefractionMap()   const;
	const GLuint getShadowMap()            const;
	const GLuint getBloomMap()             const;
	const GLuint getBloomedDofSceneMap()   const;
	const GLuint getDepthMap()             const;
	const GLuint getBlurMap()              const;
	const GLuint getMotionBlurMap()        const;

	// Matrices
	const mat4 & getViewMatrix()        const;
	const mat4 & getProjectionMatrix()  const;
	const mat4 & getSkyRotationMatrix() const;
	const mat4 & getShadowMatrix()      const;

	// Vectors
	const vec3 getCameraPos()					const;
	const vec3 getAmbientLightingColor()		const;
	const vec3 getDirectionalLightingColor()    const;
	const vec3 getDirectionalLightingPosition()	const;
	const vec3 getShadowAreaCenter()			const;
	const vec3 getFogColor()					const;

	// Floats
	const float getAmbientLightingIntensity()	  const;
	const float getDirectionalLightingIntensity() const;
	const float getSpecularLightingIntensity()	  const;
	const float getFogMinDistance()				  const;
	const float getBloomIntensity()				  const;
	const float getBloomTreshold()				  const;
	const float getCameraYaw()					  const;
	const float getCameraPitch()				  const;
	const float getNearZ()						  const;
	const float getFarZ()						  const;
	const float getDofMinDistance()				  const;
	const float getSkyReflectionFactor()		  const;
	const float getSceneReflectionHeight()		  const;
	const float getSceneReflectionFactor()		  const;
	const float getShadowAreaSize()				  const;

	// Integers
	const int getBloomBlurSize() const;

	// Booleans
	const bool isMsaaEnabled()                 const;
	const bool isAmbientLightingEnabled()      const;
	const bool isDirectionalLightingEnabled()  const;
	const bool isSpecularLightingEnabled()     const;
	const bool isPointLightingEnabled()        const;
	const bool isFogEnabled()                  const;
	const bool isLightMappingEnabled()         const;
	const bool isSkyReflectionsEnabled()       const;
	const bool isSceneReflectionsEnabled()     const;
	const bool isBloomEnabled()                const;
	const bool isWaterEffectsEnabled()         const;
	const bool isSkyHdrEnabled()               const;
	const bool isShadowsEnabled()              const;
	const bool isDofEnabled()                  const;
	const bool isMotionBlurEnabled()           const;
	const bool isWireframeRenderingEnabled()   const;
	const bool isAabbFrameRenderingEnabled()   const;
	const bool isShadowFrameRenderingEnabled() const;
	const bool isDebugRenderingEnabled()       const;

private:
	// Textures
	GLuint _sceneMap             = 0;
	GLuint _skyReflectionCubeMap = 0;
	GLuint _sceneReflectionMap   = 0;
	GLuint _sceneRefractionMap   = 0;
	GLuint _shadowMap            = 0;
	GLuint _bloomMap             = 0;
	GLuint _bloomedDofSceneMap   = 0;
	GLuint _depthMap             = 0;
	GLuint _blurMap              = 0;
	GLuint _motionBlurMap        = 0;
	
	// Matrices
	mat4 _viewMatrix        = mat4(1.0f);
	mat4 _projectionMatrix  = mat4(1.0f);
	mat4 _skyRotationMatrix = mat4(1.0f);
	mat4 _shadowMatrix      = mat4(1.0f);

	// Vectors
	vec3 _cameraPosition			  = vec3(0.0f);
	vec3 _ambientLightingColor		  = vec3(1.0f);
	vec3 _directionalLightingColor    = vec3(1.0f);
	vec3 _directionalLightingPosition = vec3(0.0f);
	vec3 _shadowAreaCenter			  = vec3(0.0f);
	vec3 _fogColor					  = vec3(1.0f);

	// Floats
	float _ambientLightingIntensity     = 1.0f;
	float _directionalLightingIntensity = 0.0f;
	float _specularLightingIntensity	= 0.0f;
	float _fogMinDistance               = 0.0f;
	float _bloomIntensity               = 0.0f;
	float _bloomTreshold                = 0.0f;
	float _cameraYaw                    = 0.0f;
	float _cameraPitch                  = 0.0f;
	float _nearZ                        = 0.0f;
	float _farZ                         = 0.0f;
	float _dofMinDistance               = 0.0f;
	float _skyReflectionFactor          = 0.0f;
	float _sceneReflectionHeight        = 0.0f;
	float _sceneReflectionFactor        = 0.0f;
	float _shadowAreaSize				= 0.0f;
	
	// Integers
	int _bloomBlurSize = 0;

	// Booleans
	bool _isMsaaEnabled                 = false;
	bool _isAmbientLightingEnabled      = false;
	bool _isDirectionalLightingEnabled  = false;
	bool _isSpecularLightingEnabled     = false;
	bool _isPointLightingEnabled        = false;
	bool _isFogEnabled                  = false;
	bool _isLightMappingEnabled         = false;
	bool _isSkyReflectionsEnabled       = false;
	bool _isSceneReflectionsEnabled     = false;
	bool _isBloomEnabled                = false;
	bool _isWaterEffectsEnabled         = false;
	bool _isSkyHdrEnabled               = false;
	bool _isShadowsEnabled              = false;
	bool _isDofEnabled                  = false;
	bool _isMotionBlurEnabled           = false;
	bool _isWireframeRenderingEnabled   = false;
	bool _isAabbFrameRenderingEnabled   = false;
	bool _isShadowFrameRenderingEnabled	= false;
	bool _isDebugRenderingEnabled		= false;
};