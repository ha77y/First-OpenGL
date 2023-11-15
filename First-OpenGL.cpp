#include <iostream>
#include <fstream>
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>

using namespace std;


class object
{
public:
	float* vertexArray;
    float* indexArray;
    float* textureArray;
    float* normalArray;

    object(int nNum, int tNum, int vNum, int iNum)
    {
        // Allocating memory for each attribute in the object 
        vertexArray = (float*)malloc(sizeof(float) * vNum *3);
        indexArray = (float*)malloc(sizeof(float) * iNum * 3);
        textureArray = (float*)malloc(sizeof(float) * tNum * 2);
        normalArray = (float*)malloc(sizeof(float) * nNum * 9);
    
        /*
        vertexArray = new float[vNum];
        indexArray = new float[iNum];
        textureArray = new float[tNum];
        normalArray = new float[nNum];
        */
    }
    object()
    {
        vertexArray = nullptr;
        indexArray = nullptr;
        textureArray = nullptr;
        normalArray = nullptr;

        std::cout << "Default Constructor called" << endl;
    };
    ~object()
    {
        delete[] vertexArray;
        delete[] indexArray;
        delete[] textureArray;
        delete[] normalArray;
    }


};

//Asset Importer .obj

object* import_obj(const string& file_location ) {

	ifstream f(file_location);
    string line;
	if(!f.good())
	{
        cout << "FileStream Error : cannot read file " <<endl;
        return new object();
	}

     int normalCount = 0 , uvCount =0 , vertexCount =0, indexCount =0;

    while (getline(f,line))
    {
        if(line.substr(0,2) == "vn")
        {
	        //add to normal attribute at position normalCount
            normalCount++;
        }
        else if (line.substr(0,2) == "vt")
        {
	        //add to uv attribute at position uvCount
            uvCount++;
        }
        else if(line.substr(0,1) == "v")
        {
	        //add to vector attribute at position vectorCount
            vertexCount++;
        }
        else if(line.substr(0,1) == "f")
        {
	        //add to index array at position faceCount
            indexCount++;
        }
        
    }

	auto* myObject = new object(normalCount,uvCount,vertexCount, indexCount);

    //Reset file to starting position
    f.close();
    f.clear();
    ifstream f2(file_location);
  
    
    string newline;
    normalCount = 0; uvCount = 0; vertexCount = 0; indexCount = 0;


    //todo Write data from file to arrays

    string title;
    float a = 0, b = 0, c = 0;

    //while(getline(f,line)
    while(getline(f2,newline))
    {
        cout << newline;
        f2 >> title >> a >> b >> c;
        cout << title << " " << a << " " << b << " " << c << endl;
        if (title == "vn")
        {
        	myObject->normalArray[normalCount*3 ] = a;
        	myObject->normalArray[normalCount*3 + 1] = b;
        	myObject->normalArray[normalCount*3 + 2] = c;
            
            normalCount++;
        }
        else if (title == "vt")
        {
			myObject->textureArray[uvCount * 2 ] =a;
			myObject->textureArray[uvCount * 2 +1] =b;
			
            
            uvCount++;
        }
        else if (title == "v")
        {
            
        	myObject->vertexArray[vertexCount * 3 ]=a;
        	myObject->vertexArray[vertexCount * 3 +1]=b;
        	myObject->vertexArray[vertexCount * 3 +2]=c;
            
            vertexCount++;
        }
        else if (title == "f")
        {
            string a, b, c;
            f2 >> title >> a >> b >> c;
            float x, y, z;
            // a = "1/1/1" 

            a.replace(a.begin(), a.end(), '/', ' ');
            b.replace(b.begin(), b.end(), '/', ' ');
            c.replace(c.begin(), c.end(), '/', ' ');
            (ifstream)a >> x >> y >> z;
            myObject->indexArray[indexCount * 9] = x;
            myObject->indexArray[indexCount * 9 +1] = y;
            myObject->indexArray[indexCount * 9 +2] = z;
            (ifstream)b >> x >> y >> z;
            myObject->indexArray[indexCount * 9 + 3] = x;
            myObject->indexArray[indexCount * 9 + 4] = y;
            myObject->indexArray[indexCount * 9 + 5] = z;
            (ifstream)c >> x >> y >> z;
            myObject->indexArray[indexCount * 9 + 6] = x;
            myObject->indexArray[indexCount * 9 + 7] = y;
            myObject->indexArray[indexCount * 9 + 8] = z;

            indexCount++;
            
        }
    }

    cout << "Vertex positions: " << (myObject->vertexArray[1]) << endl
         << "Normals: " << sizeof(myObject->normalArray) << endl
         << "uv count: " << sizeof(myObject->textureArray) << endl
         << "Indexes: " << sizeof(myObject->indexArray) << endl;


    f.close();
    return myObject;

};


constexpr int window_width = 800;
constexpr int window_height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);    
};

float vertices[]{
    //positions             //Colors( RGB) 
    -0.5f, -0.5f, 0.0f,      1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, 0.0f,      0.0f,  1.0f,  0.0f,
     0.0f,  0.5f, 0.0f,      0.0f,  0.0f,  1.0f
};

float BackgroundVerts[]{
    -1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f
};


int main()
{
    glfwInit();

    object* ball =import_obj("C://Users//harri//OneDrive//Desktop//Ball.obj");

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "LearnOpenGL", nullptr, nullptr);
    
    if (window == nullptr) {
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

    glViewport(0, 0, window_width, window_height);


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
        "layout (location = 1) in vec3 vertCol;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   ourColor = vertCol;\n"
        "}\0";

    //source code for frag shader
    const char* TrifragmentShaderSource = "#version 330 core\n"
        "in vec3 ourColor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(ourColor,1.0f);\n"
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
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); //Set the source code of vertex shader (idk what count is)
                                                                //to the predefined source
    glCompileShader(vertexShader);                              //compile 


    //Repeat for Fragment shaders 
    GLuint TrifragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(TrifragmentShader, 1, &TrifragmentShaderSource, nullptr);

    glCompileShader(TrifragmentShader);

    GLuint QuadFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(QuadFragmentShader, 1, &QuadFragShaderSource, nullptr);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

