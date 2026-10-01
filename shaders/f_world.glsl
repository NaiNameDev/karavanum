#version 430 core

out vec4 out_color;

flat in int f_orig_z;
flat in uint f_id;

uniform int view_z;

void main() {
	if (f_orig_z > view_z) {
		out_color = vec4(0.0f);
		return;
	}
	
	out_color = vec4(1.0f, 1.0f, 1.0f, 1.0);
	
	if (view_z - f_orig_z > 10) {
		out_color.xyz *= 0.3;
	}
	if (view_z - f_orig_z > 20) {
		out_color.xyz *= 0.6;
	}
	out_color.xyz *= float((f_orig_z - view_z) + 255.0f)/255.0f;
}
