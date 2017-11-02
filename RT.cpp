#include <iostream>
#include "graphics.h"
#include "my_graphics_class.h"

//void output_sphere_with_material();
//void output_depth_graphic();
void ray_trace_reflection();
RgbColor ray_trace_recursive(Scene scene, Ray3 ray, int reflect_cnt);

int main() {
	//output_sphere_with_material();
	//output_depth_graphic();
	ray_trace_reflection();
	return 0;
}

void ray_trace_reflection() {
	int h_pixel = 512, w_pixel = 512;
	initgraph(w_pixel, h_pixel);
	Scene scene;
	/*
	Sphere s1(Vector3(-10, 10, -10), 10, new Phong(RgbColor(0, 0, 1), RgbColor(1, 1, 1), 16, 0.25));
	Sphere s2(Vector3(10, 10, -10), 10, new Phong(RgbColor(1, 0, 0), RgbColor(1, 1, 1), 16, 0.25));
	Plane p1(Vector3(0, 1, 0), -20, new Phong(RgbColor(1, 0.75294, 0.79608), RgbColor(1, 1, 1), 16, 0));
	scene.add_geometry_(&s1);
	scene.add_geometry_(&s2);
	scene.add_geometry_(&p1);
	*/
	Sphere s1(Vector3(10, 0, -25), 10, new Phong(RgbColor(0, 0, 1), RgbColor(1, 1, 1), 16, 0.5));
	Sphere s2(Vector3(-10, 0, -25), 5, new Phong(RgbColor(1, 0, 0), RgbColor(1, 1, 1), 16, 0.2));
	Plane p1(Vector3(0, 0, 1), -50, new Checker(0.1, 0.2));
	Plane p2(Vector3(1, 0, 0), -40, new Phong(RgbColor(1, 0.75294, 0.79608), RgbColor(1, 1, 1), 16, 1));
	Plane p3(Vector3(0, 1, 0), 30, new Phong(RgbColor(0.2, 0.2, 0.2), RgbColor(1, 1, 1), 16, 0));
	Plane p4(Vector3(0, 1, 0), -30, new Phong(RgbColor(0, 0.2, 0), RgbColor(1, 1, 1), 16, 0));
	Plane p5(Vector3(1, 0, 0), 40, new Checker(0.1, 0));
	Plane p6(Vector3(0, 0, 1), 30, new Checker(0.1, 0));
	scene.add_geometry_(&s1);
	scene.add_geometry_(&s2);
	scene.add_geometry_(&p1);
	scene.add_geometry_(&p2);
	scene.add_geometry_(&p3);
	scene.add_geometry_(&p4);
	scene.add_geometry_(&p5);
	scene.add_geometry_(&p6);
	PerspectiveCamera cam(Vector3(1, 10, 15), Vector3(0, 0, -1), Vector3(0, 1, 0), 105);
	for (int y = 0; y < h_pixel; ++y) {
		double sy = 1 - double(y) / h_pixel;
		for (int x = 0; x < w_pixel; ++x) {
			double sx = double(x) / w_pixel;
			Ray3 ray = cam.generate_ray_(sx, sy);
			int pixel_color = ray_trace_recursive(scene, ray, 3).calculate_color_();
			putpixel(x, y, pixel_color);
		}
	}
	system("pause");
	closegraph();
	return;
}

RgbColor ray_trace_recursive(Scene scene, Ray3 ray, int reflect_cnt) {
	IntersectResult result = scene.intersect_(ray);
	RgbColor color = RgbColor(0, 0, 0);
	if (result.p_geometry) {
		double reflectiveness = result.p_geometry->get_material_()->get_reflectiveness_();
		color = result.p_geometry->get_material_()->sample_(ray, result, Vector3(1, 1, 1));
		color = color * (1 - reflectiveness);
		if (reflectiveness > 0 && reflect_cnt > 0) {
			Vector3 r = result.normal * ray.get_direction_().dot_product_(result.normal) * -2 + ray.get_direction_();
			RgbColor reflected_color = ray_trace_recursive(scene, Ray3(result.position, r), reflect_cnt - 1);
			color = color + reflected_color * reflectiveness;
		}
	}
	return color;
}

/*
void output_sphere_with_material() {
	int h_pixel = 512, w_pixel = 512;
	initgraph(w_pixel, h_pixel);
	Scene scene;
	Sphere s1(Vector3(0, 10, -10), 10, new Phong(RgbColor(0, 0, 1), RgbColor(1, 1, 1), 16));
	//Sphere s1(Vector3(0, 0, -10), 10, new Checker(1, 0));
	//Sphere s1(Vector3(0, 0, -10), 10, new Depth(20));
	Plane p1(Vector3(0, 1, 0), 0, new Checker(0.2, 0));
	scene.add_geometry_(&s1);
	scene.add_geometry_(&p1);
	PerspectiveCamera cam(Vector3(0, 10, 15), Vector3(0, 0, -1), Vector3(0, 1, 0), 90);
	for (int y = 0; y < h_pixel; ++y) {
		double sy = 1 - double(y) / h_pixel;
		for (int x = 0; x < w_pixel; ++x) {
			double sx = double(x) / w_pixel;
			Ray3 ray = cam.generate_ray_(sx, sy);

			int pixel_color;
			putpixel(x, y, pixel_color);
		}
	}
	system("pause");
	closegraph();
	return;
}
/*
void output_depth_graphic() {
	int h_pixel = 512, w_pixel = 512;
	initgraph(w_pixel, h_pixel);
	Sphere s1(Vector3(0, 0, -10), 10, new Depth(20));
	PerspectiveCamera cam(Vector3(0, 0, 10), Vector3(0, 0, -1), Vector3(0, 1, 0), 105);
	int max_depth = 20;
	for (int y = 0; y < h_pixel; ++y) {
		double sy = 1 - double(y) / h_pixel;
		for (int x = 0; x < w_pixel; ++x) {
			double sx = double(x) / w_pixel;
			Ray3 ray = cam.generate_ray_(sx, sy);
			IntersectResult result = s1.intersect_(ray);
			if (result.p_geometry) {
				std::cout << sx << ' ' << sy << std::endl;
				double pixel_depth = result.distance / max_depth;
				if (pixel_depth > 1) {
					pixel_depth = 0;
				}
				else {
					pixel_depth = 1 - pixel_depth;
				}
				int pixel_color = RgbColor((result.normal.get_vec_x_() + 1) / 2, (result.normal.get_vec_y_() + 1) / 2, (result.normal.get_vec_z_() + 1) / 2).calculate_color_();
				putpixel(x, y, pixel_color);
				/*
				int pixel_color = (result.normal.get_vec_x_() + 1) * 128;
				pixel_color <<= 8;
				pixel_color += (result.normal.get_vec_y_() + 1) * 128;
				pixel_color <<= 8;
				pixel_color += (result.normal.get_vec_z_() + 1) * 128;
				
			}
		}
	}
	system("pause");
	closegraph();
	return;
}
*/