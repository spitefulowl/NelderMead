// Nelder_Mead.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include "utils.h"
#include "unconditional.h"

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

int main()
{
	{
		point<double, 2> base(-1.2, 1.);
		first<point<double, 2>> function{};
		//unconditional<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(0.000001);
		unconditional<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 5.3, base, function);
		auto result = cond.get_solution(0.000001);
		for (auto& elem : result) {
			printf("Point: %f %f\n", elem[0], elem[1]);
			printf("Criterion: %.8f\n", function(elem));
		}
	}
	printf("\n\n\n");
	{
		point<double, 2> base(-1.2, -1.);
		second<point<double, 2>> function{};
		//unconditional<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(0.000001);
		unconditional<double, second<point<double, 2>>, 2> cond(1., 2., 0.5, 5, base, function);
		auto result = cond.get_solution(0.000001);
		for (auto& elem : result) {
			printf("Point: %f %f\n", elem[0], elem[1]);
			printf("Criterion: %.8f\n", function(elem));
		}
	}
	printf("\n\n\n");
	{
		point<double, 4> base(3., -1., 0., 1.);
		third<point<double, 4>> function{};
		//unconditional<double, first<point<double, 2>>, 2> cond(1., 2., 0.5, 0.28, base, function);
		//auto result = cond.get_solution(0.000001);
		unconditional<double, third<point<double, 4>>, 4> cond(1., 2., 0.5, 5, base, function);
		auto result = cond.get_solution(0.0000001);
		for (auto& elem : result) {
			printf("Point: %f %f %f %f\n", elem[0], elem[1], elem[2], elem[3]);
			printf("Criterion: %.8f\n", function(elem));
		}
	}
}
