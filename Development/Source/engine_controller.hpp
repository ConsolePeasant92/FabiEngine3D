#pragma once
#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "top_viewport_controller.hpp"
#include "left_viewport_controller.hpp"
#include "right_viewport_controller.hpp"
#include "bottom_viewport_controller.hpp"

class EngineController final : public FabiEngine3D
{
public:
	EngineController();
	~EngineController();

	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE(float delta);
	void FE3D_CONTROLLER_DESTROY();

private:
	shared_ptr<EngineGuiManager> _gui;

	float _delta = 0.0f;

	string _currentProject = "";
	
	LeftViewportController _leftViewportController;
	RightViewportController _rightViewportController;
	TopViewportController _topViewportController;
	BottomViewportController _bottomViewportController;
};