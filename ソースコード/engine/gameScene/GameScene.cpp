#include "GameScene.h"
#include "Easing.h"
#include "XMFLOAT_Helper.h"

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
	spriteCommon->LoadTexture(5, L"Resources/sprite/click.png");
	
	audio->Initialize();
	//�^�C�g��
	audio->LoadWave("click_.wav");//SE
	audio->LoadWave("Dianthus_.wav");//BGM

	//�Q�[��
	audio->LoadWave("taikin_.wav");//�ދ�SE
	audio->LoadWave("tukamu_.wav");//�}�E�X
	audio->LoadWave("neppa_.wav");//�ċp�F
	audio->LoadWave("Working_City.wav");//BGM
	audio->LoadWave("15347_.wav");//���ѐ�

	//���U���g
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

	count = 0;
	titleSprite = Sprite::Create(spriteCommon, 3, { 0.0f, 0.0f });
	clickSprite = Sprite::Create(spriteCommon, 5);
	clickSprite->SetPosition({ WinApp::window_width * 0.5f, WinApp::window_height * 0.7f, 0.0f });
	clickSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	clickSprite->Update();

	particleManager = ParticleManager2d::Create();
	particleManager->SetSpriteCommon(spriteCommon);

	timer = new Timer(spriteCommon, 4);
	timer->SetLimitTime(120);
	timer->SetPosition({ 200.0f, 130.0f });
	timer->SetSize(1.0f);
	timer->Initialize();

	score = new Score(spriteCommon, 4);
	score->SetScore(employee->GetScore());
	score->SetPosition({ 600.0f, 150.0f });
	score->SetSize(1.0f);
	score->Initialize();

	fade = new Fade(spriteCommon, 2);
	fade->SetFadeState(Fade::FadeState::FADEIN);

	lightFade = new Fade(spriteCommon, 2);
	lightFade->SetFadeColor({ 0.0f, 0.0f, 0.0f, 0.5f });
	lightFade->SetFadeState(Fade::FadeState::FADE);

	guide = new Guide(spriteCommon);
	guide->SetInput(input);
	guide->Initialize();

	result = new Result(spriteCommon, 4);
	result->SetRanking({ 0 });

	sceneState = SceneState::TITLE;

	ShowCursor(FALSE);
}

void GameScene::Update()
{

	input->Update();


	switch (sceneState)
	{
	case GameScene::TITLE:

	{
		float eaing = Easing::OutQuart((float)(count % 60 <= 30 ? count % 60 : 60 - count % 60), 30.0f);
		clickSprite->SetColor({ 1.0f, 1.0f, 1.0f, eaing });
		clickSprite->SetSize({ 1280.0f + eaing * 160.0f, 720.0f + eaing * 90.0f });
		clickSprite->Update();
	}

	if (fade->GetFadeState() == Fade::FadeState::NONEFADE)
	{
		if (input->TriggerMouseLeft())
		{
			fade->SetFadeState(Fade::FadeState::FADEOUT);
			audio->PlayWave("click_.wav", false);
		}
	}
	count++;

	if (fade->GetFadeState() == Fade::FadeState::FADE)
	{
		count = 0;
		fade->SetFadeState(Fade::FadeState::FADEIN);
		guide->Initialize();
		timer->Initialize();
		employee->Ins(spriteCommon, input, audio);
		score->SetScore(employee->GetScore());
		score->Initialize();
		sceneState = SceneState::GUIDE;

		audio->PlayWave("Working_City.wav", true);
		audio->Stop("Dianthus_.wav");
	}

	break;
	case GameScene::GUIDE:

		
		if (input->TriggerMouseLeft())
		{
			audio->Stop("click_.wav");
			audio->PlayWave("click_.wav", false);
		}
		guide->Update();

		if (lightFade->GetFadeState() == Fade::FadeState::FADE &&
			guide->GetEndFlag())
		{
			lightFade->SetFadeState(Fade::FadeState::FADEIN);
		}

		count++;

		if (lightFade->GetFadeState() == Fade::FadeState::NONEFADE)
		{
			count = 0;
			sceneState = SceneState::GAMEPLAY;
		}

		break;
	case GameScene::GAMEPLAY:

		if (input->PushMouseLeft())
		{
			audio->PlayWave("tukamu_.wav",false);//�}�E�X

			if (hand != nullptr)
			{
				delete hand;
				hand = nullptr;
			}
			hand = Sprite::Create(spriteCommon, 71, { 0.5f,0.5f });
		}
		else
		{
			audio->Stop("tukamu_.wav");//�}�E�X
			if (hand != nullptr)
			{
				delete hand;
				hand = nullptr;
			}
			hand = Sprite::Create(spriteCommon, 70, { 0.5f,0.5f });

		}

		timer->Update();

		employee->SetPlayTime(timer->GetCurrentTime());

		employee->Update();

		particleManager->Update();

		score->SetScore(max(employee->GetScore(), 0));

		score->Update();

		count++;

		if (timer->GetLimitFlag() || employee->GetScore() <= 0)
		{
			count = 0;
			clickSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			clickSprite->Update();
			lightFade->SetFadeState(Fade::FadeState::FADEOUT);
			result->Initialize(max(employee->GetScore(), 0));

			if (hand != nullptr)
			{
				delete hand;
				hand = nullptr;
			}
			hand = Sprite::Create(spriteCommon, 70, { 0.5f,0.5f });

			sceneState = SceneState::RESULT;
		}

		break;
	case GameScene::RESULT:

		if (lightFade->GetFadeState() == Fade::FadeState::FADE)
		{
			result->Update();
		}

		if (result->GetEndFlag())
		{
			float e = Easing::OutQuart((float)(count % 60 <= 30 ? count % 60 : 60 - count % 60), 30.0f);
			clickSprite->SetColor({ 1.0f, 1.0f, 1.0f, e });
			clickSprite->SetSize({ 1280.0f + e * 160.0f, 720.0f + e * 90.0f });
			clickSprite->Update();

			if (input->TriggerMouseLeft())
			{
				fade->SetFadeState(Fade::FadeState::FADEOUT);
			}
		}

		count++;

		if (fade->GetFadeState() == Fade::FadeState::FADE)
		{
			count = 0;
			fade->SetFadeState(Fade::FadeState::FADEIN);
			clickSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			clickSprite->Update();
			sceneState = SceneState::TITLE;

			audio->PlayWave("Dianthus_.wav", true);
			audio->Stop("Working_City.wav"); 
		}

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

		clickSprite->Draw();

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

		particleManager->Draw();

		score->Draw();

		timer->Draw();

		score->Draw();

		//DrawDbTxt();
		debTxt->DrawAll();

		break;
	case GameScene::RESULT:

		employee->Draw();

		timer->Draw();

		score->Draw();

		lightFade->Draw();

		result->Draw();

		clickSprite->Draw();

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

