#include <iostream>

#include <glm/glm.hpp>

#include <engine/engine.hpp>

Engine engine(1280, 720, "Karavanum");

void on_ready() {
}
void process(float delta) {
	//engine.print_fps_info();
}
void on_quit() {
	std::cout << "bye!\n";
}

int main() {
	engine.ready_signal.connect(on_ready);
	engine.process_signal.connect(process);
	engine.quit_signal.connect(on_quit);
	
	engine.run();
}
