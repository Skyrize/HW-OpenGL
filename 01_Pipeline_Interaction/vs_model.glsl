#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;

out VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} vs_out;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);
    vs_out.tc = tc;

    vec3 normalsT = mat3(transpose(inverse(model_matrix))) * normals;
    vs_out.normals = normalize(vec4(normalsT, 1.0));

    vs_out.fragPos = model_matrix * vec4(position, 1);
}
