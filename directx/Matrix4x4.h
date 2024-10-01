#pragma once
#include <memory>

#include "Vector3.h"

class Matrix4x4
{
	public:
		float m_mat[4][4] = {};

	public:
		Matrix4x4() {}
		~Matrix4x4() {}

		void setIdentity() {
			::memset(m_mat, 0, sizeof(float) * 16);
			m_mat[0][0] = 1;
			m_mat[1][1] = 1;
			m_mat[2][2] = 1;
			m_mat[3][3] = 1;
		}

		void setTranslation(const Vector3& translation) {
			this->setIdentity();
			m_mat[3][0] = translation.x;
			m_mat[3][1] = translation.y;
			m_mat[3][2] = translation.z;
		}

		void setScale(const Vector3& scale) {
			this->setIdentity();
			m_mat[0][0] = scale.x;
			m_mat[1][1] = scale.y;
			m_mat[2][2] = scale.z;
		}

		void operator *=(const Matrix4x4& matrix) {
			Matrix4x4 out;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					out.m_mat[i][j] =
						m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
						m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
				}
			}

			this->setMatrix(out);
		}

		void setMatrix(const Matrix4x4& matrix) {
			::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
		}

		void setOrthoLH(float width, float height, float near_plane, float far_plane) {
			this->setIdentity();
			m_mat[0][0] = 2.0f / width;
			m_mat[1][1] = 2.0f / height;
			m_mat[2][2] = 1.0f / (far_plane - near_plane);
			m_mat[3][2] = -(near_plane / (far_plane - near_plane));
		}

		void printMatrix() {
			for (int i = 0; i < 4; i++) {
				std::cout << i << " [";
				for (int j = 0; j < 4; j++) {
					std::cout << m_mat[i][j] << " ";
				}
				std::cout << "]" << std::endl;
			}
		}
};
