#version 410 core
layout (location = 0) in vec3 m_pos;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    TexCoords = m_pos;
    vec4 pos = projectionMatrix * viewMatrix * vec4(m_pos , 1.0);
    gl_Position = pos.xyww;
}
