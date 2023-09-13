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


	camera->SetTarget({ 0, 0, 00 });
	camera->SetDistance(3.0f);
	camera->SetEye({ 0, 10, 0 });
	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	spriteCommon->LoadTexture(0, L"Resources/sprite/debugfont.png");
	spriteCommon->LoadTexture(1, L"Resources/sprite/drawNumber.png");
	spriteCommon->LoadTexture(2, L"Resources/sprite/white1x1.png");
	spriteCommon->LoadTexture(3, L"Resources/sprite/titleBack.png");
	spriteCommon->LoadTexture(4, L"Resources/sprite/number.png");
	
	audio->Initialize();
	//タイトル
	audio->LoadWave("click_.wav");//SE
	audio->LoadWave("Dianthus_.wav");//BGM

	//ゲーム
	audio->LoadWave("taikin_.wav");//退勤SE
	audio->LoadWave("tukamu_.wav");//マウス
	audio->LoadWave("neppa_.wav");//焼却炉
	audio->LoadWave("Working_City.wav");//BGM
	audio->LoadWave("15347_.wav");//叫び声

	//リザルト
	audio->LoadWave("Re-sounds_.wav");//BGM

	float s = 0.05f;
	s = 0.1f;
	audio->SetVolume("click_.wav", s);
	audio->SetVolume("Dianthus_.wav", s);
	audio->SetVolume("taikin_.wav", s);
	audio->SetVolume("tukamu_.wav", s);
	audio->SetVolume("neppa_.wav", s);
	audio->SetVolume("Working_City.wav", s);
	audio->SetVolume("15347_.wav", s);
	audio->SetVolume("Re-sounds_.wav", s);

	employee = new Employee();
	employee->Ins(spriteCommon, input, audio);
	//employee->Update();
	
	spriteCommon->LoadTexture(70, L"Resources/sprite/hand.png");
	spriteCommon->LoadTexture(71, L"Resources/sprite/handLift.png");

	spCom->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	
	
	audio->PlayWave("Dianthus_.wav",true);
	
	
	debTxt = new DebugText;
	debTxt->Initialize(spriteCommon, 0);
	hand = Sprite::Create(spriteCommon, 70, { 0.5f,0.5f });


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

	timer = new Timer(spriteCommon, 4);
	timer->SetLimitTime(120);
	timer->SetPosition({ 200.0f, 130.0f });
	timer->SetSize(1.0f);
	timer->Initialize();

	score = new Score(spriteCommon, 4);
	score->SetScore(0);
	score->SetPosition({ 700.0f, 150.0f });
	score->SetSize(1.0f);
	score->Initialize();
	score->SetScore(employee->GetScore());
	score->Update();
	fade = new Fade(spriteCommon, 2);
	fade->SetFadeState(Fade::FadeState::FADEIN);

	lightFade = new Fade(spriteCommon, 2);
	lightFade->SetFadeColor({ 0.0f, 0.0f, 0.0f, 0.5f });
	lightFade->SetFadeState(Fade::FadeState::FADE);

	guide = new Guide(spriteCommon);
	guide->SetInput(input);
	guide->Initialize();

	sceneState = SceneState::TITLE;
	
	ShowCursor(FALSE);
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
			audio->PlayWave("click_.wav", false);

		}

		if (fade->GetFadeState() == Fade::FadeState::FADE)
		{
			fade->SetFadeState(Fade::FadeState::FADEIN);
			sceneState = SceneState::GUIDE;

			audio->PlayWave("Working_City.wav", true);
			audio->Stop("Dianthus_.wav");


		}

		break;
	case GameScene::GUIDE:

		audio->PlayWave("click_.wav", false);

		guide->Update();

		if (lightFade->GetFadeState() == Fade::FadeState::FADE &&
			guide->GetEndFlag())
		{
			lightFade->SetFadeState(Fade::FadeState::FADEIN);
		}

		if (lightFade->GetFadeState() == Fade::FadeState::NONEFADE)
		{
			sceneState = SceneState::GAMEPLAY;
		}

		break;
	case GameScene::GAMEPLAY:

		if (input->PushMouseLeft())
		{
			audio->PlayWave("tukamu_.wav",false);//マウス

			if (hand != nullptr)
			{
				delete hand;
				hand = nullptr;
			}
			hand = Sprite::Create(spriteCommon, 71, { 0.5f,0.5f });
		}
		else
		{
			audio->Stop("tukamu_.wav");//マウス
			if (hand != nullptr)
			{
				delete hand;
				hand = nullptr;
			}
			hand = Sprite::Create(spriteCommon, 70, { 0.5f,0.5f });

		}

		if (timer->GetLimitFlag() || employee->GetScore() <= 0)
		{
			sceneState = SceneState::TITLE;
		}
		timer->Update();

		employee->SetPlayTime(timer->GetCurrentTime());

		employee->Update();

		particleManager->Update();

		score->SetScore(employee->GetScore());

		score->Update();

		
		break;
	case GameScene::RESULT:
		break;
	default:
		break;
	}

	lightFade->Update();

	fade->Update();
	hand->SetPosition({ (float)input->GetMousePoint().x,(float)input->GetMousePoint().y,0 });
	hand->Update();
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

		employee->Draw();

		timer->Draw();

		score->Draw();

		lightFade->Draw();

		guide->Draw();

		break;
	case GameScene::GAMEPLAY:

		employee->Draw();

		timer->Draw();
		
		particleManager->Draw();
		score->Draw();
		
		timer->Draw();

		score->Draw();

	//DrawDbTxt();
	debTxt->DrawAll();

		break;
	case GameScene::RESULT:

		timer->Draw();

		score->Draw();

		lightFade->Draw();

		break;
	default:
		break;
	}
	hand->Draw();

	fade->Draw();
}

void GameScene::Delete()
{
	audio->Finalize();
	employee->Delete();
	delete employee;
	delete debTxt;
	delete camera;
	
	delete spriteCommon;
	delete particleManager;
	delete hand;
	delete timer;
	delete score;
	delete fade;
	delete lightFade;
}

