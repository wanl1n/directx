#pragma once

class Vector4
{
public:
	float x, y, z, a;

public:
	Vector4() : x(0), y(0), z(0), a(0) {}
	Vector4(float x) : x(x), y(x), z(x), a(x) {}
	Vector4(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}
	Vector4(const Vector4& vec) : x(vec.x), y(vec.y), z(vec.z), a(vec.a) {}
	~Vector4() {}

	static Vector4 lerp(const Vector4& start, const Vector4& end, float delta) {
		Vector4 v;

		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;
		v.a = start.a * (1.0f - delta) + end.a * delta;

		return v;
	}

	void operator +=(const Vector4& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->a += other.a;
	}

	Vector4 operator +(const Vector4& other) {
		Vector4 result;

		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;
		result.a = a + other.a;

		return result;
	}
};
