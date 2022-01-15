#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:graphics_enable_fog")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableFog();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_fog")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableFog(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setFogColor(fvec3(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal()));

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_thickness")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setFogThickness(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_min_fog_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setFogMinDistance(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_max_fog_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setFogMaxDistance(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_dof")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableDOF();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_dof")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableDOF(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setDofDynamicDistance(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_blur_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setDofBlurDistance(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setDofDynamic(args[0].getBoolean());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setDofQuality(args[0].getInteger());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_motion_blur")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableMotionBlur();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_motion_blur")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableMotionBlur(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_strength")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setMotionBlurStrength(args[0].getDecimal());
			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_quality")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setMotionBlurQuality(args[0].getInteger());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_lens_flare")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableLensFlare();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_lens_flare")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableLensFlare(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dGraphicsSetter");
			}

			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\image\\misc\\flare_map\\");
			const auto filePath = (targetDirectoryPath + args[0].getString());

			_fe3d->gfx_setLensFlareMap(filePath);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setLensFlareIntensity(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_sensitivity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setLensFlareSensitivity(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setBloomIntensity(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_quality")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setBloomQuality(args[0].getInteger());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_blur_count")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setBloomBlurCount(args[0].getInteger());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_type")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString() == "EVERYTHING")
			{
				_fe3d->gfx_setBloomType(BloomType::EVERYTHING);

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else if(args[0].getString() == "PARTS")
			{
				_fe3d->gfx_setBloomType(BloomType::PARTS);

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
			else
			{
				Logger::throwWarning("invalid bloom type!");

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:graphics_set_enable_bloom")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableBloom();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_disable_bloom")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableBloom(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_speed")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setSkyExposureSpeed(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->gfx_setSkyExposureIntensity(args[0].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_sky_exposure")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_enableSkyExposure();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_sky_exposure")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->gfx_disableSkyExposure(false);

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:graphics` functionality as networking server!");
	}

	return true;
}