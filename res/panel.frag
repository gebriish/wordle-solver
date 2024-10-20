#version 410 core

in vec2 vPosition;

uniform vec2 uPosition;
uniform vec2 uSize;
uniform vec2 uViewport;

uniform float uRadius;
uniform vec4 uColor;


out vec4 FragColor;


void main()
{
	vec2 pos = vPosition - uPosition;
	FragColor = vec4(uColor.rgba);
}