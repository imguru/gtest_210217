
// 19_위임.cpp

struct Calc {
	virtual ~Calc() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));
};

void Sample(Calc* p) {
	printf("Add: %d\n", p->Add(10, 20));
	printf("Sub: %d\n", p->Sub(30, 20));
}

// Mocking 된 메소드가 호출되었을 때, 어떤 동작을 수행할지 정의할 수 있다. - Google Mock의 기능입니다.
//  => ON_CALL(mock, Add).WillByDefault
//    : Stub / Fake에서 활용됩니다.

using testing::Return;

TEST(CalcTest, Sample) {
	MockCalc mock;
	ON_CALL(mock, Add).WillByDefault([](int a, int b) {
		return a + b;
	});
	ON_CALL(mock, Sub).WillByDefault(Return(10));

	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Sub(30, 20));

	Sample(&mock);

}


// 결과에 대한 제어와 행위 기반 검증을 같이 사용합니다.
TEST(CalcTest, Sample) {
	MockCalc mock;
	ON_CALL(mock, Add).WillByDefault([](int a, int b) {
		return a + b;
	});
	ON_CALL(mock, Sub).WillByDefault(Return(10));

	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Sub(30, 20));

	Sample(&mock);
}

// Test Double
//  1. Stub
//  2. Fake
//  3. Spy
//  4. Mock - 행위 기반 검증








