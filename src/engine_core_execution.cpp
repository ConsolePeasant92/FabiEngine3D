#include "engine_core.hpp"
#include "engine_controller.hpp"

void EngineCore::_update()
{
	static ivec2 lastCursorPosition = _renderWindow->getCursorPosition();

	_timer->startClock("coreUpdate");
	if(_inputHandler->isKeyDown(InputType::WINDOW_X_BUTTON))
	{
		stop();
		return;
	}
	_engineController->update();
	_timer->stopClock("coreUpdate");

	_timer->startClock("physicsUpdate");
	_camera->update(lastCursorPosition);
	_cameraCollisionResponder->update();
	_raycastCalculator->update(_renderWindow->getCursorPosition());
	_raycastIntersector->update();
	_camera->updateMatrices();
	_timer->stopClock("physicsUpdate");

	_timer->startClock("3dEntityUpdate");
	_skyEntityManager->update();
	_waterEntityManager->update();
	_modelEntityManager->update();
	_quad3dEntityManager->update();
	_text3dEntityManager->update();
	_aabbEntityManager->update();
	_pointlightEntityManager->update();
	_spotlightEntityManager->update();
	_reflectionEntityManager->update();
	_timer->stopClock("3dEntityUpdate");

	_timer->startClock("2dEntityUpdate");
	_quad2dEntityManager->update();
	_text2dEntityManager->update();
	_timer->stopClock("2dEntityUpdate");

	_timer->startClock("renderUpdate");
	_masterRenderer->update();
	_timer->stopClock("renderUpdate");

	_timer->startClock("animationUpdate");
	_animation3dPlayer->update();
	_animation2dPlayer->update();
	_timer->stopClock("animationUpdate");

	_timer->startClock("soundUpdate");
	_sound3dManager->update();
	_sound2dManager->update();
	_sound3dPlayer->update();
	_sound2dPlayer->update();
	_timer->stopClock("soundUpdate");

	_timer->startClock("networkUpdate");
	_networkingServer->update();
	_networkingClient->update();
	_timer->stopClock("networkUpdate");

	_timer->startClock("miscUpdate");
	if(!Config::getInst().isApplicationExported())
	{
		static float opacity = 0.0f;

		if(opacity < 1.0f)
		{
			_renderWindow->setOpacity(opacity);
			opacity += 0.01f;
		}
		if(opacity > 1.0f)
		{
			opacity = 1.0f;
			_renderWindow->setOpacity(opacity);
		}
	}
	lastCursorPosition = _renderWindow->getCursorPosition();
	_timer->stopClock("miscUpdate");

	_updateDeltaTimes.at("coreUpdate") = _timer->getClockDeltaTime("coreUpdate");
	_updateDeltaTimes.at("physicsUpdate") = _timer->getClockDeltaTime("physicsUpdate");
	_updateDeltaTimes.at("3dEntityUpdate") = _timer->getClockDeltaTime("3dEntityUpdate");
	_updateDeltaTimes.at("2dEntityUpdate") = _timer->getClockDeltaTime("2dEntityUpdate");
	_updateDeltaTimes.at("renderUpdate") = _timer->getClockDeltaTime("renderUpdate");
	_updateDeltaTimes.at("animationUpdate") = _timer->getClockDeltaTime("animationUpdate");
	_updateDeltaTimes.at("soundUpdate") = _timer->getClockDeltaTime("soundUpdate");
	_updateDeltaTimes.at("networkUpdate") = _timer->getClockDeltaTime("networkUpdate");
	_updateDeltaTimes.at("miscUpdate") = _timer->getClockDeltaTime("miscUpdate");
}

void EngineCore::_render()
{
	_timer->startClock("depthPreRender");
	_masterRenderer->captureWorldDepth();
	_timer->stopClock("depthPreRender");
	_timer->startClock("shadowPreRender");
	_masterRenderer->captureShadows();
	_timer->stopClock("shadowPreRender");
	_timer->startClock("reflectionPreRender");
	_masterRenderer->captureCubeReflections();
	_masterRenderer->capturePlanarReflections();
	_timer->stopClock("reflectionPreRender");
	_timer->startClock("refractionPreRender");
	// insert capture cube/planar refractions here
	_timer->stopClock("refractionPreRender");
	_timer->startClock("waterPreRender");
	_masterRenderer->captureWaterReflections();
	_masterRenderer->captureWaterRefractions();
	_masterRenderer->captureWaterEdges();
	_timer->stopClock("waterPreRender");

	_timer->startClock("3dEntityRender");
	_masterRenderer->render3dEntities();
	_timer->stopClock("3dEntityRender");

	_timer->startClock("antiAliasingPostRender");
	_masterRenderer->captureAntiAliasing();
	_timer->stopClock("antiAliasingPostRender");
	_timer->startClock("bloomPreRender");
	_masterRenderer->captureBloom();
	_timer->stopClock("bloomPreRender");
	_timer->startClock("dofPreRender");
	_masterRenderer->captureDof();
	_timer->stopClock("dofPreRender");
	_timer->startClock("lensFlarePreRender");
	_masterRenderer->captureLensFlare();
	_timer->stopClock("lensFlarePreRender");
	_timer->startClock("motionBlurPreRender");
	_masterRenderer->captureMotionBlur();
	_timer->stopClock("motionBlurPreRender");

	_timer->startClock("2dEntityRender");
	_masterRenderer->render2dEntities();
	_timer->stopClock("2dEntityRender");

	_renderDeltaTimes.at("depthPreRender") = _timer->getClockDeltaTime("depthPreRender");
	_renderDeltaTimes.at("shadowPreRender") = _timer->getClockDeltaTime("shadowPreRender");
	_renderDeltaTimes.at("reflectionPreRender") = _timer->getClockDeltaTime("reflectionPreRender");
	_renderDeltaTimes.at("refractionPreRender") = _timer->getClockDeltaTime("refractionPreRender");
	_renderDeltaTimes.at("waterPreRender") = _timer->getClockDeltaTime("waterPreRender");
	_renderDeltaTimes.at("3dEntityRender") = _timer->getClockDeltaTime("3dEntityRender");
	_renderDeltaTimes.at("antiAliasingPostRender") = _timer->getClockDeltaTime("antiAliasingPostRender");
	_renderDeltaTimes.at("bloomPreRender") = _timer->getClockDeltaTime("bloomPreRender");
	_renderDeltaTimes.at("dofPreRender") = _timer->getClockDeltaTime("dofPreRender");
	_renderDeltaTimes.at("lensFlarePreRender") = _timer->getClockDeltaTime("lensFlarePreRender");
	_renderDeltaTimes.at("motionBlurPreRender") = _timer->getClockDeltaTime("motionBlurPreRender");
	_renderDeltaTimes.at("2dEntityRender") = _timer->getClockDeltaTime("2dEntityRender");
}