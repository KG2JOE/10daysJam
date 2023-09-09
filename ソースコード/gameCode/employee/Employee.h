#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"
#include"Input.h"
#include<DirectXMath.h>

#include"Table.h"

#include "Doorway.h"


class Employee
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;


public:
	enum Status
	{
		NONE,			//�����l
		Stress,			//�X�g���X			�t���O
		Dead,			//����ł�			�t���O
		Grab,			//�͂܂�Ă�		�t���O
		AttendingWork,	//�o��				�t���O
		Work,			//�d��				�t���O
		LeavingWork,	//�ދ�				�t���O
		BeltConveyor,	//�x���g�R���x�A	�t���O

	};

	enum MoveStatus
	{
		Front,
		Back,
		Right,
		Left
	};
private:

	struct EmployeeS
	{
		Sprite* sprite_;
		Status status_;
		XMFLOAT3 pos_{};
		XMFLOAT3 tablePos_{};

	};

public:

	void Ins(SpriteCommon* spCom , Input* input_);

	void Update();

	void EmployeeSUpdate(int i,int j);

	void Draw();

	void Delete();

	void Move(int i, int j,MoveStatus oveStatus);

	void CatchEmployeeWork(int i, int j);

	void CatchEmployeeGrab(int i, int j);

	int GetStatus() { return status; }
	
	bool GetCatchFlag() { return catchFlag; }

private:
	SpriteCommon* spCom{};
	Input* input{};
	Sprite* employee{};
	
	XMFLOAT3 pos;
	
	EmployeeS* employeeS[5][4];

	XMFLOAT2 mousePos{};

	bool catchFlag;


	Status status;
	Status statusFlag;

	int stress = 0;
	bool deadFlag = 0;
	MoveStatus moveStatus;


	Table* table{};

	Doorway* doorWay{};
};

