#include <iostream>

#include <engine/shader.hpp>

#include <glm/gtc/noise.hpp>

struct tile_t {
	unsigned int x : 5;
	unsigned int y : 5;
	int z : 8;
	unsigned int tile_id : 14;
}; // 32 bit

struct chunk_t {
	std::array<tile_t, 32 * 32> raw;
	int32_t x;
	int32_t y;
};

class World final {
private:
	Shader shader;
	float aspect;
	std::vector<chunk_t> chunks;

	unsigned int ssbo, vao;
public:
	glm::vec2 view_point;
	int8_t view_point_z;
	float zoom;
	
	World(std::string f_path, std::string v_path, std::string g_path, float naspect);
	~World();

	void move_camera();
	void gen_chunk(glm::vec2 chunk_pos, chunk_t& chunk);
	void gen_world();
	void draw();
};
