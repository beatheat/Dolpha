#ifdef GL_ES

precision lowp float;

#endif


varying vec2 v_texCoord;


uniform vec2 u_stepSize;


void main()
{

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);

	color += texture2D(CC_Texture0, v_texCoord + 4.0 * u_stepSize) * 0.06;
	color += texture2D(CC_Texture0, v_texCoord + 3.0 * u_stepSize) * 0.12;
	color += texture2D(CC_Texture0, v_texCoord + 2.0 * u_stepSize) * 0.18;
	color += texture2D(CC_Texture0, v_texCoord + 1.0 * u_stepSize) * 0.24;
	color += texture2D(CC_Texture0, v_texCoord + 0.0 * u_stepSize) * 0.35;	

    gl_FragColor = color;

}

