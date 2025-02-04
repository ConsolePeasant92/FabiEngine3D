#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <sstream>

void ScriptInterpreter::setCurrentProjectId(const string & projectId)
{
	_currentProjectId = projectId;
}

const bool ScriptInterpreter::hasThrownError() const
{
	return _hasThrownError;
}

const bool ScriptInterpreter::mustStopApplication() const
{
	return _mustStopApplication;
}

const int ScriptInterpreter::_getLeadingSpaces(const string & scriptLineText)
{
	int countedSpaces = 0;

	for(int index = 0; index < static_cast<int>(scriptLineText.size()); index++)
	{
		if(scriptLineText[index] == ' ')
		{
			if(index == (scriptLineText.size() - 1))
			{
				_throwRuntimeError("invalid syntax or statement");

				return 0;
			}
			else
			{
				countedSpaces++;
			}
		}
		else
		{
			break;
		}
	}

	return countedSpaces;
}

const bool ScriptInterpreter::_validateScopeDepth(int currentScopeDepth, int & targetScopeDepth)
{
	const auto isScopeDepthValid = (currentScopeDepth == (targetScopeDepth + static_cast<int>(_mustIgnoreDeeperScope)));

	if(_hasPassedLoopStatement && !isScopeDepthValid)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
	else if(_hasPassedIfStatement && !isScopeDepthValid)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
	else if(_hasPassedElifStatement && !isScopeDepthValid)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
	else if(_hasPassedElseStatement && !isScopeDepthValid)
	{
		_throwRuntimeError("invalid syntax or statement");

		return false;
	}
	else if(currentScopeDepth < targetScopeDepth)
	{
		targetScopeDepth = currentScopeDepth;

		_mustIgnoreDeeperScope = false;
	}
	else if(currentScopeDepth > targetScopeDepth)
	{
		if(_mustIgnoreDeeperScope)
		{
			return false;
		}
		else
		{
			_throwRuntimeError("invalid syntax or statement");

			return false;
		}
	}
	else
	{
		_mustIgnoreDeeperScope = false;
	}

	return true;
}

const bool ScriptInterpreter::_validateSavesDirectory()
{
	if(!Tools::isApplicationExported() && _currentProjectId.empty())
	{
		abort();
	}

	const auto isExported = Tools::isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto directoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "saves\\");

	if(!Tools::isDirectoryExisting(directoryPath))
	{
		_throwRuntimeError("Project corrupted: directory `saves\\` does not exist");

		return false;
	}

	return true;
}

void ScriptInterpreter::_throwStartupError(const string & message)
{
	Logger::throwWarning("ERROR @ script: " + message);

	_hasThrownError = true;
}

void ScriptInterpreter::_throwRuntimeError(const string & message)
{
	Logger::throwWarning("ERROR @ script \"" + _currentScriptIdsStack.back() + "\" @ line " + to_string(_currentLineIndexStack.back() + 1) + ": " + message);

	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings(int lastLoggerMessageCount)
{
	const auto messageCount = Logger::getMessageCount();

	if(messageCount > lastLoggerMessageCount)
	{
		for(int index = (lastLoggerMessageCount - 1); index < messageCount; index++)
		{
			if(Logger::getMessageList()[index]->getType() == LoggerMessageType::WARNING)
			{
				_hasThrownError = true;
			}
		}
	}
}

void ScriptInterpreter::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void ScriptInterpreter::inject(shared_ptr<Script> script)
{
	_script = script;
}

void ScriptInterpreter::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}

void ScriptInterpreter::inject(shared_ptr<Sound3dEditor> sound3dEditor)
{
	_sound3dEditor = sound3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<TerrainEditor> terrainEditor)
{
	_terrainEditor = terrainEditor;
}

void ScriptInterpreter::inject(shared_ptr<WaterEditor> waterEditor)
{
	_waterEditor = waterEditor;
}

void ScriptInterpreter::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void ScriptInterpreter::inject(shared_ptr<Quad3dEditor> quad3dEditor)
{
	_quad3dEditor = quad3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Sound2dEditor> sound2dEditor)
{
	_sound2dEditor = sound2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<AabbEditor> aabbEditor)
{
	_aabbEditor = aabbEditor;
}

void ScriptInterpreter::inject(shared_ptr<Quad2dEditor> quad2dEditor)
{
	_quad2dEditor = quad2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Text3dEditor> text3dEditor)
{
	_text3dEditor = text3dEditor;
}

void ScriptInterpreter::inject(shared_ptr<Text2dEditor> text2dEditor)
{
	_text2dEditor = text2dEditor;
}

void ScriptInterpreter::inject(shared_ptr<PointlightEditor> pointlightEditor)
{
	_pointlightEditor = pointlightEditor;
}

void ScriptInterpreter::inject(shared_ptr<SpotlightEditor> spotlightEditor)
{
	_spotlightEditor = spotlightEditor;
}

void ScriptInterpreter::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}

void ScriptInterpreter::inject(shared_ptr<CustomWorldBuilder> customWorldBuilder)
{
	_customWorldBuilder = customWorldBuilder;
}

void ScriptInterpreter::inject(shared_ptr<Duplicator> duplicator)
{
	_duplicator = duplicator;
}

void ScriptInterpreter::inject(shared_ptr<CaptorEditor> captorEditor)
{
	_captorEditor = captorEditor;
}