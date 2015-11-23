#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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
	glClearColor(0.7f, 0.6f, 0.0f, 0.9f);

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
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
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
        
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        bool shaderProgramLinkStatus = checkShaderProgramLinkStatus(shaderProgram);
        glUseProgram(shaderProgram);
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
		GLchar infolog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "Shader compilation failed\n" << infoLog << endl;
	}
	return success;
}

void checkShaderProgramLinkStatus(shaderProgram) {
    glGetProgramiv(shaderProgram,  GL_LINK_STATUS, &success);
    if(!success) {
        glgetProgramInfoLog(shaderProgram,  512,  NULL,  infoLog);
    }
    return success;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


