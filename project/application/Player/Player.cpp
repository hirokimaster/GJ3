#include "Player.h"
#include "engine/TextureManager/TextureManager.h"
#include "engine/Input/Input.h"
#include "engine/Lighting/Lighting.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"
#include "application/GlovalVariables/GlobalVariables.h"

void Player::Init(Vector3 translate)
{
	/*-----------------------あまりよくない感じ-------------------*/
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";
	// グループを追加
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItme(groupName, "main Translation", worldTransform_.translate);
	//------------------------------------------------------------//

	worldTransform_.Initialize();
	worldTransform_.translate = translate;

	skinTex_ = TextureManager::GetInstance()->Load("resources/uvChecker.png");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetAnimModel("sneakWalk.gltf");
	object_->SetWorldTransform(worldTransform_);
	object_->SetTexHandle(skinTex_);
	object_->SetColor({ 1.0f,1.0f,1.0f,1.0f });

}

void Player::Update()
{
	//ApplyGlobalVariables();

	Move();
	Fall();
	object_->SetAnimationTime(aniTime_);
	object_->SetWorldTransform(worldTransform_);
	worldTransform_.UpdateMatrix();
	// カメラのYをプレイヤーに追従
	camera_->translate.y = worldTransform_.translate.y ;
}

void Player::Draw(Camera& camera)
{
	object_->Draw(camera,true);
}

void Player::Move()
{
	if (Input::GetInstance()->GetJoystickState()) {
		
		worldTransform_.translate.x += Input::GetInstance()->JoyStickParmLX(0.1f);
		if (Input::GetInstance()->JoyStickParmLX(0.5f) == 0) {
			worldTransform_.rotate.y = 3.14f;
		}
		else if (Input::GetInstance()->JoyStickParmLX(0.5f) > 0){
			worldTransform_.rotate.y = 1.57f;
		}
		else if (Input::GetInstance()->JoyStickParmLX(0.5f) < 0) {
			worldTransform_.rotate.y = -1.57f;
		}
	}
}

void Player::Fall()
{
	
	worldTransform_.translate.y -= 0.5f;
	if (worldTransform_.translate.y < 0) {
		worldTransform_.translate.y = 0;
	}

}

void Player::ApplyGlobalVariables()
{
	GlobalVariables* gVes = GlobalVariables::GetInstance();
	const char* groupName = "Player";
	worldTransform_.translate = gVes->GetVector3Value(groupName, "main Translation");
}
