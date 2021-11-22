#pragma once

#include "animation_frame.hpp"

#include <vector>

using std::vector;

class Animation final
{
public:
	Animation(const string& ID);

	// VOID
	void addFrame(const AnimationFrame& value);
	void setFrame(unsigned int index, const AnimationFrame& value);
	void setFrames(const vector<AnimationFrame>& value);
	void addPart(const string& partID, fvec3 totalMovement, fvec3 totalRotation, fvec3 totalScaling);
	void setPreviewModelID(const string& value);
	void setOldPreviewModelID(const string& value);
	void setAnimatedModelID(const string& value);
	void setTotalMovement(const string& partID, fvec3 value);
	void setTotalRotation(const string& partID, fvec3 value);
	void setTotalScaling(const string& partID, fvec3 value);
	void setInitialSize(fvec3 value);
	void setSpeedMultiplier(float value);
	void setTimesToPlay(int value);
	void setFadeFramestep(int value);
	void setFadeFrameIndex(int value);
	void setFrameIndex(unsigned int value);
	void setPaused(bool value);
	void setAutoPaused(bool value);

	// STRING
	const string& getID() const;
	const vector<string>& getPartIDs() const;
	const string& getPreviewModelID() const;
	const string& getOldPreviewModelID() const;
	const string& getAnimatedModelID() const;

	// FVEC3
	const map<string, fvec3>& getTotalMovements() const;
	const map<string, fvec3>& getTotalRotations() const;
	const map<string, fvec3>& getTotalScalings() const;
	const fvec3 getInitialSize() const;

	// FLOAT
	const float getSpeedMultiplier() const;

	// INT
	const int getTimesToPlay() const;
	const int getFadeFramestep() const;
	const int getFadeFrameIndex() const;

	// UNSIGNED INT
	const unsigned int getFrameIndex() const;

	// BOOL
	const bool isPaused() const;
	const bool isAutoPaused() const;

	// Miscellaneous
	const vector<AnimationFrame>& getFrames() const;

private:
	// STRING
	const string _ID;
	vector<string> _partIDs;
	string _previewModelID = "";
	string _oldPreviewModelID = "";
	string _animatedModelID = "";

	// FVEC3
	map<string, fvec3> _totalMovements;
	map<string, fvec3> _totalRotations;
	map<string, fvec3> _totalScalings;
	fvec3 _initialSize = fvec3(0.0f);

	// FLOAT
	float _speedMultiplier = 1.0f;

	// INT
	int _timesToPlay = 0;
	int _fadeFramestep = -1;
	int _fadeFrameIndex = -1;

	// UNSIGNED INT
	unsigned int _frameIndex = 0;

	// BOOL
	bool _isPaused = false;
	bool _isAutoPaused = false;

	// Miscellaneous
	vector<AnimationFrame> _frames;
};