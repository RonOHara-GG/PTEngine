// Pixel shader input structure
struct PS_INPUT
{
    float4 Position   : POSITION;
};

// Pixel shader output structure
struct PS_OUTPUT
{
    float4 Color   : COLOR0;
};

PS_OUTPUT ps_main( in PS_INPUT In )
{
    PS_OUTPUT Out;

    Out.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);

    return Out;
}