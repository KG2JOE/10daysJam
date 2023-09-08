#pragma once
#include "Sprite.h"
#include "XMFLOAT_Helper.h"

//��ʉ��ɕ��ׂ�摜�̐�
#define WidthNum 16
//��ʏc�ɕ��ׂ�摜�̐�
#define HeightNum 9

class Fade
{
public:
	//�t�F�[�h�̏��
	enum FadeState
	{
		FADE, //�t�F�[�h�A�E�g�������
		FADEIN, //�t�F�[�h�C�����Ă���
		NONEFADE, //�t�F�[�h�C���������
		FADEOUT, //�t�F�[�h�A�E�g���Ă���
	};

private:
	//�t�F�[�h�Ɏg���摜
	Sprite* sprites[WidthNum][HeightNum];
	//���݂̃t�F�[�h�̏��
	FadeState fadeState;
	//�t�F�[�h����F
	XMFLOAT3 fadeColor;
	//�ėp�̃J�E���g
	int count;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="spriteCommon">�X�v���C�g�R����</param>
	/// <param name="texNumber">�e�N�X�`���i���o�[</param>
	Fade(SpriteCommon* spriteCommon, int texNumber);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Fade();
	/// <summary>
	/// �t�F�[�h�C�������Ԃɏ�����
	/// </summary>
	void SetFadeIn();
	/// <summary>
	/// �t�F�[�h�A�E�g�����Ԃɏ�����
	/// </summary>
	void SetFadeOut();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �t�F�[�h����F�̐ݒ�
	/// </summary>
	/// <param name="color">�t�F�[�h����F</param>
	void SetFadeColor(XMFLOAT3 color) { fadeColor = color; }
	/// <summary>
	/// �t�F�[�h�̏�Ԃ̎擾
	/// </summary>
	/// <returns>�t�F�[�h�̏��</returns>
	FadeState GetFadeState() { return fadeState; }
};