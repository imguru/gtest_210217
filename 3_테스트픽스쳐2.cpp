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
//  2. Delegate Setup(위임 설치)
//    - 별도의 테스트 유틸리티 함수를 통해 캡슐화한다.
//   TEST: 암묵적인 TestSuite을 이용합니다.
//   TEST_F: 명시적으로 TestSuite을 만들어야 합니다.

#include <gtest/gtest.h>

// Test Suite
//  - 동일한 픽스쳐를 가지는 테스트 케이스의 집합이다.


#if 0
// TEST
TEST(SampleTest, foo) {}  // class SampleTest_foo : public testing::Test {}; 
TEST(SampleTest, goo) {}  // class SampleTest_goo : public testing::Test {};

            testing::Test
                  |
            ------------
            |          |
           foo        goo

// TEST_F
class SampleTest : public testing::Test {};
TEST_F(SampleTest, foo) {}
TEST_F(SampleTest, goo) {}

           testing::Test
                 |
             SampleTest
                 |
            ------------
            |          |
           foo        goo
#endif

//  Step 1. TestSuite 클래스를 생성합니다.
class CalculatorTest : public ::testing::Test {
protected:
	// Test Utility Method - Creation Method
	//  => Google Test 에서 제공할 때에는 protected / public 으로 만들어야 합니다.
	Calculator* Create() { return new Calculator; }
};

// Step 2. TestCase를 만들 때 TEST를 통해 만들었지만, TEST_F를 통해 만들어야 합니다.
TEST_F(CalculatorTest, PlusTest) {
	Calculator* calc = Create();

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
	// Arrange
	Calculator* calc = Create();
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 4) << "2 더하기 2를 하였을 때";
}








