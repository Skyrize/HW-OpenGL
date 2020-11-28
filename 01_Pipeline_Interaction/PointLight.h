#pragma once
#include "Light.h"

class PointLight :
    public Light
{
protected:
public:
    PointLight(Entity& parent);
    virtual void Bind(GLuint index) override;

};

