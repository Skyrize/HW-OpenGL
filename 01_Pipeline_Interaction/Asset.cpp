#include "Asset.h"
#include "RenderModule.h"
#include <iostream>
#include <filesystem>

#include <stb_image.h>

Asset Asset::instance;

Asset::Asset()
{
	textureCount = 0;
}

void Asset::End()
{
	for (auto i = textures.begin(); i != textures.end(); i++) {
		delete(i->second);
	}
	for (auto i = materials.begin(); i != materials.end(); i++) {
		delete(i->second);
	}
}

Asset::~Asset()
{
}

IndexedModel Asset::GetModel(const std::string& path)
{
	if (models.find(path) != models.end()) {
		return models[path];
	}
	models[path] = OBJModel(MODEL_PATH + path).ToIndexedModel();
	return models[path];
}

Texture *Asset::GetTexture(const std::string& path)
{
	if (textures.find(path) != textures.end()) {
		return textures[path];
	}
	Texture* newTexture = new Texture(path, this->textureCount);
	textureCount++;
	this->textures[path] = newTexture;

	newTexture->Bind();
	RenderModule::Get().GetShader().SetUniform1i("mat.u_Texture", newTexture->GetTexID());
	return newTexture;

}

Material* Asset::GetMaterial(const std::string& name)
{
	if (materials.find(name) == materials.end()) {
		throw("Error : no material with the name '" + name + "'.");
	}
	return materials[name];
}

void Asset::AddMaterial(const std::string& name, const std::string& texturePath, const MaterialData& materialData)
{
	if (materials.find(name) != materials.end()) {
		throw("Error : two materials with the same name '" + name + "'.");
	}
	Material* newMat = new Material(name, texturePath, materialData);
	this->materials[name] = newMat;
}

std::string Asset::ReadFile(std::string filePath)
{
	std::string text;
	std::ifstream fileStream(filePath);
	std::string line;

	if (fileStream.is_open()) {

		while (getline(fileStream, line)) {
			text += line;
			text += '\n';
		}
		fileStream.close();
	}
	return text;
}

void GenerateTexture(const std::string& path, GLint zoffset)
{
	GLint width, height, bpp;

	stbi_set_flip_vertically_on_load(1);
	GLubyte* localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, zoffset, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}
}

void Asset::PreloadAssets()
{
	//MaterialData defaultData = MaterialData::GetMaterial("ruby");
	MaterialData defaultData;
	std::string fabricPath;
	for (const auto& entry : std::filesystem::directory_iterator(TEXTURE_PATH)) {
		std::string name = entry.path().filename().string();
		size_t lastindex = name.find_last_of(".");
		string rawname = name.substr(0, lastindex);
		std::string path = entry.path().string();
		if (rawname == "Fabric") {
			fabricPath = path;
		}
	}

	for (const auto& entry : std::filesystem::directory_iterator(TEXTURE_PATH)) {
		std::string name = entry.path().filename().string();
		size_t lastindex = name.find_last_of(".");
		string rawname = name.substr(0, lastindex);
		std::string path = entry.path().string();

		if (rawname == "White") {
			AddMaterial("Glass", path, MaterialData::GetMaterial("glass"));
			AddMaterial("Metal", path, MaterialData::GetMaterial("metal"));
			AddMaterial("Metal Orange", path, MaterialData::GetMaterial("metal orange"));
			AddMaterial("Metal Green", path, MaterialData::GetMaterial("metal green"));
			AddMaterial("Metal Brown", path, MaterialData::GetMaterial("metal brown"));

		} else if (rawname == "Armchair_back"
			|| rawname == "Armchair_pillow"
			|| rawname == "Armchair_restleft"
			|| rawname == "Armchair_restright"
			|| rawname == "Armchair_seat") {
			AddMaterial(rawname, fabricPath, MaterialData::GetMaterial("velvet"));
		}
		else if (rawname == "Mattress" || rawname == "PillowRight" || rawname == "PillowLeft") {
			AddMaterial(rawname, fabricPath, MaterialData::GetMaterial("white fabric"));

		}
		else if (rawname == "Blanket") {
			AddMaterial(rawname, fabricPath, MaterialData::GetMaterial("blue fabric"));

		}
		else {
			AddMaterial(rawname, path, defaultData);

		}


	}
}

void Asset::Start()
{
	PreloadAssets();
}

void Asset::Update()
{
	//for (auto i = textures.begin(); i != textures.end(); i++) {
	//	Texture* t = i->second;
	//	t->Bind();
	//}
	//glBindTexture(GL_TEXTURE_2D_ARRAY, id);


}
