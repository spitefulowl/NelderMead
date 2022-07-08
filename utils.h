#ifndef __H_UTILS
#define __H_UTILS

#include <vector>
#include <algorithm>
#include <array>

template<typename T, std::size_t size>
class point {
public:
	point() {
		my_value = std::array<T, size>{};
	}
	point(const point& value) {
		this->my_value = value.my_value;
	}
	template<typename... U>
	point(U... list) {
		static_assert(sizeof...(list) == size);
		my_value = std::array<T, size>{ list... };
	}
	point operator+(point p) {
		point result;
		for (std::size_t idx = 0; idx < size; ++idx) {
			result.my_value[idx] = my_value[idx] + p.my_value[idx];
		}
		return result;
	}
	point operator-(point p) {
		point result;
		for (std::size_t idx = 0; idx < size; ++idx) {
			result.my_value[idx] = my_value[idx] - p.my_value[idx];
		}
		return result;
	}
	point& operator+=(point p) {
		this->my_value = this->operator+(p).my_value;
		return *this;
	}
	point operator/(double div) {
		point result;
		for (std::size_t idx = 0; idx < size; ++idx) {
			result.my_value[idx] = my_value[idx] / div;
		}
		return result;
	}
	point operator*(double multi) {
		point result;
		for (std::size_t idx = 0; idx < size; ++idx) {
			result.my_value[idx] = my_value[idx] * multi;
		}
		return result;
	}
	T& operator[](std::size_t idx) {
		return my_value[idx];
	}

private:
	std::array<T, size> my_value;
};

#endif /* __H_UTILS */
