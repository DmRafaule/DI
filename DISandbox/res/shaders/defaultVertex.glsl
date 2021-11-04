#version 310 es

precision mediump float;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexture;

out vec3 vColor;
out vec2 vTexture;

uniform float u_time;
uniform mat4  u_mvp;


void main(){
   vColor = aColor;
   vTexture = aTexture;
   gl_Position = u_mvp * vec4(aPos,1.0);
}