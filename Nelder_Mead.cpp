// Nelder_Mead.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include "utils.h"
#include "nelder_mead.h"

template<typename Point>
struct first {
	first(){}
	double operator()(Point value) {
		return 100. * std::pow(std::pow(value[0], 2) - value[1], 2) + std::pow(1 - value[0], 2);
	}
};

template<typename Point>
struct second {
	second() {}
	double operator()(Point value) {
		return 100. * std::pow(value[1] - std::pow(value[0], 3), 2) + std::pow((1 - value[0]), 2);
	}
};

template<typename Point>
struct third {
	third() {}
	double operator()(Point value) {
		return std::pow(value[0] + 10 * value[1], 2) + 5 * std::pow(value[2] - value[3], 2) + std::pow(value[1] - 2 * value[2], 4) + 10 * std::pow(value[0] - value[3], 4);
	}
};
#define ACCURACY 0.000001

int main()
{
	{
		std::vector<std::pair<double, double>> allowed_values = {
														{ -1.2, 0 },
														{ 1, 3 }
		};
		point<double, 2> base(-1.2, 1.);
		first<point<double, 2>> function{};
		//nelder_mead<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(ACCURACY);
		nelder_mead<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 1.3, base, function);
		auto result = cond.get_solution(ACCURACY, allowed_values);
		for (auto& elem : result) {
			printf("Point: %f %f\n", elem[0], elem[1]);
			printf("Criterion: %.12f\n", function(elem));
		}
	}
	printf("\n\n\n");
	{
		std::vector<std::pair<double, double>> allowed_values = {
														{ -1.2, -0.5 },
														{ -1, 0 }
		};
		point<double, 2> base(-1.2, -1.);
		second<point<double, 2>> function{};
		//nelder_mead<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(ACCURACY);
		nelder_mead<double, second<point<double, 2>>, 2> cond(1., 2., 0.5, 1, base, function);
		auto result = cond.get_solution(ACCURACY, allowed_values);
		for (auto& elem : result) {
			printf("Point: %f %f\n", elem[0], elem[1]);
			printf("Criterion: %.12f\n", function(elem));
		}
	}
	printf("\n\n\n");
	{
		std::vector<std::pair<double, double>> allowed_values = {
														{ 3, 4 },
														{ -2, -1 },
														{ -3, 0 },
														{ 1, 4 }
		};
		point<double, 4> base(3., -1., 0., 1.);
		third<point<double, 4>> function{};
		//nelder_mead<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(ACCURACY);
		nelder_mead<double, third<point<double, 4>>, 4> cond(1., 2., 0.5, 2.5, base, function);
		auto result = cond.get_solution(ACCURACY, allowed_values);
		for (auto& elem : result) {
			printf("Point: %f %f %f %f\n", elem[0], elem[1], elem[2], elem[3]);
			printf("Criterion: %.12f\n", function(elem));
		}
	}
}