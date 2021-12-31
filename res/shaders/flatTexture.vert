#version 310 es

precision mediump float;

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_tex0;

out vec2 f_tex0;
uniform float u_time;
uniform mat4  u_mvp;

void main(){
   f_tex0 = a_tex0;
   gl_Position = u_mvp * vec4(a_pos,1.0);
}