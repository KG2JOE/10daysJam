#include "Doorway.h"

void Doorway::Ins(SpriteCommon* spCom_)
{
	assert(spCom_);
	spCom = spCom_;
	
	spCom->LoadTexture(incinerator, L"Resources/sprite/FurnaceBack.png");
	spCom->LoadTexture(incinerator_2, L"Resources/sprite/FurnaceFront.png");
	spCom->LoadTexture(beltConveyor_1, L"Resources/sprite/beltConveyor.png");
	spCom->LoadTexture(beltConveyor_2, L"Resources/sprite/beltConveyor.png");
	spCom->LoadTexture(beltConveyor_3, L"Resources/sprite/beltConveyorBent.png");
	spCom->LoadTexture(beltConveyorAnimation, L"Resources/sprite/beltConveyorMove.png");
	spCom->LoadTexture(beltConveyorSideAnimation, L"Resources/sprite/beltConveyorMoveSide.png");
	spCom->LoadTexture(beltConveyorBentAnimation, L"Resources/sprite/beltConveyorBentMove.png");
	spCom->LoadTexture(bg, L"Resources/sprite/bg.png");
	spCom->LoadTexture(alive, L"Resources/sprite/alive.png");

	incineratorPos = { 1200,128,0 };

	incineratorSprite = Sprite::Create(spCom, incinerator, { 0.5,0.5 }, false, false);
	incineratorSprite_2 = Sprite::Create(spCom, incinerator_2, {0.5,0.5}, false, false);
	bgSprite = Sprite::Create(spCom, bg, { 0,0 }, false, false);
	aliveSprite = Sprite::Create(spCom, alive);
	aliveSprite->SetPosition({1150.0f, 600.0f, 0.0f});
	aliveSprite->Update();
	incineratorSprite->SetPosition(incineratorPos);
	incineratorSprite->Update();

	incineratorSprite_2->SetPosition(incineratorPos);
	incineratorSprite_2->Update();

	deadConveyorPos[0] = { 1200,152,0 };
	deadConveyorPos[1] = { 1200,197,0 };
	deadConveyorPos[2] = { 1200,242,0 };

	deadConveyorPos[3] = { 1200,242,0 };
	deadConveyorPos[4] = { 1200,242,0 };
	deadConveyorPos[5] = { 1200,242,0 };


	for (int i = 0; i < 5; i++)
	{
		aliveConveyorPos[i] = { 1256.f - (distance_2 *i),incineratorPos.y + distance_1 + (distance_2 * 6),0 };
		aliveConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);
		aliveConveyorSprite[i]->SetRotation(90);
		aliveConveyorSprite[i]->SetPosition(aliveConveyorPos[i]);
		aliveConveyorSprite[i]->Update();

		aliveConveyor[i] = new Animation2D(spCom, beltConveyorSideAnimation, {48.0f, 48.0f}, 5);
		aliveConveyor[i]->SetAnchorPoint({ 0.5f, 0.5f });
		aliveConveyor[i]->SetPosition({ aliveConveyorPos[i].x, aliveConveyorPos[i].y });
		aliveConveyor[i]->SetAnimationFlame(10);
		aliveConveyor[i]->SetSpriteNumbers({ 0,1,2,3,4 });
		aliveConveyor[i]->SetLoopFlag(true);
		aliveConveyor[i]->Initialize();
	}
	for (int i = 0; i < 6; i++)
	{
		if (i < 2)
		{
			deadConveyorPos[i] = { 1200,incineratorPos.y + distance_1 + (distance_2 * i),0 };
			deadConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);
			
			deadConveyor[i] = new Animation2D(spCom, beltConveyorAnimation, { 48.0f, 48.0f }, 5);
			deadConveyor[i]->SetAnchorPoint({ 0.5f, 0.5f });
			deadConveyor[i]->SetPosition({ deadConveyorPos[i].x, deadConveyorPos[i].y });
			deadConveyor[i]->SetAnimationFlame(10);
			deadConveyor[i]->SetSpriteNumbers({ 0,1,2,3,4 });
			deadConveyor[i]->SetLoopFlag(true);
			deadConveyor[i]->Initialize();

		}
		else if (i == 2)
		{
			deadConveyorPos[i] = { 1200,incineratorPos.y + distance_1 + (distance_2 * i),0 };
			deadConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_3, { 0.5,0.5 }, false, false);

			deadConveyor[i] = new Animation2D(spCom, beltConveyorBentAnimation, { 48.0f, 48.0f }, 5);
			deadConveyor[i]->SetAnchorPoint({ 0.5f, 0.5f });
			deadConveyor[i]->SetPosition({ deadConveyorPos[i].x, deadConveyorPos[i].y });
			deadConveyor[i]->SetAnimationFlame(10);
			deadConveyor[i]->SetSpriteNumbers({ 0,1,2,3,4 });
			deadConveyor[i]->SetLoopFlag(true);
			deadConveyor[i]->Initialize();
		}
		else
		{
			deadConveyorPos[i] = { 1200.f - (distance_2 * (i - 2)),incineratorPos.y + distance_1 + (distance_2 * 2),0 };
			deadConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);
			deadConveyorSprite[i]->SetRotation(90);

			deadConveyor[i] = new Animation2D(spCom, beltConveyorSideAnimation, { 48.0f, 48.0f }, 5);
			deadConveyor[i]->SetAnchorPoint({ 0.5f, 0.5f });
			deadConveyor[i]->SetPosition({ deadConveyorPos[i].x, deadConveyorPos[i].y });
			deadConveyor[i]->SetAnimationFlame(10);
			deadConveyor[i]->SetSpriteNumbers({ 0,1,2,3,4 });
			deadConveyor[i]->SetLoopFlag(true);
			deadConveyor[i]->Initialize();
		}
		deadConveyorSprite[i]->SetPosition(deadConveyorPos[i]);
		deadConveyorSprite[i]->Update();
	}
	attendingWorkPos = { 64,770,0 };
}

void Doorway::Update()
{
	for (int i = 0; i < 6; i++)
	{
		deadConveyor[i]->Update();
	}
	for (int i = 0; i < 5; i++)
	{
		aliveConveyor[i]->Update();
	}
}

void Doorway::DrawIncinerator()
{
	incineratorSprite->Draw();
}

void Doorway::Draw()
{
	bgSprite->Draw();
	aliveSprite->Draw();
	incineratorSprite_2->Draw();

	for (int i = 0; i < 6; i++)
	{
		deadConveyor[i]->Draw();
	}
	for (int i = 0; i < 5; i++)
	{
		aliveConveyor[i]->Draw();
	}
}

void Doorway::Delete()
{
	
	delete incineratorSprite;

	delete bgSprite;
	delete aliveSprite;
	delete incineratorSprite_2;

	for (int i = 0; i < 6; i++)
	{
		delete deadConveyorSprite[i];
	}
	for (int i = 0; i < 5; i++)
	{
		delete aliveConveyorSprite[i];
	}
}
