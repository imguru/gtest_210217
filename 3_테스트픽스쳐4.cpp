
#include <gtest/gtest.h>

// - xUnit Test Framework
// Test Runner가 TestCase를 실행하는 흐름
//------
#if 0
// => 신선한 픽스쳐의 전략
//   : TestSuite 객체를 한번만 생성해서 사용하는 것이 아니라,
//     각 TestCase마다 새롭게 생성해서 사용한다.
SampleTest* ts = new SampleTest;
ts->SetUp();
ts->foo();
ts->TearDown();
delete ts;

SampleTest* ts = new SampleTest;
ts->SetUp();
ts->goo();
ts->TearDown();
delete ts;

#endif
//------
class SampleTest : public testing::Test {
protected:
	SampleTest() { printf("SampleTest()\n"); }
	~SampleTest() { printf("~SampleTest()\n"); }

	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(SampleTest, foo) {
	printf("  SampleTest.foo()\n");
}

TEST_F(SampleTest, goo) {
	printf("  SampleTest.goo()\n");
}
