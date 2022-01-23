//#define NO_TEXTURE
//#define HAS_UNIFORM_COLOR
//#define HAS_COLOR_TRANSFORM

#ifdef HAS_TEXTURE
uniform sampler2D texture;
uniform vec4 colAdd;
uniform vec4 colMul;
uniform mat4 colTrans;
uniform float u_time;
uniform vec2 blurFactor;
#endif

#ifdef HAS_UNIFORM_COLOR
uniform vec4 col;
#endif

#ifdef HAS_COLOR_TRANSFORM

#endif

/*
void main()
{
    // récupère le pixel dans la texture
    #ifdef HAS_TEXTURE
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    pixel += colAdd;
    pixel *= colMul;
    pixel = colTrans * pixel;
    pixel = vec4(abs(sin(u_time)),abs(sin(u_time)),abs(sin(u_time)),1.0) * pixel;

    if ((mod(gl_TexCoord[0].y, 0.2)) > 0.1)
    {
        pixel.b = 0.0;
    }
    if ((mod(gl_TexCoord[0].x, 0.2)) > 0.1)
    {
        pixel.g = 0.0;
    }

    #else
    vec4 pixel = vec4(1.0f,1.0f,1.0f,1.0f);
    #endif

    #ifdef HAS_UNIFORM_COLOR
    pixel *= col;
    #endif

    #ifdef HAS_COLOR_TRANSFORM

    #endif

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}
*/
void main()
{
	vec2 coor = gl_TexCoord[0].xy;
	vec4 color = vec4(0.0);
	color += texture2D(texture, coor - 4.0 * blurFactor) * 0.01;
	color += texture2D(texture, coor - 3.0 * blurFactor) * 0.05;
	color += texture2D(texture, coor - 2.0 * blurFactor) * 0.1;
	color += texture2D(texture, coor - blurFactor) * 0.2;
	color += texture2D(texture, coor) * 0.2;
	color += texture2D(texture, coor + blurFactor) * 0.2;
	color += texture2D(texture, coor + 2.0 * blurFactor) * 0.1;
	color += texture2D(texture, coor + 3.0 * blurFactor) * 0.05;
	color += texture2D(texture, coor + 4.0 * blurFactor) * 0.01;
	gl_FragColor = color;
}