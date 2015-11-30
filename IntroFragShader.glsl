#version 330 core

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;
uniform float alphaValue;

void main() {
	color = texture(mySampler, fragmentUV) * vec4(1.0, 1.0, 1.0, alphaValue);
}