//#define NO_TEXTURE
//#define HAS_UNIFORM_COLOR
//#define HAS_COLOR_TRANSFORM

#ifdef HAS_TEXTURE
uniform sampler2D texture;
#endif

#ifdef HAS_UNIFORM_COLOR
uniform vec4 col;
#endif

#ifdef HAS_COLOR_TRANSFORM
uniform vec4 colAdd;
uniform vec4 colMul;
uniform mat4 colTrans;
#endif

void main()
{
    // récupère le pixel dans la texture
    #ifdef HAS_TEXTURE
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    #else
    vec4 pixel = vec4(1.0f,1.0f,1.0f,1.0f);
    #endif

    #ifdef HAS_UNIFORM_COLOR
    pixel *= col;
    #endif

    #ifdef HAS_COLOR_TRANSFORM
    pixel += colAdd;
    pixel *= colMul;
    pixel = colTrans * pixel;
    #endif

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}