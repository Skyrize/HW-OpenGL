#include "Engine.h"
#include "GLBind.h"
#include "Entity.h"
#include "Asset.h"
#include "CameraController.h"
#include "OrbitalMove.h"
#include "CameraFPS.h"
#include "DebugComponent.h"
#include "LookAtTarget.h"
#include "RenderModule.h"
#include "InstancedMesh.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include <glm/common.hpp>
#include "Animation.h"
#include "DebugController.h"

Engine Engine::instance;

//todo : 
// - light - V
// - Texture lib
// - rendering multiple objects video
// - test loading multiple objects
// - Materials video
// - try making materials (moving out texture from mesh start)
// - apply material
// - uniform faster
// BUG : can't have multiple models / light ? need diff shaders ? 
// Add awake ? problem call order with RenderModule

Engine::Engine()
{
}

void Engine::Init()
{
	if (!glfwInit()) {							// Checking for GLFW
		throw("Could not initialize GLFW...");
	}

	glfwSetErrorCallback(ErrorGLFWCallbackBind);	// Setup a function to catch and display all GLFW errors.

	HintsGLFW();								// Setup glfw with various hints.		
	RenderModule::Get().Init();
	
}

Entity* cub = nullptr;
SpotLight* spotLight = nullptr;

void Engine::Start()
{
	RenderModule::Get().Start();
	Asset::Get().Start();
	Time::Get().Start();
	Input::Get().Start();

	Entity* cam = new Entity();
	Camera* camera = cam->AddComponent<Camera>();
	cam->AddComponent<CameraFPS>();
	cam->AddComponent<CameraController>();
	cam->SetName("MainCamera");
	//cam->AddComponent<OrbitalMove>()->SetTarget(glm::vec3(0, 2, 0));
	entities.push_back(cam);
	cam->GetTransform()->LookAt(glm::vec3(0, 0, 0));
	cam->GetTransform()->SetPosition(glm::vec3(0, 0, 5));


	Entity* debug = new Entity();
	debug->AddComponent<DebugComponent>();
	entities.push_back(debug);
	debug->SetName("debug");

	Entity* cube = new Entity();
	cub = cube;
	cube->SetName("cube");
	//cam->AddComponent<LookAtTarget>()->SetTarget(cube);
	Mesh *mesh = cube->AddComponent<Mesh>();
	mesh->LoadModel("Moon.obj", "white");
	cube->GetTransform()->SetScale(glm::vec3(0.2f));
	auto anim = cub->AddComponent<Animation>();
	anim->AddClip(Clip("test", 5, Transform(glm::vec3(0), glm::vec3(0), glm::vec3(0.2f)), Transform(glm::vec3(0, 5, 5), glm::vec3(90), glm::vec3(1))));
	anim->AddClip(Clip("test2", 1, Transform(glm::vec3(0, 5, 5), glm::vec3(90), glm::vec3(1)), Transform(glm::vec3(0), glm::vec3(0), glm::vec3(0.2f))));
	entities.push_back(cube);


	Entity* light = new Entity();
	light->SetName("light");
	spotLight = light->AddComponent<SpotLight>();
	spotLight->SetInnerAngle(30.0f);
	spotLight->SetIntensity(1.0f);
	light->AddComponent<LookAtTarget>()->SetTarget(cube);
	//light->AddComponent<PointLight>();
	light->AddComponent<DebugController>();
	//auto dr = light->AddComponent<DirectionalLight>();
	Mesh* mesh2 = light->AddComponent<Mesh>();
	mesh2->LoadModel("Snowman.obj", "Moon");
	mesh2->GetTransform()->SetScale(glm::vec3(0.2f));
	mesh2->GetTransform()->SetRotation(-45, 45, 0);
	//light->AddComponent<OrbitalMove>()->SetTarget(glm::vec3(0, 3, 0));
	light->GetTransform()->SetPosition(glm::vec3(3, 3, 0));
	// Scale affect light ??
	entities.push_back(light);

	//Entity* light2 = new Entity();
	//light2->SetName("light2");
	//auto l = light2->AddComponent<PointLight>();
	//l->SetIntensity(2);
	//l->SetColor(Color(0, 0, 1));
	//light2->AddComponent<DebugController>();
	////light2->AddComponent<DirectionalLight>()->SetIntensity(1);
	//Mesh* mesh3 = light2->AddComponent<Mesh>();
	//mesh3->LoadModel("Moon.obj", "Moon");
	//mesh3->GetTransform()->SetScale(glm::vec3(0.4f));
	//auto or = light2->AddComponent<OrbitalMove>();
	//or->SetTarget(glm::vec3(0, 4, 0));
	//or->SetSpeed(-1);
	////light2->GetTransform()->SetPosition(glm::vec3(2, 3, 0));
	//// Scale affect light2 ??
	//entities.push_back(light2);


	//mesh2->LoadTexture("Moon.jpg");

	float radius = 5;
	for (float i = 0; i < 8; i++)
	{
		Entity* test = new Entity();
		test->SetName("test " + std::to_string(i));
		float angle = i * 3.141593 * 2.0f / 8.0f;
		glm::vec3 newPos(cos(angle) * radius, 0, sin(angle) * radius);
		Mesh* m = test->AddComponent<Mesh>();
		m->LoadModel("Snowman.obj", "img");
		m->GetTransform()->SetPosition(newPos);
		m->GetTransform()->SetScale(glm::vec3(0.2f));


	}

	Entity *instances = new Entity();
	instances->SetName("instances");
	InstancedMesh* inst = instances->AddComponent<InstancedMesh>();
	inst->LoadModel("lowpolytree.obj", "white");

	for (float i = 0; i < 8; i++) {
	
		float an = i * 3.141593 * 2.0f / 8.0f;
		glm::vec3 newPos(cos(an) * radius, 6, sin(an) * radius);

		inst->AddInstance(newPos, instances->GetTransform()->GetRotation(), instances->GetTransform()->GetScale());


	}
	entities.push_back(instances);
	
	RenderModule::Get().SetMainCamera(camera);

	for (auto ent : entities) {
		ent->Start();
	}

}

void Engine::Update()
{
	float angle = 30;
	float rotY = 0;
	do {										// run until the window is closed
		Time::Get().Update();
		Input::Get().Update();

		for (auto ent : entities) {
			ent->Update();
		}

		auto keyStatus = Input::Get().GetKeyStatus();
		//glm::vec3 move(0);
		//if (keyStatus[GLFW_KEY_LEFT])			rotY -= 5;
		//if (keyStatus[GLFW_KEY_RIGHT])			rotY += 5;
		if (keyStatus[GLFW_KEY_LEFT])			angle -= 0.05f;
		if (keyStatus[GLFW_KEY_RIGHT])			angle += 0.05f;
		if (keyStatus[GLFW_KEY_Y])			cub->GetComponent<Animation>()->Play("test");
		if (keyStatus[GLFW_KEY_T
		])			cub->GetComponent<Animation>()->Play("test2");
		spotLight->SetOuterAngle(angle);
		std::cout << "angle deg " << std::to_string(angle) << "//// angle rad " << std::to_string(glm::radians(angle)) << std::endl;
		//cub->GetTransform()->SetRotation(glm::vec3(0, rotY, 0));
		//if (keyStatus[GLFW_KEY_KP_ADD])			modelPosition.z += 0.10f;
		//if (keyStatus[GLFW_KEY_KP_SUBTRACT])	modelPosition.z -= 0.10f;
		RenderModule::Get().Clear();
		RenderModule::Get().Draw();


		running &= (glfwGetKey(RenderModule::Get().GetWindow(), GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(RenderModule::Get().GetWindow()) != GL_TRUE);
	} while (running);

}

void Engine::End() {
	RenderModule::Get().End();
	Asset::Get().End();

	for (Entity* ent : entities) {
		delete(ent);
	}

	glfwTerminate();	// destroys all windows and releases resources.
}

Entity* Engine::GetEntity(const std::string& name)
{
	for (Entity* ent : entities) {
		if (ent->GetName() == name)
			return ent;
	}
	std::cout << "Cannot find entity named " << name << "." << std::endl;
	return nullptr;
}


void Engine::HintsGLFW() {
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);			// Create context in debug mode - for debug message callback
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void Engine::ErrorGLFWCallback(int error, const char* description) {
	std::cout << "Error GLFW: " << description << "\n";
}

