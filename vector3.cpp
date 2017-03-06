#include <vector3.h>
#include <quaternion.h>

Vector3& Vector3::set(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	
	return *this;
}

Vector3& Vector3::set(float x, float y, float z) {
	this -> x = x;
	this -> y = y;
	this -> z = z;
	
	return *this;
}

Vector3& Vector3::scl(float alpha) {
	x *= alpha;
	y *= alpha;
	z *= alpha;
	
	return *this;
}

Vector3& Vector3::nor() {
	float len = this -> len();
	if(len != 0.0 && !(abs(len - 1.0) <= Q_FP_ERR)) {
		len = sqrt(len);
		x /= len;
		y /= len;
		z /= len;
	}
	return *this;
}


Vector3& Vector3::zero() {
	x = y = z = 0.0;
}

float Vector3::dot(const Vector3& v) {
	return x * v.x + y * v.y + z * v.z;
}

float Vector3::len() {
	return sqrt(x*x + y*y + z*z);
}

Vector3& Vector3::transform(const Quaternion& q) {
	tq0.set(x, y, z, 0.0);
	
	tq1.set(q).conjugate().mulLeft(tq0).mulLeft(q);

	x = tq1.x;
	y = tq1.y;
	z = tq1.z;

	return *this;
}

Vector3& Vector3::lerp(Vector3& v, float alpha) {
	x += alpha * (v.x - x);
	y += alpha * (v.y - y);
	z += alpha * (v.z - z);
	
	return *this;
}

Vector3& Vector3::slerp(Vector3& v, float alpha) {
	float dot = this -> dot(v);
	if(dot > 0.9995 || dot < -0.9995) {
		lerp(v, alpha);
	} else {
		float theta0 = acos(dot);
		float theta = theta0 * alpha;

		float st = sin(theta);
		float tx = v.x - x * dot;
		float ty = v.y - y * dot;
		float tz = v.z - z * dot;
		float l2 = tx * tx + ty * ty + tz * tz;
		float dl = st * ((l2 < 0.0001) ? (1.0) : (1.0/sqrt(l2)));

		scl(cos(theta));

		x += tx * dl;
		y += ty * dl;
		z += tz * dl;

		nor();
	}
	return *this;
}