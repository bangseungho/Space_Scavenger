#version 330 core

struct DirLight {
   vec3 Pos;	// 빛 위치 
   vec3 Color;  // 빛 컬러
};  

//#define NR_POINT_LIGHTS 4 
#define RIGHT_NUMBER 20

uniform int LightCount;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

uniform DirLight dirLight[RIGHT_NUMBER];

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;

uniform vec4 vColor;	// object 컬러
uniform vec3 viewPos;	// 카메라 위치

#ifndef _Max
#define _Max
#endif

#ifdef _Max
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float d;
#endif

out vec4 FragColor; //--- 프레임 버퍼로 출력

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0);

    // phase 1: Directional lighting
    for(int i = 0; i < LightCount; i++)
        result += CalcDirLight(dirLight[i], norm, viewDir);
    
    FragColor = vec4(result, 1.0) * vColor;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    float ambientLenth = 2.0f;
    vec3 ambient = ambientLenth * vec3(vColor);

    vec3 lightDir = normalize(light.Pos - FragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    float shininess = 128;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // combine results
    vec3 _Ambient  = ambient * Ka;
    vec3 _Diffuse  = light.Color  * diff * Kd;
    vec3 _Specular = light.Color * spec * Ks;

    return (_Ambient + _Diffuse + _Specular);
}

// in vec3 FragPos;
// in vec2 UV;
// in vec3 Normal;
// 
// uniform vec3 lightPos;	// 빛 위치
// uniform vec3 lightColor;// 빛 컬러
// uniform vec4 vColor;	// object 컬러
// uniform vec3 viewPos;	// 카메라 위치
// 
// out vec4 FragColor; //--- 프레임 버퍼로 출력
// 
// #ifndef _Max
// #define _Max
// #endif
// 
// #ifdef _Max
// uniform vec3 Ka;
// uniform vec3 Kd;
// uniform vec3 Ks;
// uniform float d;
// #endif
// 
// void main()
// {
//     float ambientLenth = 2.0f;
//     vec3 ambient = ambientLenth * vec3(vColor) * Ka;
//     // diffuse 
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(lightPos - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = lightColor * diff * Kd;
//     
//     // specular
//     float shininess = 128;
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);  
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
//     vec3 specular = lightColor * spec * Ks;  
//         
//     vec3 result = ambient + diffuse + specular;
//     FragColor = vec4(result, 1.0) * vColor;
// }