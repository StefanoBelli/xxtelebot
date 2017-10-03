#include <iostream>
#include <tgbot/utils/matrix.h>
#include "facility.h"

using namespace tgbot::utils;

int main()
{
	UNIT_BEGIN("matrix");

	TEST_BEGIN("SimpleMatrixCreation");
	Matrix<int> m;
	TEST_END();

	TEST_BEGIN("SimpleMatrixAlloc");
	Matrix<int> m(10,10);
	TEST_END();

	TEST_BEGIN("MatrixFillZeroThenCheckEnsureNoException");
	Matrix<int> m(10,10);
	try {
		for (int i = 0; i < 10; i++)  {
			for (int j = 0; j < 10; j++) {
				m.put(0,i,j);
			}
		}

		for (int i = 0; i < 10; i++)  {
			for (int j = 0; j < 10; j++) {
				CALL(m.at,i,j);
				CHECK_EQ(0);
			}
		}
	} catch(std::exception& e) {
		TEST_FAILURE(e.what());
	}
	TEST_END();

	TEST_BEGIN("MatrixOutOfBoundsReallocEnsureNoException");
	Matrix<int> m(2,2);
	try {
		m.put(12,1,1);
		m.put(13,1,2);
		m.put(14,2,1);
		m.put(15,2,2);
		{
			CALL(m.at,1,1);
			CHECK_EQ(12);
		}

		{
			CALL(m.at,1,2);
			CHECK_EQ(13);
		}

		{
			CALL(m.at,2,1);
			CHECK_EQ(14);
		}

		{
			CALL(m.at,2,2);
			CHECK_EQ(15);
		}

	} catch(std::exception& e) {
		TEST_FAILURE(e.what());
	}
	TEST_END();

	TEST_BEGIN("MatrixOutOfBoundsEmptyEnsureNoException");
	Matrix<int> matEmpty;
	try {
		matEmpty.put(11,0,0);
		matEmpty.put(12,1,1);
		matEmpty.put(13,1,2);
		matEmpty.put(14,2,1);
		matEmpty.put(15,2,2);
		matEmpty.put(16,0,1);

		{
			CALL(matEmpty.at,0,0);
			CHECK_EQ(11);
		}

		{
			CALL(matEmpty.at,1,1);
			CHECK_EQ(12);
		}

		{
			CALL(matEmpty.at,1,2);
			CHECK_EQ(13);
		}

		{
			CALL(matEmpty.at,2,1);
			CHECK_EQ(14);
		}

		{
			CALL(matEmpty.at,2,2);
			CHECK_EQ(15);
		}

		{
			CALL(matEmpty.at,0,1);
			CHECK_EQ(16);
		}
	} catch(std::exception& e) {
		TEST_FAILURE(e.what());
	} 
	TEST_END();

	TEST_BEGIN("MatrixCheckColsAndRows");
	Matrix<int> a(2,2);

	{
		CALL(a.getMaxCols);
		CHECK_EQ(2);
	}

	{
		CALL(a.getMaxRows);
		CHECK_EQ(2);
	}

	a.put(0,2,1);

	{
		CALL(a.getMaxRows);
		CHECK_EQ(3);
	}

	{
		CALL(a.getMaxCols);
		CHECK_EQ(2);
	}

	a.put(0,2,2);

	{
		CALL(a.getMaxRows);
		CHECK_EQ(3);
	}

	{
		CALL(a.getMaxCols);
		CHECK_EQ(3);
	}

	TEST_END();

	TEST_BEGIN("MatrixExceptionOnOutOfBounds");
	{
		bool hasExcept = false;
		try {
			Matrix<int> a;
			a.at(0,0);
		} catch(std::exception& e) {
			hasExcept = true;
		}

		if(!hasExcept) {
			TEST_FAILURE("EXCEPTION EXPECTED, GOT NOTHING TO CATCH!!");
		}
	}
	
	{
		bool hasExcept = false;
		try {
			Matrix<int> a(1,1);
			a.at(1,0);
		} catch(std::exception& e) {
			hasExcept = true;
		}

		if(!hasExcept) {
			TEST_FAILURE("EXCEPTION EXPECTED, GOT NOTHING TO CATCH!!");
		}
	}

	{
		bool hasExcept = false;
		try {
			Matrix<int> a(1,1);
			a.at(0,1);
		} catch(std::exception& e) {
			hasExcept = true;
		}

		if(!hasExcept) {
			TEST_FAILURE("EXCEPTION EXPECTED, GOT NOTHING TO CATCH!!");
		}
	}
	TEST_END();

	UNIT_END();
}
