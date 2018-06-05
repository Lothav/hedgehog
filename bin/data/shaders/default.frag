#version 130

precision mediump float;
uniform sampler2D tex;
in vec2 fragTexCoord;
out vec4 finalColor;

in vec2 coord;

void main() {
    finalColor = texture(tex, fragTexCoord);
    gl_FragDepth = -coord[1];
}
