#include "Doorway.h"

void Doorway::Ins(SpriteCommon* spCom_)
{
	assert(spCom_);
	spCom = spCom_;

	spCom->LoadTexture(incinerator, L"Resources/sprite/Furnace.png");
	spCom->LoadTexture(beltConveyor_1, L"Resources/sprite/beltConveyor.png");
	spCom->LoadTexture(beltConveyor_2, L"Resources/sprite/beltConveyor.png");
	spCom->LoadTexture(bg, L"Resources/sprite/bg.png");

	incineratorPos = { 1200,128,0 };

	incineratorSprite = Sprite::Create(spCom, incinerator, { 0.5,0.5 }, false, false);
	bgSprite = Sprite::Create(spCom, bg, { 0,0 }, false, false);
	incineratorSprite->SetPosition(incineratorPos);
	incineratorSprite->Update();


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
	}
	for (int i = 0; i < 6; i++)
	{
		if (i <= 2)
		{
			deadConveyorPos[i] = { 1200,incineratorPos.y + distance_1 + (distance_2 * i),0 };
			deadConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);

		}
		else
		{
			deadConveyorPos[i] = { 1200.f - (distance_2 * (i - 2)),incineratorPos.y + distance_1 + (distance_2 * 2),0 };
			deadConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);
			deadConveyorSprite[i]->SetRotation(90);
		}
		deadConveyorSprite[i]->SetPosition(deadConveyorPos[i]);
		deadConveyorSprite[i]->Update();
	}
	attendingWorkPos = { 64,770,0 };
}

void Doorway::Update()
{
}

void Doorway::DrawIncinerator()
{
	incineratorSprite->Draw();
}

void Doorway::Draw()
{
	bgSprite->Draw();
	for (int i = 0; i < 6; i++)
	{
		deadConveyorSprite[i]->Draw();
	}
	for (int i = 0; i < 5; i++)
	{
		aliveConveyorSprite[i]->Draw();
	}
}

void Doorway::Delete()
{

}
