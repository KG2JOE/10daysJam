#include "Result.h"
#include "WinApp.h"
#include "XMFLOAT_Helper.h"
#include "Easing.h"

Result::Result(SpriteCommon* spriteCommon, int texNumber)
{
	this->spriteCommon = spriteCommon;
	spriteCommon->LoadTexture(SpriteTexNumber::RESULTWORD, L"Resources/sprite/resultWord.png");
	spriteCommon->LoadTexture(SpriteTexNumber::RANKWORD, L"Resources/sprite/rankWord.png");
	spriteCommon->LoadTexture(SpriteTexNumber::RANKTEX, L"Resources/sprite/rank.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKF, L"Resources/sprite/commentF.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKE, L"Resources/sprite/commentE.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKD, L"Resources/sprite/commentD.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKC, L"Resources/sprite/commentC.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKB, L"Resources/sprite/commentB.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKA, L"Resources/sprite/commentA.png");
	spriteCommon->LoadTexture(SpriteTexNumber::COMMENTRANKS, L"Resources/sprite/commentS.png");

	resultWordSprite = Sprite::Create(this->spriteCommon, RESULTWORD);
	rankWordSprite = Sprite::Create(this->spriteCommon, RANKWORD);
	rankSprite = Sprite::Create(this->spriteCommon, RANKTEX);
	score = new Score(this->spriteCommon, texNumber);

	rankingNum = 0;
	endFlag = false;
	count = 0;
}

Result::~Result()
{
	delete resultWordSprite;
	delete score;
	delete rankWordSprite;
	delete rankSprite;
	if (commentSprite != nullptr)
	{
		delete commentSprite;
	}
}

void Result::Initialize(int scoreNum)
{
	resultWordSprite->SetPosition({ WinApp::window_width * 1.5f, WinApp::window_height * 0.1f, 0.0f });
	resultWordSprite->Update();

	score->SetPosition({ WinApp::window_width * 0.2f, WinApp::window_height * 0.3f });
	score->SetAlpha(0.0f);
	score->SetScore(0);
	score->Initialize();

	rankWordSprite->SetPosition({ WinApp::window_width * 1.4f, WinApp::window_height * 0.8f, 0.0f });
	rankWordSprite->Update();

	int rank = 0;
	rankingNum = ranking.size();
	for (int i = 0; i < ranking.size(); i++)
	{
		rank = i;
		if (scoreNum < ranking[i])
		{
			break;
		}
		else if (i >= ranking.size() - 1)
		{
			rank++;
		}
	}

	rank = (rankingNum - rank);

	rankSprite->SetPosition({ WinApp::window_width * 0.6f, WinApp::window_height * 0.6f, 0.0f });
	rankSprite->SetTexLeftTop({ rank * RankTexWidth, 0.0f });
	rankSprite->SetTexSize({ RankTexWidth, RankTexHeight });
	rankSprite->SetSize({ RankTexWidth, RankTexHeight });
	rankSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	rankSprite->Update();

	if (rank == 0)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKS);
	else if (rank == 1)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKA);
	else if (rank == 2)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKB);
	else if (rank == 3)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKC);
	else if (rank == 4)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKD);
	else if (rank == 5)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKE);
	else if (rank == 6)
		commentSprite = Sprite::Create(spriteCommon, COMMENTRANKF);

	commentSprite->SetPosition({ WinApp::window_width * 1.8f, WinApp::window_height * 0.7f, 0.0f });
	commentSprite->Update();

	resultState = ResultState::SCORE;
	resultScore = scoreNum;
	endFlag = false;
	count = 0;
}

void Result::Update()
{
	switch (resultState)
	{
	case Result::SCORE:
		ScoreUpdate();
		break;
	case Result::RANK:
		RankUpdate();
		break;
	case Result::COMMENT:
		CommentUpdate();
		break;
	default:
		break;
	}
}

void Result::Draw()
{
	resultWordSprite->Draw();
	score->Draw();
	rankWordSprite->Draw();
	rankSprite->Draw();
	commentSprite->Draw();
}

void Result::ScoreUpdate()
{
	float e = Easing::OutQuart((float)min(count, 30), 30.0f);
	float width = e * WinApp::window_width;
	float posX = WinApp::window_width * 1.5f - width;
	resultWordSprite->SetPosition({ posX, WinApp::window_height * 0.1f, 0.0f });
	resultWordSprite->Update();

	if (count >= 30)
	{
		float e = Easing::OutQuart((float)min(count - 30, 60), 60.0f);
		score->AddScore(resultScore / 60.0f);
		score->SetAlpha(e);
		score->Update();
	}

	if (count >= 90)
	{
		resultWordSprite->SetPosition({ WinApp::window_width * 0.5f, WinApp::window_height * 0.1f, 0.0f });
		resultWordSprite->Update();
		score->SetScore(resultScore);
		score->SetAlpha(1.0f);
		score->Update();
		count = 0;
		resultState = ResultState::RANK;
		return;
	}

	count++;
}

void Result::RankUpdate()
{
	float e = Easing::OutQuart((float)min(count, 30), 30.0f);
	float width = e * WinApp::window_width;
	float posX = WinApp::window_width * 1.4f - width;
	rankWordSprite->SetPosition({ posX, WinApp::window_height * 0.5f, 0.0f });
	rankWordSprite->Update();

	if (count >= 30)
	{
		float e = Easing::OutQuart((float)min(count - 30, 30), 30.0f);
		rankSprite->SetSize({ RankTexWidth + (1.0f - e) * RankTexWidth * 2.0f,
			RankTexHeight + (1.0f - e) * RankTexHeight * 2.0f });
		rankSprite->SetColor({ 1.0f, 1.0f, 1.0f, e });
		rankSprite->SetRotation(e * 10.0f);
		rankSprite->Update();
	}

	if (count >= 60)
	{
		rankWordSprite->SetPosition({ WinApp::window_width * 0.4f, WinApp::window_height * 0.5f, 0.0f });
		rankWordSprite->Update();
		rankSprite->SetSize({ RankTexWidth, RankTexHeight });
		rankSprite->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		rankSprite->SetRotation(10.0f);
		rankSprite->Update();
		count = 0;
		resultState = ResultState::COMMENT;
		return;
	}

	count++;
}

void Result::CommentUpdate()
{
	float e = Easing::OutQuart((float)min(count, 30), 30.0f);
	float width = e * WinApp::window_width;
	float posX = WinApp::window_width * 1.8f - width;
	commentSprite->SetPosition({ posX, WinApp::window_height * 0.7f, 0.0f });
	commentSprite->SetRotation(-20.0f * e);
	commentSprite->Update();

	if (count >= 30)
	{
		commentSprite->SetPosition({ WinApp::window_width * 0.8f, WinApp::window_height * 0.7f, 0.0f });
		commentSprite->SetRotation(-20.0f);
		commentSprite->Update();
		count = 0;
		resultState = ResultState::END;
		endFlag = true;
		return;
	}

	count++;
}
