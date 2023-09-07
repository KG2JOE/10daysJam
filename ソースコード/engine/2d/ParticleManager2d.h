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

public: //�\����
	struct Particle2d {
		//���W
		XMFLOAT2 pos_ = { 0, 0 };
		//�傫��
		XMFLOAT2 size_ = { 1, 1 };
		//��]
		float rot_ = 0.0f;
		//���x�x�N�g��
		XMFLOAT2 velocity_ = { 0, 0 };
		//�����x
		XMFLOAT2 accel_ = { 0, 0 };
		//�F
		XMFLOAT3 color_ = { 1, 1, 1 };
		//�A���t�@�l
		float alpha_ = 1.0f;
		//�����p�����[�^
		XMFLOAT3 start_Color_ = { 1, 1, 1 };
		XMFLOAT2 start_Size_ = { 1, 1 };
		float start_Rot_ = 0.0f;
		float start_Alpha_ = 1.0f;
		//�ŏI�p�����[�^
		XMFLOAT3 end_Color_ = { 1, 1, 1 };
		XMFLOAT2 end_Size_ = { 0, 0 };
		float end_Rot_ = 0.0f;
		float end_Alpha_ = 0.0f;
		//���݃t���[��
		int32_t nowFrame_;
		//�ŏI�t���[��
		int32_t endFrame_;
		//�p�[�e�B�N���摜
		std::unique_ptr<Sprite> particle_;
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ParticleManager2d* Create();
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<ParticleManager2d> UniquePtrCreate();
	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<Particle2d> ParticleCreate();

public: //�����o�֐�
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N���ǉ�
	/// </summary>
	/// <param name="particle">�p�[�e�B�N��</param>
	void Add(int texNumber, int32_t life, XMFLOAT2 position, XMFLOAT2 velocity, XMFLOAT2 accel, XMFLOAT2 start_scale = { 1.0f, 1.0f }, XMFLOAT2 end_scale = { 1.0f, 1.0f }, XMFLOAT3 start_color = { 1.0f, 1.0f, 1.0f }, XMFLOAT3 end_color = { 0.0f, 0.0f, 0.0f }, float start_alpha = 1.0f, float end_alpha = 0.0f);

	void SetSpriteCommon(SpriteCommon* spriteCommon) { spriteCommon_ = spriteCommon; }

private: //�����o�ϐ�
	//�p�[�e�B�N�����X�g
	std::forward_list<Particle2d> particleList_;
};