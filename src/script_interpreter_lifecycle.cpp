#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <sstream>

using std::istringstream;

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d,
									 Script& script,
									 SkyEditor& skyEditor,
									 TerrainEditor& terrainEditor,
									 WaterEditor& waterEditor,
									 ModelEditor& modelEditor,
									 BillboardEditor& billboardEditor,
									 QuadEditor& quadEditor,
									 Animation2dEditor& animation2dEditor,
									 Animation3dEditor& animation3dEditor,
									 SoundEditor& soundEditor,
									 WorldEditor& worldEditor)
	:
	_fe3d(fe3d),
	_script(script),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_quadEditor(quadEditor),
	_soundEditor(soundEditor),
	_animation2dEditor(animation2dEditor),
	_animation3dEditor(animation3dEditor),
	_worldEditor(worldEditor)
{

}

void ScriptInterpreter::load()
{
	auto lastLoggerMessageCount = Logger::getMessageCount();

	for(const auto& scriptID : _script.getScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		string scriptType = "";
		if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_initialize"))
		{
			_initializeScriptIDs.push_back(scriptID);
			scriptType = "script_type_initialize";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_update"))
		{
			_updateScriptIDs.push_back(scriptID);
			scriptType = "script_type_update";
		}
		else if(scriptFile->getLineText(0) == (META_KEYWORD + " script_type_terminate"))
		{
			_terminateScriptIDs.push_back(scriptID);
			scriptType = "script_type_terminate";
		}
		else
		{
			Logger::throwWarning("No script_type META found on line 1 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}

		if(scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_entry"))
		{
			if(scriptType == "script_type_initialize" && _initEntryID.empty())
			{
				_initEntryID = _initializeScriptIDs.back();
			}
			else if(scriptType == "script_type_update" && _updateEntryID.empty())
			{
				_updateEntryID = _updateScriptIDs.back();
			}
			else if(scriptType == "script_type_terminate" && _terminateEntryID.empty())
			{
				_terminateEntryID = _terminateScriptIDs.back();
			}
			else
			{
				Logger::throwWarning("Entry point for " + scriptType + " defined multiple times!");
				_hasThrownError = true;
				return;
			}
		}
		else if(scriptFile->getLineText(1) == (META_KEYWORD + " script_execution_waiting"))
		{
		}
		else
		{
			Logger::throwWarning("No script_execution META found on line 2 @ script \"" + scriptID + "\"");
			_hasThrownError = true;
			return;
		}
	}

	if(_initEntryID.empty() && !_initializeScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for INITIALIZE script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_updateEntryID.empty() && !_updateScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for UPDATE script(s)!");
		_hasThrownError = true;
		return;
	}
	if(_terminateEntryID.empty() && !_terminateScriptIDs.empty())
	{
		Logger::throwWarning("No script_execution_entry META defined for TERMINATE script(s)!");
		_hasThrownError = true;
		return;
	}

	for(const auto& scriptID : _script.getScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		for(unsigned int lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
		{
			auto scriptLineText = scriptFile->getLineText(lineIndex);
			auto scriptLineTextStream = istringstream(scriptLineText);
			string noWhiteSpace;
			scriptLineTextStream >> noWhiteSpace;

			if(noWhiteSpace.substr(0, 3) == "///")
			{
				unsigned int charIndex;
				for(charIndex = 0; charIndex < scriptLineText.size(); charIndex++)
				{
					if(scriptLineText[charIndex] != ' ')
					{
						break;
					}
				}

				scriptFile->setLineText(lineIndex, scriptLineText.substr(charIndex));
			}
		}
	}

	if(Config::getInst().isApplicationExported())
	{
		auto skyTexturePaths = _skyEditor.getTexturePathsFromFile();
		auto terrainTexturePaths = _terrainEditor.getTexturePathsFromFile();
		auto terrainBitmapPaths = _terrainEditor.getBitmapPathsFromFile();
		auto waterTexturePaths = _waterEditor.getTexturePathsFromFile();
		auto modelMeshPaths = _modelEditor.getMeshPathsFromFile();
		auto modelTexturePaths = _modelEditor.getTexturePathsFromFile();
		auto billboardTexturePaths = _billboardEditor.getTexturePathsFromFile();
		auto quadTexturePaths = _quadEditor.getTexturePathsFromFile();
		auto audioPaths = _soundEditor.getAudioPathsFromFile();

		_fe3d.misc_cacheMeshes(modelMeshPaths);

		vector<string> texturePaths2D;
		texturePaths2D.insert(texturePaths2D.end(), terrainTexturePaths.begin(), terrainTexturePaths.end());
		texturePaths2D.insert(texturePaths2D.end(), waterTexturePaths.begin(), waterTexturePaths.end());
		texturePaths2D.insert(texturePaths2D.end(), modelTexturePaths.begin(), modelTexturePaths.end());
		texturePaths2D.insert(texturePaths2D.end(), billboardTexturePaths.begin(), billboardTexturePaths.end());
		texturePaths2D.insert(texturePaths2D.end(), quadTexturePaths.begin(), quadTexturePaths.end());
		_fe3d.misc_cache2dTextures(texturePaths2D);

		_fe3d.misc_cache3dTextures(skyTexturePaths);

		_fe3d.misc_cacheBitmaps(terrainBitmapPaths);

		_fe3d.misc_cacheAudios(audioPaths);
	}

	_fe3d.sky_selectMainSky("");

	_skyEditor.loadFromFile();

	_terrainEditor.loadFromFile();

	_waterEditor.loadFromFile();

	_modelEditor.loadFromFile();

	_billboardEditor.loadFromFile();

	_quadEditor.loadFromFile();

	_animation2dEditor.loadFromFile(false);
	_animation3dEditor.loadFromFile(false);

	_soundEditor.loadFromFile();

	_fe3d.camera_reset();

	if(_fe3d.misc_isVsyncEnabled())
	{
		_fe3d.misc_disableVsync();
	}
	_fe3d.misc_setCursorVisible(true);

	_checkEngineWarnings(lastLoggerMessageCount);
}

void ScriptInterpreter::unload()
{
	_fe3d.sky_selectMixSky("");
	_fe3d.sky_setMixValue(0.0f);

	if(!Config::getInst().isApplicationExported())
	{
		_fe3d.sky_selectMainSky("@@background");
	}

	for(const auto& ID : _fe3d.sky_getIDs())
	{
		if(ID != "@@background")
		{
			_fe3d.sky_delete(ID);
		}
	}

	_animation2dEditor.stopBillboardAnimations();
	_animation2dEditor.stopQuadAnimations();
	_animation3dEditor.stopModelAnimations();

	_fe3d.terrain_deleteAll();
	_fe3d.water_deleteAll();
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.aabb_deleteAll();
	_fe3d.sound2d_deleteAll();
	_fe3d.sound3d_deleteAll();
	_fe3d.pointlight_deleteAll();
	_fe3d.spotlight_deleteAll();
	_fe3d.reflection_deleteAll();

	for(const auto& ID : _fe3d.quad_getIDs())
	{
		if(ID[0] != '@')
		{
			_fe3d.quad_delete(ID);
		}
	}

	for(const auto& ID : _fe3d.text_getIDs())
	{
		if(ID[0] != '@')
		{
			_fe3d.text_delete(ID);
		}
	}

	_fe3d.camera_reset();

	_fe3d.collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	if(_fe3d.collision_isCameraResponseEnabled())
	{
		_fe3d.collision_disableCameraResponse();
	}
	if(_fe3d.collision_isTerrainResponseEnabled())
	{
		_fe3d.collision_disableTerrainResponse();
	}

	if(_fe3d.raycast_isTerrainPointingEnabled())
	{
		_fe3d.raycast_disableTerrainPointing();
	}

	if(_fe3d.gfx_isAntiAliasingEnabled())
	{
		_fe3d.gfx_disableAntiAliasing(true);
	}
	if(_fe3d.gfx_isAmbientLightingEnabled())
	{
		_fe3d.gfx_disableAmbientLighting(true);
	}
	if(_fe3d.gfx_isDirectionalLightingEnabled())
	{
		_fe3d.gfx_disableDirectionalLighting(true);
	}
	if(_fe3d.gfx_isFogEnabled())
	{
		_fe3d.gfx_disableFog(true);
	}
	if(_fe3d.gfx_isShadowsEnabled())
	{
		_fe3d.gfx_disableShadows(true);
	}
	if(_fe3d.gfx_isSkyExposureEnabled())
	{
		_fe3d.gfx_disableSkyExposure(true);
	}
	if(_fe3d.gfx_isDofEnabled())
	{
		_fe3d.gfx_disableDOF(true);
	}
	if(_fe3d.gfx_isMotionBlurEnabled())
	{
		_fe3d.gfx_disableMotionBlur(true);
	}
	if(_fe3d.gfx_isLensFlareEnabled())
	{
		_fe3d.gfx_disableLensFlare(true);
	}
	if(_fe3d.gfx_isBloomEnabled())
	{
		_fe3d.gfx_disableBloom(true);
	}
	_fe3d.gfx_setCubeReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setPlanarReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d.gfx_setPlanarRefractionQuality(Config::MIN_REFRACTION_QUALITY);
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	if(_fe3d.server_isRunning())
	{
		_fe3d.server_stop();
	}

	if(_fe3d.client_isRunning())
	{
		_fe3d.client_stop();
	}

	if(_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if(_fe3d.misc_isWireframeRenderingEnabled())
	{
		_fe3d.misc_disableWireframeRendering();
	}
	if(!_fe3d.misc_isVsyncEnabled())
	{
		_fe3d.misc_enableVsync();
	}
	if(_fe3d.misc_isMillisecondTimerStarted())
	{
		_fe3d.misc_stopMillisecondTimer();
	}
	_fe3d.misc_setCursorVisible(false);

	_debuggingTimes.clear();
	_localVariables.clear();
	_currentScriptIDsStack.clear();
	_currentLineIndexStack.clear();
	_initializeScriptIDs.clear();
	_updateScriptIDs.clear();
	_terminateScriptIDs.clear();
	_globalVariables.clear();
	_initEntryID = "";
	_updateEntryID = "";
	_terminateEntryID = "";
	_engineFunctionCallCount = 0;
	_executionDepth = 0;
	_hasThrownError = false;
	_mustStopApplication = false;
	_hasPassedLoopStatement = false;
	_hasPassedIfStatement = false;
	_hasPassedElifStatement = false;
	_hasPassedElseStatement = false;
	_mustIgnoreDeeperScope = false;
	_isDebugging = false;
}