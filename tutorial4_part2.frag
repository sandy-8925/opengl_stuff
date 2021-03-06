#version 330 core

in vec3 vertColour;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    color = texture(ourTexture, TexCoord) * vec4(vertColour, 1.0f);
}
