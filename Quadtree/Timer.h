#pragma once
#include <SDL.h>
#include <stdio.h>

class Timer {
public:
	Timer(bool canStart);
	void Pause();
	void Unpause();
	void Start();
	float GetDeltaTime();
	float GetTotalElapsedTime();
	bool HasStarted();
	bool isPaused();
	void Stop();
	void ResetDeltaTime(float lastDeltaT);

private:
	bool started;
	bool paused;
	float startTicks;
	float pauseTicks;
	float LastDeltaTimeRequestTicks;


};

