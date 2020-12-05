#pragma once
#include "Component.h"
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform :
    public Component
{
protected:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	glm::quat rotation = glm::quat(1, 0, 0, 0);

	//glm::vec3		eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3		front = glm::vec3(0.0f, 0.0f, 1.0f);
	//glm::vec3		up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3		right = glm::vec3(1.0f, 0.0f, 0.0f);

private:
	void UpdateVectors();
public:
	Transform(Entity& parent);
	Transform(glm::vec3 position, glm::vec3 rotationEuler, glm::vec3 scale);
	virtual void Start() override;
	virtual void Update() override;

	glm::mat4 GetModelMatrix();
	glm::mat4 GetTranslationMatrix();
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetScaleMatrix();
	glm::vec3 GetRotationEuler();

	void Translate(glm::vec3 translation);
	void LookAt(glm::vec3 target, glm::vec3 up = glm::vec3(0,1,0));
	void Rotate(glm::vec3 euler);
	void RotateAround(glm::vec3 point, glm::vec3 axis, GLfloat angle);
public:
    glm::vec3 GetPosition() const;
    void SetPosition(glm::vec3 position);

    glm::vec3 GetScale() const;
    void SetScale(glm::vec3 scale);

    glm::quat GetRotation() const;
	void SetRotation(glm::quat rotation);
	void SetRotation(glm::vec3 eulerAngles);
	void SetRotation(float eulerX, float eulerY, float eulerZ);

	glm::vec3 GetFront() const;

    glm::vec3 GetUp() const;

    glm::vec3 GetRight() const;

};

