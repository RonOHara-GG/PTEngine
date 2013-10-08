layout(location = 0) in vec4 InPosition;
layout(location = 3) in vec2 InUV0;


uniform mat4 WorldViewProjection;

varying vec2 texCoord;

void main()
{
	gl_Position = WorldViewProjection * InPosition;
	texCoord = InUV0;
}