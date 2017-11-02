#include <cmath>
//#include <iostream>
#include "my_graphics_class.h"

Vector3::Vector3(double x, double y, double z) {
	m_x = x;
	m_y = y;
	m_z = z;
	return;
}

double Vector3::vec_length_() {
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}
double Vector3::vec_sqr_length_() {
	return m_x * m_x + m_y * m_y + m_z * m_z;
}
Vector3 Vector3::normalize_vec_() {
	double length = 1 / this->vec_length_();
	return *this * length;
}
Vector3 Vector3::get_negate_() {
	return *this * -1;
}
Vector3 Vector3::operator+(Vector3 com) {
	Vector3 temp;
	temp.m_x = m_x + com.m_x;
	temp.m_y = m_y + com.m_y;
	temp.m_z = m_z + com.m_z;
	return temp;
}
Vector3 Vector3::operator-(Vector3 com) {
	Vector3 temp;
	temp.m_x = m_x - com.m_x;
	temp.m_y = m_y - com.m_y;
	temp.m_z = m_z - com.m_z;
	return temp;
}
Vector3 Vector3::operator/(double com) {
	Vector3 temp;
	temp.m_x = m_x / com;
	temp.m_y = m_y / com;
	temp.m_z = m_z / com;
	return temp;
}
Vector3 Vector3::operator*(double com) {
	Vector3 temp;
	temp.m_x = m_x * com;
	temp.m_y = m_y * com;
	temp.m_z = m_z * com;
	return temp;
}
Vector3 &Vector3::operator=(Vector3 com) {
	m_x = com.m_x;
	m_y = com.m_y;
	m_z = com.m_z;
	return *this;
}
double Vector3::dot_product_(Vector3 vec) {
	return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
}
Vector3 Vector3::cross_product_(Vector3 vec) {
	Vector3 temp;
	temp.m_x = m_y * vec.m_z - m_z * vec.m_y;
	temp.m_y = m_z * vec.m_x - m_x * vec.m_z;
	temp.m_z = m_x * vec.m_y - m_y * vec.m_x;
	return temp;
}
double Vector3::get_vec_x_() {
	return m_x;
}
double Vector3::get_vec_y_() {
	return m_y;
}
double Vector3::get_vec_z_() {
	return m_z;
}

Ray3::Ray3(Vector3 vec, Vector3 dir) {
	m_origin = vec;
	m_direction = dir;
	return;
}
Vector3 Ray3::get_point_(double t) {
	return m_origin + m_direction * t;
}
Vector3 Ray3::get_origin_() {
	return m_origin;
}
Vector3 Ray3::get_direction_() {
	return m_direction;
}

RgbColor::RgbColor(double r, double g, double b) {
	m_r = r;
	m_g = g;
	m_b = b;
	return;
}
RgbColor RgbColor::operator+(RgbColor com) {
	double r = m_r + com.m_r;
	double g = m_g + com.m_g;
	double b = m_b + com.m_b;
	return RgbColor(r, g, b);
}
RgbColor RgbColor::operator*(RgbColor com) {
	return RgbColor(m_r * com.m_r, m_g * com.m_g, m_b * com.m_b);
}
RgbColor RgbColor::operator*(double com) {
	return RgbColor(m_r * com, m_g * com, m_b * com);
}
RgbColor &RgbColor::operator=(RgbColor com) {
	m_r = com.m_r;
	m_g = com.m_g;
	m_b = com.m_b;
	return *this;
}
double RgbColor::get_r_() {
	return m_r;
}
double RgbColor::get_g_() {
	return m_g;
}
double RgbColor::get_b_() {
	return m_b;
}
int RgbColor::calculate_color_() {
	int color = int((m_r < 1 ? m_r : 1) * 255);
	color <<= 8;
	color += int((m_g < 1 ? m_g : 1) * 255);
	color <<= 8;
	color += int((m_b < 1 ? m_b : 1) * 255);
	return color;
}


RgbColor Material::sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_colorB) {
	return RgbColor();
}
double Material::get_reflectiveness_() {
	return 0;
}

Phong::Phong(RgbColor diffuse, RgbColor specular, double shiness, double reflectiveness) {
	m_diffuse = diffuse;
	m_specular = specular;
	m_shiness = shiness;
	m_reflectiveness = reflectiveness;
}
RgbColor Phong::sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color) {
	double n_dot_l = result.normal.dot_product_(light_direction);
	Vector3 h = (light_direction - ray.get_direction_()).normalize_vec_();
	double n_dot_h = result.normal.dot_product_(h);
	RgbColor diffuse_term = m_diffuse * (n_dot_l > 0 ? n_dot_l : 0);
	RgbColor specular_term = m_specular * pow((n_dot_h > 0 ? n_dot_h : 0), m_shiness);
	return light_color * (diffuse_term + specular_term);
}
double Phong::get_reflectiveness_() {
	return m_reflectiveness;
}

Checker::Checker(double scale, double refelctiveness) {
	m_scale = scale;
	m_reflectiveness = refelctiveness;
	return;
}
RgbColor Checker::sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color) {
	int temp = int(floor(result.position.get_vec_x_() * m_scale) + floor(result.position.get_vec_y_() * m_scale) + floor(result.position.get_vec_z_() * m_scale));
	temp = abs(temp) % 2;
	double n_dot_l = result.normal.dot_product_(light_direction);
	return RgbColor(temp, temp, temp)  * (n_dot_l > 0 ? n_dot_l : 0);
}
double Checker::get_reflectiveness_() {
	return m_reflectiveness;
}

Depth::Depth(double max_depth) {
	m_max_depth = max_depth;
	return;
}

RgbColor Depth::sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color) {
	double pixel_depth = result.distance / m_max_depth;
	if (pixel_depth > 1) {
		pixel_depth = 0;
	}
	else {
		pixel_depth = 1 - pixel_depth;
	}
	return RgbColor(pixel_depth, pixel_depth, pixel_depth);
}

IntersectResult Geometry::intersect_(Ray3 ray) {
	return IntersectResult();
}
Material *Geometry::get_material_() {
	return nullptr;
}

Sphere::Sphere(Vector3 vec, double r, Material *material) {
	m_center = vec;
	m_radius = r;
	m_sqr_radius = r * r;
	m_material = material;
	return;
}
IntersectResult Sphere::intersect_(Ray3 ray) {
	Vector3 v = ray.get_origin_() - m_center;
	double d_dot_v = ray.get_direction_().dot_product_(v);
	IntersectResult intersect_result;
	if (d_dot_v <= 0) {
		double delta = d_dot_v * d_dot_v - v.vec_sqr_length_() + m_sqr_radius;
		if (delta >= 0) {
			intersect_result.p_geometry = this;
			intersect_result.distance = -d_dot_v - sqrt(delta);
			intersect_result.position = ray.get_point_(intersect_result.distance);
			intersect_result.normal = (intersect_result.position - m_center).normalize_vec_();
		}
	}
	return intersect_result;
}
Material *Sphere::get_material_() {
	return m_material;
}

Plane::Plane(Vector3 normal, double distance, Material *material) {
	m_normal = normal.normalize_vec_();
	m_distance = distance;
	m_p_material = material;
	m_position = m_normal * distance;
	return;
}
Material *Plane::get_material_() {
	return m_p_material;
}
IntersectResult Plane::intersect_(Ray3 ray) {
	double a = ray.get_direction_().dot_product_(m_normal);
	IntersectResult result;
	if ((a - 0) < pow(1, -8)) {
		double b = m_normal.dot_product_(m_position - ray.get_origin_());
		result.p_geometry = this;
		result.distance = b / a;
		result.position = ray.get_point_(result.distance);
		if (a < 0) {
			result.normal = m_normal;
		}
		else {
			result.normal = m_normal.get_negate_();
		}
		if (result.distance < 0) {
			result.p_geometry = NULL;
		}
	}
	return result;
}

PerspectiveCamera::PerspectiveCamera(Vector3 eye, Vector3 front, Vector3 up, double fov) {
	m_eye = eye;
	m_front = front.normalize_vec_();
	m_up = up.normalize_vec_();
	m_right = front.cross_product_(up).normalize_vec_();
	m_fov_scale = tan(fov * 0.5 * 3.14159265 / 180) * 2;
}
Ray3 PerspectiveCamera::generate_ray_(double x, double y) {
	Vector3 r = m_right * (x - 0.5) * m_fov_scale;
	Vector3 u = m_up * (y - 0.5) * m_fov_scale;
	return (Ray3(m_eye, (m_front + r + u).normalize_vec_()));
}

IntersectResult Scene::intersect_(Ray3 ray) {
	IntersectResult result;
	for (auto iter = m_union.begin(); iter != m_union.end(); ++iter) {
		IntersectResult temp = (*iter)->intersect_(ray);
		if (temp.p_geometry && (result.distance < 0 || result.distance >  temp.distance)) {
			result = temp;
		}
	}
	return result;
}
Geometry *Scene::add_geometry_(Geometry *geometry) {
	m_union.push_back(geometry);
	return geometry;
}
void Scene::clear_scene_() {
	m_union.clear();
	return;
}