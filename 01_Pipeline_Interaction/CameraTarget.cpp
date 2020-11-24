#include "CameraTarget.h"
#include "RenderModule.h"
#include "Entity.h"

Entity* CameraTarget::GetTarget() const
{
    return target;
}

void CameraTarget::SetTarget(Entity* target)
{
    this->target = target;
}

void CameraTarget::Start()
{
	mainCamera = RenderModule::Get().GetMainCamera();
}

void CameraTarget::Update()
{
	if (target)
		mainCamera->LookAt(target->GetTransform()->GetPosition());
}

