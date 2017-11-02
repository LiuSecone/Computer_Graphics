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
	Geometry *p_geometry;
	double distance;
	Vector3 position = Vector3();
	Vector3 normal = Vector3();
};

class RgbColor {
private:
	double m_r, m_g, m_b;
public:
	RgbColor(double r = 1, double g = 1, double b = 1);
	RgbColor operator+(RgbColor com);
	RgbColor operator*(RgbColor com);
	RgbColor operator*(double com);
	RgbColor &operator=(RgbColor com);
	double get_r_();
	double get_g_();
	double get_b_();
	int calculate_color_();
};

class Material {
public:
	Material() {}
	virtual RgbColor sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color = RgbColor());
	virtual ~Material() = 0 {}
};

class Phong : public Material {
private:
	RgbColor m_diffuse, m_specular;
	double m_shiness, m_reflectiveness;
public:
	Phong(RgbColor diffuse, RgbColor specular, double shiness, double reflectiveness = 0);
	RgbColor sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color = RgbColor());
};

class Checker : public Material {
private:
	double m_scale, m_reflectiveness;
public:
	Checker(double scale, double refelctiveness = 0);
	RgbColor sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color = RgbColor());
};

class Depth : public Material {
private:
	double m_max_depth;
public:
	Depth(double max_depth);
	RgbColor sample_(Ray3 ray, IntersectResult result, Vector3 light_direction, RgbColor light_color = RgbColor());
};

class Geometry {
public:
	Geometry() {}
	virtual IntersectResult intersect_();
	virtual Material *get_material_();
	virtual ~Geometry() = 0 {}
};

class Sphere : public Geometry {
private:
	Vector3 m_center;
	double m_radius, m_sqr_radius;
	Material *m_material;
public:
	Sphere(Vector3 vec, double r, Material *material);
	Material *get_material_();
	IntersectResult intersect_(Ray3 ray);
};

class Plane : public Geometry {
private:
	Vector3 m_normal, m_position;
	double m_distance;
	Material *m_p_material;
public:
	Plane(Vector3 normal, double distance, Material *material);
	Material *get_material_();
	IntersectResult intersect_(Ray3 ray);
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