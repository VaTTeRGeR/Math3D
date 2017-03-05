#ifndef VECTOR3_H
#define VECTOR3_H

#include <Arduino.h>

#define Q_FP_ERR                0.000001

#define Q_PI                    3.141592
#define Q_PI2                   6.283185

#define Q_RADDEG                57.29577
#define Q_DEGRAD                0.01745329
class Quaternion;

struct Vector3 {
	static Quaternion tq0;
	static Quaternion tq1;

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	Vector3& set(const Vector3& v);
	Vector3& set(float x, float y, float z);
	Vector3& scl(float alpha);
	Vector3& nor();

	float dot(const Vector3& v);
	float len();
	
	Vector3& transform(const Quaternion& q);
	
	Vector3& lerp(Vector3& v, float alpha);
	Vector3& slerp(Vector3& v, float alpha);
};

#endif