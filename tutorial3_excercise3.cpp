#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left 
};

GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};  

GLuint VAO;
GLuint shaderProgram;

void setupOpenGLDrawingCode();
void drawStuff();
GLuint createShader(GLenum shaderType, GLchar** shaderSource);
bool checkShaderCompileStatus(GLuint shader);
bool checkShaderProgramLinkStatus(GLuint shaderProgram);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLchar* vertexShaderSource =  "#version 330 core\n\n\
                                layout (location = 0) in vec3 position;\n\n\
				out vec4 vertexColor;\n\n\
                                void main() {\n\
                                    gl_Position = vec4(position, 1.0);\n\
				    vertexColor = gl_Position;\n\
                                }";

GLchar* fragmentShaderSource = "#version 330 core\n\n\
                                 in vec4 vertexColor;\n\n\
                                 out vec4 color;\n\n\
                                 void main() {\n\
                                    color = vertexColor;\n\
                                 }";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if(window == NULL) {
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        setupOpenGLDrawingCode();
        
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawStuff();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void drawStuff() {
	glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

void setupOpenGLDrawingCode() {
        GLuint VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);        
        
        glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
        
        glBindVertexArray(0);
        

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, &vertexShaderSource);
	bool vertexShaderCompileSuccess = checkShaderCompileStatus(vertexShader);
        if(!vertexShaderCompileSuccess) {
            cout << "Vertex shader compilation failed" << endl;
        }

        GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	bool fragmentShaderCompileSuccess = checkShaderCompileStatus(fragmentShader);
        if(!fragmentShaderCompileSuccess) {
            cout << "Fragment shader compilation failed" << endl;
        }
        
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        bool shaderProgramLinkStatus = checkShaderProgramLinkStatus(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

GLuint createShader(GLenum shaderType, GLchar** shaderSource) {
	GLuint shaderRef = glCreateShader(shaderType);
	glShaderSource(shaderRef, 1, shaderSource, NULL);
	glCompileShader(shaderRef);
	return shaderRef;
}

bool checkShaderCompileStatus(GLuint shader) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "Shader compilation failed\n" << infoLog << endl;
                return false;
	}
	return true;
}

bool checkShaderProgramLinkStatus(GLuint shaderProgram) {
    GLint success;
    glGetProgramiv(shaderProgram,  GL_LINK_STATUS, &success);
    if(!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram,  512,  NULL,  infoLog);
        cout << "Shader program linking failed\n" << infoLog << endl;
        return false;
    }
    return true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
