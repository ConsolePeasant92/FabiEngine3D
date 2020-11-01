#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_scrollinglist.hpp"
#include "engine_gui_writefield.hpp"
#include "engine_gui_button.hpp"
#include "engine_gui_rectangle.hpp"
#include "engine_gui_textfield.hpp"

class EngineGuiScreen final
{
public:
	EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size);

	void update(bool hoverable);
	void show();
	void hide();

	const string& getID();
	const string& getParentID();

	void addScrollingList(const string& ID, vec2 position, vec2 size, vec3 color, vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, 
		vec3 textHoverColor, vec2 charSize);
	void addWriteField(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor, 
		bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);
	void addButton(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, string textContent, vec3 textColor, vec3 textHoverColor);
	void addButton(const string& ID, vec2 position, vec2 size, const string& textureName, vec3 hoverColor);
	void addRectangle(const string& ID, vec2 position, vec2 size, vec3 color, bool isCentered = true);
	void addRectangle(const string& ID, vec2 position, vec2 size, const string& textureName, bool isCentered = true);
	void addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor, bool isCentered = true);

	void deleteScrollingList(const string& ID);
	void deleteWriteField(const string& ID);
	void deleteButton(const string& ID);
	void deleteRectangle(const string& ID);
	void deleteTextfield(const string& ID);

	bool checkScrollingList(const string& ID);
	bool checkWriteField(const string& ID);
	bool checkButton(const string& ID);
	bool checkRectangle(const string& ID);
	bool checkTextfield(const string& ID);

	shared_ptr<EngineGuiScrollingList> getScrollingList(const string& ID);
	shared_ptr<EngineGuiWriteField>    getWriteField(const string& ID);
	shared_ptr<EngineGuiButton>        getButton(const string& ID);
	shared_ptr<EngineGuiRectangle>     getRectangle(const string& ID);
	shared_ptr<EngineGuiTextfield>     getTextfield(const string& ID);

	vector<shared_ptr<EngineGuiScrollingList>>& getScrollingLists();
	vector<shared_ptr<EngineGuiWriteField>>&    getWriteFields();
	vector<shared_ptr<EngineGuiButton>>&		getButtons();
	vector<shared_ptr<EngineGuiRectangle>>&		getRectangles();
	vector<shared_ptr<EngineGuiTextfield>>&		getTextfields();

private:
	FabiEngine3D& _fe3d;

	vec2 _parentPosition;
	vec2 _parentSize;

	const string _ID;
	const string _parentID;

	bool _isActive = false;

	vector<shared_ptr<EngineGuiScrollingList>> _scrollingLists;
	vector<shared_ptr<EngineGuiWriteField>> _writeFields;
	vector<shared_ptr<EngineGuiButton>> _buttons;
	vector<shared_ptr<EngineGuiRectangle>> _rectangles;
	vector<shared_ptr<EngineGuiTextfield>> _textfields;

	vec4 _convertDimensions(vec2 position, vec2 size);
};