#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"

#include<DirectXMath.h>

class Doorway
{

private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:

	enum
	{
		attending = 20,
		leavingWork,
		incinerator,
		beltConveyor
	};

	void Ins(SpriteCommon* spCom_);

	void Update();

	void Draw();

	void Delete();

	
	
private:
	SpriteCommon* spCom{};

	Sprite* attendingWorkSprite{};
	XMFLOAT3 attendingWorkPos{};
	
	Sprite* leavingWorkSprite{};
	XMFLOAT3 leavingWorkPos{};

	Sprite* incineratorSprite{};
	XMFLOAT3 incineratorPos{};


	Sprite* beltConveyorSprite[2]{};
	XMFLOAT3 beltConveyorPos[2]{};


};

