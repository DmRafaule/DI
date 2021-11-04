#version 310 es

precision mediump float;

out vec4 color;

in vec3 vColor;
in vec2 vTexture;

uniform float u_time;
uniform vec2  u_resolution;// Write down spetial shader for loading textures

uniform sampler2D tex0;

void main(){
   color = texture(tex0,vTexture);
}