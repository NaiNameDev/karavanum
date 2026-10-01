#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec2 chunk_position;
uniform vec2 view_point;
uniform float zoom;
uniform float aspect;

flat in uvec2 orig_pos[];
flat in int orig_z[];
flat in uint id[];

flat out int f_orig_z;
flat out uint f_id;

void main() {
	f_id = id[0];
	f_orig_z = orig_z[0];

	gl_Position = vec4((orig_pos[0] + (chunk_position * 32.0f + view_point)) * zoom, 0.0f, 1.0f);
	gl_Position.y *= aspect;
	EmitVertex();

	gl_Position = vec4((orig_pos[0] + vec2(0.0f, 1.0f) + (chunk_position * 32.0f + view_point)) * zoom, 0.0f, 1.0f);
	gl_Position.y *= aspect;
    EmitVertex();
	
	gl_Position = vec4((orig_pos[0] + vec2(1.0f, 0.0f) + (chunk_position * 32.0f + view_point)) * zoom, 0.0f, 1.0f);
	gl_Position.y *= aspect;
    EmitVertex();
	
	gl_Position = vec4((orig_pos[0] + vec2(1.0f, 1.0f) + (chunk_position * 32.0f + view_point)) * zoom, 0.0f, 1.0f);
	gl_Position.y *= aspect;
    EmitVertex();

	EndPrimitive();
}
