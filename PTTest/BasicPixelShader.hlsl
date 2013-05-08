// Pixel shader input structure
struct PS_INPUT
{
    float4 Position		: POSITION;
	float3 Normal		: COLOR0;
};

// Pixel shader output structure
struct PS_OUTPUT
{
    float4 Color   : COLOR0;
};

float3 lightDir : register(c0);

PS_OUTPUT psmain( in PS_INPUT In )
{
    PS_OUTPUT Out;

    float light = dot(lightDir, In.Normal);
	Out.Color = float4(light, light, light, 1.0f);

    return Out;
}