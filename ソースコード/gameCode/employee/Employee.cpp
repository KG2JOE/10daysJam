#include "Employee.h"
#include "collision.h"

void Employee::Ins(SpriteCommon* spCom_, Input* input_)
{
	assert(spCom_);
	assert(input_);
	spCom = spCom_;
	input = input_;

	//spCom->LoadTexture(NONE, L"Resources/sprite/humanBack.png");
	spCom->LoadTexture(NONE, L"Resources/sprite/bg(2).png");
	/*spCom->LoadTexture(Stress, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(Dead, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(Grab, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(AttendingWork, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(Work, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(LeavingWork, L"Resources/sprite/coraRe.png");
	spCom->LoadTexture(BeltConveyor, L"Resources/sprite/coraRe.png");*/

	employee = Sprite::Create(spCom, (UINT)Status::NONE, { 0,0 }, false, false);
	pos = { 0,0,0 };
	//pos = { 500,450,0 };
	employee->SetPosition(pos);
	//employee->SetSize({32,32});
	employee->Update();
	status = AttendingWork;
	moveStatus = Left;
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
		employee->SetPosition({ mousePos.x,mousePos.y,0 });
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
		if (statusFlag == Grab)
		{
			employee = Sprite::Create(spCom, (UINT)Status::Grab, { 0,0 }, false, false);
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
	employee->Update();
}

void Employee::Draw()
{
	spCom->PreDraw();

	employee->Draw();
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

void Employee::CatchEmployee()
{
	if (catchFlag == true)
	{
		bool isHit = Collision::HitBox({pos.x,pos.y}, 32, mousePos);

		if (isHit && input->PushMouseLeft())
		{
			catchFlag == true;
			status = Grab;
		}
	}

}