#pragma once
#include "../am.h"

namespace am {
	namespace math {

		/**
		 * @brief The Mat3D class template represents a 3D matrix of arbitrary type.
		 *
		 * This class template allows you to create and manipulate a 3D matrix of a specified
		 * data type. It provides methods to access elements, query dimensions, and retrieve
		 * the data as a vector.
		 *
		 * @tparam T The data type of the elements in the matrix.
		 */
		template <typename T>
		class Mat3D {

		public:
			/**
			 * @brief Constructor for the Mat3D class template with specified dimensions.
			 *
			 * @param width The width (number of columns) of the 3D matrix.
			 * @param height The height (number of rows) of the 3D matrix.
			 * @param depth The depth (number of layers) of the 3D matrix.
			 */
			Mat3D(size_t width, size_t height, size_t depth) {
				m_w = width;
				m_h = height;
				m_d = depth;
				m_data.reserve(m_w * m_h * m_d);
			}

			/**
			 * @brief Constructor for the Mat3D class template with specified dimensions and initial value.
			 *
			 * @param width The width (number of columns) of the 3D matrix.
			 * @param height The height (number of rows) of the 3D matrix.
			 * @param depth The depth (number of layers) of the 3D matrix.
			 * @param value The initial value to fill the matrix with.
			 */
			Mat3D(size_t width, size_t height, size_t depth, T value) {
				m_w = width;
				m_h = height;
				m_d = depth;
				m_data.assign(m_w * m_h * m_d, value);
			}

			/**
			 * @brief Accesses the element at the specified position in the 3D matrix.
			 *
			 * @param x The column index.
			 * @param y The row index.
			 * @param z The layer index.
			 * @return A reference to the element at the specified position.
			 */
			T& at(size_t x, size_t y, size_t z) {
				return m_data[(z * m_h * m_w) + (y * m_w) + x];
			}

			/**
			 * @brief Retrieves the width (number of columns) of the 3D matrix.
			 *
			 * @return The width of the matrix.
			 */
			constexpr size_t width() {
				return m_w;
			}

			/**
			 * @brief Retrieves the height (number of rows) of the 3D matrix.
			 *
			 * @return The height of the matrix.
			 */
			const size_t height() {
				return m_h;
			}

			/**
			 * @brief Retrieves the depth (number of layers) of the 3D matrix.
			 *
			 * @return The depth of the matrix.
			 */
			const size_t depth() {
				return m_d;
			}

			/**
			 * @brief Calculates the total size (number of elements) of the 3D matrix.
			 *
			 * @return The total size of the matrix.
			 */
			const size_t size() {
				return m_w * m_h * m_d;
			}

			/**
			 * @brief Retrieves the data of the 3D matrix as a vector.
			 *
			 * @return A vector containing the matrix elements.
			 */
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
}
