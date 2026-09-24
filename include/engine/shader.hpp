#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	std::vector<unsigned int> tmp_shaders;
	std::string load_file(const char* path);
	void check_errors(unsigned int shader, std::string type);

public:
	unsigned int program;
	
	~Shader();

	void init_shader_program();
	void attach_shader(std::string type, const char* path);
	void create_shader_program();
	
	void execute();
	void compute_execute(unsigned int wgx, unsigned int wgy, unsigned int wgz);
	
	void set_uniform(std::string name, glm::mat4 var);
	void set_uniform(std::string name, glm::vec3 var);
	void set_uniform(std::string name, glm::vec2 var);
	void set_uniform(std::string name, float var);
	void set_uniform(std::string name, int var); 
};
