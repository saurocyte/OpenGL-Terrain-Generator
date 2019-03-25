#ifndef SHADERPROGRAM
#define SHADERPROGRAM

#include <array>
#include <glm/glm.hpp>
#include <string>

class ShaderProgram
{
  public:
	ShaderProgram(const std::string vertexPath, const std::string fragmentPath);
	ShaderProgram() = default;
	~ShaderProgram() = default;

	auto use()																						-> void;
	auto setUniform(std::string unfiormName, glm::vec2 x)	-> void;
	auto setUniform(std::string unfiormName, glm::vec4 x)	-> void;
	auto setUniform(std::string unfiormName, glm::mat4 x)	-> void;
	auto setUniform(std::string unfiormName, float x)			-> void;

  private:
	class Shader
	{
		friend class ShaderProgram;

	  public:
		Shader(unsigned int _type);
		~Shader() = default;
		
	  private:
		unsigned int id;
		// Valid type values are: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER
		unsigned int type;
		auto compileFrom(const char *shaderSource)						-> void;

	};

	unsigned int shaderProgram;
	Shader vertexShader;
	Shader fragmentShader;

	// For nicer constructor
	auto compile()																				-> void;
};

#endif