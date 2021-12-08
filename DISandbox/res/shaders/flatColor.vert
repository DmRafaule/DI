#version 310 es

precision mediump float;

layout(location = 0) in vec3 a_pos;


uniform float u_time;
uniform mat4  u_model;
uniform mat4  u_proj;
uniform mat4  u_view;

void main(){
   gl_Position = u_proj * u_view * u_model * vec4(a_pos,1.0);
}