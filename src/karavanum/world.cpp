#include <karavanum/world.hpp>

World::World(std::string f_path, std::string v_path, std::string g_path, float naspect) {
	is_first = true;
	view_point = glm::vec2(0.0f);
	view_point_z = 0.0f;
	zoom = 1.0f;
	aspect = naspect;

	shader.init_shader_program();
	shader.attach_shader("FRAGMENT", f_path.c_str());
	shader.attach_shader("GEOMETRY", g_path.c_str());
	shader.attach_shader("VERTEX", v_path.c_str());
	shader.create_shader_program();
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ssbo);
}
World::~World() {
	glDeleteBuffers(1, &ssbo);
	glDeleteBuffers(1, &vao);
}

// dodelat nada tut poka zaglushka
void World::gen_chunk(glm::vec2 chunk_pos, chunk_t& chunk) {
	chunk.x = (int)chunk_pos.x; chunk.y = (int)chunk_pos.y;

	for (unsigned int i = 0; i < 32; i++) {
		for (unsigned int j = 0; j < 32; j++) {
			float prl = glm::simplex(glm::vec2(i/256.0f + chunk_pos.x/8.0f, j/256.0f + chunk_pos.y/8.0f));
			chunk.raw[i * 32 + j] = (tile_t){i, j, (int8_t)(prl * 8.0f), 0};
		}
	}
}
void World::gen_world() {
	chunk_t ch;

	// does old and new boxes colliding
	if (((left_point.x > last_left.x && right_point.x < last_left.x)||
		 (left_point.x > last_right.x && right_point.x < last_right.x)) 
		  &&
		((left_point.y > last_left.y && right_point.y < last_left.y)||
		 (left_point.y > last_right.y && right_point.y < last_right.y)) && !is_first) {
		float min_x = glm::min(left_point.x, last_left.x);
		float min_y = glm::min(left_point.y, last_left.y);
		
		return;
	}
	// is it first time rendering or something
	chunks.clear();

	glm::vec2 left_point = glm::vec2(-0.5f * zoom * aspect, -0.5f * zoom) - view_point;
	glm::vec2 right_point =glm::vec2(0.5f * zoom * aspect, 0.5f * zoom) - view_point;

	std::vector<glm::vec2> gen_coords;
	std::vector<glm::vec2> free_coords;

	// x * 0.03125 = x / 32.0
	float x_end = glm::ceil(right_point.x * 0.03125) + 2;
	float y_end = glm::ceil(right_point.y * 0.03125) + 2;
	for (int i = glm::floor(left_point.x * 0.03125) - 2; i < x_end; i++) {
		for (int j = glm::floor(left_point.y * 0.03125) - 2; j < y_end; j++) {
			chunks.push_back(ch);
			gen_chunk(glm::vec2(i, j), chunks[chunks.size()-1]);
		}
	}
	is_first = false;
}

void World::draw() {
	shader.execute();
	
	for (auto& ch : chunks) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, ch.raw.size() * sizeof(tile_t), ch.raw.data(), GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	
		shader.set_uniform("chunk_position", glm::vec2(ch.x, ch.y));
		shader.set_uniform("view_point", view_point);
		shader.set_uniform("view_z", view_point_z);
		shader.set_uniform("zoom", 1.0f/zoom);
		shader.set_uniform("aspect", aspect);

		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, 1024);
	}
}
