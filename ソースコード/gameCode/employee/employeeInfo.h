#pragma once

enum class Status
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

enum class MoveStatus
{
	Front,
	Back,
	Right,
	Left
};
