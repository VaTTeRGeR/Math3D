#ifndef QUATERNION_H
#define QUATERNION_H

#include <Arduino.h>

#define Q_FP_ERR                0.000001

#define Q_PI                    3.141592
#define Q_PI2                   6.283185

#define Q_RADDEG                57.29577
#define Q_DEGRAD                0.01745329

class Vector3;

struct Quaternion {
	static Vector3 tv0;
	
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float w = 1.0;
	
	Quaternion&	idt();
	Quaternion&	set(const Quaternion& q);
	Quaternion&	set(float x, float y, float z, float w);
	
	Quaternion&	conjugate();
	Quaternion&	nor();
	float		len();
	
	Quaternion&	mul(const Quaternion& q);
	Quaternion&	mulLeft(const Quaternion& q);
	
	Quaternion& setFromAxis(Vector3& v, float angle);
	Quaternion& setFromCross(Vector3& v0, Vector3& v1);
};

#endif