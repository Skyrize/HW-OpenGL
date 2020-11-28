#include "SpotLight.h"
#include "RenderModule.h"
#include "Transform.h"


SpotLight::SpotLight(Entity& parent)
	: Light(parent)
{
	this->type = LightType::SPOT;
}


void SpotLight::Bind(GLuint index)
{
	Light::Bind(index);
	Shader& shader = RenderModule::Get().GetShader();
	std::string i = "lights[" + std::to_string(index) + "].";


	shader.SetUniform3f(i + "position", transform->GetPosition());
	shader.SetUniform3f(i + "direction", transform->GetFront());
	//std::cout << "direction = " << VTS(transform->GetFront()) << std::endl;
	//std::cout << "angle " << std::to_string(glm::radians(angle)) << std::endl;
	shader.SetUniform1f(i + "innerAngle", glm::radians(innerAngle));
	shader.SetUniform1f(i + "outerAngle", glm::radians(outerAngle));

	std::cout << "innerAngle " << std::to_string(glm::radians(innerAngle)) << std::endl;
	std::cout << "outerAngle " << std::to_string(glm::radians(outerAngle)) << std::endl;
}


GLfloat SpotLight::GetInnerAngle() const
{
	return innerAngle;
}

void SpotLight::SetInnerAngle(GLfloat angle)
{
	if (angle > outerAngle)
		outerAngle = angle;
	this->innerAngle = angle;
}

GLfloat SpotLight::GetOuterAngle() const
{
	return outerAngle;
}

void SpotLight::SetOuterAngle(GLfloat angle)
{
	if (angle < innerAngle)
		angle = innerAngle;
	this->outerAngle = angle;
}

