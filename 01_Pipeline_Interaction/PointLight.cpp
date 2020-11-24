#include "PointLight.h"
#include "RenderModule.h"
#include "Transform.h"

PointLight::PointLight(Entity& parent)
	: Light(parent)
{
	this->type = LightType::POINT;
}

void PointLight::Bind(GLuint index)
{
	Light::Bind(index);
	Shader& shader = RenderModule::Get().GetShader();
	std::string i = "lights[" + std::to_string(index) + "].";


	shader.SetUniform1f(i + "lightConstant", lightConstant);
	shader.SetUniform1f(i + "lightLinear", lightLinear);
	shader.SetUniform1f(i + "lightQuadratic", lightQuadratic);
	shader.SetUniform3f(i + "position", transform->GetPosition());
}

GLfloat PointLight::GetLightConstant() const
{
    return lightConstant;
}

void PointLight::SetLightConstant(GLfloat lightConstant)
{
    this->lightConstant = lightConstant;
}

GLfloat PointLight::GetLightLinear() const
{
    return lightLinear;
}

void PointLight::SetLightLinear(GLfloat lightLinear)
{
    this->lightLinear = lightLinear;
}

GLfloat PointLight::GetLightQuadratic() const
{
    return lightQuadratic;
}

void PointLight::SetLightQuadratic(GLfloat lightQuadratic)
{
    this->lightQuadratic = lightQuadratic;
}

