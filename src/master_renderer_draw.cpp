#include "master_renderer.hpp"
#include "render_storage.hpp"

#include <functional>
#include <map>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;
using std::map;

void MasterRenderer::renderLogo(shared_ptr<Quad2d> quad2d, const ivec2 & size)
{
	glViewport(0, 0, size.x, size.y);
	glClear(GL_COLOR_BUFFER_BIT);

	_quad2dColorRenderer->bind();
	_quad2dColorRenderer->render(quad2d);
	_quad2dColorRenderer->unbind();

	glViewport(0, 0, Tools::getWindowSize().x, Tools::getWindowSize().y);
}

void MasterRenderer::render3d()
{
	_worldColorCaptureBuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderStorage->setTriangleCountingEnabled(true);

	_renderSky();
	_renderTerrain();
	_renderWater();
	_renderOpaqueModels();
	_renderOpaqueQuad3ds();
	_renderOpaqueText3ds();
	_renderAabbs();
	_renderTransparentModels();
	_renderTransparentQuad3ds();
	_renderTransparentText3ds();

	_renderStorage->setTriangleCountingEnabled(false);

	_worldColorCaptureBuffer->unbind();

	_renderStorage->setPrimarySceneMap(_worldColorCaptureBuffer->getTexture(0));
	_renderStorage->setSecondarySceneMap(_worldColorCaptureBuffer->getTexture(1));
	_renderStorage->setFinalSceneMap(_renderStorage->getPrimarySceneTextureBuffer());
}

void MasterRenderer::render2d()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(Tools::getDisplayPosition().x, Tools::getDisplayPosition().y, Tools::getDisplaySize().x, Tools::getDisplaySize().y);

	_renderFinalScene();

	glViewport(0, 0, Tools::getWindowSize().x, Tools::getWindowSize().y);

	_renderStorage->setTriangleCountingEnabled(true);

	_renderGUI();

	_renderStorage->setTriangleCountingEnabled(false);
}

void MasterRenderer::_renderSky()
{
	if(_skyManager->getSelectedSky() != nullptr)
	{
		_skyColorRenderer->bind();
		_skyColorRenderer->render(_skyManager->getSelectedSky());
		_skyColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTerrain()
{
	if(_terrainManager->getSelectedTerrain() != nullptr)
	{
		_terrainColorRenderer->bind();
		_terrainColorRenderer->processPointlights(_pointlightManager->getPointlights());
		_terrainColorRenderer->processSpotlights(_spotlightManager->getSpotlights());
		_terrainColorRenderer->render(_terrainManager->getSelectedTerrain());
		_terrainColorRenderer->unbind();
	}
}

void MasterRenderer::_renderWater()
{
	if(_waterManager->getSelectedWater() != nullptr)
	{
		_waterColorRenderer->bind();
		_waterColorRenderer->processPointlights(_pointlightManager->getPointlights());
		_waterColorRenderer->processSpotlights(_spotlightManager->getSpotlights());
		_waterColorRenderer->render(_waterManager->getSelectedWater());
		_waterColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueModels()
{
	if(!_modelManager->getModels().empty())
	{
		_modelColorRenderer->bind();
		_modelColorRenderer->processPointlights(_pointlightManager->getPointlights());
		_modelColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		for(const auto & [modelId, model] : _modelManager->getModels())
		{
			bool isTransparent = false;

			for(const auto & partId : model->getPartIds())
			{
				if(model->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;
				}
			}

			if(isTransparent)
			{
				continue;
			}

			if(model->isLevelOfDetailed())
			{
				const auto levelOfDetailModel = _modelManager->getModels().find(model->getLevelOfDetailId())->second;
				const auto originalPosition = levelOfDetailModel->getBasePosition();
				const auto originalRotation = levelOfDetailModel->getBaseRotation();
				const auto originalSize = levelOfDetailModel->getBaseSize();
				const auto originalVisibility = levelOfDetailModel->isVisible();

				levelOfDetailModel->setBasePosition(model->getBasePosition());
				levelOfDetailModel->setBaseRotation(model->getBaseRotation());
				levelOfDetailModel->setBaseSize(model->getBaseSize());
				levelOfDetailModel->setVisible(model->isVisible());
				levelOfDetailModel->updateTransformation();

				_modelColorRenderer->render(levelOfDetailModel, _captorManager->getCaptors());

				levelOfDetailModel->setBasePosition(originalPosition);
				levelOfDetailModel->setBaseRotation(originalRotation);
				levelOfDetailModel->setBaseSize(originalSize);
				levelOfDetailModel->setVisible(originalVisibility);
				levelOfDetailModel->updateTransformation();
			}
			else
			{
				_modelColorRenderer->render(model, _captorManager->getCaptors());
			}
		}

		_modelColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentModels()
{
	if(!_modelManager->getModels().empty())
	{
		_modelColorRenderer->bind();
		_modelColorRenderer->processPointlights(_pointlightManager->getPointlights());
		_modelColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		for(const auto & [modelId, model] : _modelManager->getModels())
		{
			bool isTransparent = false;

			for(const auto & partId : model->getPartIds())
			{
				if(model->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;

					break;
				}
			}

			if(!isTransparent)
			{
				continue;
			}

			if(model->isLevelOfDetailed())
			{
				const auto levelOfDetailModel = _modelManager->getModels().find(model->getLevelOfDetailId())->second;
				const auto originalPosition = levelOfDetailModel->getBasePosition();
				const auto originalRotation = levelOfDetailModel->getBaseRotation();
				const auto originalSize = levelOfDetailModel->getBaseSize();
				const auto originalVisibility = levelOfDetailModel->isVisible();

				levelOfDetailModel->setBasePosition(model->getBasePosition());
				levelOfDetailModel->setBaseRotation(model->getBaseRotation());
				levelOfDetailModel->setBaseSize(model->getBaseSize());
				levelOfDetailModel->setVisible(model->isVisible());
				levelOfDetailModel->updateTransformation();

				_modelColorRenderer->render(levelOfDetailModel, _captorManager->getCaptors());

				levelOfDetailModel->setBasePosition(originalPosition);
				levelOfDetailModel->setBaseRotation(originalRotation);
				levelOfDetailModel->setBaseSize(originalSize);
				levelOfDetailModel->setVisible(originalVisibility);
				levelOfDetailModel->updateTransformation();
			}
			else
			{
				_modelColorRenderer->render(model, _captorManager->getCaptors());
			}
		}

		_modelColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueQuad3ds()
{
	if(!_quad3dManager->getQuad3ds().empty())
	{
		_quad3dColorRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
		{
			if(quad3d->getOpacity() < 1.0f)
			{
				continue;
			}

			_quad3dColorRenderer->render(quad3d);
		}

		_quad3dColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentQuad3ds()
{
	if(!_quad3dManager->getQuad3ds().empty())
	{
		_quad3dColorRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
		{
			if(quad3d->getOpacity() == 1.0f)
			{
				continue;
			}

			_quad3dColorRenderer->render(quad3d);
		}

		_quad3dColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueText3ds()
{
	if(!_text3dManager->getText3ds().empty())
	{
		_quad3dColorRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getOpacity() < 1.0f)
			{
				continue;
			}

			for(const auto & quad3d : text3d->getQuad3ds())
			{
				_quad3dColorRenderer->render(quad3d);
			}
		}

		_quad3dColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentText3ds()
{
	if(!_text3dManager->getText3ds().empty())
	{
		_quad3dColorRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getOpacity() == 1.0f)
			{
				continue;
			}

			for(const auto & quad3d : text3d->getQuad3ds())
			{
				_quad3dColorRenderer->render(quad3d);
			}
		}

		_quad3dColorRenderer->unbind();
	}
}

void MasterRenderer::_renderAabbs()
{
	if(!_aabbManager->getAabbs().empty())
	{
		_aabbColorRenderer->bind();

		for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
		{
			_aabbColorRenderer->render(aabb);
		}

		_aabbColorRenderer->unbind();
	}
}

void MasterRenderer::_renderFinalScene()
{
	_renderSurface->setDiffuseMap(_renderStorage->getFinalSceneTextureBuffer());

	_quad2dColorRenderer->bind();
	_quad2dColorRenderer->render(_renderSurface);
	_quad2dColorRenderer->unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_quad2dManager->getQuad2ds().empty() || !_text2dManager->getText2ds().empty())
	{
		_quad2dColorRenderer->bind();

		map<int, vector<shared_ptr<Quad2d>>> orderedQuad2ds = {};

		for(const auto & [quad2dId, quad2d] : _quad2dManager->getQuad2ds())
		{
			if(quad2d->getId() != _renderStorage->getCursorId())
			{
				orderedQuad2ds.insert({quad2d->getDepth(), {quad2d}});
			}
		}

		for(const auto & [text2dId, text2d] : _text2dManager->getText2ds())
		{
			vector<shared_ptr<Quad2d>> quad2ds = {};

			for(const auto & quad2d : text2d->getQuad2ds())
			{
				quad2ds.push_back(quad2d);
			}

			orderedQuad2ds.insert({text2d->getDepth(), quad2ds});
		}

		for(const auto & [quad2dId, quad2ds] : orderedQuad2ds)
		{
			for(const auto & quad2d : quad2ds)
			{
				_quad2dColorRenderer->render(quad2d);
			}
		}
	}

	if(!_renderStorage->getCursorId().empty())
	{
		_quad2dColorRenderer->render(_quad2dManager->getQuad2ds().at(_renderStorage->getCursorId()));
	}

	_quad2dColorRenderer->unbind();
}