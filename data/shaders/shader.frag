#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform float u_time;
uniform vec2 u_resolution;
uniform sampler2D texture1;

#define PI 3.14159265359

void main() {
		vec2 st = gl_FragCoord.xy / u_resolution;
		//gl_FragColor = vec4(st.x, st.y, 0.3, 1.0);
        FragColor = texture(texture1, TexCoord);
}
