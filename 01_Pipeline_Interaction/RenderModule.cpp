#include "RenderModule.h"
#include "Entity.h"
#include "Engine.h"
#include "GLBind.h"
#include "Asset.h"

RenderModule RenderModule::instance;

RenderModule::RenderModule()
{
}

void RenderModule::SetupRender() {
	glfwSwapInterval(1);	// Ony render when synced (V SYNC)

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_STEREO, GL_FALSE);
	// Enable blend
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderModule::Init()
{
	window = glfwCreateWindow(windowWidth, windowHeight, "My OpenGL Application", NULL, NULL);
	if (!window) {								// Window or OpenGL context creation failed
		throw("Could not initialise GLFW...");
	}
	glfwMakeContextCurrent(window);				// making the OpenGL context current
												// Start GLEW (note: always initialise GLEW after creating your window context.)
	glewExperimental = GL_TRUE;					// hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
	GLenum errGLEW = glewInit();
	if (GLEW_OK != errGLEW) {					// Problems starting GLEW?
		throw("Could not initialise GLEW...");
	}

	DebugGL();									// Setup callback to catch openGL errors.	

												// Setup all the message loop callbacks.
	glfwSetWindowSizeCallback(window, OnResizeCallbackBind);		// Set callback for resize
	glfwSetKeyCallback(window, OnKeyCallbackBind);					// Set Callback for keys
	glfwSetMouseButtonCallback(window, OnMouseButtonCallbackBind);	// Set callback for mouse click
	glfwSetCursorPosCallback(window, OnMouseMoveCallbackBind);		// Set callback for mouse move
	glfwSetScrollCallback(window, OnMouseWheelCallbackBind);		// Set callback for mouse wheel.

	SetupRender();
}

void RenderModule::End()
{
	glfwMakeContextCurrent(window);		// destroys window handler
}

void RenderModule::Start()
{
	aspect = (float)windowWidth / (float)windowHeight;
	
	shader.Generate();
	shader.CreateShader("vs_model.glsl", GL_VERTEX_SHADER);
	shader.CreateShader("fs_model.glsl", GL_FRAGMENT_SHADER);

	shader.Validate();
	shader.Bind();
	
	// A few optimizations.
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

void RenderModule::Update()
{
}
/*

GLfloat lightConstant = 1.0f;
GLfloat shininess = 32.0f;
GLfloat lightLinear = 0.7f;
GLfloat lightQuadratic = 1.8f;

GLfloat ambientConst = 1.0;
glm::vec3 ambientColour(1.0f, 1.0f, 1.0f);
GLfloat diffuseConst = 1.0;
glm::vec3 diffuseColour(1.0f, 1.0f, 1.0f);
GLfloat specularConst = 1;
glm::vec3 specularColour(1.0f, 1.0f, 1.0f);
glm::vec3 rot(0);
glm::vec3 lightPos = glm::vec3(0, 5, 0);
void RenderPointLight(Shader& shader)
{
	if (!light) {
		light = Engine::Get().GetEntity("light");
	}
	lightPos.x		= sin(Time::Get().GetCurrentTime()) * 4 * 1;
	lightPos.z		= cos(Time::Get().GetCurrentTime()) * 4 * 1;
	shader.SetUniform1f("lightConstant", lightConstant);
	shader.SetUniform1f("lightLinear", lightLinear);
	shader.SetUniform1f("lightQuadratic", lightQuadratic);

	light->GetTransform()->SetPosition(lightPos);
	shader.SetUniform4f("lightPosition", lightPos, 1.0f);
	glm::vec3 viewPosition = RenderModule::Get().GetMainCamera()->GetTransform()->GetPosition();
	shader.SetUniform4f("viewPosition", viewPosition.x, viewPosition.z, viewPosition.z, 1.0f);
}

glm::vec4 directionalLightDirection(0.0f, 0.0f, 1.0f, 0.0f);
void RenderDirectionalLight(Shader& shader)
{

	shader.SetUniform4f("dirLightDirection", directionalLightDirection);

}

glm::vec4 spotLightDirection(0.0f, -1.0f, 0.0f, 0.0f);
GLfloat angle = 30;
void RenderSpotLight(Shader& shader)
{

	shader.SetUniform4f("spotLightDirection", spotLightDirection);
}

*/

void RenderModule::Draw()
{
	glm::mat4 viewMatrix = mainCamera->GetView();
	glm::mat4 projMatrix = mainCamera->GetProjection();
	glm::vec3 viewPosition = RenderModule::Get().GetMainCamera()->GetTransform()->GetPosition();

	shader.Bind();
	/// replace with component 
	//auto keyStatus = Input::Get().GetKeyStatus();
	//if (keyStatus[GLFW_KEY_LEFT])			ambientConst = glm::clamp(ambientConst + 0.05f, 0.0f, 10.0f);
	//if (keyStatus[GLFW_KEY_RIGHT])			ambientConst = glm::clamp(ambientConst - 0.05f, 0.0f, 10.0f);
	//if (keyStatus[GLFW_KEY_UP])				diffuseConst = glm::clamp(diffuseConst + 0.05f, 0.0f, 10.0f);
	//if (keyStatus[GLFW_KEY_DOWN])			diffuseConst = glm::clamp(diffuseConst - 0.05f, 0.0f, 10.0f);
	//if (keyStatus[GLFW_KEY_N])				specularConst = glm::clamp(specularConst + 5.0f, 0.0f, 1000000.0f);
	//if (keyStatus[GLFW_KEY_B])			specularConst = glm::clamp(specularConst - 5.0f, 0.0f, 1000000.0f);
	//if (keyStatus[GLFW_KEY_M])				lightConstant += 0.05f;
	//if (keyStatus[GLFW_KEY_L])			lightConstant -= 0.05f;


	//std::cout << "ambientConst :" << std::to_string(ambientConst) << ", " << "diffuseConst :" << std::to_string(diffuseConst) << ", " << "specularConst :" << std::to_string(specularConst) << ", " << "lightConstant :" << std::to_string(lightConstant) << std::endl;


	shader.SetUniform4f("viewPosition", viewPosition, 1.0f);

	//RenderDirectionalLight(shader);
	int i = 0;
	for (auto light : lights) {
		light->Bind(i);
		i++;
	}


	for (auto renderer : renderers) {
		renderer->Draw();
	}
	shader.SetUniformMatrix4fv("view_matrix", viewMatrix);
	shader.SetUniformMatrix4fv("proj_matrix", projMatrix);
	glfwSwapBuffers(window);				// swap buffers (avoid flickering and tearing)
}

void RenderModule::Clear() const
{
	glViewport(0, 0, windowWidth, windowHeight);

	// Clear colour buffer
	glm::vec4 backgroundColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); glClearBufferfv(GL_COLOR, 0, &backgroundColor[0]);

	// Clear deep buffer
	static const GLfloat one = 1.0f; glClearBufferfv(GL_DEPTH, 0, &one);

}

void RenderModule::Register(IRender* newRenderer)
{
	renderers.push_back(newRenderer);
}

void RenderModule::Register(Light* newLight)
{
	lights.push_back(newLight);
}

void RenderModule::Unregister(IRender* target)
{
	renderers.remove(target);
}

void RenderModule::Unregister(Light* target)
{
	lights.remove(target);
}

GLFWwindow* RenderModule::GetWindow()
{
	return this->window;
}

Camera* RenderModule::GetMainCamera()
{
	return this->mainCamera;
}

void RenderModule::SetMainCamera(Camera* newCamera)
{
	this->mainCamera = newCamera;
	mainCamera->UpdateAspectRender(aspect);
}

static void APIENTRY openGLDebugCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const GLvoid* userParam);

void RenderModule::DebugGL() {
	//Output some debugging information
	std::cout << "VENDOR: " << (char*)glGetString(GL_VENDOR) << std::endl;
	std::cout << "VERSION: " << (char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "RENDERER: " << (char*)glGetString(GL_RENDERER) << std::endl;

	// Enable Opengl Debug
	//glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
}

void RenderModule::OnResizeCallback(GLFWwindow* window, int w, int h) {
	windowWidth = w;
	windowHeight = h;

	aspect = (float)w / (float)h;
	mainCamera->UpdateAspectRender(aspect);
}

static void APIENTRY openGLDebugCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const GLvoid* userParam) {

	std::cout << "---------------------opengl-callback------------" << std::endl;
	std::cout << "Message: " << message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << " --- ";

	std::cout << "id: " << id << " --- ";
	std::cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "NOTIFICATION";
	}
	std::cout << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

