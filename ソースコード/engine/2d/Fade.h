#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

#define WidthNum 16
#define HeightNum 9

class Fade
{
public:
	enum FadeState
	{
		FADE,
		FADEIN,
		NONEFADE,
		FADEOUT,
	};
private:
	Sprite* sprites[16][9];
	FadeState fadeState;
	XMFLOAT3 fadeColor;
	int count;

public:
	Fade(SpriteCommon* spriteCommon, int texNumber);
	~Fade();
	void SetFadeIn();
	void SetFadeOut();
	void Update();
	void Draw();

	FadeState GetFadeState() { return fadeState; }
};