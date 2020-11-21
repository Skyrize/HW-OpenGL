#include "Transform.h"
#include "Entity.h"

void Transform::UpdateVectors()
{
    //eulerAngles = glm::eulerAngles(this->rotation);
    //eulerAngles.x = glm::degrees(atan2(2 * rotation.x * rotation.w - 2 * rotation.y * rotation.z, 1 - 2 * rotation.x * rotation.x - 2 * rotation.z * rotation.z));
    //eulerAngles.y = glm::degrees(atan2(2 * rotation.y * rotation.w - 2 * rotation.x * rotation.z, 1 - 2 * rotation.y * rotation.y - 2 * rotation.z * rotation.z));
    //eulerAngles.x = glm::degrees(asin(2 * rotation.x * rotation.y + 2 * rotation.z * rotation.w));

 //   front.x = cos(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.y));
 //   front.y = sin(glm::radians(eulerAngles.y));
 //   front.z = sin(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.y));
 //   front = glm::normalize(front);

 //   right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
 //   up = glm::normalize(glm::cross(right, front));

	//std::cout << "transform " + this->name + " : euler: " << VTS(eulerAngles) << " | front :" << VTS(front) << " | up :" << VTS(up) << " | right :" << VTS(right) << std::endl;
	//std::cout << "transform2 " + this->name + " : euler: " << VTS(eulerAngles) << " | front :" << VTS(GetFront()) << " | up :" << VTS(GetUp()) << " | right :" << VTS(GetRight()) << std::endl << std::endl;
}

Transform::Transform(Entity& parent)
	: Component(parent)
{
}

void Transform::Start()
{
}

void Transform::Update()
{
}

glm::mat4 Transform::GetModelMatrix()
{
    glm::mat4 modelMatrix = GetTranslationMatrix();
    //if (parent.GetName() == "cube")
    //std::cout << "hein trans \n" << MTS(modelMatrix) << std::endl;
    modelMatrix *= GetRotationMatrix();
    //if (parent.GetName() == "cube")
    //std::cout << "hein trans + rot \n" << MTS(modelMatrix) << std::endl;
    modelMatrix *= GetScaleMatrix();
    //if (parent.GetName() == "cube")
    //std::cout << "hein trans + rot + scale \n" << MTS(modelMatrix) << std::endl;

	return modelMatrix;
}

glm::mat4 Transform::GetTranslationMatrix()
{
    return glm::translate(glm::mat4(1), this->position);
}

glm::mat4 Transform::GetRotationMatrix()
{
	return glm::toMat4(this->rotation);
}

glm::mat4 Transform::GetScaleMatrix()
{
    return glm::scale(glm::mat4(1), this->scale);
}



glm::vec3 Transform::GetRotationEuler()
{
    //return this->eulerAngles;
    glm::vec3 euler = glm::eulerAngles(this->rotation);

    euler.x = glm::degrees(euler.x);
    euler.y = glm::degrees(euler.y);
    euler.z = glm::degrees(euler.z);
	return euler;
}

void Transform::Translate(glm::vec3 translation)
{
    this->position += translation;
}

void Transform::LookAt(glm::vec3 direction)
{
    this->SetRotation(direction * this->rotation);
}

void Transform::Rotate(glm::vec3 euler)
{
    glm::vec3 radians(glm::radians(euler.x), glm::radians(euler.y), glm::radians(euler.z));
    this->SetRotation(glm::quat(radians) * this->rotation);
}

void Transform::RotateAround(glm::vec3 point, glm::vec3 axis, GLfloat angle)
{
}

glm::vec3 Transform::GetPosition() const
{
    return position;
} 

void Transform::SetPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Transform::GetScale() const
{
    return scale;
}

void Transform::SetScale(glm::vec3 scale)
{
    this->scale = scale;
}

glm::quat Transform::GetRotation() const
{
    return rotation;
}

void Transform::SetRotation(glm::quat rotation)
{
    this->rotation = glm::normalize(rotation);
}

void Transform::SetRotation(glm::vec3 eulerAngles)
{
    glm::vec3 radians(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
    SetRotation(glm::quat(radians));
}

void Transform::SetRotation(float eulerX, float eulerY, float eulerZ)
{
    SetRotation(glm::vec3(eulerX, eulerY, eulerZ));
}

glm::vec3 Transform::GetFront() const
{
	return this->rotation * glm::vec3(0, 0, -1);
}

void Transform::SetFront(glm::vec3 front)
{
	SetRotation(glm::lookAt(this->position, this->position + front, glm::vec3(0, 1, 0)));
}

glm::vec3 Transform::GetUp() const
{
	return this->rotation * glm::vec3(0, 1, 0);
}

glm::vec3 Transform::GetRight() const
{
	return this->rotation * glm::vec3(1, 0, 0);
}
