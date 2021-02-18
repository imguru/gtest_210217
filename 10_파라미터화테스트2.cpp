// 10_파라미터화테스트.cpp

// SUT
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) {
			return false;
		}
	}

	return true;
}

#include <gtest/gtest.h>

// 해결 방법: 파라미터화 테스트 패턴 
//   의도: 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심 테스트에서 코드 중복을 없애는 기법.
//   => xUnit Test Framework의 기능입니다.
//
// int data[] = { 2, 3, 5, 7, 11, 13, 17, 19};

// 적용 방법
// 1) Test Suite class을 명시적으로 작성해야 합니다.
//   기존 
// class PrimeTest : public testing::Test {};

//   파라미터화 테스트
// class TestSuiteName : public testing::TestWithParam<InputType> {};

class PrimeTest : public testing::TestWithParam<int> {
};

// 2) DataSet 정의 - 전역 변수(매크로)
// INSTANTIATE_TEST_SUITE_P(변수명, TestSuiteName, 데이터);
INSTANTIATE_TEST_SUITE_P(primeValues, PrimeTest, testing::Values(2, 3, 5, 7, 11, 13, 17, 19));


// 3) TestCase를 만들면 됩니다.
//  TEST / TEST_F
// => TEST_P를 통해 TestCase를 만들어야 합니다.
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}
















