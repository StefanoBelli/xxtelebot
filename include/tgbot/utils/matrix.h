#ifndef TGBOT_MATRIX_H
#define TGBOT_MATRIX_H

#include <exception>
#include <utility>
#include <cstdlib>

namespace tgbot {

	/*!
	 * @brief Project-provided utilities, most of them used within the project
	 */
	namespace utils {
		class MatrixException : public std::exception {
			private:
				unsigned char code;

			public:
				explicit MatrixException(const unsigned char& whatCode) : code(whatCode) {}
				const unsigned char& getCode() const noexcept {
					return code;
				}

				virtual const char* what() const noexcept {
					return (code) ? "Exceeding matrix limits" : "Exhausted memory, can't allocate more";
				}
		};

		template <typename _TyElems>
			class Matrix {
				private:
					int maxRow;
					int maxCol;
					_TyElems** _matrix;

				public:
					inline Matrix() : maxRow(0), maxCol(0) {
						_matrix = new _TyElems*;
					}

					inline Matrix(const int& r, const int& c)	:
						maxRow(r), maxCol(c) {

							_matrix = new _TyElems*[r];
							for(int i=0;i<r;i++)
								_matrix[i] = new _TyElems[c];
					}

					inline ~Matrix() {
						for(int i=0;i<maxRow;i++)
							delete[] _matrix[i];

						delete[] _matrix;
					}

					inline Matrix(const Matrix& prev) :
						maxRow(prev.maxRow), maxCol(prev.maxCol) {
							_matrix = new _TyElems*[prev.maxRow];
							for(int i=0;i<prev.maxRow;i++) {
								_matrix[i] = new _TyElems[prev.maxCol];
								for(int j=0;j<prev.maxCol;j++)
									_matrix[i][j] = prev._matrix[i][j];
							}
					}

					inline Matrix(Matrix&& prev) :
						maxRow(std::move(prev.maxRow)),
						maxCol(std::move(prev.maxCol)) {
							_matrix = new _TyElems*[prev.maxRow];
							for(int i=0;i<prev.maxRow;i++) {
								_matrix[i] = new _TyElems[prev.maxCol];
								for(int j=0;j<prev.maxCol;j++)
									_matrix[i][j] = std::move(prev._matrix[i][j]);
							}
						}

					inline Matrix& operator=(const Matrix& prev) {
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

					inline const _TyElems& at(const int& r, const int& c) const {
						if(r > maxRow-1 || c > maxCol-1)
							throw MatrixException(1);
					
						return _matrix[r][c];
					}

					inline const _TyElems& _at(const int& r, const int& c) const noexcept {
						return _matrix[r][c];
					}

					inline void put(const _TyElems& what, const int& r, const int& c) {
						if(r > maxRow-1) {
							_matrix = (_TyElems**) realloc(_matrix, (r+1) * sizeof(_TyElems*));
							if(!_matrix) //nullptr
								throw MatrixException(0);

							for(int i = maxRow; i < r+1; i++)
								_matrix[i] = new _TyElems[maxCol];

							maxRow = r + 1;
						}

						if(c > maxCol-1) {
							for (int i=0; i < maxRow; i++) {
								_matrix[i] = (_TyElems*) realloc(_matrix[i], (c+1) * sizeof(_TyElems));

								if(!_matrix[i]) //nullptr
									throw MatrixException(0);
							}

							maxCol = c + 1;
						}

						_matrix[r][c] = what;
					}
					
					inline const int& getMaxRows() const {
						return maxRow;
					}

					inline const int& getMaxCols() const {
						return maxCol;
					}
			};

	} //utils

} //tgbot

#endif
