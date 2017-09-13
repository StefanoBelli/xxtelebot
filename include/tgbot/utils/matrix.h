#ifndef TGBOT_MATRIX_H
#define TGBOT_MATRIX_H

#include <valarray>

namespace tgbot {

	/*!
	 * @brief Project-provided utilities, most of them used within the project
	 */
	namespace utils {
		template <typename _TyElems>
			class Matrix {
				private:
					std::valarray<_TyElems> _matrix;

				public:
					Matrix(int maxRow, int maxCol);
					_TyElems& elemAt(int row, int col);
			};
	} //utils

} //tgbot

#endif
