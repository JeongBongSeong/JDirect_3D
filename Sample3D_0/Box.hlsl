struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION; // 3 -> 4
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

cbuffer cb0 : register(b0)
{
	//1개의 레지스터 (x,y,z,w)
	matrix g_matWorld : packoffset(c0);
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	float4 Color0 : packoffset(c12);
	float TimerX : packoffset(c13.x);

};


VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	//float fScaleX = cos(TimerX) * 0.5f + 0.5f;
	//float fScaleY = sin(TimerX) * 0.5f + 0.5f;
	float4 vLocal = float4(v.p.xyz, 1.0f);// float4(v.p.x, v.p.y, v.p.z, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;
	pOut.n = v.n;
	pOut.t = v.t;
	pOut.c = v.c;
	return pOut;
}

Texture2D	g_txColor : register(t0);
Texture2D	g_txMask : register(t1);
SamplerState	g_Sample : register(s0);

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 mask = g_txMask.Sample(g_Sample, input.t);
	float4 final = color;
	//final = final * input.c;
	final.a = 1.0f;// -mask.r;
	return final;
}

float4 PSAlphaBlend(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 final = color * input.c;
	final.a = color.a;
	return final;
}