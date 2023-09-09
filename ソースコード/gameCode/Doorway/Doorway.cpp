#include "Doorway.h"

void Doorway::Ins(SpriteCommon* spCom_)
{
	assert(spCom_);
	spCom = spCom_;

	spCom->LoadTexture(incinerator, L"Resources/sprite/Furnace.png");
	spCom->LoadTexture(beltConveyor_1, L"Resources/sprite/beltConveyor.png");
	spCom->LoadTexture(beltConveyor_2, L"Resources/sprite/beltConveyor.png");

	incineratorPos = {1200,50,0};

	incineratorSprite = Sprite::Create(spCom, incinerator, { 0.5,0.5 }, false, false);
	incineratorSprite->SetPosition(incineratorPos);
	incineratorSprite->Update();
	

	beltConveyorPos[0] = { 1200,200,0 };
	beltConveyorPos[1] = { 1200,400,0 };
	beltConveyorPos[2] = { 1200,150,0 };


	for (int i = 0; i < 3; i++)
	{

		beltConveyorSprite[i] = Sprite::Create(spCom, beltConveyor_1, { 0.5,0.5 }, false, false);
		beltConveyorSprite[i]->SetPosition(beltConveyorPos[i]);
		beltConveyorSprite[i]->Update();
	}
	attendingWorkPos = { 64,720,0 };
}

void Doorway::Update()
{
}

void Doorway::Draw()
{
	incineratorSprite->Draw();

	for (int i = 0; i < 3; i++)
	{
		beltConveyorSprite[i]->Draw();
	}

}

void Doorway::Delete()
{

}
