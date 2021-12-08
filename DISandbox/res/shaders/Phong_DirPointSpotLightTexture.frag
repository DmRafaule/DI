#version 310 es

precision mediump float;

out vec4 color;

in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTex;


uniform float u_time;
uniform vec3  u_color;
uniform vec3  viewPos;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;
struct PointLight {    
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;  
};  
uniform PointLight pointLights;
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLight;



struct Material{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){

   // properties
   vec3 norm = normalize(vNormal);
   vec3 viewDir = normalize(viewPos - vFragPos);
   // phase 1: Directional lighting
   vec3 result = CalcDirLight(dirLight, norm, viewDir);
   // phase 2: Point lights
   //for(int i = 0; i < 1; i++)
       result += CalcPointLight(pointLights, norm, vFragPos, viewDir);    
   // phase 3: Spot light
   result += CalcSpotLight(spotLight, norm, vFragPos, viewDir);    
   
   color = vec4(result, 1.0);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse,vTex));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse,vTex));
    vec3 specular = light.specular * spec * u_color;
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse,vTex));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse,vTex));
    vec3 specular = light.specular * spec * u_color;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
   vec3 lightDir = normalize(light.position - fragPos); 

   float theta = dot(lightDir, normalize(-light.direction));
   float epsilon = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff)/ epsilon,0.0,1.0);
   
   // Set up ambient
   vec3 ambient = light.ambient * vec3(texture(material.diffuse,vTex));
   // Set up diffuse
   float diff = max(dot(normal, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,vTex));
   diffuse *= intensity;
   // Set up specular
   vec3 reflectDir = reflect(-lightDir,normal);
   float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
   vec3 specular = light.specular * spec * u_color;
   specular *= intensity;
   // Set up attenuation for fading light in distance
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
   diffuse *= intensity * attenuation;
   specular *= intensity * attenuation;
   ambient *= attenuation;

   return (ambient  + diffuse + specular);
}