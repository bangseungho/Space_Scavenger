#version 330 core

uniform vec4 vColor;    

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
  
uniform Material material;


out vec4 FragColor; //--- 프레임 버퍼로 출력
void main()
{
    //vec3 ambient  = light.ambient * material.ambient;
    //vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    //vec3 specular = light.specular * (spec * material.specular);  
    //    
    //vec3 result = ambient + diffuse + specular;
    //FragColor = vec4(result, 1.0) * vColor;
    FragColor = vColor;
}