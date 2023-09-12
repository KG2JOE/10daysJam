#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//�摜�̐�������̉���
#define TexWidth 52.0f
//�摜�̐�������̏c��
#define TexHeight 65.0f
//�ő包��
#define MaxSprite 10

class Score
{
private:
	//�\�����鐔���̉摜
	Sprite* sprites[MaxSprite];
	//���W
	XMFLOAT2 position;
	//�T�C�Y
	float size;
	//�����x
	float alpha;
	//���݂̃X�R�A
	int currentScore;
	//0�ŉE�l�ߕ\�����邩�ǂ���
	bool printZeroFlag;
	/// <summary>
	/// ���݂̃X�R�A�ɕ`���؂�ւ���
	/// </summary>
	void SetCurrentScore();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="spriteCommon">�X�v���C�g�R����</param>
	/// <param name="texNumber">�e�N�X�`���i���o�[</param>
	Score(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Score();
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
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT2 position)
	{
		this->position = position;
		for (int i = 0; i < MaxSprite; i++)
		{
			sprites[i]->SetPosition({ position.x + (MaxSprite - 1 - i) * TexWidth * size, position.y, 0.0f });
		}
	}
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
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
	/// 0�ŉE�l�ߕ\�����邩�ǂ����̐ݒ�
	/// </summary>
	/// <param name="flag">0�ŉE�l�ߕ\�����邩�ǂ���</param>
	void SetPrintZero(bool flag) { printZeroFlag = flag; }
	/// <summary>
	/// ���݂̃X�R�A�̐ݒ�
	/// </summary>
	/// <param name="score">���݂̃X�R�A</param>
	void SetScore(int score) { currentScore = score; }
	/// <summary>
	/// ���݂̃X�R�A�Ƀv���X����
	/// </summary>
	/// <param name="score">�v���X����X�R�A</param>
	void AddScore(int score) { currentScore += score; }
	/// <summary>
	/// ���݂̃X�R�A�̎擾
	/// </summary>
	/// <returns>���݂̃X�R�A</returns>
	int GetScore() { return currentScore; }
	/// <summary>
	/// �����x�̐ݒ�
	/// </summary>
	/// <param name="alpha">�����x</param>
	void SetAlpha(float alpha) { this->alpha = alpha; }
};