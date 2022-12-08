#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aPos;
    mat4 v = mat4(mat3(view));
    gl_Position = projection * v * model * vec4(aPos, 1.0);
}  