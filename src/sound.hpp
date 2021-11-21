#pragma once

#include "mathematics.hpp"

#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class Sound final
{
public:
	Sound(const string& ID, const string& filePath, Mix_Chunk* dataPointer);

	// Voids
	void make3D(fvec3 position, float maxVolume, float maxDistance);
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void setVolume(float value);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	// Strings
	const string& getID() const;
	const string& getFilePath() const;

	// Vectors
	const fvec3 getPosition() const;

	// Decimals
	const float getVolume() const;
	const float getMaxVolume() const;
	const float getMaxDistance() const;

	// Booleans
	const bool is3D() const;

	// Miscellaneous
	Mix_Chunk* getDataPointer() const;

private:
	// Strings
	string _ID = "";
	string _filePath = "";

	// Vectors
	fvec3 _position = fvec3(0.0f);

	// Decimals
	float _volume = 1.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;

	// Booleans
	bool _is3D = false;

	// Miscellaneous
	Mix_Chunk* _dataPointer = nullptr;
};