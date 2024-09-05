#include "GameCamera.h"
#include "application/GlovalVariables/GlobalVariables.h"
void GameCamera::Init()
{

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "GameCamera";
	// グループを追加
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	//globalVariables->AddItme(groupName, "main Translation", camera_.translate);
	globalVariables->AddItme(groupName, "main Rotation", camera_.rotate);
	globalVariables->AddItme(groupName, "main farZ", camera_.farZ);
	camera_.Initialize();
	camera_.translate.z = -40;
	camera_.translate.y = 105;
	camera_.farZ = 50.0f;
	camera_.rotate.x = 0.0f;
}

void GameCamera::Update()
{
	//ApplyGlobalVariables();
	camera_.UpdateMatrix();
}

void GameCamera::ApplyGlobalVariables()
{
	GlobalVariables* gVes = GlobalVariables::GetInstance();
	const char* groupName = "GameCamera";
	//camera_.translate = gVes->GetVector3Value(groupName, "main Translation");
	camera_.rotate = gVes->GetVector3Value(groupName, "main Rotation");
	camera_.farZ = gVes->GetFloatValue(groupName, "main farZ");
}
