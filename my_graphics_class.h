#pragma once
#ifndef MY_GRAPHICS_CLASS_
#define MY_GRAPHICS_CLASS_
#include <cmath>

class Geometry;

class Vector3 {
private:
	double m_x, m_y, m_z;
public:
	Vector3(double x = 0, double y = 0, double z = 0);
	double vec_length_();
	double vec_sqr_length_();
	double get_vec_x_();
	double get_vec_y_();
	double get_vec_z_();
	Vector3 normalize_vec_();
	Vector3 get_negate_();
	Vector3 operator+(Vector3 com);
	Vector3 operator-(Vector3 com);
	Vector3 operator/(double com);
	Vector3 operator*(double com);
	Vector3 &operator=(Vector3 com);
	double dot_product_(Vector3 vec);
	Vector3 cross_product_(Vector3 vec);
};

class Ray3 {
private:
	Vector3 m_origin, m_direction;
public:
	Ray3(Vector3 vec, Vector3 dir);
	Vector3 get_point_(double t);
	Vector3 get_origin_();
	Vector3 get_direction_();
};

class IntersectResult {
public:
	Geometry *p_geometry = 0;
	double distance;
	Vector3 position = Vector3();
	Vector3 normal = Vector3();
};

class Geometry {
public:
	Geometry() {}
	IntersectResult intersect_(Ray3) {};
	virtual ~Geometry() = 0 {};
};

class Sphere : public Geometry{
private:
	Vector3 m_center;
	double m_radius, m_sqr_radius;
public:
	Sphere(Vector3 vec, double r);
	IntersectResult intersect_(Ray3);
};

class PerspectiveCamera {
private:
	Vector3 m_eye, m_front, m_up, m_right;
	double m_fov_scale;
public:
	PerspectiveCamera(Vector3 eye, Vector3 front, Vector3 up, double fov);
	Ray3 generate_ray_(double x, double y);
};

#endif