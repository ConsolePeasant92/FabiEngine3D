#pragma once

#include "fe3d.hpp"
#include "engine_gui_button.hpp"

class EngineGuiWriteField final : public EngineGuiButton
{
public:
	EngineGuiWriteField(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor,
						fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered);

	// VOID
	void update(bool hoverable) override;
	void setActive(bool active);
	void setPermActive(bool active);
	void changeTextContent(const string& content) override;

	// STRING
	const string getTextContent() const;
	
	// BOOL
	const bool confirmedInput() const;
	const bool isActive() const;
	const bool hasTextContentChanged();

private:
	// VOID
	void _updateActivation();
	void _updateTyping();

	// STRING
	string _lastTextContent = "";
	string _currentTextContent = "";

	// FLOAT
	static inline const float CHAR_WIDTH = 0.02f;

	// INT
	static inline const int MAX_PASSED_BAR_FRAMES = 50;
	static inline const int MAX_PASSED_BACKSPACE_FRAMES = 20;

	// BOOL
	const bool _noNumbers;
	const bool _noCaps;
	const bool _noSpecials;
	const bool _noLetters;
	const bool _minusAllowed;
	bool _mustBeActive = false;
	bool _isActive = false;
	bool _confirmedInput = false;
};