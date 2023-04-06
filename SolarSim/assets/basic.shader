#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;

out vec2 io_UV;

uniform mat4 u_ViewProjection;

void main()
{
    io_UV = a_UV;
    gl_Position = u_ViewProjection * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 io_UV;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, io_UV);
}