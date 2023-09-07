#pragma once

enum class Status
{
	NONE,			//初期値
	Stress,			//ストレス			フラグ
	Dead,			//死んでる			フラグ
	Grab,			//掴まれてる		フラグ
	AttendingWork,	//出勤				フラグ
	Work,			//仕事				フラグ
	LeavingWork,	//退勤				フラグ
	BeltConveyor,	//ベルトコンベア	フラグ

};

enum class MoveStatus
{
	Front,
	Back,
	Right,
	Left
};
