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
