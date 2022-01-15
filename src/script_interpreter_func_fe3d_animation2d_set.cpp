#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_start_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->startBillboardAnimation(args[0].getString(), args[1].getString(), args[2].getInteger());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->pauseBillboardAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_all_billboards")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->pauseBillboardAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_autopause_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->autopauseBillboardAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_autopause_all_billboards")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->autopauseBillboardAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->resumeBillboardAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_all_billboards")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->resumeBillboardAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->stopBillboardAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_all_billboards")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->stopBillboardAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_set_billboard_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				_animation2dEditor->setBillboardAnimationFramestep(args[0].getString(), args[1].getString(), args[1].getInteger());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_start_quad")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->startQuadAnimation(args[0].getString(), args[1].getString(), args[2].getInteger());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_quad")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->pauseQuadAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_all_quads")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->pauseQuadAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_autopause_quad")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->autopauseQuadAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_autopause_all_quads")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->autopauseQuadAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_quad")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->resumeQuadAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_all_quads")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->resumeQuadAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_quad")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->stopQuadAnimation(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_all_quads")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->stopQuadAnimations();

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_set_quad_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				_animation2dEditor->setQuadAnimationFramestep(args[0].getString(), args[1].getString(), args[1].getInteger());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation3d` functionality as networking server!");
	}

	return true;
}