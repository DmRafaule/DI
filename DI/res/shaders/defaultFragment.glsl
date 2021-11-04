#version 310 es

precision mediump float;

out vec4 color;

in vec3 vColor;
in vec2 vTexture;

uniform float u_time;
uniform vec2  u_resolution;

uniform sampler2D text;
uniform sampler2D text1;

void main(){
   color = vec4(vColor,1.0);
}