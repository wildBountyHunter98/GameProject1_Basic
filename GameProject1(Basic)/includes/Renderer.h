#pragma once
internal void
Render_Background(u32 bg_color) {
	u32* pixel = (u32*)render_state.memory;
	for (int h = 0; h < render_state.height; h++) {
		for (int w = 0; w < render_state.width; w++) {
			*pixel++ = bg_color;
		}
	}
}

internal void
Clear_Screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int h = 0; h < render_state.height; h++) {
		for (int w = 0; w < render_state.width; w++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int pos_x, int pos_y, int width, int height, u32 color) {

	pos_x = clamp(render_state.width, 0, pos_x);
	width = clamp(render_state.width, 0, width);
	pos_y = clamp(render_state.height, 0, pos_y);
	height = clamp(render_state.height, 0, height);

	for (int y = pos_y; y < height; y++) {
		u32* pixel = (u32*)render_state.memory + pos_x + y * render_state.width;
		for (int x = pos_x; x < width; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float pos_x, float pos_y, float width, float height, u32 color) {
	pos_x *= render_state.height * render_scale;
	pos_y *= render_state.height * render_scale;
	width *= render_state.height * render_scale;
	height *= render_state.height * render_scale;

	// Set 0,0  as center of the screen
	pos_x += render_state.width / 2.f;
	pos_y += render_state.height / 2.f;

	// Change to pixels
	int x0 = pos_x - width;
	int x1 = pos_x + width;
	int y0 = pos_y - height;
	int y1 = pos_y + height;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}