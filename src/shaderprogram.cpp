#include <shaderprogram.hpp>
#include <initializer_list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::Shader::Shader(unsigned int _type) : type(_type)
{
}

void ShaderProgram::Shader::compileFrom(const char *shaderSource) 
{
    id = glCreateShader(type);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);

    // Refactor into error masnager or something
    int success;
    char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
    	glGetShaderInfoLog(id, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::compile()
{ 
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.id);
    glAttachShader(shaderProgram, fragmentShader.id);
    glLinkProgram(shaderProgram);

    // Refactor into error manager or something
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
}


ShaderProgram::ShaderProgram(const std::string vertexPath, const std::string fragmentPath) : vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER) {
    // Retrieve the vertex/fragment source code from filePath
    std::string vCode, fCode;
    std::ifstream vShaderFile, fShaderFile;
    // Ensure that steams will throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        vShaderFile.close();
        fShaderFile.close();
        vCode = vShaderStream.str();
        fCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_READ_FAILURE" << std::endl;
    }
    fragmentShader.compileFrom(fCode.c_str());
    vertexShader.compileFrom(vCode.c_str());
    compile();
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

void ShaderProgram::setUniform(std::string uniformName, glm::vec4 x)
{
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4f(uniformLocation, x[0], x[1], x[2], x[3]);
}

void ShaderProgram::setUniform(std::string uniformName, float x) {
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1f(uniformLocation, x);
}

void ShaderProgram::setUniform(std::string uniformName, glm::mat4 x) {
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(x));
}

void ShaderProgram::setUniform(std::string uniformName, glm::vec2 x) {
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform2f(uniformLocation, x[0], x[1]);
}