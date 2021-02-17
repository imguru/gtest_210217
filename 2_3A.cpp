// 2_3A.cpp
//  - 단위 테스트를 구성하는 방법.

// 테스트 대상 코드
//  - SUT(System Under Test)
//  - CUT(Class or Code Under Test)

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

//---------
#include <gtest/gtest.h>

// 1. Test Suite의 이름은 테스트 대상 클래스의 마지막에 Test/Spec 접미를 붙이는 것이 일반적입니다.
//  => CalculatorTest / CalculatorSpec

// 3A
// 1. Arrange: 테스트 하고자 하는 클래스의 객체를 생성하고, 필요한 경우 적절하게 설정하고 준비한다.
// 2. Act: 객체에 작용을 가한다.
// 3. Assert: 기대하는 바를 단언한다.

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










