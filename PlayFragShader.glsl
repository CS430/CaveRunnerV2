#version 330 core

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main() {
	color = texture(mySampler, fragmentUV);
}