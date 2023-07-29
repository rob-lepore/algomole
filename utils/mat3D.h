#pragma once
#include "../am.h"

namespace am {
	template <typename T> 
	class Mat3D {

	public:
		Mat3D(size_t width, size_t height, size_t depth) {
			m_w = width;
			m_h = height;
			m_d = depth;
			m_data.reserve(m_w * m_h * m_d);
		}

		Mat3D(size_t width, size_t height, size_t depth, T value) {
			m_w = width;
			m_h = height;
			m_d = depth;
			m_data.assign(m_w * m_h * m_d, value);
		}

		T& at(size_t x, size_t y, size_t z) {
			return m_data[(z * m_h * m_w) + (y * m_w) + x];
		}

		size_t width() {
			return m_w;
		}

		size_t height() {
			return m_h;
		}

		size_t depth() {
			return m_d;
		}

		size_t size() {
			return m_w * m_h * m_d;
		}

		std::vector<T> data() {
			return m_data;
		}

	private:
		size_t m_w;
		size_t m_h;
		size_t m_d;

		std::vector<T> m_data;

	};



}
