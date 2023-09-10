#include "Score.h"

Score::Score(SpriteCommon* spriteCommon, int texNumber)
{
	for (int i = 0; i < MaxSprite; i++)
	{
		sprites[i] = Sprite::Create(spriteCommon, texNumber);
	}

	position = { 0.0f, 0.0f };
	size = 1.0f;
	currentScore = 0;
	printZeroFlag = false;

	for (int i = 0; i < MaxSprite; i++)
	{
		sprites[i]->SetPosition({ position.x + (MaxSprite - 1 - i) * TexWidth * size, position.y, 0.0f });
		sprites[i]->SetTexLeftTop({ 0.0f, 0.0f });
		sprites[i]->SetTexSize({ TexWidth, TexHeight });
		sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
		sprites[i]->Update();
	}
}

Score::~Score()
{
	for (int i = 0; i < MaxSprite; i++)
	{
		delete sprites[i];
	}
}

void Score::Initialize()
{
	for (int i = 0; i < MaxSprite; i++)
	{
		sprites[i]->SetPosition({ position.x + (MaxSprite - 1 - i) * TexWidth * size, position.y, 0.0f });
		sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
	}

	SetCurrentScore();
}

void Score::Update()
{
	SetCurrentScore();
}

void Score::Draw()
{
	for (int i = 0; i < MaxSprite; i++)
	{
		sprites[i]->Draw();
	}
}

void Score::SetCurrentScore()
{
	int digit = 10;
	int num = 0;
	for (int i = 0; i < MaxSprite; i++)
	{
		if (currentScore == num && i > 0)
		{
			sprites[i]->SetTexSize({ 0.0f, TexHeight });
			sprites[i]->Update();
			continue;
		}

		int placeNum = currentScore % (int)(std::pow(digit, i + 1)) - num;
		num += placeNum;
		sprites[i]->SetTexLeftTop({ placeNum / (int)(std::pow(digit, i)) * TexWidth, 0.0f });
		sprites[i]->SetTexSize({ TexWidth, TexHeight });
		sprites[i]->Update();
	}
}
