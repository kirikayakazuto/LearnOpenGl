#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

uniform vec3 viewPos;       // 摄像机位置

struct Light {
    vec3 direction;
    // vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

void main() {
    
    /** 环境光 */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    /** 灯光 */
    vec3 norm = normalize(normal);
    // vec3 lightDir = normalize(light.position - fragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    /** 镜面光 */
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflecDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflecDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    // 最终颜色等于 光的颜色 * 物品颜色
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
