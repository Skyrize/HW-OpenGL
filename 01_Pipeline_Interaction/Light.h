#pragma once
#include "Component.h"

typedef glm::vec3 Color;
enum class LightType
{
    DIRECTIONAL = 0,
    POINT = 1,
    //SPOT = 2,
    //AREA = 3?

};

class Light :
    public Component
{
protected:
	LightType type = LightType::POINT;
	GLfloat intensity = 1;
	Color color = Color(1.0f, 1.0f, 1.0f);
public:
    Light(Entity& parent);
    ~Light();

    virtual void Bind(GLuint index);
public:
	LightType GetType() const;
	void SetType(LightType type);

    GLfloat GetIntensity() const;
    void SetIntensity(GLfloat intensity);

    Color GetColor() const;
    void SetColor(Color color);

};

