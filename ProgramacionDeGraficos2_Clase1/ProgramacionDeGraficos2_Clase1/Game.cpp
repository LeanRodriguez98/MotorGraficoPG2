#include "Game.h"

Game::Game()
{
}
Game::~Game()
{
}
bool Game::OnStart() {
	
	renderer->SetProjectionPerspective(45.0F, 2.4F, 0.1F, 100000.0F);

	ImputManager::GetInstance()->SetWindow(window);

	camera = new Camera(renderer);
	mainCameraNode = new Node(renderer);
	mainCameraNode->AddComponent(camera);
	theNodoOne = new Node(renderer);
	theNodoTwo = new Node(renderer);
	theNodoOne->AddChild(theNodoTwo);
	sceneNode = new Node(renderer);
	sceneNode->AddChild(mainCameraNode);
	sceneNode->AddChild(theNodoOne);
	MeshLoader::GetInstance()->LoadMesh("3DAssets\\Car.fbx", "3DAssets\\CarTexture.bmp", theNodoTwo, renderer);
	SetSceneNode(sceneNode);
	return true;
}
bool Game::OnStop() {
	delete camera;

	return false;
}
bool Game::OnUpdate() {


	if (ImputManager::GetInstance()->GetKeyDown(DownKey))
	{
		camera->CameraWalk(-1000.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(UpKey))
	{
		camera->CameraWalk(1000.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(LeftKey))
	{
		camera->CameraStrafe(-1000.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		camera->CameraStrafe(1000.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(AKey))
	{
		camera->CameraRoll(10.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(DKey))
	{
		camera->CameraRoll(-10.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(WKey))
	{
		camera->CameraPitch(10.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(SKey))
	{
		camera->CameraPitch(-10.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(QKey))
	{
		camera->CameraYaw(10.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(EKey))
	{
		camera->CameraYaw(-10.0F * Time::dt);
	}

	theNodoOne->Update();

	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}

	theNodoTwo->GetChildByIndex(1)->SetRotationZ(theNodoTwo->GetChildByIndex(1)->GetRotationZ() + Time::dt);
	theNodoTwo->GetChildByIndex(2)->SetRotationZ(theNodoTwo->GetChildByIndex(2)->GetRotationZ() + Time::dt);

	return true;
}

void Game::OnDraw()
{
	//theNodoOne->Draw();
	//theNodoTwo->GetNode(3)->Draw();
	//theNodoTwo->GetNode(2)->Draw();
}

