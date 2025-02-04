#pragma once

#include "engine_interface.hpp"
#include "gui_window.hpp"

class GuiViewport final
{
public:
	GuiViewport(shared_ptr<EngineInterface> fe3d, const string & id, const fvec2 & position, const fvec2 & size, const fvec3 & color);
	~GuiViewport();

	void update(bool isInteractable);
	void createWindow(const string & windowId, const fvec2 & position, const fvec2 & size, const fvec3 & color);
	void deleteWindow(const string & windowId);
	void deleteWindows();

	const unordered_map<string, shared_ptr<GuiWindow>> & getWindows() const;

	const shared_ptr<GuiWindow> getWindow(const string & windowId) const;

	const string & getId();

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool hasWindow(const string & windowId) const;
	const bool isHovered() const;

private:
	void _updateHovering(bool isInteractable);

	const string _id;
	const string _quad2dId;

	unordered_map<string, shared_ptr<GuiWindow>> _windows = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	bool _isHovered = false;
};