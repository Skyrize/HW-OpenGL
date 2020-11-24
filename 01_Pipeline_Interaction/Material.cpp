#include "Material.h"
#include "Asset.h"
#include "RenderModule.h"

Material::Material(const std::string& name, const std::string& texturePath, const MaterialData& materialData)
{
	this->name = name;
	this->texture = Asset::Get().GetTexture(texturePath);
	this->data = MaterialData(materialData);
}

void Material::Bind()
{
	Shader& shader = RenderModule::Get().GetShader();

	shader.SetUniform3f("mat.ambient", data.ambient);
	shader.SetUniform3f("mat.diffuse", data.diffuse);
	shader.SetUniform3f("mat.specular", data.specular);
	shader.SetUniform1f("mat.shininess", 32.0f);
	if (texture) {
		texture->Bind();
		shader.SetUniform1i("mat.u_Texture", texture->GetTexID());
	}
}
