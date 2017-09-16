#ifndef TGBOT_MATRIX_H
#define TGBOT_MATRIX_H

#include <exception>
#include <utility>

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
					int maxRow;
					int maxCol;
					_TyElems** _matrix;

				public:
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

					Matrix(const Matrix& prev) :
						maxRow(prev.maxRow), maxCol(prev.maxCol) {
							_matrix = new _TyElems*[prev.maxRow];
							for(int i=0;i<prev.maxRow;i++) {
								_matrix[i] = new _TyElems[prev.maxCol];
								for(int j=0;j<prev.maxCol;j++)
									_matrix[i][j] = prev._matrix[i][j];
							}
						}

					Matrix(Matrix&& prev) :
						maxRow(std::move(prev.maxRow)),
						maxCol(std::move(prev.maxCol)) {
							_matrix = new _TyElems*[prev.maxRow];
							for(int i=0;i<prev.maxRow;i++) {
								_matrix[i] = new _TyElems[prev.maxCol];
								for(int j=0;j<prev.maxCol;j++)
									_matrix[i][j] = std::move(prev._matrix[i][j]);
							}
						}

					Matrix& operator=(const Matrix& prev) {
						if(*_matrix) {
							for (int i = 0; i < maxRow; i++)
								delete[] _matrix[i];
							delete[] _matrix;
						}

						_matrix = new _TyElems*[prev.maxRow];
						for(int i=0;i<prev.maxRow;i++) {
							_matrix[i] = new _TyElems[prev.maxCol];
							for(int j=0;j<prev.maxCol;j++)
								_matrix[i][j] = prev._matrix[i][j];
						}

						maxCol = prev.maxCol;
						maxRow = prev.maxRow;

						return *this;
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
