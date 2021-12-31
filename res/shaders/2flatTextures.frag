#version 310 es

precision mediump float;

out vec4 f_color;
in vec2 f_tex0;

uniform float u_time;
uniform sampler2D u_tex0;
uniform sampler2D u_tex1;


void main(){
   f_color = mix(texture(u_tex0,f_tex0),texture(u_tex1,f_tex0),0.7f);
}