Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normals : NORMAL0;
    float3 dirTocamera : TEXCOORD1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 lightDir;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    //AMBIENT LIGHT
    float ka = 0.1;
    float3 ia = float3(1.0, 1.0, 1.0);

    float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
    float kd = 0.7;
    float3 id = float3(1.0, 1.0, 1.0);
    float amount_diffuse_light = max(0.0, dot(lightDir.xyz, input.normals));

    float3 diffuse_light = kd * amount_diffuse_light * id;

	//SPECULAR LIGHT
    float ks = 1.0;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflected_light = reflect(lightDir.xyz, input.normals);
    float shininess = 30.0;
    float amount_specular_light = pow(max(0.0, dot(reflected_light, input.dirTocamera)), shininess);

    float3 specular_light = ks * amount_specular_light * is;

    float3 final_light = ambient_light + diffuse_light + specular_light;

    return float4(final_light, 1.0);
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5);
}