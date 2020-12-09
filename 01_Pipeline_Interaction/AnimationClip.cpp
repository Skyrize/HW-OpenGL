#include "AnimationClip.h"
#include "Transform.h"
#include "Time.h"

AnimationClip::AnimationClip(Transform* target, const Clip &clip)
	: target(target), clip(clip)
{
}

void AnimationClip::Reset(Callback callback)
{
	this->callback = callback;
	this->currentTime = 0;
	this->isDone = false;
	target->SetPosition(clip.begin.GetPosition());
	target->SetScale(clip.begin.GetScale());
	target->SetRotation(clip.begin.GetRotation());
}


void AnimationClip::Play()
{
	if (isDone) {
		return;
	}

	if (currentTime >= clip.length) {
		isDone = true;
		target->SetPosition(clip.end.GetPosition());
		target->SetScale(clip.end.GetScale());
		target->SetRotation(clip.end.GetRotation());
		if (callback)
			callback();
	} else {
		GLfloat delta = Time::Get().GetDeltaTime();
		GLfloat t = currentTime / clip.length;
		glm::vec3 newPos = glm::mix(clip.begin.GetPosition(), clip.end.GetPosition(), t);
		glm::vec3 newScale = glm::mix(clip.begin.GetScale(), clip.end.GetScale(), t);
		glm::quat newRot = glm::slerp(clip.begin.GetRotation(), clip.end.GetRotation(), t);



		target->SetPosition(newPos);
		target->SetScale(newScale);
		target->SetRotation(newRot);
		currentTime += delta;
	}

}

std::string AnimationClip::GetName() const
{
    return clip.name;
}

