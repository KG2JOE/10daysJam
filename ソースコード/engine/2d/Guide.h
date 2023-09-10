#pragma once
#include <vector>
#include "Input.h"
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

class Guide
{
public:
	enum GuideState
	{
		DISPLAYIN,
		DISPLAYVIEW,
		DISPLAYOUT,
	};
private:
	Input* input = nullptr;
    std::vector<Sprite*> guideSprites;
	Sprite* rightAllowSprite = nullptr;
	Sprite* leftAllowSprite = nullptr;
	Sprite* startSprite = nullptr;
	GuideState guideState;
	int maxSpriteNum;
	int currentSprite;
	int nextSprite;
	bool endFlag;
	int count;

public:
	Guide(SpriteCommon* spriteCommon, std::vector<int> guideTexNumbers, int allowTexNumber, int startTexNumber);
	~Guide();
	void Initialize();
	void Update();
	void Draw();
	void SetInput(Input* input) { this->input = input; }

private:
	void DisplayIn();
	void DisplayView();
	void DisplayOut();
	bool RightAllowPush();
	bool LeftAllowPush();
	bool StartPush();
};