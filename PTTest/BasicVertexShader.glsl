layout(location = 0) in vec4 InPosition;
layout(location = 1) in vec3 InNormal;
layout(location = 3) in vec2 InUV0;

uniform mat4 WorldViewProjection;
uniform mat3 NormalMatrix;

varying vec3 worldNormal;
varying vec2 texCoord;

void main()
{
	gl_Position = WorldViewProjection * InPosition;
	worldNormal = NormalMatrix * InNormal;
	texCoord = InUV0;
}