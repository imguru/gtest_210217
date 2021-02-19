
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct Element {};

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





