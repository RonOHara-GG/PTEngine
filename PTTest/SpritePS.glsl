varying vec2 texCoord;

uniform sampler2D textureSampler;

void main()
{
	gl_FragColor = texture2D(textureSampler, texCoord);
	//gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}