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
	//�Q�[���V�[���̏��
	enum SceneState
	{
		TITLE, //�^�C�g��
		GUIDE, //�������
		GAMEPLAY, //�Q�[���v���C
		RESULT, //���U���g
	};
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
	using InsObj = InstancingObject3d;
public:

	//�G���W��������
	void EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//�S�̂̏�����
	void Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//�S�̍X�V
	void Update();

	//�S�̕`��
	void Draw();

	//�S�̍폜
	void Delete();

private://�G���W��
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

