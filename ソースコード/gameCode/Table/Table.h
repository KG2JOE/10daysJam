#pragma once

#include "SpriteCommon.h"
#include "Sprite.h"
#include<DirectXMath.h>
class Table
{

private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;


public:

	void Ins(SpriteCommon* spCom_);

	void Update();

	void Draw();

	void Delete();

private:
	SpriteCommon* spCom;
	Sprite* table[5][4]{};
	
	XMFLOAT3 pos[5][4]{};

	XMFLOAT2 mapInsPos{};

	float startPosX = 196.f;
	float startPosY = 128.f;

	float intervalX = 160.f;
	float intervalY = 128.f;


};

