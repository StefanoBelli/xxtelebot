#ifndef TGBOT_MATRIX_H
#define TGBOT_MATRIX_H

#include <exception>

namespace tgbot {

	/*!
	 * @brief Project-provided utilities, most of them used within the project
	 */
	namespace utils {

		class MatrixException : public std::exception {
			public:
				virtual const char* what() const noexcept;
		};

		template <typename _TyElems>
			class Matrix {
				private:
					const int maxRow;
					const int maxCol;
					_TyElems** _matrix;

				public:
					Matrix(const Matrix& prev) = delete;
					Matrix& operator=(const Matrix& prev) = delete;
					Matrix(Matrix&& prev) = delete;

					Matrix(const int& r, const int& c)	:
						maxRow(r), maxCol(c) {

							_matrix = new _TyElems*[r];
							for(int i=0;i<r;i++)
								_matrix[i] = new _TyElems[c];
						}

					~Matrix() {
						for(int i=0;i<maxRow;i++)
							delete[] _matrix[i];

						delete[] _matrix;
					}

					_TyElems& at(const int& r, const int& c) {
						if(r > maxRow-1 || c > maxCol-1)
							throw MatrixException();

						return _matrix[r][c];
					}

					const int& getMaxRows() const {
						return maxRow;
					}

					const int& getMaxCols() const {
						return maxCol;
					}
			};

	} //utils

} //tgbot

#endif
