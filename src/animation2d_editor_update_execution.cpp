#include "animation2d_editor.hpp"

void Animation2dEditor::_updateBillboardAnimationExecution()
{
	for(auto& [idPair, animation] : _startedBillboardAnimations)
	{
		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						if(animation.getPlayCount() == -1)
						{
							_billboardAnimationsToStop.insert(idPair);
							_billboardAnimationsToStart.insert(idPair);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_billboardAnimationsToStop.insert(idPair);
							}
							else
							{
								animation.setRowIndex(0);
							}
						}
					}
					else
					{
						animation.setRowIndex(animation.getRowIndex() + 1);
					}
				}
				else
				{
					animation.setColumnIndex(animation.getColumnIndex() + 1);
				}
			}
			else
			{
				animation.setPassedFrames(animation.getPassedFrames() + 1);
			}
		}

		fvec2 uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
							   (static_cast<float>(animation.getRowCount() - animation.getRowIndex() - 1) * uvMultiplier.y));

		_fe3d.billboard_setUvMultiplier(idPair.second, uvMultiplier);
		_fe3d.billboard_setUvOffset(idPair.second, uvOffset);
	}

	for(const auto& idPair : _billboardAnimationsToStop)
	{
		if(isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			stopBillboardAnimation(idPair.first, idPair.second);
		}
	}
	_billboardAnimationsToStop.clear();

	for(const auto& idPair : _billboardAnimationsToStart)
	{
		if(!isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			startBillboardAnimation(idPair.first, idPair.second, -1);
		}
	}
	_billboardAnimationsToStart.clear();
}

void Animation2dEditor::_updateQuadAnimationExecution()
{
	for(auto& [idPair, animation] : _startedQuadAnimations)
	{
		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						if(animation.getPlayCount() == -1)
						{
							_quadAnimationsToStop.insert(idPair);
							_quadAnimationsToStart.insert(idPair);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_quadAnimationsToStop.insert(idPair);
							}
							else
							{
								animation.setRowIndex(0);
							}
						}
					}
					else
					{
						animation.setRowIndex(animation.getRowIndex() + 1);
					}
				}
				else
				{
					animation.setColumnIndex(animation.getColumnIndex() + 1);
				}
			}
			else
			{
				animation.setPassedFrames(animation.getPassedFrames() + 1);
			}
		}

		fvec2 uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
							   (static_cast<float>(animation.getRowIndex()) * uvMultiplier.y));

		_fe3d.quad_setUvMultiplier(idPair.second, uvMultiplier);
		_fe3d.quad_setUvOffset(idPair.second, uvOffset);
	}

	for(const auto& idPair : _quadAnimationsToStop)
	{
		if(isQuadAnimationStarted(idPair.first, idPair.second))
		{
			stopQuadAnimation(idPair.first, idPair.second);
		}
	}
	_quadAnimationsToStop.clear();

	for(const auto& idPair : _quadAnimationsToStart)
	{
		if(!isQuadAnimationStarted(idPair.first, idPair.second))
		{
			startQuadAnimation(idPair.first, idPair.second, -1);
		}
	}
	_quadAnimationsToStart.clear();
}