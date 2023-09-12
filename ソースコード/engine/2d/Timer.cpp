#include "Timer.h"

Timer::Timer(SpriteCommon* spriteCommon, int texNumber)
{
	for (int i = 0; i < 4; i++)
	{
		sprites[i] = Sprite::Create(spriteCommon, texNumber);
	}
	colon = Sprite::Create(spriteCommon, texNumber);

	position = { 0.0f, 0.0f };
	size = 1.0f;
	limitTime = 0;
	currentTime = limitTime;
	count = 0;
	limitFlag = false;

	for (int i = 0; i < 4; i++)
	{
		sprites[i]->SetPosition({ position.x + (i + i / 2) * TexWidth * size, position.y, 0.0f });
		sprites[i]->SetTexLeftTop({ 0.0f, 0.0f });
		sprites[i]->SetTexSize({ TexWidth, TexHeight });
		sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
		sprites[i]->Update();
	}

	colon->SetPosition({ position.x + 2 * TexWidth * size, position.y, 0.0f });
	colon->SetTexLeftTop({ 10.0f * TexWidth, 0.0f });
	colon->SetTexSize({ TexWidth, TexHeight });
	colon->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
	colon->Update();
}

Timer::~Timer()
{
	for (int i = 0; i < 4; i++)
	{
		delete sprites[i];
	}
	delete colon;
}

void Timer::Initialize()
{
	currentTime = limitTime;
	count = 0;
	limitFlag = false;

	for (int i = 0; i < 4; i++)
	{
		sprites[i]->SetPosition({ position.x + (i + i / 2) * TexWidth * size, position.y, 0.0f });
		sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
	}

	SetCurrentTime();

	colon->SetPosition({ position.x + 2 * TexWidth * size, position.y, 0.0f });
	colon->SetTexLeftTop({ 10 * TexWidth, 0.0f });
	colon->SetTexSize({ TexWidth, TexHeight });
	colon->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
	colon->Update();
}

void Timer::Update()
{
	if (count >= 60)
	{
		currentTime--;
		count = 0;
	}

	SetCurrentTime();

	if (currentTime > 0)
	{
		count++;
	}
	else
	{
		limitFlag = true;
	}
}

void Timer::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		sprites[i]->Draw();
	}

	colon->Draw();
}

void Timer::SetCurrentTime()
{
	int minutes = currentTime / 60;
	int second = currentTime % 60;
	sprites[0]->SetTexLeftTop({ minutes / 10 * TexWidth, 0.0f });
	sprites[0]->SetTexSize({ TexWidth, TexHeight });
	sprites[0]->Update();
	sprites[1]->SetTexLeftTop({ minutes % 10 * TexWidth, 0.0f });
	sprites[1]->SetTexSize({ TexWidth, TexHeight });
	sprites[1]->Update();
	sprites[2]->SetTexLeftTop({ second / 10 * TexWidth, 0.0f });
	sprites[2]->SetTexSize({ TexWidth, TexHeight });
	sprites[2]->Update();
	sprites[3]->SetTexLeftTop({ second % 10 * TexWidth, 0.0f });
	sprites[3]->SetTexSize({ TexWidth, TexHeight });
	sprites[3]->Update();
}
