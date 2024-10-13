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

	float dist = 0.0;

	if(pos.x < uRadius && pos.y < uRadius)
		dist = length(pos - vec2(uRadius));
	else if(pos.x > uSize.x - uRadius && pos.y < uRadius)
		dist = length(pos - vec2(uSize.x - uRadius, uRadius));
	else if(pos.x > uSize.x - uRadius && pos.y > uSize.y - uRadius)
		dist = length(pos - vec2(uSize.x - uRadius, uSize.y - uRadius));
	else if(pos.x < uRadius && pos.y > uSize.y - uRadius)
		dist = length(pos - vec2(uRadius, uSize.y - uRadius));


	float val = 1 - smoothstep(uRadius - 0.5, uRadius, dist);
	FragColor = vec4(uColor.rgb, uColor.a * val);
}