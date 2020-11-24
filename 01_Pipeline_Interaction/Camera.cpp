#include "Camera.h"
#include <GLM/gtx/transform.hpp>
#include "Entity.h"

Camera::Camera(Entity& parent)
    : Component(parent)
{
}

void Camera::Move(glm::vec3 distance)
{
    transform->Translate(distance);
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(transform->GetPosition(),					// eye
        transform->GetPosition() + transform->GetFront(),	// centre
        transform->GetUp());
}

glm::mat4 Camera::LookAt(const glm::vec3 &target)
{
    transform->LookAt(target);
    return GetView();
}

void Camera::UpdateAspectRender(GLfloat newAspect)
{
    projMatrix = glm::perspective(glm::radians(fovy), newAspect, zNear, zFar);
}

void Camera::Start()
{
}

void Camera::Update()
{
    //std::cout << "pos = " << VTS(transform->GetPosition()) << std::endl;
}


glm::mat4 Camera::GetProjection() const
{
    return projMatrix;
}

void Camera::SetFovy(GLfloat fovy)
{
    this->fovy = fovy;
}