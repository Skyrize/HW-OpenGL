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

void RenderModule::Draw()
{
	glm::mat4 viewMatrix = mainCamera->GetView();
	glm::mat4 projMatrix = mainCamera->GetProjection();
	glm::vec3 viewPosition = RenderModule::Get().GetMainCamera()->GetTransform()->GetPosition();

	shader.Bind();

	shader.SetUniform4f("viewPosition", viewPosition, 1.0f);

	//RenderDirectionalLight(shader);
	int i = 0;
	for (auto light : lights) {
		if (light->IsActive()) {
			light->Bind(i);
			i++;
		}
	}


	for (auto renderer : renderers) {
		if (renderer->IsActive()) {
			renderer->Draw();
		}
	}
	shader.SetUniformMatrix4fv("view_matrix", viewMatrix);
	shader.SetUniformMatrix4fv("proj_matrix", projMatrix);
	glfwSwapBuffers(window);				// swap buffers (avoid flickering and tearing)
}

void RenderModule::Clear() const
{
	glViewport(0, 0, windowWidth, windowHeight);

	// Clear colour buffer
	glm::vec4 backgroundColor = glm::vec4(0,0,0, 1.0f); glClearBufferfv(GL_COLOR, 0, &backgroundColor[0]);

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

