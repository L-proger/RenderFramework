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
	float3  worldPos : TEXCOORD3;
	float3  viewPos : TEXCOORD4;
};

cbuffer TestBuffer : register(b3) {
    float4x4 mWorld;
	float4x4 mView;
	float4x4 mProjection;
	float4 cameraWorldPos;
	float4 _DiffuseColor;
}

Texture2D diffuse : register(t0);
Texture2D tex2 : register(t1);
SamplerState MeshTextureSampler;



VS_OUTPUT main_vs(VS_INPUT v){
    VS_OUTPUT o;


	float4x4 wv = mul(mView, mWorld);
	float4x4 wvp = mul(mul(mProjection, mView), mWorld);
	
    o.vPosition = mul(wvp, float4(v.vPosition.xyz,1));

    o.normal = mul((float3x3)mWorld, v.normal);
	o.uv0 = v.uv0;
	o.uv1 = v.uv1;
	o.worldPos = mul((float3x3)mWorld, v.vPosition.xyz);
	o.viewPos = mul(wv, float4(v.vPosition.xyz, 1));
    return o;
}

#include "lighting/cook_torrance_term.inc"

float4 main_ps(VS_OUTPUT input) : SV_Target
{
	float3 ambient = float3(0.3f, 0.3f, 0.4f);

	float4 diffuseColor = _DiffuseColor * diffuse.Sample(MeshTextureSampler, input.uv0);
	float3 worldPos = input.worldPos;
	float3 camPos = cameraWorldPos.xyz;
	float3 viewDir = normalize(camPos - worldPos);
	float3 sun = normalize(float3(-1, 1, -1));

	float3 surfaceColor = cook_torrance(normalize(input.normal), viewDir, sun, 0.7f, 0.1f, diffuseColor.rgb, diffuseColor.rgb);
	
	return float4(surfaceColor + ambient * diffuseColor, 1);
}