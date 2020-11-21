#pragma once

#include "Component.h"
#include <GLM/glm.hpp>			// Add helper maths library

class Camera : public Component
{
protected:
    glm::mat4		projMatrix = glm::mat4(0);									// Projection Matrix
    GLfloat			fovy = 45.0f;
    GLfloat         zNear = 0.1f;
    GLfloat         zFar = 1000.0f;



public:
	Camera(Entity& parent);
public:
    virtual void Start() override;
    virtual void Update() override;
    void Move(glm::vec3 distance);
    glm::mat4 LookAt(const glm::vec3& target);
    void UpdateAspectRender(GLfloat newAspect);

    glm::mat4 GetView() const;

    glm::mat4 GetProjection() const;

    void SetFovy(GLfloat fovy);

};

