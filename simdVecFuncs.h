﻿#pragma once

#include <immintrin.h>
#include <type_traits>
#include <cassert>

#include "simdmacros.h"

#define GMATH_SIMD

namespace GMath {

	//SIMD vector operations are only for floating number vectors with dimension 4
	template <typename T, int dim>
	inline void simd_Copy(std::array<T, dim>& rst, const std::array<T, dim>& src) {
#ifdef GMATH_SIMD
		constexpr int eSize = sizeof(T);

		if constexpr (eSize == 4 && dim == 4) {
			__m128A rstValue = _mm_load_ps(src.data());
			_mm_store_ps(rst.data(), rstValue);
		}
		else if constexpr (eSize == 8 && dim == 4) {
			__m256dA rstValue = _mm256_load_pd(src.data());
			_mm256_store_pd(rst.data(), rstValue);
		}
		else
#endif
		{
			rst[0] = src[0];
			rst[1] = src[1];
			rst[2] = src[2];
			rst[3] = src[3];
		}
	}


	template<typename T, int dim>
	inline void simd_VecAdd(std::array<T, dim>& rst, const std::array<T, dim>& arr1, const std::array<T, dim>& arr2) {
#ifdef GMATH_SIMD
		constexpr int eSize = sizeof(T);
		constexpr bool do8 = true;
		constexpr int loop8 = dim >> 3;
		constexpr int rem8 = dim & 0b111;
		if constexpr (loop8 == 0)

			//float
			if constexpr (eSize == 4) {

			}

		//Vector<float, 4>
		if constexpr (eSize == 4 && dim == 4) {
			__m128A add1 = _mm_load_ps(arr1.data());
			__m128A add2 = _mm_load_ps(arr2.data());
			__m128A rstValue = _mm_add_ps(add1, add2);
			_mm_store_ps(rst.data(), rstValue);
		}
		//Vector<double, 4>
		else if constexpr (eSize == 8 && dim == 4) {
			__m256dA add1 = _mm256_load_pd(arr1.data());
			__m256dA add2 = _mm256_load_pd(arr2.data());
			__m256dA rstValue = _mm256_add_pd(add1, add2);
			_mm256_store_pd(rst.data(), rstValue);
		}
		else
#endif
		{
			rst[0] = arr1[0] + arr2[0];
			rst[1] = arr1[1] + arr2[1];
			rst[2] = arr1[2] + arr2[2];
			rst[3] = arr1[3] + arr2[3];
		}
	}

	template <typename T, int dim>
	inline void simd_VecSub(std::array<T, dim>& rst, const std::array<T, dim>& arr1, const std::array<T, dim>& arr2) {

		constexpr int eSize = sizeof(T);

		//Vector<float, 4>
		if constexpr (eSize == 4 && dim == 4) {
			__m128A sub1 = _mm_load_ps(arr1.data());
			__m128A sub2 = _mm_load_ps(arr2.data());
			__m128A rstValue = _mm_sub_ps(sub1, sub2);
			_mm_store_ps(rst.data(), rstValue);
		}
		//Vector<double, 4>
		else if constexpr (eSize == 8 && dim == 4) {
			__m256dA sub1 = _mm256_load_pd(arr1.data());
			__m256dA sub2 = _mm256_load_pd(arr2.data());
			__m256dA rstValue = _mm256_sub_pd(sub1, sub2);
			_mm256_store_pd(rst.data(), rstValue);
		}
		else

		{
			rst[0] = arr1[0] - arr2[0];
			rst[1] = arr1[1] - arr2[1];
			rst[2] = arr1[2] - arr2[2];
			rst[3] = arr1[3] - arr2[3];
		}
	}

	//NOTE: do not use rst as the sub1 input, it will greatly slow down this process
	template <typename T, int dim>
	inline void simd_VecNeg(std::array<T, dim>& rst, const std::array<T, dim>& arr) {
#ifdef GMATH_SIMD
		constexpr int eSize = sizeof(T);

		//Vector<float, 4>
		if constexpr (eSize == 4 && dim == 4) {
			__m128A sub1 = _mm_setzero_ps();
			__m128A sub2 = _mm_load_ps(arr.data());
			__m128A rstValue = _mm_sub_ps(sub1, sub2);
			_mm_store_ps(rst.data(), rstValue);
		}
		//Vector<double, 4>
		else if constexpr (eSize == 8 && dim == 4) {
			__m256dA sub1 = _mm256_setzero_pd();
			__m256dA sub2 = _mm256_load_pd(arr.data());
			__m256dA rstValue = _mm256_sub_pd(sub1, sub2);
			_mm256_store_pd(rst.data(), rstValue);
		}
		else
#endif
		{
			rst[0] = rst[0] - arr[0];
			rst[1] = rst[1] - arr[1];
			rst[2] = rst[2] - arr[2];
			rst[3] = rst[3] - arr[3];
		}
	}

	template <typename T, int dim>
	inline void simd_VecMul(std::array<T, dim>& rst, const std::array<T, dim>& arr1, const std::array<T, dim>& arr2) {

		constexpr int eSize = sizeof(T);
		if constexpr (SIMD_OK(T, dim)) {
			__simd_vectype mul1 = _simd_load(arr1.data());
			__simd_vectype mul2 = _simd_load(arr2.data());
			__simd_vectype rstValue = _simd_multiply(mul1, mul2);
			_simd_store(rst.data(), rstValue);
		}
		else {
			for (int i = 0; i < dim; i++) {
				rst[i] = arr1[i] * arr2[i];
			}
		}
	}



}

#undef GMATH_SIMD