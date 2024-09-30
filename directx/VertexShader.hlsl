struct VS_INPUT
{
    float4 position : POSITION;
    float4 position1 : POSITION1;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    unsigned int m_time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    output.position = input.position;
    //output.position = lerp(input.position, input.position1, (sin(m_angle) + 1.0f) / 2.0f);
    
    //// Vertex in world space coordinates.
    //output.position = mul(input.position, m_world);
    //// View Space coordinates.
    //output.position = mul(output.position, m_view);
    //// Screen Space coordinates.
    //output.position = mul(output.position, m_proj);
    
    output.color = input.color;
    
	return output;
}