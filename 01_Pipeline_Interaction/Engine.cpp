#include "Engine.h"
#include "GLBind.h"
#include "Entity.h"
#include "Asset.h"
#include "CameraController.h"
#include "CameraDrone.h"
#include "CameraFPS.h"
#include "DebugComponent.h"
#include "RenderModule.h"
#include "InstancedMesh.h"

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

void Engine::Start()
{
	RenderModule::Get().Start();
	Asset::Get().Start();
	Time::Get().Start();
	Input::Get().Start();

	Entity* cam = new Entity();
	Entity* debug = new Entity();
	Entity* cube = new Entity();
	Entity* light = new Entity();

	cub = cube;
	cam->SetName("MainCamera");
	cube->SetName("cube");
	Camera *camera = cam->AddComponent<Camera>();
	cam->AddComponent<CameraFPS>();
	cam->AddComponent<CameraController>();
	debug->AddComponent<DebugComponent>();
	Mesh *mesh = cube->AddComponent<Mesh>();
	mesh->LoadModel("Snowman.obj", "img.png");
	Mesh* mesh2 = light->AddComponent<Mesh>();
	mesh2->LoadModel("Moon.obj", "moon.jpg");
	light->GetTransform()->SetPosition(glm::vec3(0, 3, 4));
	cube->GetTransform()->SetScale(glm::vec3(0.2f));
	cube->GetTransform()->SetPosition(glm::vec3(0, 1, 1));

	entities.push_back(cam);
	entities.push_back(debug);
	entities.push_back(cube);

	//mesh2->LoadTexture("Moon.jpg");

	float radius = 5;
	for (float i = 0; i < 8; i++)
	{
		Entity* test = new Entity();

		float angle = i * 3.141593 * 2.0f / 8.0f;
		glm::vec3 newPos(cos(angle) * radius, 0, sin(angle) * radius);
		Mesh* m = test->AddComponent<Mesh>();
		m->LoadModel("Snowman.obj", "img.png");
		m->GetTransform()->SetPosition(newPos);


	}

	Entity *instances = new Entity();
	InstancedMesh* inst = instances->AddComponent<InstancedMesh>();
	inst->LoadModel("lowpolytree.obj", "img2.png");

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

GLfloat lightConstant = 1.0f;
GLfloat lightLinear = 0.7f;
GLfloat lightQuadratic = 1.8f;

GLfloat ambientConst = 1.0;
glm::vec3 ambientColour(1.0f, 1.0f, 1.0f);
GLfloat diffuseConst = 1.0;
glm::vec3 diffuseColour(1.0f, 1.0f, 1.0f);
GLfloat specularConst = 1.0;
glm::vec3 specularColour(1.0f, 1.0f, 1.0f);
glm::vec3 rot(0);
void RenderPointLight(Shader& shader)
{
	GLfloat		camX = sin(Time::Get().GetCurrentTime()) * 4 * 1;
	GLfloat		camZ = cos(Time::Get().GetCurrentTime()) * 4 * 1;
	shader.SetUniform1f("lightConstant", lightConstant);
	shader.SetUniform1f("lightLinear", lightLinear);
	shader.SetUniform1f("lightQuadratic", lightQuadratic);

	shader.SetUniform1f("shininess", 32.0f);
	shader.SetUniform4f("specularColour", specularColour, 1.0);
	shader.SetUniform1f("specularConst", specularConst);
	shader.SetUniform4f("diffuseColour", diffuseColour, 1.0);
	shader.SetUniform1f("diffuseConst", diffuseConst);
	shader.SetUniform4f("ambientColour", ambientColour, 1.0f);
	shader.SetUniform1f("ambientConst", ambientConst);
	shader.SetUniform4f("lightPosition", camX, 5.0f, camZ, 1.0f);
	glm::vec3 viewPosition = RenderModule::Get().GetMainCamera()->GetTransform()->GetPosition();
	shader.SetUniform4f("viewPosition", viewPosition.x, viewPosition.z, viewPosition.z, 1.0f);
}

glm::vec4 directionalLightDirection(0.0f, 0.0f, 1.0f, 0.0f);
void RenderDirectionalLight(Shader& shader)
{

	shader.SetUniform4f("dirLightDirection", directionalLightDirection);
}

void Engine::Update()
{

	Shader &shader = RenderModule::Get().GetShader();

	do {										// run until the window is closed
		Time::Get().Update();
		Input::Get().Update();

		for (auto ent : entities) {
			ent->Update();
		}

		RenderPointLight(shader);
		RenderDirectionalLight(shader);

		/// replace with component 
		auto keyStatus = Input::Get().GetKeyStatus();
		if (keyStatus[GLFW_KEY_LEFT])			rot.y += 0.05f;
		if (keyStatus[GLFW_KEY_RIGHT])			rot.y -= 0.05f;
		if (keyStatus[GLFW_KEY_UP])				directionalLightDirection.x += 0.05;
		if (keyStatus[GLFW_KEY_DOWN])			directionalLightDirection.z -= 0.05f;
		//glm::vec3 move(0);
		//if (keyStatus[GLFW_KEY_LEFT])			move.x -= 0.05f;
		//if (keyStatus[GLFW_KEY_RIGHT])			move.x += 0.05f;
		//cub->GetTransform()->SetRotation(rot);
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

