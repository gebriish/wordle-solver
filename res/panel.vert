#version 410 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPosition;
uniform vec2 uSize;

uniform vec2 uViewport;

out vec2 vPosition;

void main()
{
	vec2 position = aPos * uSize + uPosition * vec2(1,-1);
	vPosition = position * vec2(1,-1);


	position /= uViewport;
	position = position * 2.0f - vec2(1,-1);


	gl_Position = vec4(position, 0.0f, 1.0f);
}