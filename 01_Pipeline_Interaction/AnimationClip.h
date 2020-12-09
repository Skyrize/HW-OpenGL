#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Transform.h"
#include <functional>

//typedef void (*Callback)();
using Callback = std::function<void()>;
struct Clip {
	std::string name = "";
	GLfloat length = 0;
	Transform begin;
	Transform end;

	Clip(const std::string& name, GLfloat length, const Transform& begin, const Transform& end)
		: name(name), length(length), begin(begin), end(end)
	{

	};
};

class AnimationClip
{
protected:
	Transform* target;
	Clip clip;
	GLfloat currentTime = 0;
	bool isDone = true;
	Callback callback = nullptr;
public:
	AnimationClip(Transform* target, const Clip& clip);
	void Reset(Callback callback);
	void Play();
    std::string GetName() const;

};

