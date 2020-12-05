#include "Animation.h"

Animation::Animation(Entity& parent)
	: Component(parent)
{
}

void Animation::Start()
{
}

void Animation::Update()
{
	if (currentClipIndex != -1)
		clips[currentClipIndex].Play();
}


void Animation::Play(const std::string& clipName)
{
	for (GLuint i = 0; i != clips.size(); i++) {
		if (clips[i].GetName() == clipName) {
			currentClipIndex = i;
			clips[currentClipIndex].Reset();
			return;
		}
	}
	throw("Error : can't find clip " + clipName);
}

void Animation::AddClip(const Clip& clip)
{
	for (GLuint i = 0; i != clips.size(); i++) {
		if (clips[i].GetName() == clip.name) {
			throw("Error : two clips with the same name " + clip.name);
		}
	}
	this->clips.push_back(AnimationClip(this->transform, clip));
}
