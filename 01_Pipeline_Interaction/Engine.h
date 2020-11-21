#pragma once

#include "IObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "Time.h"
#include "Input.h"

class Engine : IObject
{
protected:
	GLboolean				running = true;									// Are we still running?
	std::vector<Entity*>	entities;

public:
	Engine();
	void Init();
	virtual void Start() override;
	virtual void Update() override;
	void End();
	Entity* GetEntity(const std::string& name);


	void HintsGLFW();

	//callbacks
	void ErrorGLFWCallback(int error, const char* description);

	//Singleton
private:
	static Engine instance;
public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	static Engine& Get() noexcept {
		return instance;
	}


};