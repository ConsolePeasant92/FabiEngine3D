#pragma once

#include "sound3d.hpp"
#include "audio_loader.hpp"

class Sound3dManager final
{
public:
	void update();
	void createSound(const string& ID, const string& audioPath, AudioLoader& audioLoader);
	void deleteSound(const string& ID);
	void deleteSounds();

	const bool isSoundExisting(const string& ID) const;

	Sound3d& getSound(const string& ID);
	vector<Sound3d>& getSounds();

private:
	const int _findSoundIndex(const string& ID) const;

	vector<Sound3d> _sounds;
};