
uniform sampler2D u_texture;

void main(void)
{
	vec4 color = texture2D(u_texture, gl_TexCoord[0].xy);
	float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
	vec3 grayscale = vec3(gray);
	gl_FragColor = vec4(grayscale, color.a);
}