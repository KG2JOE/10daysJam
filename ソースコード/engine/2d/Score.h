#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//画像の数字一つ分の横幅
#define TexWidth 52.0f
//画像の数字一つ分の縦幅
#define TexHeight 65.0f
//最大桁数
#define MaxSprite 10

class Score
{
private:
	//表示する数字の画像
	Sprite* sprites[MaxSprite];
	//座標
	XMFLOAT2 position;
	//サイズ
	float size;
	//透明度
	float alpha;
	//現在のスコア
	int currentScore;
	//0で右詰め表示するかどうか
	bool printZeroFlag;
	/// <summary>
	/// 現在のスコアに描画を切り替える
	/// </summary>
	void SetCurrentScore();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="texNumber">テクスチャナンバー</param>
	Score(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT2 position)
	{
		this->position = position;
		for (int i = 0; i < MaxSprite; i++)
		{
			sprites[i]->SetPosition({ position.x + (MaxSprite - 1 - i) * TexWidth * size, position.y, 0.0f });
		}
	}
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(float size)
	{
		this->size = size;
		for (int i = 0; i < MaxSprite; i++)
		{
			sprites[i]->SetPosition({ position.x + i * TexWidth * size, position.y, 0.0f });
			sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
		}
	}
	/// <summary>
	/// 0で右詰め表示するかどうかの設定
	/// </summary>
	/// <param name="flag">0で右詰め表示するかどうか</param>
	void SetPrintZero(bool flag) { printZeroFlag = flag; }
	/// <summary>
	/// 現在のスコアの設定
	/// </summary>
	/// <param name="score">現在のスコア</param>
	void SetScore(int score) { currentScore = score; }
	/// <summary>
	/// 現在のスコアにプラスする
	/// </summary>
	/// <param name="score">プラスするスコア</param>
	void AddScore(int score) { currentScore += score; }
	/// <summary>
	/// 現在のスコアの取得
	/// </summary>
	/// <returns>現在のスコア</returns>
	int GetScore() { return currentScore; }
	/// <summary>
	/// 透明度の設定
	/// </summary>
	/// <param name="alpha">透明度</param>
	void SetAlpha(float alpha) { this->alpha = alpha; }
};