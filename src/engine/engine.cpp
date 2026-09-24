#include <engine/engine.hpp>

Engine::Engine(unsigned int width, unsigned int height, std::string app_name)
	: main_window(width, height, app_name) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	main_window.create_window();
	main_window.make_current();
	glfwSetCursorPosCallback(main_window.glfw_window, [](GLFWwindow* win, double x, double y) {
		global_mouse_event.emit(x, y);
		global_mouse_position = glm::vec2(x, y);
	});
	glfwSetFramebufferSizeCallback(main_window.glfw_window, [](GLFWwindow* win, int w, int h){glViewport(0, 0, w, h);});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		exit(1);
	}
	
	glfwSetWindowSize(main_window.glfw_window, main_window.width, main_window.height);
	
	last = glfwGetTime(); max_fps = 0.0d; all_fps = 0.0d; frame_cnt = 0;
}

Engine::~Engine() {
	glfwTerminate();
}

void Engine::run() {
	ready_signal.emit();
	while(!main_window.should_close()) {
		current = glfwGetTime();
		delta = current - last;
		last = current;

		main_window.clear();
		
		process_signal.emit(delta);

		main_window.swap_buffers();
	}
	quit_signal.emit();
}

void Engine::print_fps_info() {
	if (delta > 0.001f) {
		std::cout << "FPS: " << 1.0f / delta << ", MAX_FPS: " << max_fps << ", AVG_FPS: " << all_fps / frame_cnt << ", DELTA: " << delta << "\n";
		if (1.0f/delta > max_fps) max_fps = (double)(1.0f/delta);
		frame_cnt++; all_fps += 1.0f/delta;
	}
}
