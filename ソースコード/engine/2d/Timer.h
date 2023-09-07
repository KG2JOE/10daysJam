#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//�摜�̐�������̉���
#define TexWidth 34.0f 
//�摜�̐�������̏c��
#define TexHeight 64.0f

class Timer
{
private:
	//�\�����鐔���̉摜
	Sprite* sprites[4];
	//�\������R�����p�̉摜
	Sprite* colon = nullptr;
	//���W
	XMFLOAT2 position;
	//�T�C�Y
	float size;
	//�^�C�����~�b�g�̎���
	int limitTime;
	//���݂̎���
	int currentTime;
	//�ėp�̃J�E���g
	int count;
	//�^�C�����~�b�g�ɂȂ������ǂ���
	bool limitFlag;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="spriteCommon">�X�v���C�g�R����</param>
	/// <param name="texNumber">�e�N�X�`���i���o�[</param>
	Timer(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Timer();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// ���݂̎��Ԃɕ`���؂�ւ���
	/// </summary>
	void SetCurrentTime();
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
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
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
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
	/// �^�C�����~�b�g�̐ݒ�
	/// </summary>
	/// <param name="time">�^�C�����~�b�g</param>
	void SetLimitTime(int time) { limitTime = time; }
	/// <summary>
	/// �^�C�����~�b�g�ɂȂ������ǂ����̎擾
	/// </summary>
	/// <returns>�^�C�����~�b�g�ɂȂ������ǂ���</returns>
	bool GetLimitFlag() { return limitFlag; }
};