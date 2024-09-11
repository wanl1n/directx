float4 vsmain(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

float4 psmain(float4 pos : SV_POSITION) : SV_Target
{
    return float4(1.0f, 0.992f, 0.816f, 1.0f);
}