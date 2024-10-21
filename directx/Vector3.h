#pragma once
#include <cmath>
class Vector3
{
	public:
		float x, y, z;

	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x) : x(x), y(x), z(x) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		Vector3(const Vector3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
		//Vector3(Vector3D vec) : x(vec.x), y(vec.y), z(vec.z) {}
		~Vector3() {}

		static Vector3 lerp(const Vector3& start, const Vector3& end, float delta) {
			Vector3 v;

			v.x = start.x * (1.0f - delta) + end.x * delta;
			v.y = start.y * (1.0f - delta) + end.y * delta;
			v.z = start.z * (1.0f - delta) + end.z * delta;

			return v;
		}

		float magnitude() {
			return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
		}

		Vector3 normalize() {
			float magnitude = this->magnitude();
			Vector3 normal = Vector3(x, y, z);

			if (magnitude == 0) {
				normal.x = 0;
				normal.y = 0;
				normal.z = 0;
				return normal;
			}

			normal.x /= magnitude;
			normal.y /= magnitude;
			normal.z /= magnitude;

			return normal; 
		}

		void operator +=(const Vector3& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
		}

		void operator -=(const Vector3& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
		}

		void operator +=(float addend) {
			this->x += addend;
			this->y += addend;
			this->z += addend;
		}

		Vector3 operator +(const Vector3& other) {
			Vector3 result;

			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;

			return result;
		}

		Vector3 operator *(const Vector3& other) {
			Vector3 result;

			result.x = x * other.x;
			result.y = y * other.y;
			result.z = z * other.z;

			return result;
		}

		Vector3 operator *(float mult) {
			Vector3 result;

			result.x = x * mult;
			result.y = y * mult;
			result.z = z * mult;

			return result;
		}

		bool operator !=(const Vector3& other) {
			if (other.x != this->x ||
				other.y != this->y ||
				other.z != this->z)
				return true;
			else
				return false;
		}
};
