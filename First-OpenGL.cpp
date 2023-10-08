// First-OpenGlL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>

const int windowWidth = 800;
const int windowHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);    
};

int main()
{
    glfwInit();


    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create window " << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to load Glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);

    


    while (!glfwWindowShouldClose(window))
    {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}

