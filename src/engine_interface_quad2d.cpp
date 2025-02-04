#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad2d_create(const string & quad2dId, bool isCentered)
{
	_core->getQuad2dManager()->createQuad2d(quad2dId, isCentered);
}

void EngineInterface::quad2d_delete(const string & quad2dId)
{
	for(const auto & [startedAnimation2dId, startedQuad2dId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimation2dIds())
	{
		if(quad2dId == startedQuad2dId)
		{
			quad2d_stopAnimation2d(startedQuad2dId, startedAnimation2dId);
		}
	}

	if(quad2dId == _core->getRenderStorage()->getCursorId())
	{
		_core->getRenderStorage()->setCursorId("");
	}

	_core->getQuad2dManager()->deleteQuad2d(quad2dId);
}

void EngineInterface::quad2d_setVisible(const string & quad2dId, bool value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setVisible(value);
}

void EngineInterface::quad2d_setDiffuseMap(const string & quad2dId, const string & value)
{
	if(value.empty())
	{
		_core->getQuad2dManager()->getQuad2d(quad2dId)->setDiffuseMap(nullptr);
		_core->getQuad2dManager()->getQuad2d(quad2dId)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->getImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getQuad2dManager()->getQuad2d(quad2dId)->setDiffuseMap(texture);
		_core->getQuad2dManager()->getQuad2d(quad2dId)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad2d_setPosition(const string & quad2dId, const fvec2 & position)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setPosition(position);
}

void EngineInterface::quad2d_setRotation(const string & quad2dId, float rotation)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setRotation(rotation);
}

void EngineInterface::quad2d_setSize(const string & quad2dId, const fvec2 & size)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setSize(size);
}

void EngineInterface::quad2d_move(const string & quad2dId, const fvec2 & change)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->move(change);
}

void EngineInterface::quad2d_rotate(const string & quad2dId, float change)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->rotate(change);
}

void EngineInterface::quad2d_scale(const string & quad2dId, const fvec2 & change)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->scale(change);
}

void EngineInterface::quad2d_moveTo(const string & quad2dId, const fvec2 & target, float speed)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->moveTo(target, speed);
}

void EngineInterface::quad2d_rotateTo(const string & quad2dId, float target, float speed)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->rotateTo(target, speed);
}

void EngineInterface::quad2d_scaleTo(const string & quad2dId, const fvec2 & target, float speed)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->scaleTo(target, speed);
}

void EngineInterface::quad2d_setColor(const string & quad2dId, const fvec3 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setColor(value);
}

void EngineInterface::quad2d_setOpacity(const string & quad2dId, float value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setOpacity(value);
}

void EngineInterface::quad2d_setMinClipPosition(const string & quad2dId, const fvec2 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setMinClipPosition(value);
}

void EngineInterface::quad2d_setMaxClipPosition(const string & quad2dId, const fvec2 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setMaxClipPosition(value);
}

void EngineInterface::quad2d_setWireframed(const string & quad2dId, bool value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setWireframed(value);
}

void EngineInterface::quad2d_setWireframeColor(const string & quad2dId, const fvec3 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setWireframeColor(value);
}

void EngineInterface::quad2d_setUvMultiplier(const string & quad2dId, const fvec2 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setUvMultiplier(value);
}

void EngineInterface::quad2d_setUvOffset(const string & quad2dId, const fvec2 & value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setUvOffset(value);
}

void EngineInterface::quad2d_startAnimation2d(const string & quad2dId, const string & animation2dId, int playCount)
{
	_core->getAnimation2dPlayer()->startQuad2dAnimation2d(animation2dId, quad2dId, playCount);
}

void EngineInterface::quad2d_pauseAnimation2d(const string & quad2dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->pauseQuad2dAnimation2d(animation2dId, quad2dId);
}

void EngineInterface::quad2d_autopauseAnimation2d(const string & quad2dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->autopauseQuad2dAnimation2d(animation2dId, quad2dId);
}

void EngineInterface::quad2d_resumeAnimation2d(const string & quad2dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->resumeQuad2dAnimation2d(animation2dId, quad2dId);
}

void EngineInterface::quad2d_stopAnimation2d(const string & quad2dId, const string & animation2dId)
{
	_core->getAnimation2dPlayer()->stopQuad2dAnimation2d(animation2dId, quad2dId);
}

void EngineInterface::quad2d_setAnimation2dRowIndex(const string & animation2dId, const string & quad2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimation2dRowIndex(animation2dId, quad2dId, value);
}

void EngineInterface::quad2d_setAnimation2dColumnIndex(const string & animation2dId, const string & quad2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimation2dColumnIndex(animation2dId, quad2dId, value);
}

void EngineInterface::quad2d_setAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimation2dIntervalMultiplier(animation2dId, quad2dId, value);
}

void EngineInterface::quad2d_setAnimation2dIntervalDivider(const string & animation2dId, const string & quad2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimation2dIntervalDivider(animation2dId, quad2dId, value);
}

void EngineInterface::quad2d_setAnimation2dUpdateCount(const string & animation2dId, const string & quad2dId, int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimation2dUpdateCount(animation2dId, quad2dId, value);
}

void EngineInterface::quad2d_setTextureRepeat(const string & quad2dId, int value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setTextureRepeat(value);
}

void EngineInterface::quad2d_setHorizontallyFlipped(const string & quad2dId, bool value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setHorizontallyFlipped(value);
}

void EngineInterface::quad2d_setVerticallyFlipped(const string & quad2dId, bool value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setVerticallyFlipped(value);
}

void EngineInterface::quad2d_setLightness(const string & quad2dId, float value)
{
	_core->getQuad2dManager()->getQuad2d(quad2dId)->setLightness(value);
}

const bool EngineInterface::quad2d_isExisting(const string & quad2dId) const
{
	return _core->getQuad2dManager()->isQuad2dExisting(quad2dId);
}

const fvec2 & EngineInterface::quad2d_getPosition(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getPosition();
}

const float EngineInterface::quad2d_getRotation(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getRotation();
}

const float EngineInterface::quad2d_getOpacity(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getOpacity();
}

const float EngineInterface::quad2d_getLightness(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getLightness();
}

const int EngineInterface::quad2d_getTextureRepeat(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getTextureRepeat();
}

const int EngineInterface::quad2d_getAnimation2dPlayCount(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dPlayCount(animation2dId, quad2dId);
}

const int EngineInterface::quad2d_getAnimation2dRowIndex(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dRowIndex(animation2dId, quad2dId);
}

const int EngineInterface::quad2d_getAnimation2dColumnIndex(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dColumnIndex(animation2dId, quad2dId);
}

const int EngineInterface::quad2d_getAnimation2dIntervalMultiplier(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dIntervalMultiplier(animation2dId, quad2dId);
}

const int EngineInterface::quad2d_getAnimation2dIntervalDivider(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dIntervalDivider(animation2dId, quad2dId);
}

const int EngineInterface::quad2d_getAnimation2dUpdateCount(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimation2dUpdateCount(animation2dId, quad2dId);
}

const vector<string> EngineInterface::quad2d_getIds() const
{
	vector<string> result = {};

	for(const auto & [quad2dId, quad2d] : _core->getQuad2dManager()->getQuad2ds())
	{
		result.push_back(quad2d->getId());
	}

	return result;
}

const vector<string> EngineInterface::quad2d_getAnimation2dIds(const string & quad2dId) const
{
	vector<string> result = {};

	for(const auto & [startedAnimation2dId, startedQuad2dId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimation2dIds())
	{
		if(quad2dId == startedQuad2dId)
		{
			result.push_back(startedAnimation2dId);
		}
	}

	return result;
}

const string & EngineInterface::quad2d_getDiffuseMapPath(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getDiffuseMapPath();
}

const fvec3 & EngineInterface::quad2d_getWireframeColor(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getWireframeColor();
}

const fvec2 & EngineInterface::quad2d_getSize(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getSize();
}

const fvec2 & EngineInterface::quad2d_getMinClipPosition(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getMinClipPosition();
}

const fvec2 & EngineInterface::quad2d_getMaxClipPosition(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getMaxClipPosition();
}

const fvec2 & EngineInterface::quad2d_getUvMultiplier(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getUvMultiplier();
}

const fvec2 & EngineInterface::quad2d_getUvOffset(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getUvOffset();
}

const fvec3 & EngineInterface::quad2d_getColor(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->getColor();
}

const bool EngineInterface::quad2d_isVisible(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->isVisible();
}

const bool EngineInterface::quad2d_isCentered(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->isCentered();
}

const bool EngineInterface::quad2d_hasDiffuseMap(const string & quad2dId) const
{
	return (_core->getQuad2dManager()->getQuad2d(quad2dId)->getDiffuseTextureBuffer() != nullptr);
}

const bool EngineInterface::quad2d_isWireframed(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->isWireframed();
}

const bool EngineInterface::quad2d_isAnimation2dStarted(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimation2dStarted(animation2dId, quad2dId);
}

const bool EngineInterface::quad2d_isAnimation2dPaused(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimation2dPaused(animation2dId, quad2dId);
}

const bool EngineInterface::quad2d_isAnimation2dAutopaused(const string & quad2dId, const string & animation2dId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimation2dAutopaused(animation2dId, quad2dId);
}

const bool EngineInterface::quad2d_isHorizontallyFlipped(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->isHorizontallyFlipped();
}

const bool EngineInterface::quad2d_isVerticallyFlipped(const string & quad2dId) const
{
	return _core->getQuad2dManager()->getQuad2d(quad2dId)->isVerticallyFlipped();
}