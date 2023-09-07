#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

#define TexWidth 34.0f
#define TexHeight 64.0f
#define MaxSprite 10

class Score
{
private:
	Sprite* sprites[MaxSprite];
	XMFLOAT2 position;
	float size;
	
	int currentScore;

	bool printZeroFlag;

public:
	Score(SpriteCommon* spriteCommon, int texNumber);
	~Score();
	void Initialize();
	void Update();
	void Draw();

	void SetCurrentScore();

	void SetPosition(XMFLOAT2 position)
	{
		this->position = position;
		for (int i = 0; i < MaxSprite; i++)
		{
			sprites[i]->SetPosition({ position.x + (MaxSprite - 1 - i) * TexWidth * size, position.y, 0.0f });
		}
	}
	void SetSize(float size)
	{
		this->size = size;
		for (int i = 0; i < MaxSprite; i++)
		{
			sprites[i]->SetPosition({ position.x + i * TexWidth * size, position.y, 0.0f });
			sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
		}
	}
	void SetPrintZero(bool flag) { printZeroFlag = flag; }
	void SetScore(int score) { currentScore = score; }
	void AddScore(int score) { currentScore += score; }
	int GetScore() { return currentScore; }
};