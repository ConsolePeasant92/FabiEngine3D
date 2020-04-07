#pragma once
#include <windows.h>
#include <map>
#include <string>

using std::string;

class Timer final
{
public:
	Timer()  = default;
	~Timer() = default;

	void setCustomDeltaTime(float delta);
	void calculateDeltaTime();
	void start(const string& ID);
	void stop();

	float getDeltaPart(const string& ID);
	float getDeltaTime();

	void uSleep(int waitTime);

private:
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _time1, _time2;

	std::map<string, float> _deltaParts;

	string _currentID = "";

	float _deltaTime = 0.0f;
};