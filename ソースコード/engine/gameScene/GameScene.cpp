#include "GameScene.h"

void GameScene::EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{
	//winApp = winApp_;
	dxCommon = dxCommon_;
	input = input_;
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	Object3d::StaticInitialize(dxCommon->GetDev());

	Object3d::SetCamera(camera);

	InsObj::StaticInitialize(dxCommon->GetDev());

	InsObj::SetCamera(camera);


	// カメラ注視点をセット
	camera->SetTarget({ 0, 0, 00 });
	camera->SetDistance(3.0f);
	camera->SetEye({ 0, 10, 0 });
	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	spriteCommon->LoadTexture(0, L"Resources/sprite/debugfont.png");
	spriteCommon->LoadTexture(1, L"Resources/sprite/drawNumber.png");
	spriteCommon->LoadTexture(2, L"Resources/sprite/white1x1.png");

	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("ice1.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.05f;
	audio->SetVolume("BGM4.wav", s);
	s = 0.1f;
	audio->SetVolume("ice1.wav", s);

	debTxt = new DebugText;
	debTxt->Initialize(spriteCommon, 0);

	particleManager = ParticleManager2d::Create();
	particleManager->SetSpriteCommon(spriteCommon);

	timer = new Timer(spriteCommon, 1);
	timer->SetLimitTime(120);
	timer->SetPosition({ 100.0f, 100.0f });
	timer->SetSize(5.0f);
	timer->Initialize();

	score = new Score(spriteCommon, 1);
	score->SetScore(0);
	score->SetPosition({ 100.0f, 100.0f });
	score->SetSize(2.0f);
	score->Initialize();

	fade = new Fade(spriteCommon, 2);
}




void GameScene::Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{
	assert(winApp_);
	assert(dxCommon_);
	assert(input_);
	EngineIns(winApp_, dxCommon_, input_);

	timer->Initialize();
	score->Initialize();
	fade->SetFadeOut();
}

void GameScene::Update()
{
	//particleManager->Add(0, 10, { 100.0f, 100.0f }, { 0.0f, 10.0f }, { 0.0f, 10.0f }, {100.0f, 100.0f});
	particleManager->Update();
	timer->Update();
	score->AddScore(1);
	score->Update();
	fade->Update();
}



void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	Object3d::PostDraw();

	spriteCommon->PreDraw();
	particleManager->Draw();
	timer->Draw();
	//score->Draw();
	fade->Draw();
	// ４．描画コマンドここまで
}

void GameScene::Delete()
{
	audio->Finalize();
	delete debTxt;
	delete camera;
	
	delete spriteCommon;
	delete particleManager;

	delete timer;
	delete score;
	delete fade;
}

