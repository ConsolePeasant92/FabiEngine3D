#pragma once

#include "script_event.hpp"

class ScriptEventTime : public ScriptEvent
{
public:
	using ScriptEvent::ScriptEvent;

	bool isTriggered() override;

private:

};