#pragma once
#include "Sprite.h"
#include <forward_list>
#include <iostream>

class ParticleManager2d
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	SpriteCommon* spriteCommon_ = nullptr;

public: //構造体
	struct Particle2d {
		//座標
		XMFLOAT2 pos_ = { 0, 0 };
		//大きさ
		XMFLOAT2 size_ = { 1, 1 };
		//回転
		float rot_ = 0.0f;
		//速度ベクトル
		XMFLOAT2 velocity_ = { 0, 0 };
		//加速度
		XMFLOAT2 accel_ = { 0, 0 };
		//色
		XMFLOAT3 color_ = { 1, 1, 1 };
		//アルファ値
		float alpha_ = 1.0f;
		//初期パラメータ
		XMFLOAT3 start_Color_ = { 1, 1, 1 };
		XMFLOAT2 start_Size_ = { 1, 1 };
		float start_Rot_ = 0.0f;
		float start_Alpha_ = 1.0f;
		//最終パラメータ
		XMFLOAT3 end_Color_ = { 1, 1, 1 };
		XMFLOAT2 end_Size_ = { 0, 0 };
		float end_Rot_ = 0.0f;
		float end_Alpha_ = 0.0f;
		//現在フレーム
		int32_t nowFrame_;
		//最終フレーム
		int32_t endFrame_;
		//パーティクル画像
		std::unique_ptr<Sprite> particle_;
	};

public: //静的メンバ関数
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static ParticleManager2d* Create();
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<ParticleManager2d> UniquePtrCreate();
	/// <summary>
	/// パーティクル生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<Particle2d> ParticleCreate();

public: //メンバ関数
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル追加
	/// </summary>
	/// <param name="particle">パーティクル</param>
	void Add(int texNumber, int32_t life, XMFLOAT2 position, XMFLOAT2 velocity, XMFLOAT2 accel, XMFLOAT2 start_scale = { 1.0f, 1.0f }, XMFLOAT2 end_scale = { 1.0f, 1.0f }, XMFLOAT3 start_color = { 1.0f, 1.0f, 1.0f }, XMFLOAT3 end_color = { 0.0f, 0.0f, 0.0f }, float start_alpha = 1.0f, float end_alpha = 0.0f);

	void SetSpriteCommon(SpriteCommon* spriteCommon) { spriteCommon_ = spriteCommon; }

private: //メンバ変数
	//パーティクルリスト
	std::forward_list<Particle2d> particleList_;
};