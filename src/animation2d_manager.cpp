#include "animation2d_manager.hpp"

using std::make_shared;

void Animation2dManager::createAnimation(const string& id)
{
	if(isAnimationExisting(id))
	{
		abort();
	}

	auto animation = make_shared<Animation2d>(id);

	_animations.insert(make_pair(id, animation));
}

void Animation2dManager::deleteAnimation(const string& id)
{
	if(!isAnimationExisting(id))
	{
		abort();
	}

	_animations.erase(id);
}

void Animation2dManager::deleteAnimations()
{
	_animations.clear();
}

const bool Animation2dManager::isAnimationExisting(const string& id) const
{
	return (_animations.find(id) != _animations.end());
}

shared_ptr<Animation2d> Animation2dManager::getAnimation(const string& id)
{
	auto iterator = _animations.find(id);

	if(iterator == _animations.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Animation2d>>& Animation2dManager::getAnimations()
{
	return _animations;
}