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
		bg,
	};

	void Ins(SpriteCommon* spCom_);

	void Update();

	void DrawIncinerator();
	void Draw();

	void Delete();

	XMFLOAT3 GetAttendingWorkPos() { return attendingWorkPos; }
	XMFLOAT3 GetIncineratorPos() { return incineratorPos; }
	
	XMFLOAT3 GetDeadConveyorPos(int i) { return deadConveyorPos[i]; }
	XMFLOAT3 GetAliveConveyorPos(int i) { return aliveConveyorPos[i]; }
	
	
private:
	SpriteCommon* spCom{};

	XMFLOAT3 attendingWorkPos{};
	
	XMFLOAT3 leavingWorkPos{};

	Sprite* bgSprite{};


	Sprite* incineratorSprite{};
	XMFLOAT3 incineratorPos{};

	Sprite* deadConveyorSprite[6]{};
	XMFLOAT3 deadConveyorPos[6]{};

	Sprite* aliveConveyorSprite[5]{};
	XMFLOAT3 aliveConveyorPos[5]{};

	float distance_1 = 102.f;
	float distance_2 = 45.f;
};

