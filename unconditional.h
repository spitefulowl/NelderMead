#pragma once
#include "utils.h"
#include <cmath>
#include <algorithm>

template<typename T, typename Function, std::size_t size>
class unconditional {
private:
	using point_type = point<T, size>;
	using point_list_type = std::array<point_type, size + 1>;
public:
	unconditional(double alpha, double beta, double gamma, double size_factor, point<T, size>& base_point, Function function) {
		this->base_point = base_point;
		this->alpha = alpha;
		this->beta = beta;
		this->gamma = gamma;
		this->size_factor = size_factor;
		this->function = function;
	}
private:
	void generate_points() {
		point_list[0] = base_point;
		for (std::size_t idx = 0; idx < size; ++idx) {
			point_type e;
			e[idx] = size_factor;
			point_list[idx + 1] = base_point + e;
		}
	}
	bool terminate(point_list_type& list, double eps) {
		double value = 0;
		for (std::size_t idx = 1; idx < size; ++idx) {
			value += std::pow(function(list[idx]) - function(list[0]), 2);
		}
		value /= static_cast<double>(size);
		value = std::sqrt(value);
		return value < eps;
	}
	point_type central(point_list_type& list) {
		point_type result;
		for (std::size_t idx = 0; idx < size; ++idx) {
			result += list[idx];
		}
		return result / size;
	}
	point_type reflect(point_type& central_point, point_type& max_point) {
		return central_point + (central_point - max_point) * alpha;
	}
	point_type extend(point_type& central_point, point_type& reflect_point) {
		return central_point + (reflect_point - central_point) * beta;
	}
	point_type compress(point_list_type& list, point_type& reflect_point, point_type& central_point) {
		if (function(reflect_point) < function(list[size])) {
			return central_point + (reflect_point - central_point) * gamma;
		}
		else {
			return central_point + (list[size] - central_point) * gamma;
		}
	}
public:
	point_list_type get_solution(double eps) {
		generate_points();
		point_list_type new_list = point_list;
		std::size_t counter{ 0 };
		while (!terminate(new_list, eps)) {
			counter++;
			point_list = new_list;
			std::sort(new_list.begin(), new_list.end(), [this](auto& first, auto& second) {
				return this->function(first) < this->function(second);
				});
			point_type central_point = central(new_list);
			point_type reflect_point = reflect(central_point, new_list[size]);
			double reflect_criterion = function(reflect_point);
			double max_criterion = function(new_list[size]);
			double prev_max_criterion = function(new_list[size - 1]);
			double min_criterion = function(new_list[0]);
			if (min_criterion <= reflect_criterion && reflect_criterion <= prev_max_criterion) {
				new_list[size] = reflect_point;
			}
			else {
				if (reflect_criterion < min_criterion) {
					point_type extend_point = extend(central_point, reflect_point);
					if (function(extend_point) >= reflect_criterion) { // maybe >= min_criterion
						new_list[size] = reflect_point;
					}
					else {
						new_list[size] = extend_point;
					}
				}
				else {
					if (reflect_criterion > prev_max_criterion) {
						point_type compress_point = compress(new_list, reflect_point, central_point);
						double minimal = std::min(reflect_criterion, max_criterion);
						if (function(compress_point) < minimal) {
							new_list[size] = compress_point;
						}
						else {
							for (std::size_t idx = 1; idx < size + 1; ++idx) {
								new_list[idx] = (new_list[0] + new_list[idx]) / 2;
							}
						}
					}
				}
			}
		}
		printf("Counter: %u\n", static_cast<unsigned int>(counter));
		return new_list;
	}

private:
	double alpha;
	double beta;
	double gamma;
	double size_factor;
	point_type base_point;
	Function function;
	point_list_type point_list;
};