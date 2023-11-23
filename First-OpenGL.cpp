
#include <iostream>
#include <fstream>
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class vec3
{
private:
    float x;
    float y;
    float z;
public:
    vec3(float _x,float _y,float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    vec3() { x = NULL; y = NULL; z = NULL;}
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getZ()
    {
        return z;
    }
    void setX(float n)
    {
        std::cout << " SET X to " << n << endl;
        x = n;
    }
    void setY(float n)
    {
        std::cout << " SET Y to " << n << endl;
        y = n;
    }
    void setZ(float n)
    {
        std::cout << "SET Z to " << n << endl;
        z = n;
    }
};

class vec2
{
private:
    float x;
    float y;
public:
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    void setX(float n)
    {
        x = n;
    }
    void setY(float n)
    {
        y = n;
    }
};

class object
{
public:
	vec3* vertexArray;
    vec3* indexArray;
    vec2* textureArray;
    vec3* normalArray;

    object(int nNum, int tNum, int vNum, int iNum)
    {
        // Allocating memory for each attribute in the object 
        vertexArray = (vec3*)malloc(sizeof(vec3) * vNum );
        indexArray = (vec3*)malloc(sizeof(vec3) * iNum );
        textureArray = (vec2*)malloc(sizeof(vec2) * tNum );
        normalArray = (vec3*)malloc(sizeof(vec3) * nNum * 3);
    
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
    string title;
	if(!f.good())
	{
        std::cout << "FileStream Error : cannot read file " <<endl;
        return new object();
	}
    f >> title;

     int normalCount = 0 , uvCount =0 , vertexCount =0, indexCount =0;

    while (getline(f,line))
    {
        if (title == "vn")
        {
	        //add to normal attribute at position normalCount
            normalCount++;
        }
        else if (title == "vt")
        {
	        //add to uv attribute at position uvCount
            uvCount++;
        }
        else if (title == "v")
        {
	        //add to vector attribute at position vectorCount
            vertexCount++;
        }
        else if (title == "f")
        {
	        //add to index array at position faceCount
            indexCount++;
        }
        
    }

	auto* myObject = new object(normalCount,uvCount,vertexCount, indexCount);

    //Reset file to starting position
    f.clear();
    f.seekg(0);
    normalCount = 0; uvCount = 0; vertexCount = 0; indexCount = 0;


    string a, b, c;
    vec3 newNormal;
    
    while (getline(f, line)){
        title = line.substr(0, 2);
        if( title!= "v " && title != "vt" && title != "vn" && title !="f " )
        {
            std::cout << "whoops" << endl;
        }
        else {
            f >> title >> a >> b >> c;
            std::cout << title << " " << a << " " << b << " " << c << endl;
            /*
            if (title == "vn")
            {
                cout << line << endl;
                //vecPoint to determine x y z assignments x:0  y:1  z:2 ;
                int startPointer = 0, length = 0, vecPoint = 0;
                newNormal.setX(stof(a));
                newNormal.setY(stof(b));
                newNormal.setZ(stof(c));

                myObject->normalArray[normalCount] = newNormal;
                cout << newNormal.getX() << " " << newNormal.getY() << " " << newNormal.getZ()<< " " << endl;



                normalCount++;
            }
            /*
            else if (title == "vt")
            {
                f2 >> title >> a >> b;
                myObject->textureArray[uvCount].setX(a);
                myObject->textureArray[uvCount].setY(b);


                uvCount++;
            }
            else if (title == "v")
            {
                f2 >> title >> a >> b >> c;
                cout << a;
                myObject->vertexArray[vertexCount * 3].setX(a);
                myObject->vertexArray[vertexCount * 3].setY(b);
                myObject->vertexArray[vertexCount * 3].setZ(c);

                vertexCount++;
            }
            /*
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
                cout << x << " " << y << " " << z << endl;
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

            } */
        }
    }
    std::cout << "Vertex positions: " << sizeof(myObject->vertexArray) << endl
         << "Normals: " << (myObject->normalArray[0].getX()) << endl
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

/**/

// failed attempts

// attempt to read file
// problem:
// File would be one line behind title component meaning all values were displaced
// this meant that a vertex coordinate would be stored as a normal and a normal as a texture coord , etc 
 /*
            for (int i =0; i<=line.length();i++)
            {

                length++;

                if(line[i] == ' ' || i == line.length())
                {
                    if(i != 0)
                    {
                        float CoordValue = stof(line.substr(startPointer, length));
                        //determine which component of the vector to set
                        switch (vecPoint)
                        {
                        case 0: newNormal.setX(CoordValue); vecPoint++; break;
                        case 1: newNormal.setY(CoordValue); vecPoint++; break;
                        case 2: newNormal.setZ(CoordValue); vecPoint = 0; break;
                        default: cout << "what?";
                        }
                    }

                    startPointer = i;
                    length = 0;
                }

            }
            */