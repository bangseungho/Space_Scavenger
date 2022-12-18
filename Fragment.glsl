#version 330 core

struct DirLight {
   vec3 Pos;	// �� ��ġ 
   vec3 Color;  // �� �÷�
};  
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

#define RIGHT_NUMBER 10

uniform DirLight dirLight[RIGHT_NUMBER];
uniform int LightCount;

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;

uniform vec4 vColor;	// object �÷�
uniform vec3 viewPos;	// ī�޶� ��ġ

#ifndef _Max
#define _Max
#endif

#ifdef _Max
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float d;
#endif

uniform int lightTypeIndex; // 0 : �� ����, 1 : �� ���� ����
out vec4 FragColor; //--- ������ ���۷� ���

void main()
{
    vec3 result = vec3(0);
    if(lightTypeIndex == 1)
    {
        FragColor = vec4(Ka,1) * vColor;
    }
    else if(lightTypeIndex == 0)
    {
        // properties
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        // phase 1: Directional lighting
        for(int i = 0; i < LightCount; i++)
            result += CalcDirLight(dirLight[i], norm, viewDir);
    
        FragColor = vec4(result, 1.0) * vColor + vec4(0.001f * Ka, 1);
    }
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    float ambientLenth = 0.1f;
    vec3 ambient = ambientLenth * Ka;

    vec3 lightDir = normalize(light.Pos - FragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    //float shininess = 128;
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // combine results
    vec3 _Ambient  = ambient;
    vec3 _Diffuse  = light.Color  * diff * Kd;
    //vec3 _Specular = light.Color * spec * Ks;

    return (_Ambient + _Diffuse);// + _Specular);
}