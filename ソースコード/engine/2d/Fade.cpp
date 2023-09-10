#include "Fade.h"
#include "WinApp.h"

Fade::Fade(SpriteCommon* spriteCommon, int texNumber)
{
	for (int x = 0; x < WidthNum; x++)
	{
		for (int y = 0; y < HeightNum; y++)
		{
			sprites[x][y] = Sprite::Create(spriteCommon, texNumber);
		}
	}

	fadeState = FadeState::NONEFADE;
	fadeColor = { 0.0f, 0.0f, 0.0f};
	count = 0;

	for (int x = 0; x < WidthNum; x++)
	{
		for (int y = 0; y < HeightNum; y++)
		{
			sprites[x][y]->SetPosition({ (x + 0.5f) * (float)WinApp::window_width / WidthNum, (y + 0.5f) * (float)WinApp::window_height / HeightNum, 0.0f });
			sprites[x][y]->SetSize(XMFLOAT2{ (float)WinApp::window_width / WidthNum, (float)WinApp::window_height / HeightNum });
			sprites[x][y]->SetColor({fadeColor.x, fadeColor.y, fadeColor.z, 0.0f});
			sprites[x][y]->Update();
		}
	}
}

Fade::~Fade()
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			delete sprites[x][y];
		}
	}
}

void Fade::SetFadeState(FadeState state)
{
	switch (state)
	{
	case Fade::FADE:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetPosition({ (x + 0.5f) * (float)WinApp::window_width / WidthNum, (y + 0.5f) * (float)WinApp::window_height / HeightNum, 0.0f });
				sprites[x][y]->SetSize(XMFLOAT2{ (float)WinApp::window_width / WidthNum, (float)WinApp::window_height / HeightNum });
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 1.0f });
				sprites[x][y]->Update();
			}
		}

		fadeState = FadeState::FADE;

		break;
	case Fade::FADEIN:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 1.0f });
				sprites[x][y]->Update();
			}
		}

		fadeState = FadeState::FADEIN;

		break;
	case Fade::NONEFADE:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetPosition({ (x + 0.5f) * (float)WinApp::window_width / WidthNum, (y + 0.5f) * (float)WinApp::window_height / HeightNum, 0.0f });
				sprites[x][y]->SetSize(XMFLOAT2{ (float)WinApp::window_width / WidthNum, (float)WinApp::window_height / HeightNum });
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 0.0f });
				sprites[x][y]->Update();
			}
		}

		fadeState = FadeState::NONEFADE;

		break;
	case Fade::FADEOUT:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 0.0f });
				sprites[x][y]->Update();
			}
		}

		fadeState = FadeState::FADEOUT;

		break;
	default:
		break;
	}
}

void Fade::Update()
{
	switch (fadeState)
	{
	case Fade::FADE:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetPosition({ (x + 0.5f) * (float)WinApp::window_width / WidthNum, (y + 0.5f) * (float)WinApp::window_height / HeightNum, 0.0f });
				sprites[x][y]->SetSize(XMFLOAT2{ (float)WinApp::window_width / WidthNum, (float)WinApp::window_height / HeightNum });
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 1.0f });
				sprites[x][y]->Update();
			}
		}

		break;
	case Fade::FADEIN:

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				float alpha = 1.0f - (count - (x + y) * 5.0f) / 30.0f;
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, alpha });
				sprites[x][y]->Update();
			}
		}

		count++;

		if (count >= 30 + (WidthNum + HeightNum - 2) * 5)
		{
			count = 0;
			fadeState = FadeState::NONEFADE;
		}

		break;
	case Fade::NONEFADE:

		count = 0;

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				sprites[x][y]->SetPosition({ (x + 0.5f) * (float)WinApp::window_width / WidthNum, (y + 0.5f) * (float)WinApp::window_height / HeightNum, 0.0f });
				sprites[x][y]->SetSize(XMFLOAT2{ (float)WinApp::window_width / WidthNum, (float)WinApp::window_height / HeightNum });
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, 0.0f });
				sprites[x][y]->Update();
			}
		}

		break;
	case Fade::FADEOUT:

		for (int x = 0; x < WidthNum; x++)
		{
			for (int y = 0; y < HeightNum; y++)
			{
				float alpha = (count - (x + y) * 5.0f) / 30.0f;
				sprites[x][y]->SetColor({ fadeColor.x, fadeColor.y, fadeColor.z, alpha });
				sprites[x][y]->Update();
			}
		}

		count++;

		if (count >= 30 + (WidthNum + HeightNum - 2) * 5)
		{
			count = 0;
			fadeState = FadeState::FADE;
		}

		break;
	default:
		break;
	}
}

void Fade::Draw()
{
	for (int x = 0; x < WidthNum; x++)
	{
		for (int y = 0; y < HeightNum; y++)
		{
			if (sprites[x][y]->GetSize().x <= 0.0f || 
				sprites[x][y]->GetSize().y <= 0.0f ||
				sprites[x][y]->GetColor().w <= 0.0f)
			{
				continue;
			}
			sprites[x][y]->Draw();
		}
	}
}
