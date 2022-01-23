varying out vec4 vert_pos;
uniform float vert_time;
uniform float displacement;
uniform vec2 movement;
uniform float movement_speed;

void main()
{
    // transforme la position du vertex
    vec4 worldPos = gl_Vertex;

    worldPos.x += cos(vert_time) * movement_speed;
    worldPos.y += sin(vert_time) * movement_speed;
    
    worldPos.xy += worldPos * 20;
    gl_Position = gl_ModelViewProjectionMatrix * worldPos;

    // transforme les coordonnées de texture
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0 + displacement;

    // transmet la couleur
    gl_FrontColor = gl_Color;
}