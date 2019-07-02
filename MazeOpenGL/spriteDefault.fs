#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D sprite;

void main()
{


FragColor = texture(sprite,TexCoords) * vec4(color,1.0);
}

