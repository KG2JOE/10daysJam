#include "Guide.h"
#include "WinApp.h"
#include "Easing.h"

Guide::Guide(SpriteCommon* spriteCommon)
{
	spriteCommon->LoadTexture(SpriteTexNumber::GUIDE1, L"Resources/sprite/guide1.png");
	spriteCommon->LoadTexture(SpriteTexNumber::GUIDE2, L"Resources/sprite/guide2.png");
	spriteCommon->LoadTexture(SpriteTexNumber::GUIDE3, L"Resources/sprite/guide3.png");
	spriteCommon->LoadTexture(SpriteTexNumber::GUIDE4, L"Resources/sprite/guide4.png");
	spriteCommon->LoadTexture(SpriteTexNumber::ALLOW, L"Resources/sprite/allow.png");
	spriteCommon->LoadTexture(SpriteTexNumber::START, L"Resources/sprite/start.png");

	for (int i = 0; i < 4; i++)
	{
		guideSprites.push_back(Sprite::Create(spriteCommon, GUIDE1 + i));
		guideSprites[i]->SetPosition({ WinApp::window_width * 1.5f, WinApp::window_height * 0.4f, 0.0f });
		guideSprites[i]->Update();
	}

	rightAllowSprite = Sprite::Create(spriteCommon, ALLOW);
	rightAllowSprite->SetPosition({ WinApp::window_width * 2.0f - 120.0f, WinApp::window_height * 0.4f, 0.0f });
	rightAllowSprite->Update();
	leftAllowSprite = Sprite::Create(spriteCommon, ALLOW);
	leftAllowSprite->SetPosition({ 120.0f - WinApp::window_width, WinApp::window_height * 0.4f, 0.0f });
	leftAllowSprite->SetIsFlipX(true);
	leftAllowSprite->Update();
	startSprite = Sprite::Create(spriteCommon, START);
	startSprite->SetPosition({ WinApp::window_width * 0.5f, WinApp::window_height * 2.0f - 120.0f, 0.0f });
	startSprite->Update();
	guideState = GuideState::DISPLAYIN;
	maxSpriteNum = 4;
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
	if (endFlag)
	{
		return;
	}

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
		float e = Easing::OutQuart((float)min(count, 30), 30.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width * 1.5f - width;
		guideSprites[nextSprite]->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		guideSprites[nextSprite]->Update();
	}
	else
	{
		float e = Easing::OutQuart((float)min(count, 30), 30.0f);
		float width = e * (float)WinApp::window_width;
		float posX = -WinApp::window_width * 0.5f + width;
		guideSprites[nextSprite]->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		guideSprites[nextSprite]->Update();
	}

	if (nextSprite < maxSpriteNum - 1 && count >= 15)
	{
		float e = Easing::OutQuart((float)min(count - 15, 15), 15.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width * 2.0f - 120.0f - width;
		rightAllowSprite->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		rightAllowSprite->Update();
	}

	if (nextSprite > 0 && count >= 15)
	{
		float e = Easing::OutQuart((float)min(count - 15, 15), 15.0f);
		float width = e * (float)WinApp::window_width;
		float posX = 120.0f - WinApp::window_width + width;
		leftAllowSprite->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		leftAllowSprite->Update();
	}

	if (nextSprite >= maxSpriteNum - 1 && count >= 15)
	{
		float e = Easing::OutQuart((float)min(count - 15, 15), 15.0f);
		float height = e * (float)WinApp::window_height;
		float posY = WinApp::window_height * 2.0f - 120.0f - height;
		startSprite->SetPosition({ WinApp::window_width * 0.5f,  posY, 0.0f });
		startSprite->Update();
	}

	if (count >= 30)
	{
		count = 0;
		currentSprite = nextSprite;
		guideState = GuideState::DISPLAYVIEW;
		return;
	}

	count++;
}

void Guide::DisplayView()
{
	if (currentSprite < maxSpriteNum - 1 && RightAllowPush())
	{
		count = 0;
		nextSprite = currentSprite + 1;
		guideState = GuideState::DISPLAYOUT;
		return;
	}

	if (currentSprite > 0 && LeftAllowPush())
	{
		count = 0;
		nextSprite = currentSprite - 1;
		guideState = GuideState::DISPLAYOUT;
		return;
	}

	if (currentSprite >= maxSpriteNum - 1 && StartPush())
	{
		count = 0;
		nextSprite = currentSprite + 1;
		guideState = GuideState::DISPLAYOUT;
		return;
	}
}

void Guide::DisplayOut()
{
	if (currentSprite < nextSprite)
	{
		float e = Easing::OutQuart((float)min(count, 30), 30.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width * 0.5f - width;
		guideSprites[currentSprite]->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		guideSprites[currentSprite]->Update();
	}
	else
	{
		float e = Easing::OutQuart((float)min(count, 30), 30.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width * 0.5f + width;
		guideSprites[currentSprite]->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		guideSprites[currentSprite]->Update();
	}

	if (currentSprite < maxSpriteNum - 1)
	{
		float e = Easing::OutQuart((float)min(count, 15), 15.0f);
		float width = e * (float)WinApp::window_width;
		float posX = WinApp::window_width - 120.0f + width;
		rightAllowSprite->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		rightAllowSprite->Update();
	}

	if (currentSprite > 0)
	{
		float e = Easing::OutQuart((float)min(count, 15), 15.0f);
		float width = e * (float)WinApp::window_width;
		float posX = 120.0f - width;
		leftAllowSprite->SetPosition({ posX,  WinApp::window_height * 0.4f, 0.0f });
		leftAllowSprite->Update();
	}

	if (currentSprite >= maxSpriteNum - 1)
	{
		float e = Easing::OutQuart((float)min(count, 15), 15.0f);
		float height = e * (float)WinApp::window_height;
		float posY = WinApp::window_height - 120.0f + height;
		startSprite->SetPosition({ WinApp::window_width / 2.0f,  posY, 0.0f });
		startSprite->Update();
	}

	if (count >= 30)
	{
		count = 0;
		guideState = GuideState::DISPLAYIN;
		if (nextSprite >= maxSpriteNum)
		{
			endFlag = true;
		}
		return;
	}

	count++;
}

bool Guide::RightAllowPush()
{
	if (rightAllowSprite->GetPosition().x - rightAllowSprite->GetSize().x / 2.0f <= input->GetMousePoint().x &&
		rightAllowSprite->GetPosition().x + rightAllowSprite->GetSize().x / 2.0f >= input->GetMousePoint().x &&
		rightAllowSprite->GetPosition().y - rightAllowSprite->GetSize().y / 2.0f <= input->GetMousePoint().y &&
		rightAllowSprite->GetPosition().y + rightAllowSprite->GetSize().y / 2.0f >= input->GetMousePoint().y)
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
		leftAllowSprite->GetPosition().y + leftAllowSprite->GetSize().y / 2.0f >= input->GetMousePoint().y)
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
		startSprite->GetPosition().y + startSprite->GetSize().y / 2.0f >= input->GetMousePoint().y)
	{
		return input->TriggerMouseLeft();
	}

	return false;
}
