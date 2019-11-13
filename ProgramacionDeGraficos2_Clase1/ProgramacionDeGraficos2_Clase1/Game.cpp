#include "Game.h"

Game::Game()
{
}
Game::~Game()
{
}
bool Game::OnStart() {
	

	ImputManager::GetInstance()->SetWindow(window);

	camera = new Camera(renderer);
	mainCameraNode = new Node(renderer);
	mainCameraNode->AddComponent(camera);
	theNodoOne = new Node(renderer);
	theNodoTwo = new Node(renderer);
	theNodoTree = new Node(renderer);
	theNodoOne->AddChild(theNodoTwo);
	sceneNode = new Node(renderer);
	sceneNode->AddChild(mainCameraNode);
	sceneNode->AddChild(theNodoOne);
	theNodoOne->AddChild(theNodoTree);
	MeshLoader::GetInstance()->LoadMesh("3DAssets\\BSPfinal.fbx", "3DAssets\\ToadTexture.bmp", theNodoTwo, renderer, camera);
	theNodoTwo->SetTranslationY(theNodoTwo->GetTranslationY() - 50.0f);
	Time::drawedObjets = 0;
	SetSceneNode(sceneNode);
	return true;
}
bool Game::OnStop() {
	delete camera;

	return false;
}
bool Game::OnUpdate() {

	cout << "Drawed Obj: " << Time::drawedObjets << endl;
	Time::drawedObjets = 0;

	if (ImputManager::GetInstance()->GetKeyDown(DownKey))
	{
		camera->CameraWalk(-100.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(UpKey))
	{
		camera->CameraWalk(100.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
	{
		camera->CameraStrafe(100.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		camera->CameraStrafe(-100.0F * Time::dt);

	}
	else if (ImputManager::GetInstance()->GetKeyDown(AKey))
	{
		camera->CameraRoll(3.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(DKey))
	{
		camera->CameraRoll(-3.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(WKey))
	{
		camera->CameraPitch(3.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(SKey))
	{
		camera->CameraPitch(-3.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(QKey))
	{
		camera->CameraYaw(3.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(EKey))
	{
		camera->CameraYaw(-3.0F * Time::dt);
	}
	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}
	return true;
}

void Game::OnDraw()
{
}

