// Pixel shader input structure
struct PS_INPUT
{
	float2 UV			: COLOR0;
};

// Pixel shader output structure
struct PS_OUTPUT
{
    float4 Color   : COLOR0;
};

texture spriteTex;
sampler2D textureSampler = sampler_state {
    Texture = (spriteTex);
    MagFilter = Linear;
    MinFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

PS_OUTPUT psmain( in PS_INPUT In )
{
    PS_OUTPUT Out;

	float4 tex = tex2D(textureSampler, In.UV);
	Out.Color = tex;

    return Out;
}