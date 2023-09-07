#include "Employee.h"
#include "collision.h"

void Employee::Ins(SpriteCommon* spCom_, Input* input_)
{
	assert(spCom_);
	assert(input_);
	spCom = spCom_;
	input = input_;
	
	spCom->LoadTexture(NONE, L"Resources/sprite/humanBack.png");
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employee_[i][j] = Sprite::Create(spCom, (UINT)Status::NONE, {0.5,0.5}, false, false);

		}
	}

	employee = Sprite::Create(spCom, (UINT)Status::NONE, { 0.5,0.5 }, false, false);
	//pos = { 0,0,0 };
	pos = { 500,450,0 };
	employee->SetPosition(pos);
	employee->SetSize({ 60,60 });
	//employee->SetSize({32,32});
	employee->Update();
	status = Work;
	moveStatus = Left;
	catchFlag = 0;

	table = new Table();
	table->Ins(spCom);
}

void Employee::Update()
{
	input->Update();

	mousePos.x = input->GetMousePoint().x;
	mousePos.y = input->GetMousePoint().y;

	switch (status)
	{
	case Employee::NONE:
		break;
	case Employee::Stress:
		break;
	case Employee::Dead:
		break;
	case Employee::Grab:
		pos.x = mousePos.x;
		pos.y = mousePos.y;
		employee->SetPosition(pos);
		CatchEmployeeGrab();

		break;
	case Employee::AttendingWork:
		//Move();
		if (statusFlag == Work)
		{
			employee = Sprite::Create(spCom, (UINT)Status::Work, { 0,0 }, false, false);
			employee->SetPosition(pos);
		}
		break;
	case Employee::Work:
		CatchEmployeeWork();

		if (statusFlag == Grab)
		{
			employee = Sprite::Create(spCom, (UINT)Status::NONE, { 0,0 }, false, false);
			employee->SetPosition(pos);
		}
		if (statusFlag == Dead)
		{
			employee = Sprite::Create(spCom, (UINT)Status::Dead, { 0,0 }, false, false);
			employee->SetPosition(pos);
		}
		break;
	case Employee::LeavingWork:


		break;
	case Employee::BeltConveyor:
		break;
	default:
		break;
	}
	table->Update();
	employee->Update();
}

void Employee::Draw()
{
	spCom->PreDraw();

	employee->Draw();
	table->Draw();

}

void Employee::Delete()
{

}

void Employee::Move()
{
	switch (moveStatus)
	{
	case Employee::Front:
		pos.y -= 3.f;
		break;
	case Employee::Back:
		pos.y += 3.f;
		break;
	case Employee::Right:
		pos.x += 3.f;

		break;
	case Employee::Left:
		pos.x -= 3.f;

		break;
	default:
		break;
	}
	employee->SetPosition(pos);

}

void Employee::CatchEmployeeWork()
{
	bool isHit = Collision::HitBox({ pos.x,pos.y }, 32, mousePos);

	if (isHit && input->TriggerMouseLeft())
	{
		status = Grab;
	}

}

void Employee::CatchEmployeeGrab()
{
	if (input->PushMouseLeft())
	{
		status = Grab;
	}
	else
	{
		status = Work;
	}
}