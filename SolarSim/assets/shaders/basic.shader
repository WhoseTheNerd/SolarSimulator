#shader vertex
#version 410
#line 3

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Color;

out vec2 io_UV;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
    io_UV = a_UV;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment
#version 410
#line 23

out vec4 FragColor;

in vec2 io_UV;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, io_UV);
}