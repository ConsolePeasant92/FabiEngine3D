#pragma once

#include "animation3d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Animation3dManager final
{
public:
	void createAnimation(const string& id);
	void deleteAnimation(const string& id);
	void deleteAnimations();

	const bool isAnimationExisting(const string& id) const;

	shared_ptr<Animation3d> getAnimation(const string& id);
	const unordered_map<string, shared_ptr<Animation3d>>& getAnimations();

private:
	unordered_map<string, shared_ptr<Animation3d>> _animations;
};