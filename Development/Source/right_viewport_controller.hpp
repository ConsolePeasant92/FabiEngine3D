#pragma once

#include "base_viewport_controller.hpp"

class RightViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::BaseViewportController;
	
	// Voids
	void initialize() override;
	void update() override;

private:
	// Vectors
	static inline const Vec3 FRAME_COLOR = Vec3(0.175f);
	static inline const Vec3 BLACK = Vec3(0.0f);
	static inline const Vec3 WHITE = Vec3(1.0f);

	// Decimals
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
};