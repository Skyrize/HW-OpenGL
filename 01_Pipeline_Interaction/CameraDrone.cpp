#include "CameraDrone.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void CameraDrone::Start()
{
	mainCamera = RenderModule::Get().GetMainCamera();
	keyStatus = Input::Get().GetKeyStatus();
}

void CameraDrone::Update()
{
	if (keyStatus[GLFW_KEY_Z])	radius += radialSpeed;
	if (keyStatus[GLFW_KEY_S])	radius -= radialSpeed;

	GLfloat		camX = sin(Time::Get().GetCurrentTime()) * radius * speed;
	GLfloat		camZ = cos(Time::Get().GetCurrentTime()) * radius * speed;
	transform->SetPosition(glm::vec3(camX, 0, camZ));
	mainCamera->LookAt(target);
}

GLfloat CameraDrone::GetRadius() const
{
	return radius;
}

void CameraDrone::SetRadius(GLfloat radius)
{
	this->radius = radius;
}

GLfloat CameraDrone::GetSpeed() const
{
	return speed;
}

void CameraDrone::SetSpeed(GLfloat speed)
{
	this->speed = speed;
}

glm::vec3 CameraDrone::GetTarget() const
{
    return target;
}

void CameraDrone::SetTarget(glm::vec3 target)
{
    this->target = target;
}


GLfloat CameraDrone::GetRadialSpeed() const
{
    return radialSpeed;
}

void CameraDrone::SetRadialSpeed(GLfloat radialSpeed)
{
    this->radialSpeed = radialSpeed;
}

