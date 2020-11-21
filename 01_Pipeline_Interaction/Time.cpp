#include "Time.h"

Time Time::instance;

void Time::Start()
{
}

void Time::Update()
{
	currentTime = (GLfloat)glfwGetTime();		// retrieve timelapse
	deltaTime = currentTime - lastTime;		// Calculate delta time
	lastTime = currentTime;					// Save for next frame calculations.
}

GLfloat Time::GetDeltaTime()
{
	return this->deltaTime;
}

GLfloat Time::GetCurrentTime()
{
	return this->currentTime;
}