struct VS_INPUT
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normals : NORMAL0;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normals : NORMAL0;
    float3 dirToCamera : TEXCOORD1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 lightDir;
    float4 cameraPos;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
	
	//WORLD SPACE
    output.position = mul(input.position, m_world);
    output.dirToCamera = normalize(output.position.xyz - cameraPos.xyz);
    
	//VIEW SPACE
    output.position = mul(output.position, m_view);
	//SCREEN SPACE
    output.position = mul(output.position, m_proj);

    output.texcoord = input.texcoord;
    output.normals = input.normals;
    return output;
}
