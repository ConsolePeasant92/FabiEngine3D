#include "water_editor.hpp"

#include <algorithm>

void WaterEditor::setCurrentProjectId(const string& projectId)
{
	_currentProjectId = projectId;
}

const bool WaterEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string>& WaterEditor::getLoadedIds()
{
	sort(_loadedWaterIds.begin(), _loadedWaterIds.end());
	return _loadedWaterIds;
}