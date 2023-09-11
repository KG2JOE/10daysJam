#pragma once
#include <vector>
#include "Input.h"
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

class Guide
{
public:
	//��������̕\�����
	enum GuideState
	{
		DISPLAYIN, //�p�l������ʓ��ɓ����Ă�����
		DISPLAYVIEW, //�p�l�����\������Ă�����
		DISPLAYOUT, //�p�l������ʊO�ɏo�Ă������
	};

private:
	//�}�E�X���͎擾�p
	Input* input = nullptr;
	//��������̉摜
    std::vector<Sprite*> guideSprites;
	//�E���̉摜
	Sprite* rightAllowSprite = nullptr;
	//�����̉摜
	Sprite* leftAllowSprite = nullptr;
	//�X�^�[�g�{�^���̉摜
	Sprite* startSprite = nullptr;
	//��������̕\�����
	GuideState guideState;
	//��������̉摜����
	int maxSpriteNum;
	//���ݕ\������Ă���摜
	int currentSprite;
	//���ɕ\������\��̉摜
	int nextSprite;
	//����������I���������ǂ���
	bool endFlag;
	//�ėp�J�E���g
	int count;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="spriteCommon">�X�v���C�g�R����</param>
	/// <param name="guideTexNumbers">��������̃e�N�X�`���i���o�[</param>
	/// <param name="allowTexNumber">���̃e�N�X�`���i���o�[</param>
	/// <param name="startTexNumber">�X�^�[�g�{�^���̃e�N�X�`���i���o�[</param>
	Guide(SpriteCommon* spriteCommon, std::vector<int> guideTexNumbers, int allowTexNumber, int startTexNumber);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Guide();
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
	/// ���̓N���X�̎擾
	/// </summary>
	/// <param name="input"></param>
	void SetInput(Input* input) { this->input = input; }
	/// <summary>
	/// ����������I���������ǂ���
	/// </summary>
	/// <returns>����������I���������ǂ���</returns>
	bool GetEndFlag() { return endFlag; }

private:
	/// <summary>
	/// �p�l������ʓ��ɓ����Ă����Ԃ̏���
	/// </summary>
	void DisplayIn();
	/// <summary>
	/// �p�l�����\������Ă����Ԃ̏���
	/// </summary>
	void DisplayView();
	/// <summary>
	/// �p�l������ʊO�ɏo�Ă�����Ԃ̏���
	/// </summary>
	void DisplayOut();
	/// <summary>
	/// �E���̃{�^�������������ǂ���
	/// </summary>
	/// <returns>�E���̃{�^�������������ǂ���</returns>
	bool RightAllowPush();
	/// <summary>
	/// �����̃{�^�������������ǂ���
	/// </summary>
	/// <returns>�����̃{�^�������������ǂ���</returns>
	bool LeftAllowPush();
	/// <summary>
	/// �X�^�[�g�{�^�������������ǂ���
	/// </summary>
	/// <returns>�X�^�[�g�{�^�������������ǂ���</returns>
	bool StartPush();
};