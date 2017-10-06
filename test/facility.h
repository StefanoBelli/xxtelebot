#ifndef TGBOT_API_TESTING_H
#define TGBOT_API_TESTING_H

#define __OUT_TEST_BEGIN() \
	std::cout << "\t-- Beginning tests: " << stest_name << '\n'; 

#define __OUT_TEST_END() \
	std::cout << "\t-- End tests: " << stest_name << '\n';

#define __OUT_TEST_FAIL(expect, got) \
	std::cerr << "\t!! Test failed - expecting: " << expect << ", got: " << got << '\n';

#define __OUT_TEST_FAIL_EXCEPTION(xwhat) \
	std::cerr << "\t!! Test failed - exception raised - what(): " <<  xwhat <<'\n';

#define __OUT_UNIT_FAIL() \
	std::cerr << "!! Unit failed: one or more test didn't pass\n"

#define UNIT_BEGIN(xname) \
	int testFailure = 0; \
	constexpr char const* name = xname; \
	std::cout << "** Starting unit testing for: \"" << name << "\"\n"

#define UNIT_END() \
	if(testFailure) \
		__OUT_UNIT_FAIL(); \
	std::cout << "** Tests done for: \"" << name << "\"\n"; \
	return 0;

#define TEST_BEGIN(xname) \
	{ \
		constexpr char const* stest_name = xname; \
		__OUT_TEST_BEGIN()

#define CALL(callback, ...) \
		auto rv = callback(__VA_ARGS__)
	
#define CALL_(callback) \
		auto rv = callback()

#define CHECK_EQ(xvalue) \
		if(rv != xvalue) { \
			testFailure++; \
			__OUT_TEST_FAIL(xvalue,rv); \
		}

#define CHECK_EQ_VALUES(xval, yval) \
		if(xval != yval) { \
			testFailure++; \
			__OUT_TEST_FAIL(#yval, #xval); \
		}
		
#define TEST_END() \
		__OUT_TEST_END(); \
	}

#define TEST_FAILURE(ywhat) \
	testFailure++; \
	__OUT_TEST_FAIL_EXCEPTION(ywhat)

#endif //TGBOT_API_TESTING_H
