#pragma once
#include <vector>
#include "Sprite.h"

class Animation2D 
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

	//アニメーションに使う画像
	Sprite* sprite = nullptr;
	//元画像内のアニメーション画像サイズ
	XMFLOAT2 texSize;
	//横にどれだけ連番されているか
	int widthNum;

	//座標
	XMFLOAT2 position;
	//アンカーポイント
	XMFLOAT2 anchorPoint;
	//サイズ
	float size;
	//アニメーション切り替えまでのフレーム数
	int animationFlame;
	//汎用フレームカウント
	int count;

	//どの連番画像をどのように切り替えていくか
	std::vector<int> spriteNumbers;
	//今どの連番画像か
	int spriteIndex;
	//アニメーションがループするかどうか
	bool loopFlag;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="texNumber">テクスチャナンバー</param>
	/// <param name="TexSize">画像サイズ</param>
	/// <param name="widthNum">どれだけ横に連番されているか</param>
	Animation2D(SpriteCommon* spriteCommon, int texNumber, XMFLOAT2 TexSize, int widthNum);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Animation2D();
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
	void SetPosition(XMFLOAT2 position) { this->position = position; }
	/// <summary>
	/// アンカーポイントの設定
	/// </summary>
	/// <param name="anchorPoint">アンカーポイント</param>
	void SetAnchorPoint(XMFLOAT2 anchorPoint) { this->anchorPoint = anchorPoint; }
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(float size) { this->size = size; }
	/// <summary>
	/// アニメーション切り替えまでのフレーム数の設定
	/// </summary>
	/// <param name="flame">アニメーション切り替えまでのフレーム数</param>
	void SetAnimationFlame(int flame) { animationFlame = flame; }
	/// <summary>
	/// アニメーション指示
	/// </summary>
	/// <param name="numbers"></param>
	void SetSpriteNumbers(std::vector<int> numbers) { spriteNumbers = numbers; spriteIndex = numbers[0]; }

	/// <summary>
	/// アニメーションがループするかどうかの設定
	/// </summary>
	/// <param name="flag">アニメーションがループするかどうか</param>
	void SetLoopFlag(bool flag) { loopFlag = flag; }
};