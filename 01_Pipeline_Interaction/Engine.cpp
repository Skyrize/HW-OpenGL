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
#include "SceneController.h"
#include "DebugController.h"
#include "Manipulate.h"

Engine Engine::instance;

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

void Engine::LoadScene()
{
	/*--Camera--*/
	Entity* cam = new Entity();
	cam->SetName("MainCamera");
	auto camera = cam->AddComponent<Camera>();
	cam->AddComponent<CameraFPS>();
	cam->AddComponent<CameraController>();
	cam->AddComponent<LookAtTarget>();
	entities.push_back(cam);

	/*--SceneController--*/
	Entity* scene = new Entity();
	scene->SetName("SceneController");
	scene->AddComponent<SceneController>();
	entities.push_back(scene);

	Entity* light = new Entity(cam);
	//light->AddComponent<Mesh>()->LoadModel("Snowglobe.obj", "Bricks");
	light->SetName("light");
	light->AddComponent<PointLight>()->SetIntensity(4);
	light->GetTransform()->SetPosition(0, 0, -6);
	light->GetTransform()->SetScale(glm::vec3(0.2f));
	entities.push_back(light);


	/*--debug--*/
	Entity* debug = new Entity();
	debug->AddComponent<DebugComponent>();
	entities.push_back(debug);
	debug->SetName("Debug");

	/*--Armchair--*/
	Entity* armchair = new Entity();
	armchair->SetName("Armchair");
	armchair->GetTransform()->SetPosition(glm::vec3(-25.093f, 6.080f, 0.568));
	armchair->SetTag("Animate");
	armchair->AddComponent<Manipulate>();
	auto armchairAnim = armchair->AddComponent<Animation>();
	armchairAnim->AddClip(Clip("focus", 1, Transform(*armchair->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), armchair->GetTransform()->GetRotationEuler(), armchair->GetTransform()->GetScale())));
	armchairAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), armchair->GetTransform()->GetRotationEuler(), armchair->GetTransform()->GetScale()), Transform(*armchair->GetTransform())));
	entities.push_back(armchair);
	//armchair_back
	Entity* armchair_back = new Entity(armchair);
	armchair_back->AddComponent<Mesh>()->LoadModel("Armchair_back.obj", "Armchair_back");
	armchair_back->AddComponent<Animation>();
	entities.push_back(armchair_back);
	//armchair_backleftfoot
	Entity* armchair_backleftfoot = new Entity(armchair);
	armchair_backleftfoot->AddComponent<Mesh>()->LoadModel("Armchair_backleftfoot.obj", "Wood2");
	armchair_backleftfoot->AddComponent<Animation>();
	entities.push_back(armchair_backleftfoot);
	//armchair_backrightfoot
	Entity* armchair_backrightfoot = new Entity(armchair);
	armchair_backrightfoot->AddComponent<Mesh>()->LoadModel("Armchair_backrightfoot.obj", "Wood2");
	armchair_backrightfoot->AddComponent<Animation>();
	entities.push_back(armchair_backrightfoot);
	//armchair_buttonback
	Entity* armchair_buttonback = new Entity(armchair);
	armchair_buttonback->AddComponent<Mesh>()->LoadModel("Armchair_buttonback.obj", "Wood2");
	armchair_buttonback->AddComponent<Animation>();
	entities.push_back(armchair_buttonback);
	//armchair_buttonseat
	Entity* armchair_buttonseat = new Entity(armchair);
	armchair_buttonseat->AddComponent<Mesh>()->LoadModel("Armchair_buttonseat.obj", "Wood2");
	armchair_buttonseat->AddComponent<Animation>();
	entities.push_back(armchair_buttonseat);
	//armchair_frontleftfoot
	Entity* armchair_frontleftfoot = new Entity(armchair);
	armchair_frontleftfoot->AddComponent<Mesh>()->LoadModel("Armchair_frontleftfoot.obj", "Wood2");
	armchair_frontleftfoot->AddComponent<Animation>();
	entities.push_back(armchair_frontleftfoot);
	//armchair_frontrightfoot
	Entity* armchair_frontrightfoot = new Entity(armchair);
	armchair_frontrightfoot->AddComponent<Mesh>()->LoadModel("Armchair_frontrightfoot.obj", "Wood2");
	armchair_frontrightfoot->AddComponent<Animation>();
	entities.push_back(armchair_frontrightfoot);
	//armchair_pillow
	Entity* armchair_pillow = new Entity(armchair);
	armchair_pillow->AddComponent<Mesh>()->LoadModel("Armchair_pillow.obj", "Armchair_pillow");
	armchair_pillow->AddComponent<Animation>();
	entities.push_back(armchair_pillow);
	//armchair_plate
	Entity* armchair_plate = new Entity(armchair);
	armchair_plate->AddComponent<Mesh>()->LoadModel("Armchair_plate.obj", "Wood2");
	armchair_plate->AddComponent<Animation>();
	entities.push_back(armchair_plate);
	//armchair_restleft
	Entity* armchair_restleft = new Entity(armchair);
	armchair_restleft->AddComponent<Mesh>()->LoadModel("Armchair_restleft.obj", "Armchair_restleft");
	armchair_restleft->AddComponent<Animation>();
	entities.push_back(armchair_restleft);
	//armchair_restright
	Entity* armchair_restright = new Entity(armchair);
	armchair_restright->AddComponent<Mesh>()->LoadModel("Armchair_restright.obj", "Armchair_restright");
	armchair_restright->AddComponent<Animation>();
	entities.push_back(armchair_restright);
	//armchair_seat
	Entity* armchair_seat = new Entity(armchair);
	armchair_seat->AddComponent<Mesh>()->LoadModel("Armchair_seat.obj", "Armchair_seat");
	armchair_seat->AddComponent<Animation>();
	entities.push_back(armchair_seat);

	/*--Bed--*/
	Entity* bed = new Entity();
	bed->SetName("Bed");
	bed->AddComponent<Mesh>()->LoadModel("Bed.obj", "Wood2");
	bed->GetTransform()->SetPosition(glm::vec3(0, 6.538f, 0));
	bed->SetTag("Animate");
	bed->AddComponent<Manipulate>();
	auto bedAnim = bed->AddComponent<Animation>();
	bedAnim->AddClip(Clip("focus", 1, Transform(*bed->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), bed->GetTransform()->GetRotationEuler(), bed->GetTransform()->GetScale())));
	bedAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), bed->GetTransform()->GetRotationEuler(), bed->GetTransform()->GetScale()), Transform(*bed->GetTransform())));
	entities.push_back(bed);
	/*--Blanket--*/
	Entity* blanket = new Entity();
	blanket->SetName("Blanket");
	blanket->AddComponent<Mesh>()->LoadModel("Blanket.obj", "Blanket");
	blanket->GetTransform()->SetPosition(glm::vec3(0.04f, 5.848f, -1.263f));
	blanket->SetTag("Animate");
	blanket->AddComponent<Manipulate>();
	auto blanketAnim = blanket->AddComponent<Animation>();
	blanketAnim->AddClip(Clip("focus", 1, Transform(*blanket->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), blanket->GetTransform()->GetRotationEuler(), blanket->GetTransform()->GetScale())));
	blanketAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), blanket->GetTransform()->GetRotationEuler(), blanket->GetTransform()->GetScale()), Transform(*blanket->GetTransform())));
	entities.push_back(blanket);
	/*--Mattress--*/
	Entity* mattress = new Entity();
	mattress->SetName("Mattress");
	mattress->AddComponent<Mesh>()->LoadModel("Mattress.obj", "Mattress");
	mattress->GetTransform()->SetPosition(glm::vec3(0, 6.152f, 0));
	mattress->SetTag("Animate");
	mattress->AddComponent<Manipulate>();
	auto mattressAnim = mattress->AddComponent<Animation>();
	mattressAnim->AddClip(Clip("focus", 1, Transform(*mattress->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), mattress->GetTransform()->GetRotationEuler(), mattress->GetTransform()->GetScale())));
	mattressAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), mattress->GetTransform()->GetRotationEuler(), mattress->GetTransform()->GetScale()), Transform(*mattress->GetTransform())));
	entities.push_back(mattress);
	/*--PillowLeft--*/
	Entity* pillowLeft = new Entity();
	pillowLeft->SetName("PillowLeft");
	pillowLeft->AddComponent<Mesh>()->LoadModel("Pillow_left.obj", "PillowLeft");
	pillowLeft->GetTransform()->SetPosition(glm::vec3(-0.251f, 7.950f, 1.878f));
	pillowLeft->SetTag("Animate");
	pillowLeft->AddComponent<Manipulate>();
	auto pillowLeftAnim = pillowLeft->AddComponent<Animation>();
	pillowLeftAnim->AddClip(Clip("focus", 1, Transform(*pillowLeft->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), pillowLeft->GetTransform()->GetRotationEuler(), pillowLeft->GetTransform()->GetScale())));
	pillowLeftAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), pillowLeft->GetTransform()->GetRotationEuler(), pillowLeft->GetTransform()->GetScale()), Transform(*pillowLeft->GetTransform())));
	entities.push_back(pillowLeft);
	/*--PillowRight--*/
	Entity* pillowRight = new Entity();
	pillowRight->SetName("PillowRight");
	pillowRight->AddComponent<Mesh>()->LoadModel("Pillow_right.obj", "PillowRight");
	pillowRight->GetTransform()->SetPosition(glm::vec3(0.796f, 8.114f, -5.822f));
	pillowRight->SetTag("Animate");
	pillowRight->AddComponent<Manipulate>();
	auto pillowRightAnim = pillowRight->AddComponent<Animation>();
	pillowRightAnim->AddClip(Clip("focus", 1, Transform(*pillowRight->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), pillowRight->GetTransform()->GetRotationEuler(), pillowRight->GetTransform()->GetScale())));
	pillowRightAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), pillowRight->GetTransform()->GetRotationEuler(), pillowRight->GetTransform()->GetScale()), Transform(*pillowRight->GetTransform())));
	entities.push_back(pillowRight);

	/*--Room--*/
	Entity* room = new Entity();
	room->SetName("Room");
	room->AddComponent<Mesh>()->LoadModel("Room.obj", "Bricks");
	room->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	entities.push_back(room);

	/*--Floor--*/
	Entity* floor = new Entity();
	floor->SetName("Floor");
	floor->AddComponent<Mesh>()->LoadModel("Floor.obj", "Wood3");
	floor->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	entities.push_back(floor);

	/*--Snowglobe--*/
	Entity* snowglobe = new Entity();
	snowglobe->SetName("Snowglobe");
	snowglobe->GetTransform()->SetPosition(glm::vec3(-15.857f, 7.210f, 7.228f));
	auto snowglobeAnim = snowglobe->AddComponent<Animation>();
	snowglobeAnim->AddClip(Clip("focus", 1, Transform(*snowglobe->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), snowglobe->GetTransform()->GetRotationEuler(), snowglobe->GetTransform()->GetScale())));
	snowglobeAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), snowglobe->GetTransform()->GetRotationEuler(), snowglobe->GetTransform()->GetScale()), Transform(*snowglobe->GetTransform())));
	entities.push_back(snowglobe);
	snowglobe->SetTag("Animate");
	snowglobe->AddComponent<Manipulate>();
	//snowglobeBase
	Entity* snowglobeBase = new Entity(snowglobe);
	snowglobeBase->AddComponent<Mesh>()->LoadModel("SnowglobeBase.obj", "Wood1");
	snowglobeBase->AddComponent<Animation>();
	entities.push_back(snowglobeBase);
	//snowglobeSnow
	Entity* snowglobeSnow = new Entity(snowglobe);
	snowglobeSnow->AddComponent<Mesh>()->LoadModel("SnowglobeSnow.obj", "Snow");
	snowglobeSnow->AddComponent<Animation>();
	entities.push_back(snowglobeSnow);
	//snowglobeSnowman_Base
	Entity* snowglobeSnowman_Base = new Entity(snowglobe);
	snowglobeSnowman_Base->AddComponent<Mesh>()->LoadModel("SnowglobeSnowman_Base.obj", "Snow");
	snowglobeSnowman_Base->AddComponent<Animation>();
	entities.push_back(snowglobeSnowman_Base);
	//snowglobeSnowman_Middle
	Entity* snowglobeSnowman_Middle = new Entity(snowglobe);
	snowglobeSnowman_Middle->AddComponent<Mesh>()->LoadModel("SnowglobeSnowman_Middle.obj", "Snow");
	snowglobeSnowman_Middle->AddComponent<Animation>();
	entities.push_back(snowglobeSnowman_Middle);
	//snowglobeSnowman_Top
	Entity* snowglobeSnowman_Top = new Entity(snowglobe);
	snowglobeSnowman_Top->AddComponent<Mesh>()->LoadModel("SnowglobeSnowman_Top.obj", "Snow");
	snowglobeSnowman_Top->AddComponent<Animation>();
	entities.push_back(snowglobeSnowman_Top);
	//snowglobeStick_Left
	Entity* snowglobeStick_Left = new Entity(snowglobe);
	snowglobeStick_Left->AddComponent<Mesh>()->LoadModel("SnowglobeStick_Left.obj", "Wood2");
	snowglobeStick_Left->AddComponent<Animation>();
	entities.push_back(snowglobeStick_Left);
	//snowglobeStick_Left1
	Entity* snowglobeStick_Left1 = new Entity(snowglobe);
	snowglobeStick_Left1->AddComponent<Mesh>()->LoadModel("SnowglobeStick_Left1.obj", "Wood2");
	snowglobeStick_Left1->AddComponent<Animation>();
	entities.push_back(snowglobeStick_Left1);
	//snowglobeStick_Right
	Entity* snowglobeStick_Right = new Entity(snowglobe);
	snowglobeStick_Right->AddComponent<Mesh>()->LoadModel("SnowglobeStick_Right.obj", "Wood2");
	snowglobeStick_Right->AddComponent<Animation>();
	entities.push_back(snowglobeStick_Right);
	//snowglobeStick_Right1
	Entity* snowglobeStick_Right1 = new Entity(snowglobe);
	snowglobeStick_Right1->AddComponent<Mesh>()->LoadModel("SnowglobeStick_Right1.obj", "Wood2");
	snowglobeStick_Right1->AddComponent<Animation>();
	entities.push_back(snowglobeStick_Right1);
	//snowglobeLittle_Mouth_Rock
	Entity* snowglobeLittle_Mouth_Rock = new Entity(snowglobe);
	snowglobeLittle_Mouth_Rock->AddComponent<Mesh>()->LoadModel("SnowglobeLittle_Mouth_Rock.obj", "Fabric");
	snowglobeLittle_Mouth_Rock->AddComponent<Animation>();
	entities.push_back(snowglobeLittle_Mouth_Rock);
	//snowglobeLittle_Mouth_Rock1
	Entity* snowglobeLittle_Mouth_Rock1 = new Entity(snowglobe);
	snowglobeLittle_Mouth_Rock1->AddComponent<Mesh>()->LoadModel("SnowglobeLittle_Mouth_Rock1.obj", "Fabric");
	snowglobeLittle_Mouth_Rock1->AddComponent<Animation>();
	entities.push_back(snowglobeLittle_Mouth_Rock1);
	//snowglobeLittle_Mouth_Rock2
	Entity* snowglobeLittle_Mouth_Rock2 = new Entity(snowglobe);
	snowglobeLittle_Mouth_Rock2->AddComponent<Mesh>()->LoadModel("SnowglobeLittle_Mouth_Rock2.obj", "Fabric");
	snowglobeLittle_Mouth_Rock2->AddComponent<Animation>();
	entities.push_back(snowglobeLittle_Mouth_Rock2);
	//snowglobeLittle_Mouth_Rock3
	Entity* snowglobeLittle_Mouth_Rock3 = new Entity(snowglobe);
	snowglobeLittle_Mouth_Rock3->AddComponent<Mesh>()->LoadModel("SnowglobeLittle_Mouth_Rock3.obj", "Fabric");
	snowglobeLittle_Mouth_Rock3->AddComponent<Animation>();
	entities.push_back(snowglobeLittle_Mouth_Rock3);
	//snowglobeRight_Eye
	Entity* snowglobeRight_Eye = new Entity(snowglobe);
	snowglobeRight_Eye->AddComponent<Mesh>()->LoadModel("SnowglobeRight_Eye.obj", "Fabric");
	snowglobeRight_Eye->AddComponent<Animation>();
	entities.push_back(snowglobeRight_Eye);
	//snowglobeLeft_Eye
	Entity* snowglobeLeft_Eye = new Entity(snowglobe);
	snowglobeLeft_Eye->AddComponent<Mesh>()->LoadModel("SnowglobeLeft_Eye.obj", "Fabric");
	snowglobeLeft_Eye->AddComponent<Animation>();
	entities.push_back(snowglobeLeft_Eye);
	//snowglobeCarrot
	Entity* snowglobeCarrot = new Entity(snowglobe);
	snowglobeCarrot->AddComponent<Mesh>()->LoadModel("SnowglobeCarrot.obj", "Metal Orange");
	snowglobeCarrot->AddComponent<Animation>();
	entities.push_back(snowglobeCarrot);
	//snowglobeHat
	Entity* snowglobeHat = new Entity(snowglobe);
	snowglobeHat->AddComponent<Mesh>()->LoadModel("SnowglobeHat.obj", "Fabric");
	snowglobeHat->AddComponent<Animation>();
	entities.push_back(snowglobeHat);
	//snowglobePines1
	Entity* snowglobePines1 = new Entity(snowglobe);
	snowglobePines1->AddComponent<Mesh>()->LoadModel("SnowglobePines1.obj", "Metal Green");
	snowglobePines1->AddComponent<Animation>();
	entities.push_back(snowglobePines1);
	//snowglobeTrunk1
	Entity* snowglobeTrunk1 = new Entity(snowglobe);
	snowglobeTrunk1->AddComponent<Mesh>()->LoadModel("SnowglobeTrunk1.obj", "Metal Brown");
	snowglobeTrunk1->AddComponent<Animation>();
	entities.push_back(snowglobeTrunk1);
	//snowglobePines2
	Entity* snowglobePines2 = new Entity(snowglobe);
	snowglobePines2->AddComponent<Mesh>()->LoadModel("SnowglobePines2.obj", "Metal Green");
	snowglobePines2->AddComponent<Animation>();
	entities.push_back(snowglobePines2);
	//snowglobeTrunk2
	Entity* snowglobeTrunk2 = new Entity(snowglobe);
	snowglobeTrunk2->AddComponent<Mesh>()->LoadModel("SnowglobeTrunk2.obj", "Metal Brown");
	snowglobeTrunk2->AddComponent<Animation>();
	entities.push_back(snowglobeTrunk2);
	//snowglobePines3
	Entity* snowglobePines3 = new Entity(snowglobe);
	snowglobePines3->AddComponent<Mesh>()->LoadModel("SnowglobePines3.obj", "Metal Green");
	snowglobePines3->AddComponent<Animation>();
	entities.push_back(snowglobePines3);
	//snowglobeTrunk3
	Entity* snowglobeTrunk3 = new Entity(snowglobe);
	snowglobeTrunk3->AddComponent<Mesh>()->LoadModel("SnowglobeTrunk3.obj", "Metal Brown");
	snowglobeTrunk3->AddComponent<Animation>();
	entities.push_back(snowglobeTrunk3);

	/*--Table--*/
	Entity* table = new Entity();
	table->SetName("Table");
	table->GetTransform()->SetPosition(glm::vec3(-13.956f, 2.620f, 6.997f));
	table->SetTag("Animate");
	table->AddComponent<Manipulate>();
	auto tableAnim = table->AddComponent<Animation>();
	tableAnim->AddClip(Clip("focus", 1, Transform(*table->GetTransform()), Transform(glm::vec3(0.4, 25.7, -7), table->GetTransform()->GetRotationEuler(), table->GetTransform()->GetScale())));
	tableAnim->AddClip(Clip("unfocus", 1, Transform(glm::vec3(0.4, 25.7, -7), table->GetTransform()->GetRotationEuler(), table->GetTransform()->GetScale()), Transform(*table->GetTransform())));
	entities.push_back(table);
	//tableFeet1
	Entity* tableFeet1 = new Entity(table);
	tableFeet1->AddComponent<Mesh>()->LoadModel("TableFeet1.obj", "Wood2");
	tableFeet1->AddComponent<Animation>();
	entities.push_back(tableFeet1);
	//tableGlass
	Entity* tableFeet2 = new Entity(table);
	tableFeet2->AddComponent<Mesh>()->LoadModel("TableFeet2.obj", "Wood2");
	tableFeet2->AddComponent<Animation>();
	entities.push_back(tableFeet2);
	//TableGlass
	Entity* tableGlass = new Entity(table);
	tableGlass->AddComponent<Mesh>()->LoadModel("TableGlass.obj", "Glass");
	tableGlass->AddComponent<Animation>();
	entities.push_back(tableGlass);
	//snowglobeGlass
	Entity* snowglobeGlass = new Entity(snowglobe);
	snowglobeGlass->AddComponent<Mesh>()->LoadModel("SnowglobeGlass.obj", "Glass");
	snowglobeGlass->AddComponent<Animation>();
	entities.push_back(snowglobeGlass);

	/*--Arrow--*/
	Entity* arrow = new Entity();
	arrow->SetName("Arrow");
	arrow->AddComponent<Mesh>()->LoadModel("Arrow.obj", "Bricks");
	entities.push_back(arrow);

	//anim->AddClip(Clip("test", 5, Transform(glm::vec3(0), glm::vec3(0), glm::vec3(0.2f)), Transform(glm::vec3(0, 5, 5), glm::vec3(90), glm::vec3(1))));
	//anim->AddClip(Clip("test2", 1, Transform(glm::vec3(0, 5, 5), glm::vec3(90), glm::vec3(1)), Transform(glm::vec3(0), glm::vec3(0), glm::vec3(0.2f))));


	RenderModule::Get().SetMainCamera(camera);
}

void Engine::Start()
{
	RenderModule::Get().Start();
	Asset::Get().Start();
	Time::Get().Start();
	Input::Get().Start();

	LoadScene();



	for (auto ent : entities) {
		ent->Start();
	}

}

void Engine::Update()
{
	do {										// run until the window is closed
		Time::Get().Update();
		Input::Get().Update();

		for (auto ent : entities) {
			if (ent->IsActive()) {
				ent->Update();
			}
		}

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

std::vector<Entity*> Engine::GetEntitiesByTag(const std::string tag)
{
	std::vector<Entity*> result;

	for (Entity* entity : entities) {
		if (entity->GetTag() == tag) {
			result.push_back(entity);
		}
	}
	return result;
}


void Engine::HintsGLFW() {
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);			// Create context in debug mode - for debug message callback
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void Engine::ErrorGLFWCallback(int error, const char* description) {
	std::cout << "Error GLFW: " << description << "\n";
}

