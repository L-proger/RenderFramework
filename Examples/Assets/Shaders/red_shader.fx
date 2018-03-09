struct VS_INPUT
{
	float4 vPosition : POSITION;
	float3 normal : NORMAL;
	float2 uv0 : UV0;
	float2 uv1 : UV1;
};

struct VS_OUTPUT {
	float4  vPosition : SV_POSITION;
	float3  normal : TEXCOORD0;
	float2  uv0 : TEXCOORD1;
	float2  uv1 : TEXCOORD2;
};

cbuffer TestBuffer : register(b3) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProjection;
}

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState MeshTextureSampler;

VS_OUTPUT main_vs(VS_INPUT v) {
	VS_OUTPUT o;

	float4x4 wvp = mul(mul(mProjection, mView), mWorld);

	o.vPosition = mul(wvp, float4(v.vPosition.xyz, 1));

	o.normal = mul((float3x3)mWorld, v.normal);
	o.uv0 = v.uv0;
	o.uv1 = v.uv1;
	return o;
}


float4 main_ps(VS_OUTPUT input) : SV_Target
{
	float3 sun = normalize(float3(-1,1,-1));
	float lit = dot(sun, input.normal);
	float3 diffuse = float3(1, 0, 0);

	return float4(diffuse * lit, 1);
}