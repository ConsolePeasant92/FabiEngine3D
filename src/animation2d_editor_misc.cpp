#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Animation2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string> Animation2dEditor::getAnimationIDs()
{
	vector<string> result;

	// Find all IDs
	for(const auto& animation : _animations)
	{
		result.push_back(animation->getID());
	}

	// Sort alphabetically
	sort(result.begin(), result.end());

	return result;
}

const vector<string> Animation2dEditor::getStartedBillboardAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedBillboardAnimations)
	{
		IDs.insert(idPair.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedImageAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedImageAnimations)
	{
		IDs.insert(idPair.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedBillboardAnimationIDs(const string& billboardID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedBillboardAnimations)
	{
		if(billboardID == idPair.second)
		{
			IDs.insert(idPair.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedImageAnimationIDs(const string& imageID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedImageAnimations)
	{
		if(imageID == idPair.second)
		{
			IDs.insert(idPair.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

void Animation2dEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("Animation2dEditor::_deleteAnimation");
}

shared_ptr<Animation2d> Animation2dEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("Animation2dEditor::_getAnimation");
}

const bool Animation2dEditor::isAnimationExisting(const string& ID) const
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

const bool Animation2dEditor::isBillboardAnimationStarted(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Return
	return (_startedBillboardAnimations.find(make_pair(animationID, billboardID)) != _startedBillboardAnimations.end());
}

const bool Animation2dEditor::isBillboardAnimationPlaying(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	// Return
	return !isBillboardAnimationPaused(animationID, billboardID);
}

const bool Animation2dEditor::isBillboardAnimationPaused(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
		return false;
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	// Return
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).isPaused();
}

const bool Animation2dEditor::isImageAnimationStarted(const string& animationID, const string& imageID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Return
	return (_startedImageAnimations.find(make_pair(animationID, imageID)) != _startedImageAnimations.end());
}

const bool Animation2dEditor::isImageAnimationPlaying(const string& animationID, const string& imageID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	// Return
	return !isImageAnimationPaused(animationID, imageID);
}

const bool Animation2dEditor::isImageAnimationPaused(const string& animationID, const string& imageID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on image with ID \"" + imageID + "\": ";

	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
		return false;
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).isPaused();
}