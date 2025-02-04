#pragma once

#include "engine_interface.hpp"
#include "gui_scrolling_list.hpp"
#include "gui_input_box.hpp"
#include "gui_button.hpp"
#include "gui_quad_field.hpp"
#include "gui_text_field.hpp"

class GuiScreen final
{
public:
	GuiScreen(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & parentPosition, const fvec2 & parentSize);

	void update(bool isInteractable);
	void setVisible(bool value);
	void createScrollingList(const string & scrollingListId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, const fvec2 & characterSize, float scrollingSpeed, bool isCentered);
	void createInputBox(const string & inputBoxId, const fvec2 & position, const fvec2 & size, const fvec3 & color, const fvec3 & hoverColor, const fvec3 & textColor, const fvec3 & textHoverColor, int maxCharacterCount, bool isLettersAllowed, bool isNumbersAllowed, bool isSpecialsAllowed, bool isCentered);
	void createButton(const string & buttonId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & defaultQuadColor, const fvec3 & hoveredQuadColor, const string & textContent, const fvec3 & defaultTextColor, const fvec3 & hoveredTextColor, bool isCentered);
	void createQuadField(const string & quadFieldId, const fvec2 & position, const fvec2 & size, const string & diffuseMapPath, const fvec3 & color, bool isCentered);
	void createTextField(const string & textFieldId, const fvec2 & position, const fvec2 & size, const string & textContent, const fvec3 & textColor, bool isCentered);
	void deleteScrollingList(const string & scrollingListId);
	void deleteInputBox(const string & inputBoxId);
	void deleteButton(const string & buttonId);
	void deleteQuadField(const string & quadFieldId);
	void deleteTextField(const string & textFieldId);
	void deleteScrollingLists();
	void deleteInputBoxes();
	void deleteButtons();
	void deleteQuadFields();
	void deleteTextFields();

	const unordered_map<string, shared_ptr<GuiScrollingList>> & getScrollingLists() const;
	const unordered_map<string, shared_ptr<GuiInputBox>> & getInputBoxes() const;
	const unordered_map<string, shared_ptr<GuiButton>> & getButtons() const;
	const unordered_map<string, shared_ptr<GuiQuadField>> & getQuadFields() const;
	const unordered_map<string, shared_ptr<GuiTextField>> & getTextFields() const;

	const shared_ptr<GuiScrollingList> getScrollingList(const string & scrollingListId) const;
	const shared_ptr<GuiInputBox> getInputBox(const string & inputBoxId) const;
	const shared_ptr<GuiButton> getButton(const string & buttonId) const;
	const shared_ptr<GuiQuadField> getQuadField(const string & quadFieldId) const;
	const shared_ptr<GuiTextField> getTextField(const string & textFieldId) const;

	const string & getId() const;
	const string & getParentId() const;

	const bool hasScrollingList(const string & scrollingListId) const;
	const bool hasInputBox(const string & inputBoxId) const;
	const bool hasButton(const string & buttonId) const;
	const bool hasQuadField(const string & quadFieldId) const;
	const bool hasTextField(const string & textFieldId) const;

private:
	const fvec2 _getConvertedPosition(const fvec2 & position) const;
	const fvec2 _getConvertedSize(const fvec2 & size) const;

	const string _id;
	const string _parentId;

	unordered_map<string, shared_ptr<GuiScrollingList>> _scrollingLists = {};
	unordered_map<string, shared_ptr<GuiInputBox>> _inputBoxes = {};
	unordered_map<string, shared_ptr<GuiButton>> _buttons = {};
	unordered_map<string, shared_ptr<GuiQuadField>> _quadFields = {};
	unordered_map<string, shared_ptr<GuiTextField>> _textFields = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	fvec2 _parentPosition = fvec2(0.0f);
	fvec2 _parentSize;
};