struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 gpsmain(PS_INPUT input) : SV_TARGET
{
    //return input.color;
    return float4(0.5f, 0.5f, 0.5f, 0.1f);
}