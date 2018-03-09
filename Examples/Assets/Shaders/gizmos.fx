struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT {
	float4  position : SV_POSITION;
	float4  color : TEXCOORD0;
};

cbuffer TestBuffer : register(b3) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProjection;
	float alphaMul;
}

VS_OUTPUT main_vs(VS_INPUT v) {
	VS_OUTPUT o;

	float4x4 wvp = mul(mul(mProjection, mView), mWorld);
	o.position = mul(wvp, float4(v.position.xyz, 1));
	o.color = v.color;
	return o;
}

float4 main_ps(VS_OUTPUT input) : SV_Target{
	float4 color = input.color;
	color *= alphaMul;
	return color;
}