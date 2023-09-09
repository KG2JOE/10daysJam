#include "Employee.h"
#include "collision.h"

void Employee::Ins(SpriteCommon* spCom_, Input* input_)
{
	assert(spCom_);
	assert(input_);
	spCom = spCom_;
	input = input_;
	
	spCom->LoadTexture(NONE, L"Resources/sprite/human.png");
	table = new Table();
	table->Ins(spCom);
	doorWay = new Doorway();
	doorWay->Ins(spCom);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j] = new EmployeeS();

			employeeS[i][j]->sprite_ = Sprite::Create(spCom, (UINT)Status::NONE, {0.5,0.5}, false, false);
			
			employeeS[i][j]->tablePos_ = table->GetPos(i, j);
			employeeS[i][j]->tablePos_.y -= 25.f;

			employeeS[i][j]->pos_ = doorWay->GetAttendingWorkPos();
			employeeS[i][j]->sprite_->SetPosition(employeeS[i][j]->pos_);
			employeeS[i][j]->sprite_->SetSize({ 60,60 });
			employeeS[i][j]->status_ = AttendingWork;
		}
	}

	employee = Sprite::Create(spCom, (UINT)Status::NONE, { 0.5,0.5 }, false, false);
	//pos = { 0,0,0 };
	pos = { 500,450,0 };
	employee->SetPosition(pos);
	employee->SetSize({ 60,60 });
	//employee->SetSize({32,32});
	employee->Update();
	status = AttendingWork;
	moveStatus = Left;
	catchFlag = 0;

	
}

void Employee::Update()
{
	input->Update();

	mousePos.x = input->GetMousePoint().x;
	mousePos.y = input->GetMousePoint().y;
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			EmployeeSUpdate(i,j);
			
		}
	}
	table->Update();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j]->sprite_->SetPosition(employeeS[i][j]->pos_);
			employeeS[i][j]->sprite_->Update();
		}
	}
	//employee->Update();
}

void Employee::EmployeeSUpdate(int i, int j)
{
	switch (employeeS[i][j]->status_)
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
		employeeS[i][j]->pos_.x = mousePos.x;
		employeeS[i][j]->pos_.y = mousePos.y;
		employeeS[i][j]->sprite_->SetPosition(employeeS[i][j]->pos_);
		employee->SetPosition(pos);
		CatchEmployeeGrab(i, j);

		break;
	case Employee::AttendingWork:
		if (employeeS[i][j]->tablePos_.y < employeeS[i][j]->pos_.y)
		{
			Move(i,j, Front);
			if (employeeS[i][j]->tablePos_.y >= employeeS[i][j]->pos_.y)
			{
				employeeS[i][j]->pos_.y = employeeS[i][j]->tablePos_.y;
			}
		}
		if (employeeS[i][j]->pos_.y == employeeS[i][j]->tablePos_.y)
		{
			Move(i, j,Right);
			if (employeeS[i][j]->tablePos_.x <= employeeS[i][j]->pos_.x)
			{
				employeeS[i][j]->pos_.x = employeeS[i][j]->tablePos_.x;
				employeeS[i][j]->status_ = Work;
			}
		}

		//Move();
		break;
	case Employee::Work:
		employeeS[i][j]->pos_ = table->GetPos(i, j);
		employeeS[i][j]->pos_.y -= 25.f;

		CatchEmployeeWork(i, j);

		break;
	case Employee::LeavingWork:


		break;
	case Employee::BeltConveyor:
		break;
	default:
		break;
	}
}

void Employee::Draw()
{
	spCom->PreDraw();

	//employee->Draw();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j]->sprite_->Draw();
		}
	}
	table->Draw();
	doorWay->Draw();
}

void Employee::Delete()
{

}

void Employee::Move(int i, int j, MoveStatus oveStatus)
{
	switch (oveStatus)
	{
	case Employee::Front:
		employeeS[i][j]->pos_.y -= 3.f;
		break;
	case Employee::Back:
		employeeS[i][j]->pos_.y += 3.f;
		break;
	case Employee::Right:
		employeeS[i][j]->pos_.x += 3.f;

		break;
	case Employee::Left:
		employeeS[i][j]->pos_.x -= 3.f;

		break;
	default:
		break;
	}
	employee->SetPosition(pos);

}

void Employee::CatchEmployeeWork(int i, int j)
{
	int count = 0;
	for (int k = 0; k < 5; k++)
	{
		for (int l = 0; l < 4; l++)
		{
			if (employeeS[k][l]->status_ != Grab)
			{
				count++;
			}
			else
			{

			}
		}
	}

	if (count == 20)
	{
		bool isHit = Collision::HitBox({ employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y }, 32, mousePos);

		if (isHit && input->TriggerMouseLeft())
		{
			employeeS[i][j]->status_ = Grab;
		}
		
	}

	
	

}

void Employee::CatchEmployeeGrab(int i, int j)
{
	if (input->PushMouseLeft())
	{
		employeeS[i][j]->status_ = employeeS[i][j]->status_;
	}
	else
	{
		employeeS[i][j]->status_ = Work;


	}
	if (input->PushMouseLeft())
	{
		status = Grab;
	}
	else
	{
		status = Work;
	}
}