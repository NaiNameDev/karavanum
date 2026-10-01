#include <iostream>

#include <engine/engine.hpp>

#include <karavanum/world.hpp>

Engine engine(1280, 720, "Karavanum");
World world("shaders/f_world.glsl", "shaders/v_world.glsl", "shaders/g_world.glsl", 16.0f/9.0f);

void on_ready() {
	std::cout << "start!\n";
	
	world.gen_world();
}
void process(float delta) {
	//engine.print_fps_info();
	
	if (engine.main_window.is_action_pressed(GLFW_KEY_W)) world.view_point -= glm::vec2(0.0f, 0.01f) * (world.zoom);
	if (engine.main_window.is_action_pressed(GLFW_KEY_S)) world.view_point -= glm::vec2(0.0f, -0.01f) * (world.zoom);
	if (engine.main_window.is_action_pressed(GLFW_KEY_A)) world.view_point -= glm::vec2(-0.01f, 0.0f) * (world.zoom);
	if (engine.main_window.is_action_pressed(GLFW_KEY_D)) world.view_point -= glm::vec2(0.01f, 0.0f) * (world.zoom);
	
	if (engine.main_window.is_action_pressed(GLFW_KEY_E)) world.zoom += 0.03f;
	if (engine.main_window.is_action_pressed(GLFW_KEY_Q)) world.zoom -= 0.03f;
	
	if (engine.main_window.is_action_just_pressed(GLFW_KEY_C)) world.view_point_z -= 1;
	if (engine.main_window.is_action_just_pressed(GLFW_KEY_V)) world.view_point_z += 1;
	
	world.zoom = glm::clamp(world.zoom, 1.0f, 30.0f);
	//std::cout << world.zoom << "\n";
	world.draw();
}
void on_quit() {
	std::cout << "end!\n";
}

int main() {
	engine.ready_signal.connect(on_ready);
	engine.process_signal.connect(process);
	engine.quit_signal.connect(on_quit);
	
	engine.run();
}
