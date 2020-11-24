#include "Light.h"
#include "RenderModule.h"

Light::Light(Entity& parent)
	: Component(parent)
{
	RenderModule::Get().Register(this);
}

Light::~Light()
{
	RenderModule::Get().Unregister(this);
}

void Light::Bind(GLuint index)
{
	Shader& shader = RenderModule::Get().GetShader();
	std::string i = "lights[" + std::to_string(index) + "].";

	shader.SetUniform1i(i + "type", (GLint)this->type);
	shader.SetUniform1f(i + "intensity", this->intensity);
	shader.SetUniform3f(i + "color", this->color);
}

LightType Light::GetType() const
{
    return type;
}

void Light::SetType(LightType type)
{
    this->type = type;
}

GLfloat Light::GetIntensity() const
{
    return intensity;
}

void Light::SetIntensity(GLfloat intensity)
{
    this->intensity = intensity;
}

Color Light::GetColor() const
{
    return color;
}

void Light::SetColor(Color color)
{
    this->color = color;
}

