#pragma once
#include "IObject.h"
#include "IRender.h"
#include "Camera.h"
#include "Shader.h"
#include <list>
class RenderModule :
    public IObject, public IRender
{
protected:
	GLFWwindow*				window = nullptr;											// Keep track of the window
	GLuint					windowWidth = 1200;
	GLuint					windowHeight = 600;
	Camera*					mainCamera = nullptr;
	GLfloat					aspect = (GLfloat)windowWidth / (GLfloat)windowHeight;
	Shader					shader;

    std::list<IRender *> renderers;

public:
	RenderModule();

	void Init();
	void End();
    virtual void Start() override;
    virtual void Update() override;
	virtual void Draw() override;
	void Clear() const;

	void Register(IRender* newRenderer);
	void Unregister(IRender* target);

	GLFWwindow* GetWindow();
	Camera* GetMainCamera();
	void SetMainCamera(Camera *newCamera);

	void OnResizeCallback(GLFWwindow* window, int w, int h);
	void DebugGL();
	void SetupRender();

	Shader& GetShader() { return shader; };
	//Singleton
private:
	static RenderModule instance;
public:
	RenderModule(const RenderModule&) = delete;
	RenderModule& operator=(const RenderModule&) = delete;
	static RenderModule& Get() noexcept {
		return instance;
	}

};

