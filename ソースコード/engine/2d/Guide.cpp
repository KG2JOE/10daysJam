#include "Guide.h"
#include "WinApp.h"
#include "Easing.h"

Guide::Guide(SpriteCommon* spriteCommon, std::vector<int> guideTexNumbers, int allowTexNumber, int startTexNumber)
{
	for (int i = 0; i < guideTexNumbers.size(); i++)
	{
		guideSprites.push_back(Sprite::Create(spriteCommon, guideTexNumbers[i]));
		guideSprites[i]->SetPosition({ WinApp::window_width * 1.5f, WinApp::window_height * 0.4f, 0.0f });
		guideSprites[i]->SetSize({ 800, 450 });
		guideSprites[i]->Update();
	}

	rightAllowSprite = Sprite::Create(spriteCommon, allowTexNumber);
	rightAllowSprite->SetPosition({ WinApp::window_width * 2.0f - 120.0f, WinApp::window_height * 0.4f, 0.0f });
	rightAllowSprite->SetSize({ 100.0f, 300.0f });
	rightAllowSprite->Update();
	leftAllowSprite = Sprite::Create(spriteCommon, allowTexNumber);
	leftAllowSprite->SetPosition({ 120.0f - WinApp::window_width, WinApp::window_height * 0.4f, 0.0f });
	leftAllowSprite->SetSize({ 100.0f, 300.0f });
	leftAllowSprite->SetIsFlipX(true);
	leftAllowSprite->Update();
	startSprite = Sprite::Create(spriteCommon, startTexNumber);
	startSprite->SetPosition({ WinApp::window_width * 0.5f, WinApp::window_height * 2.0f - 120.0f, 0.0f });
	startSprite->SetSize({ 400.0f, 100.0f });
	startSprite->Update();
	guideState = GuideState::DISPLAYIN;
	maxSpriteNum = guideTexNumbers.size();
	currentSprite = -1;
	nextSprite = 0;
	endFlag = false;
	count = 0;
}

Guide::~Guide()
{
	guideSprites.clear();
	guideSprites.shrink_to_fit();

	delete rightAllowSprite;
	delete leftAllowSprite;
	delete startSprite;
}

void Guide::Initialize()
{
	guideState = GuideState::DISPLAYIN;
	currentSprite = -1;
	nextSprite = 0;
	endFlag = false;
	count = 0;
}

void Guide::Update()
{
	switch (guideState)
	{
	case Guide::DISPLAYIN:
		DisplayIn();
		break;
	case Guide::DISPLAYVIEW:
		DisplayView();
		break;
	case Guide::DISPLAYOUT:
		DisplayOut();
		break;
	default:
		break;
	}
}

void Guide::Draw()
{
	for (int i = 0; i < guideSprites.size(); i++)
	{
		guideSprites[i]->Draw();
	}

	rightAllowSprite->Draw();

	leftAllowSprite->Draw();

	startSprite->Draw();
}

void Guide::DisplayIn()
{
	if (currentSprite < nextSprite)
	{
		float e = Easing::OutQuart((float)min(count, 120), 120.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width * 1.5f - width;
		guideSprites[nextSprite]->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		guideSprites[nextSprite]->Update();
	}

	count++;
}

void Guide::DisplayView()
{
}

void Guide::DisplayOut()
{
}

bool Guide::RightAllowPush()
{
	if (rightAllowSprite->GetPosition().x - rightAllowSprite->GetSize().x / 2.0f <= input->GetMousePoint().x &&
		rightAllowSprite->GetPosition().x + rightAllowSprite->GetSize().x / 2.0f >= input->GetMousePoint().x &&
		rightAllowSprite->GetPosition().y - rightAllowSprite->GetSize().y / 2.0f <= input->GetMousePoint().y &&
		rightAllowSprite->GetPosition().y - rightAllowSprite->GetSize().y / 2.0f <= input->GetMousePoint().y)
	{
		return input->TriggerMouseLeft();
	}

	return false;
}

bool Guide::LeftAllowPush()
{
	if (leftAllowSprite->GetPosition().x - leftAllowSprite->GetSize().x / 2.0f <= input->GetMousePoint().x &&
		leftAllowSprite->GetPosition().x + leftAllowSprite->GetSize().x / 2.0f >= input->GetMousePoint().x &&
		leftAllowSprite->GetPosition().y - leftAllowSprite->GetSize().y / 2.0f <= input->GetMousePoint().y &&
		leftAllowSprite->GetPosition().y - leftAllowSprite->GetSize().y / 2.0f <= input->GetMousePoint().y)
	{
		return input->TriggerMouseLeft();
	}

	return false;
}

bool Guide::StartPush()
{
	if (startSprite->GetPosition().x - startSprite->GetSize().x / 2.0f <= input->GetMousePoint().x &&
		startSprite->GetPosition().x + startSprite->GetSize().x / 2.0f >= input->GetMousePoint().x &&
		startSprite->GetPosition().y - startSprite->GetSize().y / 2.0f <= input->GetMousePoint().y &&
		startSprite->GetPosition().y - startSprite->GetSize().y / 2.0f <= input->GetMousePoint().y)
	{
		return input->TriggerMouseLeft();
	}

	return false;
}
