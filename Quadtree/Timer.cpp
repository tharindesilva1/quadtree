#include "Timer.h"



Timer::Timer(bool canStart) :
	started{ canStart },
	LastDeltaTimeRequestTicks{ 0.0f } {

	if(canStart) Start();
}

void Timer::Pause() {

	this->paused = true;
	pauseTicks = (float) SDL_GetTicks();
}

void Timer::Unpause() {

	this->paused = false;
	pauseTicks = 0;
}

void Timer::Start() {

	this->started = true;
	LastDeltaTimeRequestTicks = 0;
	startTicks = (float) SDL_GetTicks();
}

float Timer::GetDeltaTime() {

	float r = SDL_GetTicks() - LastDeltaTimeRequestTicks;

	LastDeltaTimeRequestTicks = r + LastDeltaTimeRequestTicks;
	auto c = r / 1000.0f;
	return c;
}

void Timer::ResetDeltaTime(float lastDeltaT) {
	//LastDeltaTimeRequestTicks = lastDeltaT;

}

float Timer::GetTotalElapsedTime() {
	float result = 0;
	if(started) {
		result = paused ? pauseTicks - startTicks : SDL_GetTicks() - startTicks;
		result /= 1000;
	}
	return result;
}

bool Timer::HasStarted() {
	return this->started;
}

bool Timer::isPaused() {
	return this->paused;
}

void Timer::Stop() {

	this->started = false;
	startTicks = 0;
}
