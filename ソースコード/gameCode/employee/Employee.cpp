#include "Employee.h"
#include "collision.h"
#include"RandCreate.h"
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
			if (i == 0 && j == 0)
			{
				employeeS[i][j]->status_ = AttendingWork;

			}
			else
			{
				employeeS[i][j]->status_ = LeavingWork;
				employeeS[i][j]->time += (i * 10 + j * 20);
			}
		}
	}

	resetTime = employeeS[0][0]->time;

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

	mousePos.x = (float)input->GetMousePoint().x;
	mousePos.y = (float)input->GetMousePoint().y;
	
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
		ReturnEmployee(i, j);
		break;
	case Employee::Stress:
		break;
	case Employee::Incinerator:
		employeeS[i][j]->status_ = NONE;

		break;
	case Employee::Dead:
		CatchEmployeeWork(i, j);
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
		StressMove(i, j);
		CatchEmployeeWork(i, j);

		break;
	case Employee::LeavingWork:
		ReturnEmployee(i, j);
		break;
	case Employee::BeltConveyor:
		
		if (employeeS[i][j]->aliveFlag)
		{
			Move(i,j,Right);
			if (employeeS[i][j]->pos_.x > 1300)
			{
				employeeS[i][j]->status_ = LeavingWork;
			}
		}
		else
		{
			if (employeeS[i][j]->pos_.x< doorWay->GetDeadConveyorPos(2).x)
			{
				Move(i, j, Right);
				if (employeeS[i][j]->pos_.x >= doorWay->GetDeadConveyorPos(2).x)
				{
					employeeS[i][j]->pos_.x = doorWay->GetDeadConveyorPos(2).x;

				}
			}
			else if (employeeS[i][j]->pos_.x == doorWay->GetDeadConveyorPos(2).x)
			{
				employeeS[i][j]->pos_.x = doorWay->GetDeadConveyorPos(2).x;
				Move(i, j, Front);
				if (employeeS[i][j]->pos_.y < doorWay->GetIncineratorPos().y)
				{
					employeeS[i][j]->time = resetTime * 2;
					employeeS[i][j]->status_ = Incinerator;

				}

			}
		}

		CatchEmployeeWork(i, j);

		break;
	default:
		break;
	}
}

void Employee::Draw()
{
	spCom->PreDraw();
	doorWay->Draw();

	//employee->Draw();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j]->sprite_->Draw();
		}
	}
	table->Draw();
	doorWay->DrawIncinerator();
}

void Employee::Delete()
{

}

void Employee::ReturnEmployee(int i, int j)
{
	employeeS[i][j]->time--;
	if (employeeS[i][j]->time < 0)
	{
		employeeS[i][j]->time = resetTime;
		employeeS[i][j]->pos_ = doorWay->GetAttendingWorkPos();
		employeeS[i][j]->sprite_ = Sprite::Create(spCom, (UINT)Status::NONE, { 0.5,0.5 }, false, false);
		employeeS[i][j]->sprite_->SetSize({ 60,60 });
		employeeS[i][j]->addstress = 1;

		employeeS[i][j]->addMove = RndCreate::sGetRandInt(3, 7);

		employeeS[i][j]->stressValue = RndCreate::sGetRandInt(0,20);
		employeeS[i][j]->maxStress = RndCreate::sGetRandInt(300, 400);

		employeeS[i][j]->status_ = AttendingWork;

	}
}

void Employee::Move(int i, int j, MoveStatus oveStatus)
{
	switch (oveStatus)
	{
		
	case Employee::Front:
		employeeS[i][j]->pos_.y -= employeeS[i][j]->addMove;
		break;
	case Employee::Back:
		employeeS[i][j]->pos_.y += employeeS[i][j]->addMove;
		break;
	case Employee::Right:
		employeeS[i][j]->pos_.x += employeeS[i][j]->addMove;

		break;
	case Employee::Left:
		employeeS[i][j]->pos_.x -= employeeS[i][j]->addMove;

		break;
	default:
		break;
	}
	employee->SetPosition(pos);

}

void Employee::StressMove(int i, int j)
{
	
	if (employeeS[i][j]->stressValue < employeeS[i][j]->maxStress)
	{
		employeeS[i][j]->stressValue += employeeS[i][j]->addstress;
	}
	else
	{
		employeeS[i][j]->sprite_ = Sprite::Create(spCom,20, { 0.5,0.5 }, false, false);
		employeeS[i][j]->status_ = Dead;
	}

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
		if (employeeS[i][j]->stressValue >= employeeS[i][j]->maxStress)
		{
			bool isHit = false;
			for (int k = 0; k < 6; k++)
			{
				XMFLOAT2 temp_1 = { doorWay->GetDeadConveyorPos(k).x,doorWay->GetDeadConveyorPos(k).y };
				XMFLOAT2 temp_2 = { employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y };
				isHit = Collision::HitBox(temp_1, 48, temp_2);
				if (isHit)
				{
					employeeS[i][j]->status_ = BeltConveyor;
					employeeS[i][j]->aliveFlag = false;
					break;
				}
				else
				{
					employeeS[i][j]->status_ = Work;
				}
			}
		}
		else
		{
			bool isHit = false;
			for (int k = 0; k < 6; k++)
			{
				XMFLOAT2 temp_1 = { doorWay->GetDeadConveyorPos(k).x,doorWay->GetDeadConveyorPos(k).y };
				XMFLOAT2 temp_2 = { employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y };
				isHit = Collision::HitBox(temp_1, 48, temp_2);
				if (isHit)
				{
					employeeS[i][j]->status_ = BeltConveyor;
					employeeS[i][j]->aliveFlag = false;
					break;
				}

			}
			for (int k = 0; k < 5; k++)
			{
				if (isHit)
				{
					break;
				}
				else
				{
					XMFLOAT2 temp_1 = { doorWay->GetAliveConveyorPos(k).x,doorWay->GetAliveConveyorPos(k).y };
					XMFLOAT2 temp_2 = { employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y };
					isHit = Collision::HitBox(temp_1, 48, temp_2);
					if (isHit)
					{
						employeeS[i][j]->status_ = BeltConveyor;
						employeeS[i][j]->aliveFlag = true;

						break;
					}
					else
					{
						employeeS[i][j]->status_ = Work;
						employeeS[i][j]->aliveFlag = true;

					}
				}

			}
		}
		
		
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