// Vertex shader input structure
struct VS_INPUT
{
    float3 Position		: POSITION;
	float3 Normal		: NORMAL;
    float2 Texture		: TEXCOORD0;
};


// Vertex shader output structure
struct VS_OUTPUT
{
    float4 Position		: POSITION;
};


// Global variables
float4x4 WorldViewProj : register(c0);


VS_OUTPUT vsmain( in VS_INPUT In )
{
    VS_OUTPUT Out;

    Out.Position = mul(In.Position, WorldViewProj); 

    return Out;
}