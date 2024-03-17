#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"

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


	std::vector<Eigen::Vector4d> arre1(num, Eigen::Vector4d(1, 2, 3, 4));
	std::vector<Eigen::Vector4d> arre2(num, Eigen::Vector4d(1, 2, 3, 4));
	std::vector<Eigen::Vector4d> arre3(num);



	std::vector<glm::dvec4> arrg1(num, glm::dvec4(1, 2, 3, 4));
	std::vector<glm::dvec4> arrg2(num, glm::dvec4(1, 2, 3, 4));
	std::vector<glm::dvec4> arrg3(num);

	std::vector<Vector<double, 4>> arr1(num, Vector<double, 4>(1, 2, 3, 4));
	std::vector<Vector<double, 4>> arr2(num, Vector<double, 4>(1, 2, 3, 4));
	std::vector<Vector<double, 4>> arrRst(num);


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