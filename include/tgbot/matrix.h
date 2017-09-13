#ifndef TGBOT_MATRIX_H
#define TGBOT_MATRIX_H

#include <valarray>

namespace tgbot {
	
	template <typename _TyElems>
	class Matrix {
	private:
		std::valarray<_TyElems> _matrix;

	public:
		Matrix(int maxRow, int maxCol);
		_TyElems& elemAt(int row, int col);
	};

}

#endif
