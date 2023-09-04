#pragma once
#include "BaseEnemy.h"
class BattleEnemy : public BaseEnemy
{
public:
	static std::unique_ptr<BattleEnemy> UniqueCreate(XMFLOAT3 pos_);//作成

	void Update() {};// 更新

	void Update(XMFLOAT3 pos);

	void Draw();//描画



protected:

	

	int atkTime = 200;

	bool atkFlag = 0;

	bool moveFlag = 0;
	
	bool moveType{};


};

