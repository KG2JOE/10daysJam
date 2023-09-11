#pragma once
#include <vector>
#include "Input.h"
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

class Guide
{
public:
	//操作説明の表示状態
	enum GuideState
	{
		DISPLAYIN, //パネルが画面内に入ってくる状態
		DISPLAYVIEW, //パネルが表示されている状態
		DISPLAYOUT, //パネルが画面外に出ていく状態
	};

private:
	//マウス入力取得用
	Input* input = nullptr;
	//操作説明の画像
    std::vector<Sprite*> guideSprites;
	//右矢印の画像
	Sprite* rightAllowSprite = nullptr;
	//左矢印の画像
	Sprite* leftAllowSprite = nullptr;
	//スタートボタンの画像
	Sprite* startSprite = nullptr;
	//操作説明の表示状態
	GuideState guideState;
	//操作説明の画像枚数
	int maxSpriteNum;
	//現在表示されている画像
	int currentSprite;
	//次に表示する予定の画像
	int nextSprite;
	//操作説明が終了したかどうか
	bool endFlag;
	//汎用カウント
	int count;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="guideTexNumbers">操作説明のテクスチャナンバー</param>
	/// <param name="allowTexNumber">矢印のテクスチャナンバー</param>
	/// <param name="startTexNumber">スタートボタンのテクスチャナンバー</param>
	Guide(SpriteCommon* spriteCommon, std::vector<int> guideTexNumbers, int allowTexNumber, int startTexNumber);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Guide();
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
	/// 入力クラスの取得
	/// </summary>
	/// <param name="input"></param>
	void SetInput(Input* input) { this->input = input; }
	/// <summary>
	/// 操作説明が終了したかどうか
	/// </summary>
	/// <returns>操作説明が終了したかどうか</returns>
	bool GetEndFlag() { return endFlag; }

private:
	/// <summary>
	/// パネルが画面内に入ってくる状態の処理
	/// </summary>
	void DisplayIn();
	/// <summary>
	/// パネルが表示されている状態の処理
	/// </summary>
	void DisplayView();
	/// <summary>
	/// パネルが画面外に出ていく状態の処理
	/// </summary>
	void DisplayOut();
	/// <summary>
	/// 右矢印のボタンを押したかどうか
	/// </summary>
	/// <returns>右矢印のボタンを押したかどうか</returns>
	bool RightAllowPush();
	/// <summary>
	/// 左矢印のボタンを押したかどうか
	/// </summary>
	/// <returns>左矢印のボタンを押したかどうか</returns>
	bool LeftAllowPush();
	/// <summary>
	/// スタートボタンを押したかどうか
	/// </summary>
	/// <returns>スタートボタンを押したかどうか</returns>
	bool StartPush();
};