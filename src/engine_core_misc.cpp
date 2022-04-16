#include "engine_core.hpp"
#include "engine_controller.hpp"
#include "tools.hpp"

const shared_ptr<InputHandler> EngineCore::getInputHandler() const
{
	return _inputHandler;
}

const shared_ptr<MeshLoader> EngineCore::getMeshLoader() const
{
	return _meshLoader;
}

const shared_ptr<ImageLoader> EngineCore::getImageLoader() const
{
	return _imageLoader;
}

const shared_ptr<AudioLoader> EngineCore::getAudioLoader() const
{
	return _audioLoader;
}

const shared_ptr<SkyEntityManager> EngineCore::getSkyEntityManager() const
{
	return _skyEntityManager;
}

const shared_ptr<TerrainEntityManager> EngineCore::getTerrainEntityManager() const
{
	return _terrainEntityManager;
}

const shared_ptr<WaterEntityManager> EngineCore::getWaterEntityManager() const
{
	return _waterEntityManager;
}

const shared_ptr<ModelEntityManager> EngineCore::getModelEntityManager() const
{
	return _modelEntityManager;
}

const shared_ptr<Quad3dEntityManager> EngineCore::getQuad3dEntityManager() const
{
	return _quad3dEntityManager;
}

const shared_ptr<Text3dEntityManager> EngineCore::getText3dEntityManager() const
{
	return _text3dEntityManager;
}

const shared_ptr<AabbEntityManager> EngineCore::getAabbEntityManager() const
{
	return _aabbEntityManager;
}

const shared_ptr<Quad2dEntityManager> EngineCore::getQuad2dEntityManager() const
{
	return _quad2dEntityManager;
}

const shared_ptr<Text2dEntityManager> EngineCore::getText2dEntityManager() const
{
	return _text2dEntityManager;
}

const shared_ptr<PointlightEntityManager> EngineCore::getPointlightEntityManager() const
{
	return _pointlightEntityManager;
}

const shared_ptr<SpotlightEntityManager> EngineCore::getSpotlightEntityManager() const
{
	return _spotlightEntityManager;
}

const shared_ptr<ReflectionEntityManager> EngineCore::getReflectionEntityManager() const
{
	return _reflectionEntityManager;
}

const shared_ptr<Animation3dManager> EngineCore::getAnimation3dManager() const
{
	return _animation3dManager;
}

const shared_ptr<Animation2dManager> EngineCore::getAnimation2dManager() const
{
	return _animation2dManager;
}

const shared_ptr<RenderWindow> EngineCore::getRenderWindow() const
{
	return _renderWindow;
}

const shared_ptr<MasterRenderer> EngineCore::getMasterRenderer() const
{
	return _masterRenderer;
}

const shared_ptr<VertexBufferCache> EngineCore::getVertexBufferCache() const
{
	return _vertexBufferCache;
}

const shared_ptr<TextureBufferCache> EngineCore::getTextureBufferCache() const
{
	return _textureBufferCache;
}

const shared_ptr<WaveBufferCache> EngineCore::getWaveBufferCache() const
{
	return _waveBufferCache;
}

const shared_ptr<RenderStorage> EngineCore::getRenderStorage() const
{
	return _renderStorage;
}

const shared_ptr<Camera> EngineCore::getCamera() const
{
	return _camera;
}

const shared_ptr<RaycastCalculator> EngineCore::getRaycastCalculator() const
{
	return _raycastCalculator;
}

const shared_ptr<RaycastIntersector> EngineCore::getRaycastIntersector() const
{
	return _raycastIntersector;
}

const shared_ptr<CameraCollisionDetector> EngineCore::getCameraCollisionDetector() const
{
	return _cameraCollisionDetector;
}

const shared_ptr<CameraCollisionResponder> EngineCore::getCameraCollisionResponder() const
{
	return _cameraCollisionResponder;
}

const shared_ptr<Animation3dPlayer> EngineCore::getAnimation3dPlayer() const
{
	return _animation3dPlayer;
}

const shared_ptr<Animation2dPlayer> EngineCore::getAnimation2dPlayer() const
{
	return _animation2dPlayer;
}

const shared_ptr<Sound2dManager> EngineCore::getSound2dManager() const
{
	return _sound2dManager;
}

const shared_ptr<Sound3dManager> EngineCore::getSound3dManager() const
{
	return _sound3dManager;
}

const shared_ptr<Sound2dPlayer> EngineCore::getSound2dPlayer() const
{
	return _sound2dPlayer;
}

const shared_ptr<NetworkingHelper> EngineCore::getNetworkingHelper() const
{
	return _networkingHelper;
}

const shared_ptr<Sound3dPlayer> EngineCore::getSound3dPlayer() const
{
	return _sound3dPlayer;
}

const shared_ptr<NetworkingServer> EngineCore::getNetworkingServer() const
{
	return _networkingServer;
}

const shared_ptr<NetworkingClient> EngineCore::getNetworkingClient() const
{
	return _networkingClient;
}

const shared_ptr<Timer> EngineCore::getTimer() const
{
	return _timer;
}

void EngineCore::inject(shared_ptr<EngineController> engineController)
{
	_engineController = engineController;
}

const float EngineCore::getTotalDeltaTime() const
{
	return _totalDeltaTime;
}

const bool EngineCore::isRunning() const
{
	return _isRunning;
}

const unordered_map<string, float> & EngineCore::getUpdateDeltaTimes() const
{
	return _updateDeltaTimes;
}

const unordered_map<string, float> & EngineCore::getRenderDeltaTimes() const
{
	return _renderDeltaTimes;
}

void EngineCore::_initialize()
{
	const auto logoPath = (Configuration::getInst().isApplicationExported() ? "logo\\logo.tga" : "engine\\assets\\image\\diffuse_map\\logo.tga");
	const auto monitorSize = Tools::getMonitorSize();
	const auto windowSize = Configuration::getInst().getWindowSize();
	const auto logoSize = ivec2(static_cast<int>(static_cast<float>(monitorSize.x) * 0.4f), static_cast<int>(static_cast<float>(monitorSize.y) * 0.2f));
	const auto windowPosition = ((monitorSize - windowSize) / 2);
	const auto logoPosition = ((monitorSize - logoSize) / 2);
	const auto keyingColor = fvec3(0.1f);

	_imageLoader->cacheImage(logoPath, true);

	shared_ptr<Quad2dEntity> logo = make_shared<Quad2dEntity>("logo");
	logo->setVertexBuffer(make_shared<VertexBuffer>(0.0f, 0.0f, 2.0f, 2.0f, true));
	logo->setDiffuseMap(make_shared<TextureBuffer>(_imageLoader->loadImage(logoPath)));
	logo->setCentered(true);

	_renderWindow->setVisible(true);
	_renderWindow->setColorKeyingEnabled(true);
	_renderWindow->setKeyingColor(keyingColor);
	_renderWindow->setPosition(logoPosition);
	_renderWindow->setSize(logoSize);

	_masterRenderer->setBackgroundColor(fvec4(keyingColor.r, keyingColor.g, keyingColor.b, 1.0f));
	_masterRenderer->renderLogo(logo, logoSize);
	_masterRenderer->setBackgroundColor(fvec4(0.0f, 0.0f, 0.0f, 1.0f));

	_renderWindow->swapBuffer();

	_engineController->initialize();

	if(_isRunning)
	{
		_update();

		if(_networkingServer->isRunning())
		{
			_renderWindow->setVisible(false);
		}
		else
		{
			_renderWindow->setColorKeyingEnabled(false);
			_renderWindow->setPosition(windowPosition);
			_renderWindow->setSize(windowSize);
			_renderWindow->swapBuffer();
		}
	}
}