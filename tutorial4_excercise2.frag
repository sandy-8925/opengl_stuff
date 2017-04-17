#version 330 core

in vec2 TexCoord1;
in vec2 TexCoord2;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main() {
	color = mix(texture(ourTexture1, TexCoord1), texture(ourTexture2, TexCoord2), 0.2);
}
