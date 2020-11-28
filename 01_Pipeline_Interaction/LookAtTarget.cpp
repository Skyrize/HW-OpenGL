#include "LookAtTarget.h"
#include "RenderModule.h"
#include "Entity.h"

Entity* LookAtTarget::GetTarget() const
{
	return target;
}

void LookAtTarget::SetTarget(Entity* target)
{
	this->target = target;
}

void LookAtTarget::Start()
{
}

void LookAtTarget::Update()
{
	if (target)
		transform->LookAt(target->GetTransform()->GetPosition());
}

