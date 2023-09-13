#pragma once

#include <vector>

#include "Sprite.h"
#include "Score.h"

#define RankTexWidth 92.0f
#define RankTexHeight 129.0f

class Result
{
public:
	enum ResultState
	{
		SCORE,
		RANK,
		COMMENT,
		END,
	};

	enum SpriteTexNumber
	{
		RESULTWORD = 40,
		RANKWORD,
		RANKTEX,
		COMMENTRANKF,
		COMMENTRANKE,
		COMMENTRANKD,
		COMMENTRANKC,
		COMMENTRANKB,
		COMMENTRANKA,
		COMMENTRANKS,
	};

private:
	SpriteCommon* spriteCommon = nullptr;
	Sprite* resultWordSprite = nullptr;
	Score* score = nullptr;
	Sprite* rankWordSprite = nullptr;
	Sprite* rankSprite = nullptr;
	Sprite* commentSprite = nullptr;
	ResultState resultState;
	std::vector<int> ranking;
	int rankingNum;
	int resultScore;
	bool endFlag;
	int count;

public:
	Result(SpriteCommon* spriteCommon, int texNumber);
	~Result();
	void Initialize(int scoreNum);
	void Update();
	void Draw();
	bool GetEndFlag() { return endFlag; }
	void SetRanking(std::vector<int> ranking) 
	{ 
		this->ranking = ranking; 
		rankingNum = ranking.size();
	}

private:
	void ScoreUpdate();
	void RankUpdate();
	void CommentUpdate();
};