#pragma once

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <engine/window.hpp>
#include <engine/signal.hpp>

class Engine final {
private:
	double last; double current; double max_fps; double all_fps; unsigned int frame_cnt; float delta;

public:
	Window main_window;

	static inline Signal<double, double> global_mouse_event;
	static inline glm::vec2 global_mouse_position;

	Engine(unsigned int width, unsigned int height, std::string app_name);
	~Engine();

	Signal<> ready_signal;
	Signal<float> process_signal;
	Signal<> quit_signal;
	void run();

	void print_fps_info();
};
