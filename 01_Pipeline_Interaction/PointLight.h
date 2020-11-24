#pragma once
#include "Light.h"

class PointLight :
    public Light
{
protected:
	//need to add other values ? 
	GLfloat lightConstant = 1.0f;
	GLfloat lightLinear = 0.7f;
	GLfloat lightQuadratic = 1.8f;
public:
    PointLight(Entity& parent);
    virtual void Bind(GLuint index) override;
public:
    GLfloat GetLightConstant() const;
    void SetLightConstant(GLfloat lightConstant);

    GLfloat GetLightLinear() const;
    void SetLightLinear(GLfloat lightLinear);

    GLfloat GetLightQuadratic() const;
    void SetLightQuadratic(GLfloat lightQuadratic);

};

