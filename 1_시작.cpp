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

TEST(SampleTestSuite, FirstTestCase) {

}

TEST(SampleTestSuite2, FirstTestCase) {

}












