#version 310 es

precision mediump float;

layout(location = 0) in vec3 a_pos;


uniform float u_time;
uniform mat4  u_mvp;

void main(){
   gl_Position = u_mvp * vec4(a_pos,1.0);
}