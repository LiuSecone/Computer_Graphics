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

Sphere::Sphere(Vector3 vec, double r) {
	m_center = vec;
	m_radius = r;
	m_sqr_radius = r * r;
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