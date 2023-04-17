#shader vertex
#version 410
#line 3

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Color;

out vec2 io_UV;
out vec3 io_Normal;
out vec3 io_Color;
out vec3 io_FragPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
    io_UV = a_UV;
    io_Color = a_Color;
    io_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    io_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment
#version 410
#line 25

out vec4 FragColor;

in vec2 io_UV;
in vec3 io_Normal;
in vec3 io_Color;
in vec3 io_FragPos;

uniform sampler2D u_Texture;
uniform bool u_UseTextures;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;

void main()
{
    if (u_UseTextures) {
        vec3 color = texture(u_Texture, io_UV).xyz;
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * u_LightColor;

        vec3 norm = normalize(io_Normal);
        vec3 lightDir = normalize(u_LightPos - io_FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * u_LightColor;
        
        vec3 result = (ambient + diffuse) * color;

        FragColor = vec4(color, 1.0);
    } else {
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * u_LightColor;

        vec3 norm = normalize(io_Normal);
        vec3 lightDir = normalize(u_LightPos - io_FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * u_LightColor;
        
        vec3 result = (ambient + diffuse) * io_Color;

        FragColor = vec4(result, 1.0);
    }
}