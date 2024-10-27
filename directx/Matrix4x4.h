#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Vector4.h"

class Matrix4x4
{
	public:
		float mat[4][4] = {};

	public:
		Matrix4x4() {}
		~Matrix4x4() {}

		void setIdentity() {
			::memset(mat, 0, sizeof(float) * 16);
			mat[0][0] = 1;
			mat[1][1] = 1;
			mat[2][2] = 1;
			mat[3][3] = 1;
		}

		void setTranslation(const Vector3& translation) {
			mat[3][0] = translation.x;
			mat[3][1] = translation.y;
			mat[3][2] = translation.z;
		}

		void setScale(const Vector3& scale) {
			mat[0][0] = scale.x;
			mat[1][1] = scale.y;
			mat[2][2] = scale.z;
		}

		bool setRotationX(float x) {
			mat[1][1] = cos(x);
			mat[1][2] = sin(x);
			mat[2][1] = -sin(x);
			mat[2][2] = cos(x);

			return true;
		}

		bool setRotationY(float y) {
			mat[0][0] = cos(y);
			mat[0][2] = -sin(y);
			mat[2][0] = sin(y);
			mat[2][2] = cos(y);

			return true;
		}

		bool setRotationZ(float z) {
			mat[0][0] = cos(z);
			mat[1][0] = -sin(z);
			mat[0][1] = sin(z);
			mat[1][1] = cos(z);

			return true;
		}

		float getDeterminant() {
			Vector4 minor, v1, v2, v3;
			float det;

			v1 = Vector4(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
			v2 = Vector4(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
			v3 = Vector4(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);

			minor.cross(v1, v2, v3);
			det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
				this->mat[3][3] * minor.w);
			return det;
		}

		void inverse() {
			int a, i, j;
			Matrix4x4 out;
			Vector4 v, vec[3];
			float det = 0.0f;

			det = this->getDeterminant();
			if (!det) return;
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					if (j != i)
					{
						a = j;
						if (j > i) a = a - 1;
						vec[a].x = (this->mat[j][0]);
						vec[a].y = (this->mat[j][1]);
						vec[a].z = (this->mat[j][2]);
						vec[a].w = (this->mat[j][3]);
					}
				}
				v.cross(vec[0], vec[1], vec[2]);

				out.mat[0][i] = pow(-1.0f, (float)i) * v.x / det;
				out.mat[1][i] = pow(-1.0f, (float)i) * v.y / det;
				out.mat[2][i] = pow(-1.0f, (float)i) * v.z / det;
				out.mat[3][i] = pow(-1.0f, (float)i) * v.w / det;
			}

			this->setMatrix(out);
		}

		static Vector4 transform(const Vector4& vec, Matrix4x4 mat) {
			Vector4 out;

			std::vector<float> vec4;
			vec4.push_back(vec.x);
			vec4.push_back(vec.y);
			vec4.push_back(vec.z);
			vec4.push_back(vec.w);

			for (int i = 0; i < 4; i++) {
				out.x += mat.mat[0][i] * vec4[i];
				out.y += mat.mat[1][i] * vec4[i];
				out.z += mat.mat[2][i] * vec4[i];
				out.w += mat.mat[3][i] * vec4[i];
			}

			return out;
		}

		static Vector4 unproject(Vector3 screenPoint, Matrix4x4 viewMat, 
								Matrix4x4 projMat, float screenWidth, float screenHeight) {
			// Step 1: Normalize the screen coordinates to NDC
			float ndcX = (2.0f * screenPoint.x) / screenWidth - 1.0f;
			float ndcY = 1.0f - (2.0f * screenPoint.y) / screenHeight;
			float ndcZ = 2.0f * screenPoint.z - 1.0f; // Depth value is typically between 0 and 1

			// Create a vector in clip space with the normalized coordinates
			Vector4 clipSpaceVector = Vector4(ndcX, ndcY, ndcZ, 1.0f);

			// Step 2: Calculate the inverse of the combined view-projection matrix
			Matrix4x4 viewProjMatrix = viewMat;
			viewProjMatrix *= projMat;
			viewProjMatrix.inverse();
			Matrix4x4 inverseViewProjMatrix;
			inverseViewProjMatrix = viewProjMatrix;

			// Step 3: Apply the inverse view-projection matrix to the clip space vector
			Vector4 worldSpaceVector = Matrix4x4::transform(clipSpaceVector, inverseViewProjMatrix);
			// Step 4: Convert from homogeneous coordinates (divide by w)
			Vector4 worldSpacePoint = Vector4::splatW(worldSpaceVector) / worldSpaceVector;

			return worldSpacePoint; // This is the unprojected point in world space
		}

		void operator *=(const Matrix4x4& matrix) {
			Matrix4x4 out;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					out.mat[i][j] =
						mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
						mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
				}
			}

			this->setMatrix(out);
		}

		void setMatrix(const Matrix4x4& matrix) {
			::memcpy(mat, matrix.mat, sizeof(float) * 16);
		}

		Vector3 getZDir() {
			return Vector3(mat[2][0], mat[2][1], mat[2][2]);
		}

		Vector3 getXDir() {
			return Vector3(mat[0][0], mat[0][1], mat[0][2]);
		}

		Vector3 getTranslation() {
			return Vector3(mat[3][0], mat[3][1], mat[3][2]);
		}

		void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar) {
			float yscale = 1.0f / tan(fov / 2.0f);
			float xscale = yscale / aspect;

			mat[0][0] = xscale;
			mat[1][1] = yscale;
			mat[2][2] = zfar / (zfar - znear);
			mat[2][3] = 1.0f;
			mat[3][2] = (-znear * zfar) / (zfar - znear);
		}

		void setOrthoLH(float width, float height, float near_plane, float far_plane) {
			this->setIdentity();
			mat[0][0] = 2.0f / width;
			mat[1][1] = 2.0f / height;
			mat[2][2] = 1.0f / (far_plane - near_plane);
			mat[3][2] = -(near_plane / (far_plane - near_plane));
		}

		void printMatrix() {
			for (int i = 0; i < 4; i++) {
				std::cout << i << " [";
				for (int j = 0; j < 4; j++) {
					std::cout << mat[i][j] << " ";
				}
				std::cout << "]" << std::endl;
			}
		}
};
