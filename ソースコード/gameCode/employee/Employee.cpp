#include "Employee.h"
#include "collision.h"
#include"RandCreate.h"
#include "XMFLOAT_Helper.h"
void Employee::Ins(SpriteCommon* spCom_, Input* input_)
{
	assert(spCom_);
	assert(input_);
	spCom = spCom_;
	input = input_;

	spCom->LoadTexture(AnimationFront, L"Resources/sprite/humanWalk.png");
	spCom->LoadTexture(AnimationBack, L"Resources/sprite/humanWalkBack.png");
	spCom->LoadTexture(AnimationRight, L"Resources/sprite/humanWalkRight.png");
	spCom->LoadTexture(AnimationLeft, L"Resources/sprite/humanWalkLeft.png");
	spCom->LoadTexture(AnimationLiftMove, L"Resources/sprite/humanLiftMove.png");
	spCom->LoadTexture(SpriteFront, L"Resources/sprite/human.png");
	spCom->LoadTexture(SpriteDead, L"Resources/sprite/deadBody.png");
	spCom->LoadTexture(SpriteStressUI, L"Resources/sprite/stressUI.png");
	spCom->LoadTexture(SpriteStressBar, L"Resources/sprite/stressBar.png");
	//spCom->LoadTexture(NONE, L"Resources/sprite/human.png");
	table = new Table();
	table->Ins(spCom);
	doorWay = new Doorway();
	doorWay->Ins(spCom);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j] = new EmployeeS();

			AnimationInitialize(i, j, AnimationBack);
			employeeS[i][j]->stressBar_1 = Sprite::Create(spCom, (UINT)SpriteStatus::SpriteStressBar, { 0.0,0.0 }, false, false);
			employeeS[i][j]->stressBar_2 = Sprite::Create(spCom, (UINT)SpriteStatus::SpriteStressUI, { 0.5,0.5 }, false, false);




			employeeS[i][j]->tablePos_ = table->GetPos(i, j);
			employeeS[i][j]->tablePos_.y -= 25.f;

			employeeS[i][j]->pos_ = doorWay->GetAttendingWorkPos();
			employeeS[i][j]->animationSprite->SetPosition({ employeeS[i][j]->pos_.x, employeeS[i][j]->pos_.y });
			employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
			if (i == 0 && j == 0)
			{
				employeeS[i][j]->status_ = AttendingWork;

			}
			else
			{
				employeeS[i][j]->status_ = LeavingWork;
				employeeS[i][j]->time += (i * 60 + j * 30);
			}
			employeeS[i][j]->animationSprite->Update();
			XMFLOAT3 temp = { employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y,employeeS[i][j]->pos_.z };

			employeeS[i][j]->stressBar_1->SetPosition(temp - XMFLOAT3{ 31.0f, 6.5f, 0.0f });
			employeeS[i][j]->stressBar_2->SetPosition(temp);
			employeeS[i][j]->stressBar_1->Update();
			employeeS[i][j]->stressBar_2->Update();
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
	nowEmployeeCount = 0;
	maxEmployeeCount = 5;
	Score = 1000;
}

void Employee::Update()
{
	if (input->PushKey(DIK_P))
	{
		Score = -1000;
	}
	mousePos.x = (float)input->GetMousePoint().x;
	mousePos.y = (float)input->GetMousePoint().y;

	if (playTime == 93)
	{
		maxEmployeeCount = 8;
	}
	else if (playTime == 58)
	{
		maxEmployeeCount = 13;
	}
	else if (playTime == 24)
	{
		maxEmployeeCount = 20;
	}
	nowEmployeeCount = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (nowEmployeeCount < maxEmployeeCount)
			{
				EmployeeSUpdate(i, j);
				nowEmployeeCount++;
			}

		}
	}
	table->Update();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			employeeS[i][j]->animationSprite->SetPosition({ employeeS[i][j]->pos_.x, employeeS[i][j]->pos_.y });
			employeeS[i][j]->animationSprite->Update();

			XMFLOAT3 temp = { employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y - 40.f,employeeS[i][j]->pos_.z };
			employeeS[i][j]->stressBar_1->SetPosition(temp - XMFLOAT3{ 31.0f, 6.5f, 0.0f });
			employeeS[i][j]->stressBar_2->SetPosition(temp);
			float size = (float)employeeS[i][j]->stressValue / employeeS[i][j]->maxStress * 62.0f;
			employeeS[i][j]->stressBar_1->SetSize({ size, 13.0f });
			employeeS[i][j]->stressBar_1->Update();
			employeeS[i][j]->stressBar_2->Update();
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
		Score = Score - 1000;
		if (Score <= 0)
		{
			Score = 0;
		}
		employeeS[i][j]->status_ = NONE;
		break;
	case Employee::Dead:
		Score -= 10;
		CatchEmployeeWork(i, j);
		break;
	case Employee::Grab:
		pos.x = mousePos.x;
		pos.y = mousePos.y;
		employeeS[i][j]->pos_.x = mousePos.x;
		employeeS[i][j]->pos_.y = mousePos.y;
		employeeS[i][j]->animationSprite->SetPosition({ employeeS[i][j]->pos_.x, employeeS[i][j]->pos_.y });
		employee->SetPosition(pos);
		CatchEmployeeGrab(i, j);

		break;
	case Employee::AttendingWork:
		if (employeeS[i][j]->tablePos_.y < employeeS[i][j]->pos_.y)
		{
			Move(i, j, Front);
			if (employeeS[i][j]->tablePos_.y >= employeeS[i][j]->pos_.y)
			{

				employeeS[i][j]->pos_.y = employeeS[i][j]->tablePos_.y;
				AnimationInitialize(i, j, AnimationRight);
				employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });

			}
		}
		if (employeeS[i][j]->pos_.y == employeeS[i][j]->tablePos_.y)
		{
			Move(i, j, Right);
			if (employeeS[i][j]->tablePos_.x <= employeeS[i][j]->pos_.x)
			{
				employeeS[i][j]->pos_.x = employeeS[i][j]->tablePos_.x;

				if (employeeS[i][j]->addMove == 3)
				{
					employeeS[i][j]->stressTime = 3;
					employeeS[i][j]->oldStressTime = employeeS[i][j]->stressTime;
				}
				else if (employeeS[i][j]->addMove == 4)
				{
					employeeS[i][j]->stressTime = 3;
					employeeS[i][j]->oldStressTime = employeeS[i][j]->stressTime;
				}
				else if (employeeS[i][j]->addMove == 5)
				{
					employeeS[i][j]->stressTime = 2;
					employeeS[i][j]->oldStressTime = employeeS[i][j]->stressTime;
				}
				else if (employeeS[i][j]->addMove == 6)
				{
					employeeS[i][j]->stressTime = 1;
					employeeS[i][j]->oldStressTime = employeeS[i][j]->stressTime;
				}
				else if (employeeS[i][j]->addMove == 7)
				{
					employeeS[i][j]->stressTime = 0;
					employeeS[i][j]->oldStressTime = employeeS[i][j]->stressTime;
				}




				employeeS[i][j]->status_ = Work;
				AnimationInitialize(i, j, AnimationFront);
				employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
			}
		}

		//Move();
		break;
	case Employee::Work:
		employeeS[i][j]->pos_ = table->GetPos(i, j);
		employeeS[i][j]->pos_.y -= 25.f;

		AnimationInitialize(i, j, SpriteFront, 1, false, { 0 });
		employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });

		StressMove(i, j);
		CatchEmployeeWork(i, j);

		break;
	case Employee::LeavingWork:
		ReturnEmployee(i, j);
		break;
	case Employee::BeltConveyor:

		if (employeeS[i][j]->aliveFlag)
		{
			Move(i, j, Right);
			if (employeeS[i][j]->pos_.x > 1300)
			{
				employeeS[i][j]->status_ = LeavingWork;
			}
		}
		else
		{
			if (employeeS[i][j]->pos_.x < doorWay->GetDeadConveyorPos(2).x)
			{
				Move(i, j, Right);
				if (employeeS[i][j]->pos_.x >= doorWay->GetDeadConveyorPos(2).x)
				{
					employeeS[i][j]->pos_.x = doorWay->GetDeadConveyorPos(2).x;

				}
			}
			else if (employeeS[i][j]->pos_.x >= doorWay->GetDeadConveyorPos(2).x)
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
			if (employeeS[i][j]->status_ != LeavingWork)
			{
				employeeS[i][j]->animationSprite->Draw();
				employeeS[i][j]->stressBar_1->Draw();
				employeeS[i][j]->stressBar_2->Draw();
			}

		}
	}
	table->Draw();
	doorWay->DrawIncinerator();
}

void Employee::Delete()
{

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			
			delete employeeS[i][j]->animationSprite;
			delete employeeS[i][j]->stressBar_1;
			delete employeeS[i][j]->stressBar_2;
			delete employeeS[i][j];
		}
	}
	table->Delete();
	doorWay->Delete();

	delete table;
	delete doorWay;
}

void Employee::ReturnEmployee(int i, int j)
{
	employeeS[i][j]->time--;
	if (employeeS[i][j]->time < 0)
	{
		employeeS[i][j]->time = resetTime;
		employeeS[i][j]->pos_ = doorWay->GetAttendingWorkPos();
		AnimationInitialize(i, j, AnimationBack);
		employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
		employeeS[i][j]->addstress = 1;

		employeeS[i][j]->addMove = RndCreate::sGetRandInt(3, 7);


		employeeS[i][j]->stressValue = RndCreate::sGetRandInt(0, 20);
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
		if (employeeS[i][j]->stressTime > 0)
		{
			employeeS[i][j]->stressTime--;
		}
		else
		{

			employeeS[i][j]->stressValue += employeeS[i][j]->addstress;
			employeeS[i][j]->stressTime = employeeS[i][j]->oldStressTime;
		}
		Score++;
	}
	else
	{
		AnimationInitialize(i, j, SpriteDead, 1, false, { 0 });
		employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });

		employeeS[i][j]->addMove = 3.f;
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
		bool isHit = Collision::HitBox({ employeeS[i][j]->pos_.x,employeeS[i][j]->pos_.y }, 32, mousePos, 10);

		if (isHit && input->TriggerMouseLeft())
		{
			if (!(employeeS[i][j]->stressValue >= employeeS[i][j]->maxStress))
			{
				AnimationInitialize(i, j, AnimationLiftMove);
				employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
			}
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
					employeeS[i][j]->addMove = 3.f;
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
					AnimationInitialize(i, j, SpriteFront, 1, false, { 0 });
					employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
					employeeS[i][j]->addMove = 3.f;
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
						AnimationInitialize(i, j, SpriteFront, 1, false, { 0 });
						employeeS[i][j]->animationSprite->SetSize({ 60.0f, 60.0f });
						employeeS[i][j]->addMove = 3.f;
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

void Employee::AnimationInitialize(int i, int j, int texNumber, int texNum, bool flag, std::vector<int> numbers)
{
	if (employeeS[i][j]->animationSprite != nullptr)
	{
		delete employeeS[i][j]->animationSprite;
		employeeS[i][j]->animationSprite = nullptr;
	}
	employeeS[i][j]->animationSprite = new Animation2D(spCom, texNumber, { 48.0f, 48.0f }, 2);
	employeeS[i][j]->animationSprite->SetAnchorPoint({ 0.5f, 0.5f });
	employeeS[i][j]->animationSprite->SetAnimationFlame(15.0f);
	employeeS[i][j]->animationSprite->SetLoopFlag(true);
	employeeS[i][j]->animationSprite->SetSpriteNumbers({ 0,1 });
}
