uniform mat4 WorldViewProjection;
uniform mat3 normalMatrix;

attribute vec4 InPosition;
attribute vec3 InNormal;

varying vec3 worldNormal;

void main()
{
	gl_Position = WorldViewProjection * InPosition;
	worldNormal = normalMatrix * InNormal;
}