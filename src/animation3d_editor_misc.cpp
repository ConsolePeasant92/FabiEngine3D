#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Animation3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void Animation3dEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("Animation3dEditor::_deleteAnimation");
}

const bool Animation3dEditor::_hasReachedFloat(float first, float second, float speed) const
{
	return (first >= (second - fabsf(speed))) && (first <= (second + fabsf(speed)));
}

const bool Animation3dEditor::_comparePartIDs(vector<string> first, vector<string> second) const
{
	if(first.size() != second.size())
	{
		return false;
	}

	for(size_t i = 0; i < first.size(); i++)
	{
		if(first[i] != second[i])
		{
			return false;
		}
	}

	return true;
}

shared_ptr<Animation3d> Animation3dEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("Animation3dEditor::_getAnimation");
}

const vector<string> Animation3dEditor::getAnimationIDs() const
{
	vector<string> result;

	for(const auto& animation : _animations)
	{
		result.push_back(animation->getID());
	}

	sort(result.begin(), result.end());

	return result;
}

const vector<string> Animation3dEditor::getStartedModelAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedModelAnimations)
	{
		IDs.insert(key.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation3dEditor::getStartedModelAnimationIDs(const string& modelID) const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedModelAnimations)
	{
		if(modelID == key.second)
		{
			IDs.insert(key.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const float Animation3dEditor::getModelAnimationSpeed(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationID, modelID)).getSpeed();
}

const int Animation3dEditor::getModelAnimationPlayCount(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationID, modelID)).getPlayCount();
}

const unsigned int Animation3dEditor::getModelAnimationFrameIndex(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationID, modelID)).getFrameIndex();
}

const bool Animation3dEditor::isAnimationExisting(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

const bool Animation3dEditor::isModelAnimationStarted(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedModelAnimations.find(make_pair(animationID, modelID)) != _startedModelAnimations.end());
}

const bool Animation3dEditor::isModelAnimationPlaying(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return !isModelAnimationPaused(animationID, modelID);
}

const bool Animation3dEditor::isModelAnimationAutopaused(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationID, modelID)).isAutopaused();
}

const bool Animation3dEditor::isModelAnimationPaused(const string& animationID, const string& modelID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationID, modelID)).isPaused();
}