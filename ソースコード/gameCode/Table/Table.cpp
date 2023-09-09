#include "Table.h"

void Table::Ins(SpriteCommon* spCom_)
{
	assert(spCom_);

	spCom = spCom_;
	spCom->LoadTexture(15, L"Resources/sprite/tableBack.png");
	mapInsPos = {100,100};



	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			XMFLOAT3 temp = {((float)i* intervalX) + startPosX,((float)j* intervalY) + startPosY,0 };
			pos[i][j]=temp;

			table[i][j] = Sprite::Create(spCom, 15, { 0.5,0.5 }, false, false);

			table[i][j]->SetSize({80,60});
			table[i][j]->SetPosition(pos[i][j]);
			table[i][j]->SetTexLeftTop({ 0.0f,0.3f });
		}
	}

}

void Table::Update()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			table[i][j]->Update();
		}
	}
}

void Table::Draw()
{
	spCom->PreDraw();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			table[i][j]->Draw();
		}
	}
}

void Table::Delete()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			delete table[i][j];
		}
	}
}
