// 3_테스트픽스쳐.cpp

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// Calculator(int n) {}
};

//---------
// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 것을 Test Fixture 라고 합니다.
//        픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐 설치(Fixture Setup)" 라고 합니다.

// 픽스쳐를 설치하는 방법 
//  1. Inline Fixture Setup
//   : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//  
//  장점: 픽스쳐를 설치하는 과정과 검증 로직이 테스트 함수 안에 존재하기 떄문에
//        인과관계를 쉽게 분석할 수 있다.
//  단점: 모든 테스트 코드 안에서 '코드 중복'이 발생한다.


#include <gtest/gtest.h>

TEST(CalculatorTest, PlusTest) {
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL() << "2 + 2 하였을 때 4가 나와야 합니다.";
	}
}

#define SPEC printf

TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("> 2 더하기 2를 하였을 때 4가 나오는지 확인한다\n");
	// Arrange
	Calculator* calc = new Calculator;
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 더하기 2를 하였을 때";
}








