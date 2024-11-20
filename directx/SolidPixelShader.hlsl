Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    //AMBIENT LIGHT
    float ka = 0.1;
    float3 ia = float3(1.0, 1.0, 1.0);

    float3 ambient_light = ka * ia;
    
    return Texture.Sample(TextureSampler, input.texcoord) + input.color;
}