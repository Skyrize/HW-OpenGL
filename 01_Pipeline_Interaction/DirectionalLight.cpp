#include "DirectionalLight.h"
#include "RenderModule.h"

DirectionalLight::DirectionalLight(Entity& parent)
	: Light(parent)
{
	this->type = LightType::DIRECTIONAL;
}

void DirectionalLight::Bind(GLuint index)
{
	Light::Bind(index);
	Shader& shader = RenderModule::Get().GetShader();
	std::string i = "lights[" + std::to_string(index) + "].";

	shader.SetUniform3f(i + "direction", direction);
}

glm::vec3 DirectionalLight::GetDirection() const
{
    return direction;
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
    this->direction = direction;
}

