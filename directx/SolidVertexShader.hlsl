struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    // Vertex in world space coordinates.
    output.position = mul(input.position, m_world);
    // View Space coordinates.
    output.position = mul(output.position, m_view);
    // Screen Space coordinates.
    output.position = mul(output.position, m_proj);
    
    output.color = input.color;
    
    return output;
}