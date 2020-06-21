#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstancedModel;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;


uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(aInstancedModel * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(aInstancedModel))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * aInstancedModel * vec4(aPos, 1.0);
}
