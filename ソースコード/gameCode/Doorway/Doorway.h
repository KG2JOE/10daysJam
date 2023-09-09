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
		incinerator = 20,
		beltConveyor_1,
		beltConveyor_2,

	};

	void Ins(SpriteCommon* spCom_);

	void Update();

	void Draw();

	void Delete();

	XMFLOAT3 GetAttendingWorkPos() { return attendingWorkPos; }
	
	
private:
	SpriteCommon* spCom{};

	XMFLOAT3 attendingWorkPos{};
	
	XMFLOAT3 leavingWorkPos{};


	Sprite* incineratorSprite{};
	XMFLOAT3 incineratorPos{};

	Sprite* beltConveyorSprite[3]{};
	XMFLOAT3 beltConveyorPos[3]{};



};

