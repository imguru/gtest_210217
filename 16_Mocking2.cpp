
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct Element {};


// 1. GoogleMock을 통해 Mocking 하고자하는 인터페이스나 클래스는 반드시 가상 소멸자를 제공해야 한다.
// 2. SUT의 메소드의 기본 구현이 제공될 경우, 행위 기반 검증이 필요하다면 Mocking을 하고, 필요하지 않으면 하지 않아도 됩니다.
//    SUT의 메소드가 기본 구현을 제공하지 않는 순수 가상 함수일 경우,
//    반드시 Mocking이 필요합니다.
// 3. 이름이 동일한 다른 함수가 가려질 경우, using 선언을 통해 문제를 해결할 수 있습니다.
// 4. MOCK_METHOD를 통해 Mocking된 메소드는 더 이상 구현을 호출하지 않습니다.

class Calc {
	int x;
public:
	virtual ~Calc() {}  // 가상 소멸자는 상속을 기반으로 할때 반드시 필요합니다.

	// 행위 검증이 필요하지 않습니다.
	virtual int Add(Element x) {
		printf("Calc.Add(Element)\n");
	}
	virtual int Add(int times, Element x) {
		printf("Calc.Add(int, Element)\n");
	}

	// 행위 검증 필요합니다.
};

// 클래스를 상속할 수 있다면, 모의 객체로 만드는 것이 가능합니다.
class MockCalc : public Calc {
public:
	// 더 이상 기존 함수는 호출되지 않습니다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));

	// 함수가 가려지는 문제가 발생할 경우, 아래의 코드가 필요합니다.
	using Calc::Add;
};

void Sample(Calc* p) {
	p->Add(Element());
	p->Add(10, Element());
}

bool operator==(const Element& lhs, const Element& rhs) {
	return true;
}

TEST(MockCalc, Add) {
	MockCalc mock;

	EXPECT_CALL(mock, Add(10, Element()));
	
	// MockCalc가 Add라는 구현이 감추어지는 현상이 발생한다.
	mock.Add(Element());
	mock.Add(10, Element());

	// Sample(&mock);
}





