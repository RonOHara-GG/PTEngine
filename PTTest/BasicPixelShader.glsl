uniform vec3 lightDir;
uniform sampler2D textureSampler;

varying vec3 worldNormal;
varying vec2 texCoord;


void main()
{
	vec3 n = normalize(worldNormal);
	float light = dot(lightDir, n);
	//vec4 texColor = texture2D(textureSampler, texCoord) * light;
	vec4 texColor = vec4(light, light, light, 1.0);

	gl_FragColor = vec4(texColor.xyz, 1.0);
}