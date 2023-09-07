#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//画像の数字一つ分の横幅
#define TexWidth 34.0f 
//画像の数字一つ分の縦幅
#define TexHeight 64.0f

class Timer
{
private:
	//表示する数字の画像
	Sprite* sprites[4];
	//表示するコロン用の画像
	Sprite* colon = nullptr;
	//座標
	XMFLOAT2 position;
	//サイズ
	float size;
	//タイムリミットの時間
	int limitTime;
	//現在の時間
	int currentTime;
	//汎用のカウント
	int count;
	//タイムリミットになったかどうか
	bool limitFlag;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="texNumber">テクスチャナンバー</param>
	Timer(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Timer();
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
	/// 現在の時間に描画を切り替える
	/// </summary>
	void SetCurrentTime();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT2 position) 
	{ 
		this->position = position;
		for (int i = 0; i < 4; i++)
		{
			sprites[i]->SetPosition({ position.x + (i + i / 2) * TexWidth * size, position.y, 0.0f });
		}
		colon->SetPosition({ position.x + 2 * TexWidth * size, position.y, 0.0f });
	}
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(float size) 
	{ 
		this->size = size; 
		for (int i = 0; i < 4; i++)
		{
			sprites[i]->SetPosition({ position.x + (i + i / 2) * TexWidth * size, position.y, 0.0f });
			sprites[i]->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
		}
		colon->SetPosition({ position.x + 2 * TexWidth * size, position.y, 0.0f });
		colon->SetSize(XMFLOAT2{ TexWidth, TexHeight } *size);
	}
	/// <summary>
	/// タイムリミットの設定
	/// </summary>
	/// <param name="time">タイムリミット</param>
	void SetLimitTime(int time) { limitTime = time; }
	/// <summary>
	/// タイムリミットになったかどうかの取得
	/// </summary>
	/// <returns>タイムリミットになったかどうか</returns>
	bool GetLimitFlag() { return limitFlag; }
};