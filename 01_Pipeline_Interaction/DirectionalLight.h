#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
protected:
	glm::vec3 direction = glm::vec3(0, -1, 0);
public:
	DirectionalLight(Entity& parent);
	virtual void Bind(GLuint index) override;
public:
    glm::vec3 GetDirection() const;
    void SetDirection(glm::vec3 direction);

};

