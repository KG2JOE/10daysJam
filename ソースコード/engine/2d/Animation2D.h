#pragma once
#include <vector>
#include "Sprite.h"

class Animation2D 
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

	//�A�j���[�V�����Ɏg���摜
	Sprite* sprite = nullptr;
	//���摜���̃A�j���[�V�����摜�T�C�Y
	XMFLOAT2 texSize;
	//���ɂǂꂾ���A�Ԃ���Ă��邩
	int widthNum;

	//���W
	XMFLOAT2 position;
	//�A���J�[�|�C���g
	XMFLOAT2 anchorPoint;
	//�T�C�Y
	float size;
	//�A�j���[�V�����؂�ւ��܂ł̃t���[����
	int animationFlame;
	//�ėp�t���[���J�E���g
	int count;

	//�ǂ̘A�ԉ摜���ǂ̂悤�ɐ؂�ւ��Ă�����
	std::vector<int> spriteNumbers;
	//���ǂ̘A�ԉ摜��
	int spriteIndex;
	//�A�j���[�V���������[�v���邩�ǂ���
	bool loopFlag;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="spriteCommon">�X�v���C�g�R����</param>
	/// <param name="texNumber">�e�N�X�`���i���o�[</param>
	/// <param name="TexSize">�摜�T�C�Y</param>
	/// <param name="widthNum">�ǂꂾ�����ɘA�Ԃ���Ă��邩</param>
	Animation2D(SpriteCommon* spriteCommon, int texNumber, XMFLOAT2 TexSize, int widthNum);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Animation2D();
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
	void SetPosition(XMFLOAT2 position) { this->position = position; }
	/// <summary>
	/// �A���J�[�|�C���g�̐ݒ�
	/// </summary>
	/// <param name="anchorPoint">�A���J�[�|�C���g</param>
	void SetAnchorPoint(XMFLOAT2 anchorPoint) { this->anchorPoint = anchorPoint; }
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(float size) { this->size = size; }
	/// <summary>
	/// �A�j���[�V�����؂�ւ��܂ł̃t���[�����̐ݒ�
	/// </summary>
	/// <param name="flame">�A�j���[�V�����؂�ւ��܂ł̃t���[����</param>
	void SetAnimationFlame(int flame) { animationFlame = flame; }
	/// <summary>
	/// �A�j���[�V�����w��
	/// </summary>
	/// <param name="numbers"></param>
	void SetSpriteNumbers(std::vector<int> numbers) { spriteNumbers = numbers; spriteIndex = numbers[0]; }

	/// <summary>
	/// �A�j���[�V���������[�v���邩�ǂ����̐ݒ�
	/// </summary>
	/// <param name="flag">�A�j���[�V���������[�v���邩�ǂ���</param>
	void SetLoopFlag(bool flag) { loopFlag = flag; }
};