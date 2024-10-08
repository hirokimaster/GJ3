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
	worldTransform_.scale = { 0.5f,0.5f,0.5f };

	skinTex_ = TextureManager::GetInstance()->Load("resources/Player/player.png");
	//ModelManager::GetInstance()->LoadObjModel("walk.gltf");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();

	
	object_->SetAnimModel("Player/player.gltf");
	//object_->SetModel("Player/player.obj");
	object_->SetWorldTransform(worldTransform_);
	object_->SetTexHandle(skinTex_);
	object_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//object_->SetEnableLight(true);
	fallVelo_ = 0.0f;

	

	SetCollosionAttribute(0b01);
	SetCollisionMask(0b10);
}

void Player::ResultInit(Vector3 translate)
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
	worldTransform_.scale = { 0.5f,0.5f,0.5f };

	skinTex_ = TextureManager::GetInstance()->Load("resources/Player/player.png");
	//ModelManager::GetInstance()->LoadObjModel("walk.gltf");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();

	
	object_->SetAnimModel("Player/player.gltf");
	//object_->SetModel("Player/player.obj");
	object_->SetWorldTransform(worldTransform_);
	object_->SetTexHandle(skinTex_);
	object_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//object_->SetEnableLight(true);
	fallVelo_ = 0.0f;

	

	SetCollosionAttribute(0b01);
	SetCollisionMask(0b10);
}

void Player::Update()
{
	if (behaviorRequest_) {
		// 振る舞いを変更する
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化を実行
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInit();
			break;
		case Behavior::kDeceleration:
			BehaviorRootDecelerationInit();
			break;
		case Behavior::kElectricShock:
			BehaviorRootElectricShockInit();
			break;
		case Behavior::kWait:
			BehaviorRootWaitInit();
			break;
		}
		// 振る舞いリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
		// 通常行動
	case Behavior::kRoot:

	default:
		Move();
		BehaviorRootUpdate();
		Fall();
		break;
	case Behavior::kDeceleration:
		Move();
		BehaviorRootDecelerationUpdate();
		Fall();
		break;
	case Behavior::kElectricShock:
		BehaviorRootElectricShockUpdate();
		Fall();
		break;
	case Behavior::kWait:
		Move();
		BehaviorRootWaitUpdate();
		break;
	}


	//ApplyGlobalVariables();

	
	
	aniTime_ += 1.0f / 60.0f;
	aniTime_ = std::fmod(aniTime_, duration_);
	object_->SetAnimationTime(aniTime_);
	object_->SetWorldTransform(worldTransform_);
	worldTransform_.UpdateMatrix();
	// カメラのYをプレイヤーに追従
	camera_->translate.y = worldTransform_.translate.y;
}

void Player::Draw(Camera& camera)
{
	object_->Draw(camera,true);
}

void Player::TitleUpdate()
{


	aniTime_ += 1.0f / 60.0f;
	aniTime_ = std::fmod(aniTime_, resultDuration_);
	object_->SetAnimationTime(aniTime_);
	worldTransform_.rotate.y = 1.57f * 2.5f;
	//object_->SetAnimationTime(aniTime_);
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);

	// カメラのYをプレイヤーに追従
	camera_->translate.y = worldTransform_.translate.y -5.0f;
	//worldTransform_.rotate.y = 0.01f;
}

void Player::ResultUpdate()
{


	aniTime_ += 1.0f / 60.0f;
	aniTime_ = std::fmod(aniTime_, resultDuration_);
	object_->SetAnimationTime(aniTime_);
	worldTransform_.rotate.y = 1.57f * 2.5f;
	//object_->SetAnimationTime(aniTime_);
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);

	// カメラのYをプレイヤーに追従
	//camera_->translate.y = worldTransform_.translate.y ;
	//worldTransform_.rotate.y = 0.01f;
}

void Player::Move()
{


	if (Input::GetInstance()->PushKey(DIK_D)) {
		worldTransform_.translate.x += 0.1f;
		worldTransform_.rotate.y = 1.57f;
	}
	else if (Input::GetInstance()->PushKey(DIK_A)) {
		worldTransform_.translate.x -= 0.1f;
		worldTransform_.rotate.y = 1.57f * 2.5f;
	}

	if(Input::GetInstance()->GetJoystickState() ){


		if (!inoperable_) {
			worldTransform_.translate.x += Input::GetInstance()->JoyStickParmLX(0.1f);
			if (Input::GetInstance()->JoyStickParmLX(0.5f) == 0) {
				worldTransform_.rotate.y = 3.14f;
			}
			else if (Input::GetInstance()->JoyStickParmLX(0.5f) > 0) {
				worldTransform_.rotate.y = 1.57f;
			}
			else if (Input::GetInstance()->JoyStickParmLX(0.5f) < 0) {
				worldTransform_.rotate.y = 1.57f * 2.5f;
			}


		}
	}
	

	

		
	

	if (worldTransform_.translate.x >= 10.0f) {
		worldTransform_.translate.x = 10.0f;
	}
	else if (worldTransform_.translate.x <= -10.0f) {
		worldTransform_.translate.x = -10.0f;
	} 
}

void Player::Fall()
{
	
	worldTransform_.translate.y -= fallVelo_;
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

Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

void Player::OnCollision()
{
}

void Player::BehaviorRootInit()
{
	//fallVelo_ ;
	inoperable_ = false;
}

void Player::BehaviorRootUpdate()
{

	fallVelo_ += gravity_;
	if (fallVelo_ >= 0.3f) {
		fallVelo_ = 0.3f;
	}
}

void Player::BehaviorRootDecelerationInit()
{
	fallVelo_ = 0.05f;
	decelerationTimer_ = 0.0f;
	inoperable_ = false;
}

void Player::BehaviorRootDecelerationUpdate()
{
	decelerationTimer_++;
	if (decelerationTimer_ >=100.0f) {
		behaviorRequest_ = Behavior::kRoot;
	}
}

void Player::BehaviorRootElectricShockInit()
{
	electricShockTimer_ = 0.0f;
	fallVelo_ = 0.8f; // 仮の速さ
	inoperable_ = true;
}

void Player::BehaviorRootElectricShockUpdate()
{
	++electricShockTimer_;
	// とりあえず2秒
	if (electricShockTimer_ >= 120.0f) {
		behaviorRequest_ = Behavior::kRoot;
		inoperable_ = false;
	}
}

void Player::BehaviorRootWaitInit()
{
	
}

void Player::BehaviorRootWaitUpdate()
{
	if (isFall_)
	{
		behaviorRequest_ = Behavior::kRoot;
	}
}
