uniform vec3 lightDir;

varying vec3 worldNormal;

void main()
{
	vec3 n = normalize(worldNormal);
	float light = dot(lightDir, n);

	gl_FragColor = vec4(light, light, light,1.0);
}