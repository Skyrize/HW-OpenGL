#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Transform.h"

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
public:
	AnimationClip(Transform* target, const Clip &clip);
	void Reset();
	void Play();
    std::string GetName() const;

};

