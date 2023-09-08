#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//画面横に並べる画像の数
#define WidthNum 16
//画面縦に並べる画像の数
#define HeightNum 9

class Fade
{
public:
	//フェードの状態
	enum FadeState
	{
		FADE, //フェードアウトした状態
		FADEIN, //フェードインしてる状態
		NONEFADE, //フェードインした状態
		FADEOUT, //フェードアウトしてる状態
	};

private:
	//フェードに使う画像
	Sprite* sprites[WidthNum][HeightNum];
	//現在のフェードの状態
	FadeState fadeState;
	//フェードする色
	XMFLOAT3 fadeColor;
	//汎用のカウント
	int count;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="texNumber">テクスチャナンバー</param>
	Fade(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fade();
	/// <summary>
	/// フェードインする状態に初期化
	/// </summary>
	void SetFadeIn();
	/// <summary>
	/// フェードアウトする状態に初期化
	/// </summary>
	void SetFadeOut();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// フェードする色の設定
	/// </summary>
	/// <param name="color">フェードする色</param>
	void SetFadeColor(XMFLOAT3 color) { fadeColor = color; }
	/// <summary>
	/// フェードの状態の取得
	/// </summary>
	/// <returns>フェードの状態</returns>
	FadeState GetFadeState() { return fadeState; }
};