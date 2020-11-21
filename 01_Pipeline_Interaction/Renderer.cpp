#include "Renderer.h"
#include "RenderModule.h"

Renderer::Renderer(Entity& parent)
	: Component(parent)
{
	RenderModule::Get().Register(this);
}

Renderer::~Renderer()
{
	RenderModule::Get().Unregister(this);
}

void Renderer::Start()
{
}

void Renderer::Update()
{
}

void Renderer::Draw()
{
}

