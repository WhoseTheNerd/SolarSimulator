#shader vertex
#version 410
#line 3

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
    TexCoords = aPos;
}  

#shader fragment
#version 410
#line 20

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}