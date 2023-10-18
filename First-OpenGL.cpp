#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>



const int windowWidth = 800;
const int windowHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);    
};

float vertices[]{
    -0.5f   ,-0.5f   ,0,
    0.5f    ,-0.5f   ,0,
    0,      0.5f    ,0
};

float BackgroundVerts[]{
    -1,-1,0,
    -1,1,0,
    1,1,0,
    1,-1,0
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


    //Vertex Buffer Object
    unsigned int vbo1;
    glGenBuffers(1, &vbo1);
    unsigned int vbo2;
    glGenBuffers(1, &vbo2);

    

    //init Shader 
    GLuint TriShaderProg = glCreateProgram();
    GLuint QuadShaderProg = glCreateProgram();

    //source code for vertex shader 
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    //source code for frag shader
    const char* TrifragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.2f, 1.0f, 1.0f);\n"
        "}\0";

    const char* QuadFragShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(0.0f, 0.65f, 1.0f, 1.0f);\n"
        "}\0";

    //There is probably a way to run straight up glsl however i do not know how to do that yet



    //Compiling source code into shader program 
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);     //create vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Set the source code of vertex shader (idk what count is)
                                                                //to the predefined source
    glCompileShader(vertexShader);                              //compile 


    //Repeat for Fragment shaders 
    GLuint TrifragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(TrifragmentShader, 1, &TrifragmentShaderSource, NULL);

    glCompileShader(TrifragmentShader);

    GLuint QuadFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(QuadFragmentShader, 1, &QuadFragShaderSource, NULL);

    glCompileShader(QuadFragmentShader);


    //Attach each shader to the defined program and link them together
    glAttachShader(TriShaderProg, vertexShader);
    glAttachShader(TriShaderProg, TrifragmentShader);
    glLinkProgram(TriShaderProg);

    glAttachShader(QuadShaderProg, vertexShader);
    glAttachShader(QuadShaderProg, QuadFragmentShader);
    glLinkProgram(QuadShaderProg);
    
    
    glDeleteShader(vertexShader);
    glDeleteShader(TrifragmentShader);
    glDeleteShader(QuadFragmentShader);


    //Vertex Attribute Object 
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices , GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    GLuint VAO2;
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BackgroundVerts), BackgroundVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(BackgroundVerts),BackgroundVerts,GL_STATIC_DRAW);



    
    while (!glfwWindowShouldClose(window))
    {

        //Boiler plate stuff
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapBuffers(window);
        glfwPollEvents();

        //Render quad
        
        glUseProgram(QuadShaderProg);
        glBindVertexArray(VAO2);

        glDrawArrays(GL_QUADS, 0, 4);
        
        
        //render tri
        glUseProgram(TriShaderProg);
        glBindVertexArray(VAO1);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        

    }

    glfwTerminate();
    return 0;

}

