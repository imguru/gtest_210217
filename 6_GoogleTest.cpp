// 6_GoogleTest.cpp
#include <gtest/gtest.h>
#include <string>

// ASSERT
//   ASSERT_EQ / NE / LT / LE / GT / GE / TRUE / FALSE ...
// 주의: 하나의 테스트 케이스 안에 여러개의 ASSERT는 좋지 않다.
//  => 여러개의 단언문의 존재할 경우, 하나의 단언문이 실패하면 이후의 단언문은 수행되지 않는다.
//     "죽은 단언문"의 문제
//  => 하지만 하나의 테스트케이스에 하나의 단언문만 집어넣을 경우, 너무 많은 테스트케이스가 만들어질 수 있다.

// => xUnit Test Framework의 기능이 아닌, 구글 테스트의 기능입니다.
// EXPECT
//   EQ / NE ...
//   : 하나의 EXPECT문이 실패하면, 테스트의 결과는 실패한다.
//     이후의 코드는 계속 수행된다.
TEST(GoogleTest, Sample1) {
	int expected1 = 42;
	int expected2 = 100;

	// Act
	int actual1 = 42;
	int actual2 = 100;

	// Assert
	// ASSERT_EQ(expected1, actual1) << "Reason 1";  // Fail!
	// ASSERT_EQ(expected2, actual2) << "Reason 2";  // Fail!
	EXPECT_EQ(expected1, actual1) << "Reason 1";  // Fail!
	EXPECT_EQ(expected2, actual2) << "Reason 2";  // Fail!
}

// 2. 문자열 비교	
//  - const char* 기반의 문자열을 비교할 때 아래의 단언문을 사용해야 합니다.
//  : EXPECT_STREQ/STRNE
//    EXPECT_STRCASEEQ/STRCASENE
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	EXPECT_EQ(s1, s2);  // ==

	// C 문자열 - const char *
	const char* s3 = s1.c_str();
	const char* s4 = "hello";

	// EXPECT_EQ(s3, s4);
	EXPECT_STREQ(s3, s4);
	EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동 소수점
//  - EXPECT_DOUBLE_EQ/NE
//    EXPECT_FLOAT_EQ/NE
//    EXPECT_NEAR: 오차 범위를 직접 설정하는 것이 가능합니다.
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// 부동 소수점 타입은 ==을 통해 값의 같음을 비교하는 것이 어렵습니다.
	// EXPECT_EQ(a, b);
	// - https://en.wikipedia.org/wiki/Unit_in_the_last_place
	EXPECT_DOUBLE_EQ(a, b);  // 4ULP's
	EXPECT_NEAR(a, b, 0.000000001);
}

// SUT
void OpenFile(const std::string& filename) {
	if (filename.empty()) {
		throw std::invalid_argument("filename should not empty!");
	}

	// ...
}

// 4. 예외 테스트
// OpenFile에 잘못된 문자열이 전달될 경우, invalid_argument 예외가 발생하는지 검증하고 싶다.
//  => EXPECT_THROW
TEST(GoogleTest, Sample4) {
	std::string badFilename = "";

	EXPECT_THROW(OpenFile(badFilename), std::invalid_argument);
}

#if 0
TEST(GoogleTest, Sample4) {
	std::string badFilename = "";
	
	try {
		OpenFile(badFilename);
		FAIL() << "기대한 예외가 발생하지 않음";
	} catch (std::invalid_argument&) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음";
	}
}
#endif

// 5. 테스트 비활성화
//  => xUnit Test Framework은 테스트 비활성화 기능을 제공합니다.
//     - 비활성화 되어 있으면, 테스트 결과에 포함되지 않지만, 비활성화되어 있다는 사실을 알려줍니다.
//  방법: TestSuite 이름 또는 TestCase의 이름이 DISABLED_ 로 시작하면 됩니다.

// 비활성화된 테스트를 동작하는 방법
//  : ./a.out --gtest_also_run_disabled_tests

TEST(GoogleTest, DISABLED_Sample5) {
	FAIL() << "작성 중입니다.";
}

TEST(DISABLED_GoogleTest, Sample5) {
	FAIL() << "작성 중입니다.";
}










