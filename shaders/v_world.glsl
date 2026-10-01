#version 430 core

layout(std430, binding = 0) readonly buffer chunk_buffer {
    uint tiles[];
};

flat out uvec2 orig_pos;
flat out int orig_z;
flat out uint id;

void main() {
	orig_pos = uvec2((tiles[gl_VertexID]) & 31u, (tiles[gl_VertexID] >> 5u) & 31u);
	orig_z = (int(tiles[gl_VertexID] >> 10)) & 255;
	orig_z = (orig_z << 24) >> 24;
	id = (tiles[gl_VertexID] >> 18u) & 0x3FFFu;

	gl_Position = vec4(0.0);
}
