#ifndef TGBOT_API_TESTING_H
#define TGBOT_API_TESTING_H

#define __OUT_TEST_BEGIN() \
	std::cout << "\t-- Beginning tests: " << stest_name << '\n'; 

#define __OUT_TEST_END() \
	std::cout << "\t-- End tests: " << stest_name << '\n';

#define __OUT_TEST_CHECK() \
	std::cout << "\t-- Checking for correct result...\n";

#define __OUT_TEST_FAIL(expect, got) \
	std::cerr << "\t!! Test failed - expecting: " << expect << ", got: " << got << '\n';

#define __OUT_UNIT_FAIL() \
	std::cerr << "!! Unit failed: one or more test didn't pass\n"

#define UNIT_BEGIN(xname) \
	int testFailure = 0; \
	constexpr char const* name = xname; \
	std::cout << "** Starting unit testing for: \"" << name << "\"\n"

#define UNIT_END() \
	std::cout << "** Tests done for: \"" << name << "\"\n";

#define TEST_BEGIN(xname) \
	{ \
		constexpr char const* stest_name = xname; \
		__OUT_TEST_BEGIN()

#define CALL(callback, ...) \
		auto rv = callback(__VA_ARGS__)
	
#define CALL_(callback) \
		auto rv = callback()

#define CHECK_EQ(xvalue) \
		__OUT_TEST_CHECK(); \
		if(rv != xvalue) { \
			testFailure++; \
			__OUT_TEST_FAIL(xvalue,rv); \
		}

#define CHECK_EQ_VALUES(xval, yval) \
		__OUT_TEST_CHECK(); \
		if(xval != yval) { \
			testFailure++; \
			__OUT_TEST_FAIL(xvalue,rv); \
		}
		
#define TEST_END() \
		if(testFailure) \
			__OUT_UNIT_FAIL(); \
		__OUT_TEST_END(); \
	}

#endif //TGBOT_API_TESTING_H
