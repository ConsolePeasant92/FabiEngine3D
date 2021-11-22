#pragma once

#include "render_bus.hpp"
#include "window.hpp"

using std::numeric_limits;

class Camera final
{
public:
	Camera(RenderBus& renderBus, Window& window);

	// VOID
	void reset();
	void update(ivec2 lastCursorPosition);
	void updateMatrices();
	void move(fvec3 value);
	void setPosition(fvec3 value);
	void setThirdPersonLookat(fvec3 value);
	void setThirdPersonDistance(float value);
	void setAspectRatio(float value);
	void setFOV(float value);
	void setCursorSensitivity(float value);
	void setYaw(float value);
	void setPitch(float value);
	void setMinFirstPersonPitch(float value);
	void setMaxFirstPersonPitch(float value);
	void setMinThirdPersonPitch(float value);
	void setMaxThirdPersonPitch(float value);
	void moveFollowX(float value);
	void moveFollowZY(float value);
	void moveFollowZ(float value);
	void enableFirstPersonView(float initialYaw, float initialPitch);
	void disableFirstPersonView();
	void enableThirdPersonView(float initialYaw, float initialPitch);
	void disableThirdPersonView();
	void notifyCursorCenter();
	void invertUpVector();

	// MAT44
	const mat44& getViewMatrix() const;
	const mat44& getProjectionMatrix() const;

	// FVEC3
	const fvec3 getUpVector() const;
	const fvec3 getFrontVector() const;
	const fvec3 getRightVector() const;
	const fvec3 getPosition() const;
	const fvec3 getThirdPersonLookat() const;

	// FLOAT
	const float getFOV() const;
	const float getAspectRatio() const;
	const float getYaw() const;
	const float getPitch() const;
	const float getFirstPersonYaw() const;
	const float getFirstPersonPitch() const;
	const float getThirdPersonYaw() const;
	const float getThirdPersonPitch() const;
	const float getThirdPersonDistance() const;
	const float getNearDistance() const;
	const float getFarDistance() const;
	const float getCursorSensitivity() const;

	// BOOL
	const bool isThirdPersonViewEnabled() const;
	const bool isFirstPersonViewEnabled() const;

private:
	// MAT44
	mat44 _viewMatrix = mat44(1.0f);
	mat44 _projectionMatrix = mat44(1.0f);

	// FVEC3
	static inline const fvec3 DEFAULT_UP_VECTOR = fvec3(0.0f, 1.0f, 0.0f);
	fvec3 _upVector = fvec3(0.0f);
	fvec3 _frontVector = fvec3(0.0f);
	fvec3 _rightVector = fvec3(0.0f);
	fvec3 _position = fvec3(0.0f);
	fvec3 _thirdPersonLookat = fvec3(0.0f);

	// FLOAT
	static inline const float NEAR_DISTANCE = 0.01f;
	static inline const float FAR_DISTANCE = 2500.0f;
	static inline const float DEFAULT_CURSOR_SENSITIVITY = 0.01f;
	static inline const float DEFAULT_FOV_ANGLE = 90.0f;
	static inline const float MAX_FOV_ANGLE = 150.0f;
	static inline const float MIN_PITCH_ANGLE = -89.99f;
	static inline const float MAX_PITCH_ANGLE = 89.99f;
	static inline const float MIN_THIRD_PERSON_DISTANCE = 0.01f;
	static inline const float MAX_ACCELERATION = 10.0f;
	float _aspectRatio = 0.0f;
	float _fov = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _firstPersonYaw = 0.0f;
	float _firstPersonPitch = 0.0f;
	float _firstPersonYawAcceleration = 0.0f;
	float _firstPersonPitchAcceleration = 0.0f;
	float _minFirstPersonPitch = 0.0f;
	float _maxFirstPersonPitch = 0.0f;
	float _thirdPersonYaw = 0.0f;
	float _thirdPersonPitch = 0.0f;
	float _thirdPersonDistance = 0.0f;
	float _thirdPersonYawAcceleration = 0.0f;
	float _thirdPersonPitchAcceleration = 0.0f;
	float _minThirdPersonPitch = 0.0f;
	float _maxThirdPersonPitch = 0.0f;
	float _nearDistance = 0.0f;
	float _farDistance = 0.0f;
	float _cursorSensitivity = 0.0f;

	// BOOL
	bool _isThirdPersonViewEnabled = false;
	bool _isFirstPersonViewEnabled = false;
	bool _mustCenterCursor = false;
	bool _cursorIsBeingCentered = false;

	// Miscellaneous
	RenderBus& _renderBus;
	Window& _window;
};