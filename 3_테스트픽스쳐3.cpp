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
// 방법 3. Implicit Setup/TearDown(암묵적 설치/해체)
//    : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp 함수에서 생성한다.
//     => xUnit Test Framework가 제공하는 기능입니다.
//     => 명시적인 Test Suite 클래스를 만들어야 합니다.

//  장점: 테스트 코드 중복을 제거하고, 필요하지 않은 상호작용을 캡슐화할 수 있습니다.
//  단점: 픽스쳐 설치 코드가 테스트 함수 외부에 존재하지 때문에, 테스트 함수 만으로는 테스트 코드를 이해하기 어려울 수 있다.

#include <gtest/gtest.h>


// xUnit Test Pattern에서 테스트 케이스를 구성하는 방법 - 4단계 테스트 패턴(Four Phase Test Pattern)
// 1단계 - 테스트 픽스쳐를 설치하거나 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업을 한다. - SetUp()
// 2단계 - SUT와 상호작용한다. - TestBody()
// 3단계 - 기대 결과를 확인한다. - TestBody()
// 4단계 - 테스트 픽스쳐를 해체해서 테스트 시작 이전의 상태로 돌려놓는다. - TearDown()

class CalculatorTest : public testing::Test {
protected:
	Calculator* calc;
	void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	void TearDown() override {
		printf("TearDown()\n");
		delete calc;
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

	// 아래처럼 작성할 경우, 문제가 발생할 수 있습니다. => 위의 ASSERT가 실패할 경우.
	//  => 단언문이 실패할 경우, 이후의 코드는 더 이상 수행되지 않습니다.
	// delete calc;
	// printf("Delete\n");
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

TEST_F(CalculatorTest, Sample) {
}







