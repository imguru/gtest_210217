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
	int actual1 = 420;
	int actual2 = 1000;

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
	double b = 0.1 * 8;

	// 부동 소수점 타입은 ==을 통해 값의 같음을 비교하는 것이 어렵습니다.
	// EXPECT_EQ(a, b);
	// - https://en.wikipedia.org/wiki/Unit_in_the_last_place
	EXPECT_DOUBLE_EQ(a, b);  // 4ULP's
	EXPECT_NEAR(a, b, 0.000000001);
}


















