#include <engine/shader.hpp>

std::string Shader::load_file(const char* path) {
	FILE* f = fopen(path, "r");
	if (f == NULL) {
		std::cout << "ERROR: can not find file " << path << std::endl;
		exit(-1);
	}

	std::string ret = ""; int c;
	while ((c = fgetc(f)) != EOF) {
		ret.push_back(c);
	}
	fclose(f);

	return ret;
}
void Shader::check_errors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::attach_shader(std::string type, const char* path) {
	std::string code = load_file(path).c_str();
	const char* cstr_code = code.c_str();
	
	if (type == "VERTEX") {
		unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &cstr_code, NULL);
		glCompileShader(vert);
		check_errors(vert, "VERTEX");
		glAttachShader(program, vert);
		
		tmp_shaders.push_back(vert);
	}
	else if (type == "FRAGMENT") {
		unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &cstr_code, NULL);
		glCompileShader(frag);
		check_errors(frag, "FRAGMENT");
		glAttachShader(program, frag);
		
		tmp_shaders.push_back(frag);
	}
	else if (type == "GEOMETRY") {
		unsigned int geom = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geom, 1, &cstr_code, NULL);
		glCompileShader(geom);
		check_errors(geom, "GEOMETRY");
		glAttachShader(program, geom);
		
		tmp_shaders.push_back(geom);
	}
	else if (type == "COMPUTE") {
		unsigned int comp = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(comp, 1, &cstr_code, NULL);
		glCompileShader(comp);
		check_errors(comp, "COMPUTE");
		glAttachShader(program, comp);

		tmp_shaders.push_back(comp);
	}
	else {
		std::cout << "ERROR::SHADER unknown shader type: " << type << "\n";
	}
}

void Shader::init_shader_program() {
	program = glCreateProgram();
}

void Shader::create_shader_program() {
	glLinkProgram(program);
	check_errors(program, "PROGRAM");
	
	for (unsigned int sh : tmp_shaders) {
		glDeleteShader(sh);
	}
	tmp_shaders.clear();
}
void Shader::execute() {
	glUseProgram(program);
}
void Shader::compute_execute(unsigned int wgx, unsigned int wgy, unsigned int wgz) {
	execute();
	glDispatchCompute(wgx, wgy, wgz);
}
void Shader::set_uniform(std::string name, glm::mat4 var){ 
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(var));
}
void Shader::set_uniform(std::string name, glm::vec3 var){ 
	glUniform3f(glGetUniformLocation(program, name.c_str()), var.x, var.y, var.z);
}
void Shader::set_uniform(std::string name, glm::vec2 var){ 
	glUniform2f(glGetUniformLocation(program, name.c_str()), var.x, var.y);
}
void Shader::set_uniform(std::string name, float var){ 
	glUniform1f(glGetUniformLocation(program, name.c_str()), var); 
}
void Shader::set_uniform(std::string name, int var){ 
	glUniform1i(glGetUniformLocation(program, name.c_str()), var); 
}
