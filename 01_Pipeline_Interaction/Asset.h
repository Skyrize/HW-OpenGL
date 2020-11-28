#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>			// Add library to extend OpenGL to newest version
#include <GLFW/glfw3.h>  			// Add library to launch a window
#include <string>
#include <unordered_map>
#include "OBJLoader.h"
#include "Texture.h"
#include "IObject.h"
#include "Material.h"

#define MODEL_PATH "Assets/Models/"
#define TEXTURE_PATH "Assets/Textures/"

class Asset : public IObject
{
private:
	std::unordered_map<std::string, IndexedModel> models;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Material*> materials;

public:
	~Asset();
	IndexedModel GetModel(const std::string& path);
	Texture* GetTexture(const std::string& path);
	Material* GetMaterial(const std::string& name);
	void AddMaterial(const std::string& name, const std::string &texturePath, const MaterialData &materialData);

	static std::string ReadFile(std::string filePath);

	void PreloadAssets();
	virtual void Start() override;
	virtual void Update() override;

	//Singleton
	GLfloat textureCount;
private:
	GLuint id = 0;
	static Asset instance;
public:
	Asset();
	Asset(const Asset&) = delete;
	Asset& operator=(const Asset&) = delete;
	static Asset& Get() noexcept {
		return instance;
	}
	void End();
};

