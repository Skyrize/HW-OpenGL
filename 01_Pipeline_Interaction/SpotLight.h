#pragma once
#include "Light.h"
class SpotLight :
    public Light
{
protected:
	GLfloat innerAngle = 15.0f;
	GLfloat outerAngle = 15.0f;
public:
	SpotLight(Entity& parent);
	virtual void Bind(GLuint index) override;
public:
	GLfloat GetInnerAngle() const;
	void SetInnerAngle(GLfloat angle);
	GLfloat GetOuterAngle() const;
	void SetOuterAngle(GLfloat angle);

};

