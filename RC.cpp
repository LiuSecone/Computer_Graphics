#include <iostream>
#include "graphics.h"
#include "my_graphics_class.h"

void output_depth_graphic();

int main() {
	output_depth_graphic();
	return 0;
}

void output_depth_graphic() {
	int h_pixel = 512, w_pixel = 512;
	initgraph(w_pixel, h_pixel);
	Sphere s1(Vector3(0, 0, -10), 10);
	PerspectiveCamera cam(Vector3(0, 0, 10), Vector3(0, 0, -1), Vector3(0, 1, 0), 90);
	int max_depth = 20;
	for (int y = 0; y < h_pixel; ++y) {
		double sy = 1 - double(y) / h_pixel;
		for (int x = 0; x < w_pixel; ++x) {
			double sx = double(x) / w_pixel;
			Ray3 ray = cam.generate_ray_(sx, sy);
			IntersectResult result = s1.intersect_(ray);
			if (result.p_geometry) {
				std::cout << sx << ' ' << sy << std::endl;
				int pixel_depth = int((result.distance / max_depth) * 255);
				if (pixel_depth > 255) {
					pixel_depth = 0;
				}
				else {
					pixel_depth = 255 - pixel_depth;
				}
				/*
				int pixel_color = (result.normal.get_vec_x_() + 1) * 128;
				pixel_color <<= 8;
				pixel_color += (result.normal.get_vec_y_() + 1) * 128;
				pixel_color <<= 8;
				pixel_color += (result.normal.get_vec_z_() + 1) * 128;
				*/
				int pixel_color = pixel_depth;
				pixel_color <<= 8;
				pixel_color += pixel_depth;
				pixel_color <<= 8;
				pixel_color += pixel_depth;
				putpixel(x, y, pixel_color);
			}
		}
	}
	system("pause");
	closegraph();
	return;
}