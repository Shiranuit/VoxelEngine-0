#version 330 core
layout (location = 0) in vec3 VertexPos;

out vec3 ourColor;
out vec2 TexCoord;
in mat4 transform;
in mat4 camera;

void main()
{
    gl_Position = camera * transform * vec4(VertexPos, 1.0);
    TexCoord = VertexPos.xy;
}