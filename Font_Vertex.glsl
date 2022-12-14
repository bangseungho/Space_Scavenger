#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 modelTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * modelTransform * vec4(0,0,0,1);
}