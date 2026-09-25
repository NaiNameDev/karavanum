#include <iostream>

#include <iostream>

struct tile_t {
	unsigned int x : 5;
	unsigned int y : 5;
	int z : 8;
	unsigned int tile_id : 14;
}; // 32 bit

struct chunk_t {
	std::array<tile_t, 1024> raw;
	int64_t x;
	int64_t y;
};

class World final {
private:
	glm::vec2 camera_pos;
	int8_t camera_z;
	glm::vec2 camera_zoom;

	std::vector<chunk_t> chunks;

public:
	draw();
};
