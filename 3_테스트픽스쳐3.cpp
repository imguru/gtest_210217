// 3_테스트픽스쳐.cpp

class Calculator {
public:
	double Display() { return 4; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	// Calculator(int n) {}
};

// 픽스쳐를 설치하는 방법 
// 방법 3. Implicit Setup(암묵적 설치)
//    : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp 함수에서 생성한다.
//     => xUnit Test Framework가 제공하는 기능입니다.
//     => 명시적인 Test Suite 클래스를 만들어야 합니다.

//  장점: 테스트 코드 중복을 제거하고, 필요하지 않은 상호작용을 캡슐화할 수 있습니다.
//  단점: 픽스쳐 설치 코드가 테스트 함수 외부에 존재하지 때문에, 테스트 함수 만으로는 테스트 코드를 이해하기 어려울 수 있다.

#include <gtest/gtest.h>

class CalculatorTest : public testing::Test {
protected:
	Calculator* calc;
	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}
};

TEST_F(CalculatorTest, PlusTest) {
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

TEST_F(CalculatorTest, Plus_2Plus2_Displays4) {
	SPEC("> 2 더하기 2를 하였을 때 4가 나오는지 확인한다\n");
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 더하기 2를 하였을 때";
}








