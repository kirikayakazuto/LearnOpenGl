#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    // 最终颜色等于 光的颜色 * 物品颜色
    FragColor = vec4(lightColor * objectColor, 1.0);
}
