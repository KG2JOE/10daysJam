#pragma once


#include<vector>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "Model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugCamera.h"
#include "Collision.h"
#include"Audio.h"
#include"DebugText.h"
#include "ParticleManager2d.h"
#include "Timer.h"
#include "Score.h"
#include "Fade.h"
#include "Guide.h"

#include"InstancingObject3d.h"
using namespace DirectX;
class GameScene
{
public:
	//ゲームシーンの状態
	enum SceneState
	{
		TITLE, //タイトル
		GUIDE, //操作説明
		GAMEPLAY, //ゲームプレイ
		RESULT, //リザルト
	};
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
	using InsObj = InstancingObject3d;
public:

	//エンジン初期化
	void EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//全体の初期化
	void Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//全体更新
	void Update();

	//全体描画
	void Draw();

	//全体削除
	void Delete();

private://エンジン
	//WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;
	SpriteCommon* spriteCommon = new SpriteCommon();
	DebugText* debTxt = new DebugText;
	Audio* audio = Audio::GetInstance();
	
	int scene = 0;
	SceneState sceneState;

	//test
	Sprite* titleSprite = nullptr;
	Guide* guide = nullptr;

	ParticleManager2d* particleManager = nullptr;
	Timer* timer = nullptr;
	Score* score = nullptr;
	Fade* fade = nullptr;

	InsObj* insObj{};

	Model* test{};
};

