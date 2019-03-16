#version 330 core
layout (location = 0) in uint VertexPos;
layout (location = 1) in uint VertexColor;

uniform mat4 position;
uniform mat4 camera;

out vec3 pos;
out vec3 color;
out vec3 normal;
out vec3 fragpos;

vec4 intToVec4(uint val)
{
    return vec4(float(int(val) & 0x000000FF),
                float(int(val >> 8) & 0x000000FF),
                float(int(val >> 16) & 0x000000FF),
                float(int(val >> 24) & 0x000000FF));

}

vec3 getNormal(uint val)
{
    int byte = int(val >> 24) & 0x000000FF;
    vec3 norm = vec3(float(int(byte) & 1),
                     float(int(byte >> 1) & 1),
                     float(int(byte >> 2) & 1));
    if ((int(byte >> 3) & 1) == 1) {
        return -norm;
    } else {
        return norm;
    }
}

void main()
{
    vec4 vpos = intToVec4(VertexPos);
    vec4 vcolor = intToVec4(VertexColor);
    gl_Position = camera * position * vec4(vpos.xyz, 1.f);
    pos = gl_Position.xyz;
    fragpos = vec3(position * vec4(vpos.xyz, 1.0));
    color = (vcolor / 255.0f).xyz;
    normal = getNormal(VertexPos);
}