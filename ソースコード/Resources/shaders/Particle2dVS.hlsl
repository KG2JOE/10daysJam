#include "Particle2d.hlsli"

VSOutput main(float4 pos : POSITION, float4 color : COLOR, float scale : TEXCOORD, float rotation : ROTATION)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos = pos;
	output.color = color;
	output.scale = scale;
	output.rotation = rotation;
	return output;
}