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

// 픽스쳐를 설치하는 방법 


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








