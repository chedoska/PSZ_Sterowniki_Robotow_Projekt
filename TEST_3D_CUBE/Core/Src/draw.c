#include "draw.h"

uint16_t color_array[] = {0x001f, 0x0be4, 0xeca0, 0xe816, 0xf880, 0x3475};

void draw_demo_page(uint16_t *canvas){
	for(int i = 0; i < 200 * 200; i ++){
		canvas[i] = 0xffff;
	}
}

void draw_square_at(uint16_t *canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height){
	uint8_t x_start = x;
	uint8_t x_end = x + width;
	uint8_t y_start = y;
	uint8_t y_end = y + height;

	for(int m_x = x_start; m_x < x_end; m_x++){
		for(int m_y = y_start; m_y < y_end; m_y++){
			DRAW_PIXEL_AT(canvas,m_x,m_y,0xe8bb);
		}
	}
}

void draw_square_at_point(uint16_t *canvas, point_3d *point, uint8_t width, uint8_t height){
	proxy_point_3d proxy_point = apply_rotation_to_point(point);
	uint8_t x_start = proxy_point.x;
	uint8_t x_end = x_start + width;
	uint8_t y_start = proxy_point.y;
	uint8_t y_end = y_start + height;

	for(int m_x = x_start; m_x < x_end; m_x++){
		for(int m_y = y_start; m_y < y_end; m_y++){
			DRAW_PIXEL_AT(canvas,m_x,m_y,0xe8bb);
		}
	}
}

void draw_vertex(uint16_t *canvas, vertex_3d *vertex, uint16_t color){
	proxy_point_3d proxy_a = apply_rotation_to_point(&(vertex->a));
	proxy_point_3d proxy_b = apply_rotation_to_point(&(vertex->b));
	proxy_point_3d proxy_c = apply_rotation_to_point(&(vertex->c));

	if(abs(proxy_a.x - proxy_b.x) + abs(proxy_a.y - proxy_b.y) == CUBE_SIZE)
	draw_line(canvas, proxy_a.x, proxy_a.y, proxy_b.x, proxy_b.y, color);
	draw_line(canvas, proxy_a.x, proxy_a.y, proxy_c.x, proxy_c.y, color);
	draw_line(canvas, proxy_c.x, proxy_c.y, proxy_b.x, proxy_b.y, color);
}

void draw_line(uint16_t *canvas, int16_t ax, int16_t ay, int16_t bx, int16_t by, uint16_t color){
	if(abs(ax - bx) > abs(ay - by)){
		int8_t dx = ax < bx ? 1 : -1;
		float y = ay;
		float dy = (by - ay) / (float) abs(bx - ax);

		for(uint8_t x = ax; x != bx; x += dx){
			DRAW_PIXEL_AT(canvas,x,(int)y,color);
			y += dy;
		}
	}
	else{
		int8_t dy = ay < by ? 1 : -1;
		float x = ax;
		float dx = (bx - ax) / (float) abs(by - ay);

		for(uint8_t y = ay; y != by; y += dy){
			DRAW_PIXEL_AT(canvas,(int)x,y,color);
			x += dx;
		}
	}
}

void draw_cube(uint16_t *canvas){
	for(int i = 0; i < VERTEX_COUNT; i++){
		float normal_z = apply_rotation_to_point_only_z(&(cube_model[i].normal_vec));
		if(normal_z > 0) continue;
		draw_vertex(canvas, &(cube_model[i]), color_array[i%6]);
	}
}




