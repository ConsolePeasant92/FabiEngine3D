#include "captor_manager.hpp"

using std::make_shared;

const shared_ptr<Captor> CaptorManager::getCaptor(const string & captorId) const
{
	const auto iterator = _captors.find(captorId);

	if(iterator == _captors.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Captor>> & CaptorManager::getCaptors() const
{
	return _captors;
}

void CaptorManager::createCaptor(const string & captorId)
{
	if(isCaptorExisting(captorId))
	{
		abort();
	}

	const auto captor = make_shared<Captor>(captorId);

	_captors.insert({captorId, captor});
}

void CaptorManager::update()
{
	for(const auto & [captorId, captor] : _captors)
	{
		captor->updateTarget();
	}
}

void CaptorManager::deleteCaptor(const string & captorId)
{
	if(!isCaptorExisting(captorId))
	{
		abort();
	}

	_captors.erase(captorId);
}

void CaptorManager::deleteCaptors()
{
	_captors.clear();
}

const bool CaptorManager::isCaptorExisting(const string & captorId) const
{
	return (_captors.find(captorId) != _captors.end());
}

const bool CaptorManager::isCaptorsExisting() const
{
	return !_captors.empty();
}