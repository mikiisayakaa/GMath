#include "Vector.h"
#include "VectorDefs.h"

#include <string>
#include <iostream>
#include <vector>
#include "TimeTest.h"

#include <Eigen/Core>
#include <glm.hpp>
#include <immintrin.h>

using namespace GMath;

int main() {
	int num = 10000000;


	std::vector<Eigen::Vector4f> arre1(num, Eigen::Vector4f(1, 2, 3, 4));
	std::vector<Eigen::Vector4f> arre2(num, Eigen::Vector4f(1, 2, 3, 4));
	std::vector<Eigen::Vector4f> arre3(num);



	std::vector<glm::fvec4> arrg1(num, glm::fvec4(1, 2, 3, 4));
	std::vector<glm::fvec4> arrg2(num, glm::fvec4(1, 2, 3, 4));
	std::vector<glm::fvec4> arrg3(num);

	std::vector<Vector4f> arr1(num, Vector4f(1, 2, 3, 4));
	std::vector<Vector4f> arr2(num, Vector4f(1, 2, 3, 4));
	std::vector<Vector4f> arrRst(num);

	std::cout << Vector3f(1, 2, 3) * Vector3f(4, 5, 6);


	TIME_START("Eigen")
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < 10; j++) {
				arre3[i] = arre2[i].cwiseProduct(arre1[i]);
			}
		}
	TIME_END()


		TIME_START("glm")
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < 10; j++) {
				arrg3[i] = arrg2[i] * arrg1[i];
			}
		}
	TIME_END()

		TIME_START("GMath")
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < 10; j++) {
				arrRst[i] = arr2[i] * arr1[i];
			}
		}
	TIME_END()




}