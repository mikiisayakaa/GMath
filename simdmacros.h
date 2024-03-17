#pragma once

#include <immintrin.h>
#include <type_traits>

#define GMATH_SIMD

namespace GMath {

#ifdef GMATH_SIMD
	//define aligned SIMD variables
#ifdef _MSC_VER
#define __m128A __m128 __declspec(align(16))
#define __m256dA  __m256d __declspec(align(32))
#elif defined(__GNUC__) || defined(__clang__)
#define __m128A  __m128 __attribute__((aligned(16)))
#define __m256dA __m256d __attribute__((aligned(32)))
#endif

#define __m128_3dMask _mm_setr_epi32(-1,-1,-1,0)
#endif

#ifndef SIMD_OK
#define SIMD_OK(type, number) \
	((std::is_same_v<type, float> || std::is_same_v<type, double>) && \
		number == 4)
#endif

	template <typename T>
	struct SIMD_VecMapper {

	};

	template<typename T, int dim>
	struct SIMD_VecLoadStore {};

	template<>
	struct SIMD_VecLoadStore<float, 4> {
		inline static auto load(const float* data) {
			return _mm_load_ps(data);
		}
		inline static void store(float* rst, __m128 a) {
			_mm_store_ps(rst, a);
		}
	};

	template<>
	struct SIMD_VecLoadStore<double, 4> {
		inline static auto load(const double* data) {
			return _mm256_load_pd(data);
		}
		inline static void store(double* rst, __m256d a) {
			_mm256_store_pd(rst, a);
		}
	};

	template<>
	struct SIMD_VecMapper<float> {
		using type = __m128;
		inline static auto multiply(__m128 a, __m128 b) {
			return _mm_mul_ps(a, b);
		}
	};

	template<>
	struct SIMD_VecMapper<double> {
		using type = __m256d;
		inline static auto multiply(__m256d a, __m256d b) {
			return _mm256_mul_pd(a, b);
		}
	};


	//WARNING: T and dim must be used as template parameters
#ifndef __simd_vectype
#define __simd_vectype \
	typename SIMD_VecMapper<T>::type __declspec(align(sizeof(T) * 4))
#endif

#ifndef _simd_load
#define _simd_load(dataPtr) \
	SIMD_VecLoadStore<T, dim>::load(dataPtr);
#endif

#ifndef _simd_store
#define _simd_store(rstPtr, data) \
	SIMD_VecLoadStore<T, dim>::store(rstPtr, data);
#endif

#ifndef _simd_multiply
#define _simd_multiply(data1, data2) \
	SIMD_VecMapper<T>::multiply(data1, data2);
#endif



}

#undef GMATH_SIMD