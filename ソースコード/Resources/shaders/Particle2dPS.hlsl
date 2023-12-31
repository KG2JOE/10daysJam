#include "Particle2d.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(GSOutput input) : SV_TARGET
{
	float4 tex_color =  tex.Sample(smp, input.uv);
	return float4(tex_color.rgb * input.color.rgb, 0.5);
}