#pragma once

#include "Vector.h"

namespace GMath {

	template <typename T>
	class Vector2 : public Vector<T, 2> {
	public:
		using Vector<T, 2>::Vector;

	};

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2d = Vector2<double>;
}