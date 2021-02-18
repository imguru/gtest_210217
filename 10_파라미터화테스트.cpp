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

int data[] = { 2, 3, 5, 7, 11, 13, 17, 19};

// 1. 루프
TEST(PrimeTest, IsPrime) {
	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; ++i) {
		EXPECT_TRUE(IsPrime(data[i]));
	}
}

// 2. 나열
TEST(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(19));
}


