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
	


	mesh1 = new Mesh("3DAssets//Toad.obj", "3DAssets//ToadTexture.bmp", renderer);

	materialMesh1 = new Material();
	materialMesh1->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	mesh1->SetMaterial(materialMesh1);
	mesh1->SetTranslation(50.0f, 0.0f, -100.0f);




	mesh2 = new Mesh("3DAssets//Car.fbx", "3DAssets//CarTexture.bmp", renderer);
	mesh2->SetScale(0.1f, 0.1f, 0.1f);

	materialMesh2 = new Material();
	materialMesh2->LoadShaders("texturevertexshader.txt", "texturefragmentshader.txt");
	mesh2->SetMaterial(materialMesh2);
	mesh2->SetTranslation(0.0f, 0.0f, -100.0f);


	renderer->SetProjectionPerspective(45.0F, 2.4F, 0.1F, 100000.0F);

	return true;
}
bool Game::OnStop() {
	delete camera;
	delete mesh1;
	delete materialMesh1;
	return false;
}
bool Game::OnUpdate() {

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
		camera->CameraStrafe(-100.0F * Time::dt);
	}
	else if (ImputManager::GetInstance()->GetKeyDown(RightKey))
	{
		camera->CameraStrafe(100.0F * Time::dt);
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

	mesh1->SetRotationY(mesh1->GetRotationY() + (2.0f * Time::dt));
	mesh2->SetRotationY(mesh2->GetRotationY() - (2.0f * Time::dt));

	if (ImputManager::GetInstance()->GetKeyDown(Escape))
	{
		return false;
	}

	
	return true;
}

void Game::OnDraw()
{
	mesh1->Draw();
	mesh2->Draw();
}

