#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColor = texture(texture1, texCoord) * vec4(outColor, 1.0);
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
//    FragColor = texture(texture2, texCoord);
}
