#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_is_quad3d_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad3dAnimationStarted(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad3d_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad3dAnimationPlaying(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad3d_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad3dAnimationPaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad3d_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad3dAnimationAutopaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationRowCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationColumnCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationRowIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationColumnIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationPlayCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad3d_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad3d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad3dAnimationFramestep(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad2d_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad2dAnimationStarted(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad2d_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad2dAnimationPlaying(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad2d_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad2dAnimationPaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad2d_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuad2dAnimationAutopaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationRowCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationColumnCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationRowIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationColumnIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationPlayCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad2d_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad2d(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuad2dAnimationFramestep(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation2d` functionality as networking server!");
	}

	return true;
}