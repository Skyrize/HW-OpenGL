#pragma once
#include "Component.h"
#include "AnimationClip.h"
#include <vector>
class Transform;

class Animation :
    public Component
{
protected:
    std::vector<AnimationClip> clips;
    GLint currentClipIndex = -1;
    bool isPlaying = false;

public:
    Animation(Entity& parent);
    virtual void Start() override;
    virtual void Update() override;
    void Play(const std::string& clipName, Callback callback = nullptr);
    void AddClip(const Clip& clip);
};

