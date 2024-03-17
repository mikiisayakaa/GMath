#pragma once

#include <type_traits>
#include <array>
#include <iostream>
#include <cmath>
#include "simdtypes.h"

#include <immintrin.h>


namespace GMath {

	template <typename T, int dim, typename = std::enable_if_t<std::is_floating_point<T>::value>>
	class Vector : public std::array<T, dim>{
	public:


		template <typename ...Args,
			typename = std::enable_if_t<std::conjunction_v<std::is_convertible<Args, T>...>>>
			Vector(Args...args) : std::array<T, dim>{static_cast<T>(args)...} {}

		Vector(const Vector<T, dim>& other) {
			simd_Copy(*this, other);
		}

		int dimension() const { return dim; }

		Vector<T, dim> operator+(const Vector<T, dim>& other) const {
			Vector<T, dim> rst;
			simd_VecAdd(rst, *this, other);
			return rst;
		}

		Vector<T, dim> operator-(const Vector<T, dim>& other) const {
			Vector<T, dim> rst;
			simd_VecSub(rst, *this, other);
			return rst;
		}

		Vector<T, dim> operator-() const {
			Vector<T, dim> rst;
			simd_VecNeg(rst, *this);
			return rst;
		}

		Vector<T, dim> operator*(const Vector<T, dim>& other) const {
			Vector<T, dim> rst;
			simd_VecMul(rst, *this, other);
			return rst;
		}



		T length() const {
			T rst{ 0 };
			for (int i = 0; i < dim; i++) {
				rst += (*this)[i] * (*this)[i];
			}

			return std::sqrt(rst);
		}

		T lengthSquare() const {
			T rst{ 0 };
			for (int i = 0; i < dim; i++) {
				rst += (*this)[i] * (*this)[i];
			}
			return rst;
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector<T, dim>& vec) {
			os << "Vector(";
			for (int i = 0; i < dim; ++i) {
				os << vec[i];
				if (i < dim - 1) os << ", ";
			}
			os << ")";
			return os;
		}
	};

}

