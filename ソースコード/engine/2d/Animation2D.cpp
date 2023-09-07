#include "Animation2D.h"
#include "../base/XMFLOAT_Helper.h"

Animation2D::Animation2D(SpriteCommon* spriteCommon, int texNumber, XMFLOAT2 TexSize, int widthNum)
{
	sprite = Sprite::Create(spriteCommon, texNumber);

	this->texSize = TexSize;
	this->widthNum = widthNum;

	position = { 0.0f, 0.0f };
	anchorPoint = { 0.0f, 0.0f };
	size = 1.0f;
	animationFlame = 0;
	count = 0;

	spriteNumbers = { 0 };
	spriteIndex = 0;

	sprite->SetAnchorpoint(anchorPoint);
	sprite->SetPosition(XMFLOAT3(position.x, position.y, 0.0f));
	sprite->SetTexLeftTop({ 0.0f, 0.0f });
	sprite->SetTexSize(texSize);
	sprite->SetSize(texSize * size);
	sprite->Update();
}

Animation2D::~Animation2D()
{
	delete sprite;
}

void Animation2D::Initialize()
{
	count = 0;
	spriteIndex = 0;

	sprite->SetAnchorpoint(anchorPoint);
	sprite->SetPosition(XMFLOAT3(position.x, position.y, 0.0f));
	sprite->SetTexLeftTop({ 0.0f, 0.0f });
	sprite->SetTexSize(texSize);
	sprite->SetSize(texSize * size);
	sprite->Update();
}

void Animation2D::Update()
{
	if (count >= animationFlame)
	{
		spriteIndex++;
		if (spriteIndex >= spriteNumbers.size())
		{
			spriteIndex = 0;
		}
		count = 0;
	}

	sprite->SetAnchorpoint(anchorPoint);
	sprite->SetPosition(XMFLOAT3(position.x, position.y, 0.0f));
	sprite->SetTexLeftTop({ spriteNumbers[spriteIndex] % widthNum * texSize.x
		, spriteNumbers[spriteIndex] / widthNum * texSize.y});
	sprite->SetTexSize(texSize);
	sprite->SetSize(texSize * size);
	sprite->Update();
	count++;
}

void Animation2D::Draw()
{
	sprite->Draw();
}
