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

	shader.SetUniform3f(i + "position", transform->GetWorldPosition());
}
