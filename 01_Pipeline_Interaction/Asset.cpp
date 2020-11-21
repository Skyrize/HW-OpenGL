#include "Asset.h"
#include "RenderModule.h"

#include <stb_image.h>

Asset Asset::instance;

Asset::Asset()
{
	textureCount = 0;
}

Asset::~Asset()
{
	for (auto i = textures.begin(); i != textures.end(); i++) {
		delete(i->second);
	}
}

IndexedModel Asset::GetModel(const std::string& path)
{
	if (models.find(path) != models.end()) {
		return models[path];
	}
	models[path] = OBJModel(path).ToIndexedModel();
	return models[path];
}

GLfloat Asset::GetTexture(const std::string& path)
{
	if (textures.find(path) != textures.end()) {
		return textures[path]->GetTexID() + 1;
	}
	Texture* newTexture = new Texture();

	newTexture->Generate(path, this->textureCount);
	//newTexture->Bind();
	textureCount++;
	this->textures[path] = newTexture;
	return newTexture->GetTexID() + 1;

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

GLfloat Asset::GetTextureID(const std::string &path)
{

	if (path == "img.png") return 0;
	if (path == "img2.png") return 1;
	if (path == "moon.jpg") return 2;
}

void Asset::Start()
{
	Shader &shader = RenderModule::Get().GetShader();

	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &id);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, 4000, 4000, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	shader.Bind();
	GenerateTexture("img.png", 0);
	GenerateTexture("img2.png", 1);
	GenerateTexture("moon.jpg", 2);

	//std::vector<GLint> samplers(textureCount);
	//for (GLint i = 0; i != textureCount; i++) {
	//	samplers[i] = i;
	//}
	//}
	//GLint samplers[3] = { 0, 1, 2 };
	//shader.SetUniform1iv("u_Textures", textureCount, &samplers[0]);
	//for (auto i = textures.begin(); i != textures.end(); i++) {
	//	Texture* t = i->second;
	//	t->Bind();
	//	//shader.SetUniform1i("u_Textures_" + std::to_string(i2), t->GetTexID());
	//	shader.SetUniform1i("u_Textures[" + std::to_string(t->GetTexID()) + "]", GL_TEXTURE0 + t->GetTexID());
	//}
	

}

void Asset::Update()
{
	//for (auto i = textures.begin(); i != textures.end(); i++) {
	//	Texture* t = i->second;
	//	t->Bind();
	//}
	//glBindTexture(GL_TEXTURE_2D_ARRAY, id);


}
