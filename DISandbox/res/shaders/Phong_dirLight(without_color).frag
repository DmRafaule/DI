#version 310 es

precision mediump float;

out vec4 color;

in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTex;


uniform float u_time;
uniform vec2  u_resolution;

uniform vec3  viewPos;

struct Material{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

/*It is directional light*/

struct Light {
   //vec3 position;
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};
uniform Light light;
uniform Material material;

void main(){
   vec3 lightDir = normalize(-light.direction); 
   // Set up ambient
   vec3 ambient = light.ambient * vec3(texture(material.diffuse,vTex));
   // Set up diffuse
   vec3 norm = normalize(vNormal);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,vTex));
   // Set up specular
   vec3 viewDir = normalize(viewPos - vFragPos);
   vec3 reflectDir = reflect(-lightDir,norm);
   float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
   vec3 specular = light.specular * spec * vColor;

   vec3 result  = (ambient + diffuse + specular);
   
   color = vec4(result,1.0);
}