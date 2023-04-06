#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

void main()
{
    gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.9, 0.3, 0.8, 1.0);
}