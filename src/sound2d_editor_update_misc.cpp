#include "sound2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Sound2dEditor::_updateMiscellaneous()
{
	if(_fe3d->sound2d_isExisting(_currentSound2dId))
	{
		if(_fe3d->sound2d_isStarted(_currentSound2dId, 0))
		{
			if(_fe3d->sound2d_isPaused(_currentSound2dId, 0))
			{
				_fe3d->quad3d_setDiffuseMap("@@status", "engine\\assets\\image\\diffuse_map\\pause.tga");
			}
			else
			{
				_fe3d->quad3d_setDiffuseMap("@@status", "engine\\assets\\image\\diffuse_map\\start.tga");
			}
		}
		else
		{
			_fe3d->quad3d_setDiffuseMap("@@status", "engine\\assets\\image\\diffuse_map\\stop.tga");
		}
	}

	_fe3d->quad3d_setVisible("@@status", _fe3d->sound2d_isExisting(_currentSound2dId));
	_fe3d->quad3d_rotate("@@status", fvec3(0.0f, 0.5f, 0.0f));
}

void Sound2dEditor::_updateSound2dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createSound2d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto newSound2dId = _gui->getOverlay()->getValueFormContent();

		if(newSound2dId.empty())
		{
			Logger::throwWarning("Sound2D ID cannot be empty");

			return;
		}

		if(any_of(newSound2dId.begin(), newSound2dId.end(), isspace))
		{
			Logger::throwWarning("Sound2D ID cannot contain any spaces");

			return;
		}

		if(any_of(newSound2dId.begin(), newSound2dId.end(), isupper))
		{
			Logger::throwWarning("Sound2D ID cannot contain any capitals");

			return;
		}

		newSound2dId = ("@" + newSound2dId);

		if(find(_loadedSound2dIds.begin(), _loadedSound2dIds.end(), newSound2dId) != _loadedSound2dIds.end())
		{
			Logger::throwWarning("Sound2D already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		const auto rootPath = Tools::getRootDirectoryPath();
		const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\audio\\");

		if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

			return;
		}

		const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "WAV");
		if(filePath.empty())
		{
			return;
		}

		if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

			return;
		}

		const string finalFilePath = filePath.substr(rootPath.size());
		_fe3d->misc_clearAudioCache(finalFilePath);

		_fe3d->sound2d_create(newSound2dId, finalFilePath);

		if(_fe3d->sound2d_isExisting(newSound2dId))
		{
			_currentSound2dId = newSound2dId;
			_loadedSound2dIds.push_back(newSound2dId);
			sort(_loadedSound2dIds.begin(), _loadedSound2dIds.end());

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound2dEditorMenuChoice");
			_gui->getOverlay()->getTextField("sound2dId")->setTextContent("Sound2D: " + newSound2dId.substr(1));
			_gui->getOverlay()->getTextField("sound2dId")->setVisible(true);
		}
	}
}

void Sound2dEditor::_updateSound2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editSound2d") || (_gui->getOverlay()->getChoiceFormId() == "deleteSound2d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(_gui->getOverlay()->isChoiceFormConfirmed())
		{
			_currentSound2dId = ("@" + selectedOptionId);

			if(_gui->getOverlay()->getChoiceFormId() == "deleteSound2d")
			{
				_gui->getOverlay()->openAnswerForm("deleteSound2d", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
			}
			else
			{
				_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound2dEditorMenuChoice");

				_gui->getOverlay()->getTextField("sound2dId")->setTextContent("Sound2D: " + _currentSound2dId.substr(1));
				_gui->getOverlay()->getTextField("sound2dId")->setVisible(true);
			}
		}
	}
}

void Sound2dEditor::_updateSound2dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteSound2d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->sound2d_delete(_currentSound2dId);

			_loadedSound2dIds.erase(remove(_loadedSound2dIds.begin(), _loadedSound2dIds.end(), _currentSound2dId), _loadedSound2dIds.end());
			_currentSound2dId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentSound2dId = "";
		}
	}
}