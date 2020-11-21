#include "DebugComponent.h"
#include "Engine.h"

void DebugComponent::Start()
{
	keyStatus = Input::Get().GetKeyStatus();
}

void DebugComponent::Update()
{
	if (keyStatus[GLFW_KEY_E]) {
		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		//TODO : add Pressed / release / real input management
		isWireframe = !isWireframe;
	}
}
