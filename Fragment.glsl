#version 330 core

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;

uniform vec4 vColor;	// object 컬러
uniform vec3 lightPos;	// 빛 위치
uniform vec3 lightColor;// 빛 컬러
uniform vec3 viewPos;	// 카메라 위치

out vec4 FragColor; //--- 프레임 버퍼로 출력

#ifndef _Max
#define _Max
#endif

#ifdef _Max
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float d;
#endif

void main()
{
    float ambientLenth = 1.5f;
    vec3 ambient = ambientLenth * vec3(vColor) * Ka;
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * Kd;
    
    // specular
    float shininess = 128;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColor * spec * Ks;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0) * vColor;
}