
#include <gtest/gtest.h>

// - xUnit Test Framework
// Test Runner가 TestCase를 실행하는 흐름
//------
#if 0
SampleTest* ts = new SampleTest;
ts->SetUp();
ts->foo();
ts->TearDown();

ts->SetUp();
ts->goo();
ts->TearDown();

#endif
//------
class SampleTest : public testing::Test {
protected:
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
