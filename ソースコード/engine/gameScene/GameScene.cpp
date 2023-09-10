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
	spriteCommon->LoadTexture(3, L"Resources/sprite/titleBack.png");
	
	employee = new Employee();
	employee->Ins(spriteCommon, input);

	spriteCommon->LoadTexture(5, L"Resources/sprite/debugfont.png");
	//spriteCommon->LoadTexture(0, L"Resources/sprite/drawNumber.png");

	spCom->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	
	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("ice1.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.05f;
	audio->SetVolume("BGM4.wav", s);
	s = 0.1f;
	audio->SetVolume("ice1.wav", s);

	debTxt = new DebugText;
	debTxt->Initialize(spriteCommon, 5);



}




void GameScene::Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{
	assert(winApp_);
	assert(dxCommon_);
	assert(input_);
	EngineIns(winApp_, dxCommon_, input_);

	titleSprite = Sprite::Create(spriteCommon, 3, {0.0f, 0.0f});

	particleManager = ParticleManager2d::Create();
	particleManager->SetSpriteCommon(spriteCommon);

	timer = new Timer(spriteCommon, 1);
	timer->SetLimitTime(120);
	timer->SetPosition({ 100.0f, 100.0f });
	timer->SetSize(1.0f);
	timer->Initialize();

	score = new Score(spriteCommon, 1);
	score->SetScore(0);
	score->SetPosition({ 100.0f, 100.0f });
	score->SetSize(2.0f);
	score->Initialize();

	fade = new Fade(spriteCommon, 2);
	fade->SetFadeState(Fade::FadeState::FADEIN);
	sceneState = SceneState::GAMEPLAY;
}

void GameScene::Update()
{
	
	input->Update();

	switch (sceneState)
	{
	case GameScene::TITLE:

		if (fade->GetFadeState() == Fade::FadeState::NONEFADE &&
			input->TriggerMouseLeft())
		{
			fade->SetFadeState(Fade::FadeState::FADEOUT);
		}

		if (fade->GetFadeState() == Fade::FadeState::FADE)
		{
			fade->SetFadeState(Fade::FadeState::FADEIN);
			sceneState = SceneState::GUIDE;
		}

		break;
	case GameScene::GUIDE:
		break;
	case GameScene::GAMEPLAY:
		timer->Update();
		employee->SetPlayTime(timer->GetCurrentTime());
		employee->Update();
		particleManager->Update();
		score->AddScore(1);
		score->Update();
		break;
	case GameScene::RESULT:
		break;
	default:
		break;
	}

	fade->Update();

}

void GameScene::DrawDbTxt()
{
	
	char text2[256];
	char text1[256];
	sprintf_s(text1, "GetCatchFlag:%d", employee->GetCatchFlag());
	debTxt->Print(text1, 0, 160, 1);


	if (employee->GetStatus() == Employee::Status::NONE)
	{
		sprintf_s(text2, "NONE:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::Stress)
	{
		sprintf_s(text2, "Stress:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::Dead)
	{
		sprintf_s(text2, "Dead:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::Grab)
	{
		sprintf_s(text2, "Grab:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::AttendingWork)
	{
		sprintf_s(text2, "AttendingWork:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::Work)
	{
		sprintf_s(text2, "Work:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::LeavingWork)
	{
		sprintf_s(text2, "LeavingWork:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}
	if (employee->GetStatus() == Employee::Status::BeltConveyor)
	{
		sprintf_s(text2, "BeltConveyor:%d", employee->GetStatus());
		debTxt->Print(text2, 0, 128, 1);
	}


	
}



void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	Object3d::PostDraw();

	spriteCommon->PreDraw();

	switch (sceneState)
	{
	case GameScene::TITLE:

		titleSprite->Draw();

		break;
	case GameScene::GUIDE:

		timer->Draw();

		score->Draw();

		break;
	case GameScene::GAMEPLAY:

		employee->Draw();

		timer->Draw();
		/*particleManager->Draw();

		timer->Draw();
	

		score->Draw();*/

	//DrawDbTxt();
	debTxt->DrawAll();

	// ４．描画コマンドここまで
		break;
	case GameScene::RESULT:

		timer->Draw();

		score->Draw();

		break;
	default:
		break;
	}

	fade->Draw();
}

void GameScene::Delete()
{
	audio->Finalize();

	delete employee;
	delete debTxt;
	delete camera;
	
	delete spriteCommon;
	delete particleManager;

	delete timer;
	delete score;
	delete fade;
}

