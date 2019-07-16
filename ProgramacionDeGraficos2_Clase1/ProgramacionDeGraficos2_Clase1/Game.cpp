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
	theNodoOne->AddChild(theNodoTwo);
	sceneNode = new Node(renderer);
	sceneNode->AddChild(mainCameraNode);
	sceneNode->AddChild(theNodoOne);
	MeshLoader::GetInstance()->LoadMesh("3DAssets\\Car.fbx", "3DAssets\\CarTexture.bmp", theNodoTwo, renderer, camera);
	theNodoTwo->SetScale(0.5F, 0.5F, 0.5F);
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
		camera->CameraRoll(2.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(DKey))
	{
		camera->CameraRoll(-2.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(WKey))
	{
		camera->CameraPitch(2.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(SKey))
	{
		camera->CameraPitch(-2.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(QKey))
	{
		camera->CameraYaw(2.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(EKey))
	{
		camera->CameraYaw(-2.0F * Time::dt);
	}

	theNodoOne->Update();

	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}
	theNodoTwo->SetRotationX(theNodoTwo->GetRotationX() + Time::dt);
	theNodoTwo->GetChildByIndex(1)->SetRotationZ(theNodoTwo->GetChildByIndex(1)->GetRotationZ() + Time::dt);
	theNodoTwo->GetChildByIndex(2)->SetRotationZ(theNodoTwo->GetChildByIndex(2)->GetRotationZ() + Time::dt);
	cout<<"End of frame"<<endl;
	return true;
}

void Game::OnDraw()
{
	//theNodoOne->Draw();
	//theNodoTwo->GetNode(3)->Draw();
	//theNodoTwo->GetNode(2)->Draw();
}

