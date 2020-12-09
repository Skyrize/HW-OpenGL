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

}

Transform::Transform(Entity& parent)
	: Component(parent)
{
}

Transform::Transform(glm::vec3 position, glm::vec3 rotationEuler, glm::vec3 scale)
    :Component(Entity())
{
    this->SetPosition(position);
    this->SetScale(scale);
    this->SetRotation(rotationEuler);
}

void Transform::Start()
{
}

void Transform::Update()
{
}

glm::mat4 Transform::GetModelMatrix() const
{
    glm::mat4 parentMatrix(1);
    glm::mat4 modelMatrix = GetTranslationMatrix();
    modelMatrix *= GetRotationMatrix();
    modelMatrix *= GetScaleMatrix();

    if (parent.GetParent()) {
        parentMatrix = parent.GetParent()->GetTransform()->GetModelMatrix();
    }

	return parentMatrix * modelMatrix;
}

glm::mat4 Transform::GetTranslationMatrix() const
{
    return glm::translate(glm::mat4(1), this->position);
}

glm::mat4 Transform::GetRotationMatrix() const
{
	return glm::toMat4(this->rotation);
}

glm::mat4 Transform::GetScaleMatrix() const
{
    return glm::scale(glm::mat4(1), this->scale);
}



glm::vec3 Transform::GetRotationEuler()
{
    //return this->eulerAngles;
    glm::vec3 euler = glm::eulerAngles(this->rotation);

    euler.x = glm::degrees(euler.x);
    if (euler.x < 0) euler.x += 360;
	euler.y = glm::degrees(euler.y);
	if (euler.y < 0) euler.y += 360;
	euler.z = glm::degrees(euler.z);
	if (euler.z < 0) euler.z += 360;
	return euler;
}

void Transform::Translate(glm::vec3 translation)
{
    this->position += translation;
}

void Transform::LookAt(glm::vec3 target, glm::vec3 up /*= glm::vec3(0, 1, 0)*/)
{
    glm::vec3 direction = target - position;
	float length = glm::length(direction);

    if (length <= 0.0001f) {
        this->SetRotation(glm::quat(1, 0, 0, 0));
        return;
    }

	this->SetRotation(glm::quatLookAt(glm::normalize(direction), up));
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
glm::vec3 Transform::GetWorldPosition() const
{
    glm::mat4 modelMatrix = GetModelMatrix();
    glm::vec3 worldPosition(modelMatrix[3]);

    return worldPosition;
}


void Transform::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Transform::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->position = glm::vec3(x, y, z);
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

glm::quat Transform::GetWorldRotation() const
{
    glm::mat4 modelMatrix = GetModelMatrix();
    float wScale = sqrt(modelMatrix[0][0] * modelMatrix[0][0] + modelMatrix[0][1] * modelMatrix[0][1] + modelMatrix[0][2] * modelMatrix[0][2]);
    glm::mat3 rot = (1.0f / wScale) * glm::mat3(modelMatrix);

    return glm::quat(rot);
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
	return GetWorldRotation() * glm::vec3(0, 0, -1);
}

glm::vec3 Transform::GetUp() const
{
	return GetWorldRotation() * glm::vec3(0, 1, 0);
}

glm::vec3 Transform::GetRight() const
{
    return GetWorldRotation() * glm::vec3(1, 0, 0);
}
