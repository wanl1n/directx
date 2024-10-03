struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 dpsmain(PS_INPUT input) : SV_TARGET
{
    float3 color1 = input.color.xyz;
    float3 color2 = input.color1.xyz;
    float alpha1 = input.color.w;
    float alpha2 = input.color1.w;
    
    float deltaTime = (float) ((sin((float) (m_time / (float) 5.0f)) + 1.0f) / 2.0f);
    
    //return float4(lerp(color1, color2, deltaTime), lerp(alpha1, alpha2, deltaTime));
    
    //return float4(lerp(color1, color2, (float) ((sin((float) (m_time / (float) 500.0f)) + 1.0f) / 2.0f)), 1.0f);
    return input.color;
}