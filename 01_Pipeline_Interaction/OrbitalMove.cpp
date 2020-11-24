#include "OrbitalMove.h"
#include "RenderModule.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void OrbitalMove::Start()
{
	keyStatus = Input::Get().GetKeyStatus();
}

void OrbitalMove::Update()
{
	//if (keyStatus[GLFW_KEY_Z])	radius += radialSpeed;
	//if (keyStatus[GLFW_KEY_S])	radius -= radialSpeed;

	GLfloat		camX = sin(Time::Get().GetCurrentTime()) * radius * speed;
	camX += target.x;
	GLfloat		camZ = cos(Time::Get().GetCurrentTime()) * radius * speed;
	camZ += target.z;
	transform->SetPosition(glm::vec3(camX, target.y, camZ));
}

GLfloat OrbitalMove::GetRadius() const
{
	return radius;
}

void OrbitalMove::SetRadius(GLfloat radius)
{
	this->radius = radius;
}

GLfloat OrbitalMove::GetSpeed() const
{
	return speed;
}

void OrbitalMove::SetSpeed(GLfloat speed)
{
	this->speed = speed;
}

glm::vec3 OrbitalMove::GetTarget() const
{
    return target;
}

void OrbitalMove::SetTarget(glm::vec3 target)
{
    this->target = target;
}

//
//GLfloat OrbitalMove::GetRadialSpeed() const
//{
//    return radialSpeed;
//}
//
//void OrbitalMove::SetRadialSpeed(GLfloat radialSpeed)
//{
//    this->radialSpeed = radialSpeed;
//}
//
