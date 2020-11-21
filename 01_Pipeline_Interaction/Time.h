#pragma once
#include "IObject.h"

class Time : public IObject
{
protected:
	GLfloat					deltaTime = 0.0f;
	GLfloat					lastTime = 0.0f;
	GLfloat					currentTime = 0.0f;
public:
	Time() {};
	virtual void Start() override;
	virtual void Update() override;
	GLfloat GetDeltaTime();
	GLfloat GetCurrentTime();


	//Singleton
private:
	static Time instance;
public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	static Time& Get() noexcept {
		return instance;
	}
};

