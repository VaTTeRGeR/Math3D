#include <quaternion.h>
#include <vector3.h>

Quaternion& Quaternion::idt() {
	x = y = z = 0.0;
	w = 1.0;
	
	return *this;
}

Quaternion& Quaternion::set(const Quaternion& q) {
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	
	return *this;
}

Quaternion& Quaternion::set(float x, float y, float z, float w) {
	this -> x = x;
	this -> y = y;
	this -> z = z;
	this -> w = w;
	
	return *this;
}

Quaternion& Quaternion::conjugate() {
	x = -x;
	y = -y;
	z = -z;
	
	return *this;
}

float Quaternion::len() {
	return sqrt(x*x + y*y + z*z + w*w);
}

Quaternion& Quaternion::nor() {
	float len = this -> len();
	if(len != 0.0 && !(abs(len - 1.0) <= Q_FP_ERR)) {
		len = sqrt(len);
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}
	return *this;
}

Quaternion& Quaternion::mul(const Quaternion& q) {
	float nX = w * q.x + x * q.w + y * q.z - z * q.y;
	float nY = w * q.y + y * q.w + z * q.x - x * q.z;
	float nZ = w * q.z + z * q.w + x * q.y - y * q.x;
	float nW = w * q.w - x * q.x - y * q.y - z * q.z;
	x = nX;
	y = nY;
	z = nZ;
	w = nW;
	
	return *this;
}

Quaternion& Quaternion::mulLeft(const Quaternion& q) {
	float nX = q.w * x + q.x * w + q.y * z - q.z * y;
	float nY = q.w * y + q.y * w + q.z * x - q.x * z;
	float nZ = q.w * z + q.z * w + q.x * y - q.y * x;
	float nW = q.w * w - q.x * x - q.y * y - q.z * z;
	x = nX;
	y = nY;
	z = nZ;
	w = nW;

	return *this;
}

Quaternion& Quaternion::setFromAxis(Vector3& v, float angle) {
	angle *= Q_DEGRAD;
	float d = v.len();
	  
	if(d == 0.0) {
	  idt();
	} else {
		d = 1.0/d;

		float l_ang = angle < 0.0 ? (Q_PI2 - fmod(-angle, Q_PI2)) : fmod(angle, Q_PI2);
		float l_sin = sin(l_ang / 2.0);
		float l_cos = cos(l_ang / 2.0);

		set(d * v.x * l_sin, d * v.y * l_sin, d * v.z * l_sin, l_cos);
		nor();
	}
	return *this;
}

Quaternion& Quaternion::setFromCross(Vector3& v0, Vector3& v1) {
	float dot = v0.dot(v1);
	dot = min(dot, 1.0);
	dot = max(dot, -1.0);

	float angle = acos(dot);

	tv0.x = v0.y * v1.z - v0.z * v1.y;
	tv0.y = v0.z * v1.x - v0.x * v1.z;
	tv0.z = v0.x * v1.y - v0.y * v1.x;

	this -> setFromAxis(tv0, angle * Q_RADDEG);
	
	return *this;
}
