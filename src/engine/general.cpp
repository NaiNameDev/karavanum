#include <engine/general.hpp>

bool is_inside_rect(glm::vec2 point, glm::vec2 left_down, glm::vec2 right_up) {
	return (left_down.x <= point.x && right_up.x >= point.x) && (left_down.y <= point.y && right_up.y >= point.y);
}
