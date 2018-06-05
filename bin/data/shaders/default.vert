#version 130

uniform mat4 view;

in vec3 vert;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

out vec2 coord;

void main() {
    // Pass the tex coord straight through to the fragment shader
    fragTexCoord = vertTexCoord;
    coord = vec2(vert[0], vert[1]);
    gl_Position = view * vec4(vert, 1.0f);
}
