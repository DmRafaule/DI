#version 310 es

precision mediump float;

out vec4 color;

in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTex;


uniform float u_time;
uniform vec2  u_resolution;
uniform vec3 u_color;


uniform vec3  viewPos;

struct Material{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};
uniform Material material;

/*It is spoting light*/

struct Light {
   vec3 position;
   vec3 direction;
   float cutOff;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};
uniform Light light;

void main(){

   vec3 lightDir = normalize(light.position - vFragPos); 
   
   // Set up ambient
   vec3 ambient = light.ambient * u_color;
   // Set up diffuse
   vec3 norm = normalize(vNormal);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * u_color;
   // Set up specular
   vec3 viewDir = normalize(viewPos - vFragPos);
   vec3 reflectDir = reflect(-lightDir,norm);
   float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
   vec3 specular = light.specular * spec * u_color;

   // Set up attenuation for fading light in distance
   float distance    = length(light.position - vFragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
   vec3 result  = (ambient + diffuse + specular) * attenuation;
   
   color = vec4(result,1.0);
}