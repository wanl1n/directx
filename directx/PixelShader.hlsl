struct PS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}