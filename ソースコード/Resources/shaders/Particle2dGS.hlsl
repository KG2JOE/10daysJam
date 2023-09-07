#include "Particle2d.hlsli"

// �l�p�`�̒��_��
static const uint vnum = 4;

// �Z���^�[����̃I�t�Z�b�g�e�[�u��
static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f, 0, 0),	// ����
	float4(-0.5f,+0.5f, 0, 0),	// ����
	float4(+0.5f,-0.5f, 0, 0),	// �E��
	float4(+0.5f,+0.5f, 0, 0)	// �E��
};

// UV�e�[�u���i���オ0,0�@�E����1,1�j
static const float2 uv_array[vnum] =
{
	float2(0, 1),	// ����
	float2(0, 0),	// ����
	float2(1, 1),	// �E��
	float2(1, 0) 	// �E��
};

// �_�̓��͂���A�l�p�`���o��
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	float4 offset = float4(0, 0, 0, 0);

	float PI = 3.1415926535;

	float4x4 rot = float4x4(
		cos(input[0].rotation / 180.0 * PI), -sin(input[0].rotation / 180.0 * PI), 0.0f, 0.0f,
		sin(input[0].rotation / 180.0 * PI), cos(input[0].rotation / 180.0 * PI), 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
		);

	for (uint i = 0; i < vnum; i++) {
		// ���S����̃I�t�Z�b�g���X�P�[�����O
		offset = offset_array[i] * input[0].scale;
		offset = mul(rot, offset);
		// ���S����̃I�t�Z�b�g���r���{�[�h��]�i���f�����W�j
		offset = mul(matBillboard, offset);
		// �I�t�Z�b�g�����炷�i���[���h���W�j
		element.svpos = input[0].pos + offset;
		// �r���[�v���W�F�N�V�����ϊ�
		element.svpos = mul(mat, element.svpos);
		element.uv = uv_array[i];
		element.color = input[0].color;
		output.Append(element);
	}
}