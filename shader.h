#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include glew to get all the required OpenGL headers

class Shader
{
private:
        GLchar* readShaderFromFile(const GLchar* shaderFilePath) {
            std::string *shaderString;
            std::ifstream shaderFile;
            shaderFile.exceptions(std::ifstream::badbit);
            try {
                shaderFile.open(shaderFilePath);
                std::stringstream shaderStream;
                shaderStream << shaderFile.rdbuf();
                shaderFile.close();
                shaderString = new std::string(shaderStream.str());
            } catch(std::ifstream::failure e) {
                std::cout << "Error occurred while trying to read shader file:"  << shaderFilePath << std::endl;
                return NULL;
            }
            log("Shader code read from file:");
            log(shaderString->c_str());
            GLchar* shaderCode = shaderString->c_str();
            return shaderCode;
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
                std::cout << "Shader compilation failed\n" << infoLog << std::endl;
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
        	 std::cout << "Shader program linking failed\n" << infoLog << std::endl;
        	 return false;
    	    }
    	    return true;
	}
	
	void log(const char *logString) {
            std::cout << logString << std::endl;
        }

public:
  	// The program ID
	GLuint Program;
	bool isValid = false;
        
	// Constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
            GLchar *vertexShaderCode = readShaderFromFile(vertexPath);
            GLchar *fragmentShaderCode = readShaderFromFile(fragmentPath);
            if(vertexShaderCode == NULL) {
                return;
            }
            if(fragmentShaderCode == NULL) {
                return;
            }
            log("Successfully read shader code from files");
            log("Vertex shader: ");
            log(vertexShaderCode);
            log("Fragment shader: ");
            log(fragmentShaderCode);
            const GLuint vertexShader = createShader(GL_VERTEX_SHADER, &vertexShaderCode);
            if(!checkShaderCompileStatus(vertexShader)) {
                return;
            }
            log("Successfully compiled vertex shader");
            const GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, &fragmentShaderCode);
            if(!checkShaderCompileStatus(fragmentShader)) {
                return;
            }
            log("Successfully compiled fragment shader");
            this->Program = glCreateProgram();
	    glAttachShader(this->Program, vertexShader);
	    glAttachShader(this->Program, fragmentShader);
	    glLinkProgram(this->Program);
            log("Successfully attached and linked shaders to program");
	    if(!checkShaderProgramLinkStatus(this->Program)) {
	    	return;
	    }

	    isValid = true;

	    glDeleteShader(vertexShader);
	    glDeleteShader(fragmentShader);
        }

  	// Use the program
  	void Use() {
	    glUseProgram(this->Program);
	}
};
  
#endif
