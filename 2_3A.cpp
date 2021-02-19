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
// 1. Arrange: 테스트 하고자 하는 클래스의 객체를 생성하고, 필요한 경우 적절하게 설정하고 준비한다. - Given
// 2. Act: 객체에 작용을 가한다. - When
// 3. Assert: 기대하는 바를 단언한다. - Then

// TDD - Test Driven Development
// BDD - Behaviour Driven Development
//   1) 용어 차이
//      => "가독성": 테스트 코드를 사람의 언어와 비슷하게 만드는 것이 중요하다. - Hamcrest
//   2) 상태 기반 검증 보다는 행위 기반 검증
//      => Mock Framework을 적극적으로 활용한다.

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

// 단위 테스트 코드의 품질
// 1. 가독성
// 2. 유지보수성
//  - 테스트 코드 안에서 제어 구문의 발생을 최소화 해야 합니다.
//   ; 조건문, 반복문, 예외 처리 구문
// 3. 신뢰성

#define SPEC printf

// Test Case의 이름을 통해서 시나리오가 드러날 수 있어야 한다.
//   ex) 테스트대상함수_시나리오_기대값
//   ex) SPEC 매크로 함수
TEST(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("> 2 더하기 2를 하였을 때 4가 나오는지 확인한다\n");
	// Arrange
	Calculator* calc = new Calculator;
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	//  xUnit Test Framework은 조건에 부합되는지 여부를 검증하기 위한 다양한 함수를 제공합니다.
	//  => ASSERT_EQ / NE ...
	ASSERT_EQ(calc->Display(), 4) << "2 더하기 2를 하였을 때";
}








