
// 5_전역픽스쳐.cpp
//  - xUnit Test Framework의 기능이 아니라 GoogleTest의 고유의 기능입니다.


// 1. 테스트 픽스쳐 - TestCase 마다 수행되는 SetUp / TearDown      => 신선한 픽스쳐 전략
// 2. 스위트 픽스쳐 - TestSuite 마다 수행되는 SetUp / TearDown     => 공유 픽스쳐 전략 
// 3. 전역 픽스쳐   - 프로그램 시작/끝에 수행되는 SetUp / TearDown 
//                  => 프로그램을 검증하기 위해 필요한 설정 작업

#include <gtest/gtest.h>

TEST(SampleTest, foo) {}
TEST(SampleTest, goo) {}

TEST(MyTest, foo) {}
TEST(MyTest, goo) {}

class MyTestEnvironment : public testing::Environment {
public:
	void SetUp() override {
		printf("Global SetUp()\n");
	}
	
	void TearDown() override {
		printf("Global TearDown()\n");
	}
};

//  전역 픽스쳐를 설치하는 방법 2가지
//  1) 전역 변수 - libgtest에 main을 포함한 경우

testing::Environment* env = testing::AddGlobalTestEnvironment(new MyTestEnvironment); 


//  2) main 함수 - libgtest에 main을 포함하지 않은 경우








