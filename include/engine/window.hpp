#pragma once

#include <unordered_map>
#include <iostream>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	GLFWwindow* glfw_window;
	std::unordered_map<unsigned int, bool> key_map;
	
	unsigned int width, height;
	std::string name;
	
	Window(unsigned int nwidth, unsigned int nheight, std::string nname);
	~Window();

	void create_window();
	void make_current();
	void clear();
	void swap_buffers();
	bool should_close();
	bool is_action_pressed(unsigned int action);
	bool is_action_just_pressed(unsigned int action);
};
