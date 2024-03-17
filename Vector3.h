#pragma once

#include "Vector.h"

namespace GMath {
	template <typename T>
	class Vector3 : public Vector<T, 3> {
	public:
		using Vector<T, 3>::Vector;

		Vector3(const Vector<T, 2>& vec2, const T& val) : Vector<T, 3>(vec2[0], vec2[1], val) {}
		Vector3(const T& val, const Vector<T, 1>& vec2) : Vector<T, 3>(val, vec2[0], vec2[1]) {}
	};

	using Vector3f = Vector3<float>;
	using Vector3i = Vector3<int>;
	using Vector3d = Vector3<double>;
}