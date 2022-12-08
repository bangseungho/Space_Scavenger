#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelTransform; //--- 모델링 변환 행렬: uniform 변수로 선언
uniform mat4 projectionTransform;

out vec2 TexCoord;

void main()
{
	gl_Position = projectionTransform * modelTransform * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}