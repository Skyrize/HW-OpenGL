#pragma once
#include "Component.h"
#include "Input.h"
#include "Camera.h"
#include "CameraFPS.h"
#include "CameraController.h"
#include "Transform.h"
#include "LookAtTarget.h"
#include "AnimationClip.h"

enum class SceneState
{
    EXPLORING,
    OBSERVING,
    FOCUSING,
    DECONSTRUCTING,
    REBUILD,
    ANIMATED
};


class SceneController :
    public Component
{
private:
    SceneState state = SceneState::OBSERVING;
    KeyStatus* keyStatus = nullptr;
    LookAtTarget* camTarget = nullptr;
    CameraFPS* camFPS = nullptr;
    CameraController* camController = nullptr;
    Transform* camTransform = nullptr;
    Transform* arrowTransform = nullptr;
    Camera* mainCamera = nullptr;
    std::vector<Entity*> animated;
    int currentAnimated = 0;
    int currentDeconstructed = 0;
public:
    SceneController(Entity& parent) : Component(parent) {};
    virtual void Start() override;
    virtual void Update() override;

    void Focus();
    void Unfocus();
    void Select();
    void Unselect();
    void Deconstruct();
    void Reconstruct(Callback callback = nullptr);
    void SetObservationScene();
  
    void SetExplorationScene();
    void Next();
    void Previous();
    void NextDeconstruct();
    void PreviousDeconstruct();

};

