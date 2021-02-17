// 1_시작.cpp
// - libgtest.a 에 main이 포함되어 있기 때문에, 별도의 main 함수를 작성할 필요가 없습니다.

// Test의 용어
//  - 1.10 이전에는 Google Test의 내부 용어와 xUnit Test Framework의 용어가 차이가 있습니다.

// [xUnit Test Framework / Google Test 1.10]
// TestSuite1
//   TestCase - 가장 작은 단위의 테스트
//   TestCase
//   TestCase

// TestSuite2
//   TestCase
//   TestCase
//
// [Google Test - 1.10 이전]
//  TestCase
//    Test
//    Test
//    Test

// TestCase를 만드는 방법
// - TEST(TestSuiteName, TestCaseName)

#include <gtest/gtest.h> // !!

// 작성 중인 테스트가 아래와 같이 되어 있을 경우, 잊혀집니다.
//  > 작성 중인 테스트는 명시적인 실패를 통해 알려야 합니다.
TEST(SampleTestSuite, FirstTestCase) {
	// FAIL();
	// 테스트가 실패할 경우, 실패의 원인을 지정하는 것이 중요합니다.
	
	FAIL() << "작성 중입니다.";
}

TEST(SampleTestSuite2, FirstTestCase) {

}

