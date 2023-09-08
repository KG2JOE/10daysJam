#include "Doorway.h"

void Doorway::Ins(SpriteCommon* spCom_)
{
	assert(spCom_);
	spCom = spCom_;

	spCom->LoadTexture(attending, L"Resources/sprite/human.png");
	spCom->LoadTexture(leavingWork, L"Resources/sprite/human.png");
	spCom->LoadTexture(incinerator, L"Resources/sprite/human.png");
	spCom->LoadTexture(beltConveyor, L"Resources/sprite/human.png");

	attendingWorkSprite = Sprite::Create(spCom, attending, { 0.5,0.5 }, false, false);
	attendingWorkSprite->SetPosition(attendingWorkPos);
	attendingWorkSprite->Update();


	leavingWorkSprite = Sprite::Create(spCom, leavingWork, { 0.5,0.5 }, false, false);
	leavingWorkSprite->SetPosition(leavingWorkPos);
	leavingWorkSprite->Update();


	incineratorSprite = Sprite::Create(spCom, incinerator, { 0.5,0.5 }, false, false);
	incineratorSprite->SetPosition(incineratorPos);
	incineratorSprite->Update();


	for (int i = 0; i < 2; i++)
	{
		beltConveyorSprite[i] = Sprite::Create(spCom, beltConveyor, { 0.5,0.5 }, false, false);
		beltConveyorSprite[i]->SetPosition(beltConveyorPos[i]);
		beltConveyorSprite[i]->Update();
	}
	
}

void Doorway::Update()
{
}

void Doorway::Draw()
{
	attendingWorkSprite->Draw();
	leavingWorkSprite->Draw();
	incineratorSprite->Draw();

	for (int i = 0; i < 2; i++)
	{
		beltConveyorSprite[i]->Draw();
	}

}

void Doorway::Delete()
{

}
