#version 310 es

precision mediump float;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTex;

// World space of fragments
out vec3 vFragPos;
// Object color
out vec3 vColor;
// Normalized vectors of verticies
out vec3 vNormal;
// Texture coordinates
out vec2 vTex;

uniform float u_time;
uniform mat4  u_model;
uniform mat4  u_view;
uniform mat4  u_proj;


void main(){
   vColor = vec3(0.5,0.3,0.77);
   vTex   = aTex;
   //vNormal = mat3(u_model) * aNormal;
   // Convert vectors to perpendiculars when primitives was scaled
   vNormal = mat3(transpose(inverse(u_model))) * aNormal;  
   // Convert fragments coord to world space
   vFragPos = vec3(u_model * vec4(aPos,1.0));
   
   gl_Position = u_proj * u_view * u_model * vec4(aPos,1.0);
}