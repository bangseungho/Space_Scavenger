#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 modelTransform; //--- 모델링 변환 행렬: uniform 변수로 선언
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * modelTransform * vec4(0,0,0,1);
}