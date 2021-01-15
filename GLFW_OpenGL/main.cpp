#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./Shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void testForGlm();

void bindTexture(const char* path, GLenum type, int idx) {
    // 绑定纹理
    unsigned int texture;
    glad_glGenTextures(1, &texture);
    glad_glActiveTexture(GL_TEXTURE0 + idx);
    glad_glBindTexture(GL_TEXTURE_2D, texture);
    
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 读取图片数据
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(data) {
        // 生成纹理
        glad_glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        std::cout << "ERROR read image data " << std::endl;
    }

    stbi_image_free(data);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
};
float verticesWithColor[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

float verticesWithColorAndTexture[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

float verticesWithCube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

float texCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "outColor = aColor;\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outColor;\n"
    "void main()\n"
    "{\n"
//    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "   FragColor = vec4(outColor, 1.0);\n"
    "}\n\0";

int main()
{
    // testForGlm();
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    
    unsigned int VAO;
    glad_glGenVertexArrays(1, &VAO);
    glad_glBindVertexArray(VAO);
    
    // 顶点缓存对象
    unsigned int VBO;
    glad_glGenBuffers(1, &VBO);
    // GL_ARRAY_BUFFER表示缓存对象类型
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWithCube), verticesWithCube, GL_STATIC_DRAW);
    
    // 索引缓存对象
    unsigned int EBO;
    glad_glGenBuffers(1, &EBO);
    //
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // 传递顶点格式
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);
    
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
    glad_glBindVertexArray(0);
    
    bindTexture("/Users/hortor/self_project/GLFW_OpenGL/GLFW_OpenGL/images/wall.jpg", GL_RGB, 0);
    bindTexture("/Users/hortor/self_project/GLFW_OpenGL/GLFW_OpenGL/images/awesomeface.png", GL_RGBA, 1);

    Shader myShader("/Users/hortor/self_project/GLFW_OpenGL/GLFW_OpenGL/Shader/shader.vs", "/Users/hortor/self_project/GLFW_OpenGL/GLFW_OpenGL/Shader/shader.fs");
    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);

    
    
    
    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
        // 清理颜色
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        
        // 模型矩阵
        glm::mat4 model = glm::mat4(1.0f);
//         model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));      // 沿x轴旋转
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // 观察矩阵
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // 投影矩阵
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT * 1.0f, 0.1f, 100.0f);

        // 模型矩阵
        int modelLoc = glad_glGetUniformLocation(myShader.ID, "model");
        glad_glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // 观察矩阵
        int viewLoc = glad_glGetUniformLocation(myShader.ID, "view");
        glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // 投影矩阵
        int projectionLoc = glad_glGetUniformLocation(myShader.ID, "projection");
        glad_glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        
        // 绑定VAO, 绘制图像
        glad_glBindVertexArray(VAO);
        //glad_glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesWithCube));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void testForGlm() {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // 初始化一个矩阵
    glm::mat4 trans = glm::mat4(1.0f);
    
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std:: cout << vec.x << vec.y << vec.z << std:: endl;
}
