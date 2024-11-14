#pragma once
#include <cmath>

#include "Vector3.h"

class Vector4
{
	public:
		float x, y, z, w;

	public:
		Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4(float x) : x(x), y(x), z(x), w(x) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		Vector4(const Vector4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		Vector4(const Vector3& vec) : x(vec.x), y(vec.y), z(vec.z), w(1.0f) {}
		~Vector4() {}

		static Vector4 lerp(const Vector4& start, const Vector4& end, float delta) {
			Vector4 v;

			v.x = start.x * (1.0f - delta) + end.x * delta;
			v.y = start.y * (1.0f - delta) + end.y * delta;
			v.z = start.z * (1.0f - delta) + end.z * delta;
			v.w = start.w * (1.0f - delta) + end.w * delta;

			return v;
		}

		static Vector4 splatW(const Vector4& splat) {
			Vector4 v;

			v.x = splat.w;
			v.y = splat.w;
			v.z = splat.w;
			v.w = splat.w;

			return v;
		}

		void cross(Vector4& v1, Vector4& v2, Vector4& v3)
		{
			this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
			this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
			this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
			this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
		}

		void operator +=(const Vector4& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
		}

		Vector4 operator +(const Vector4& other) {
			Vector4 result;

			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;
			result.w = w + other.w;

			return result;
		}

		void operator /=(const Vector4& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
		}
		Vector4 operator /(const Vector4& other) {
			Vector4 v;

			v.x = x / other.x;
			v.y = y / other.y;
			v.z = z / other.z;
			v.w = w / other.w;

			return v;
		}
};
