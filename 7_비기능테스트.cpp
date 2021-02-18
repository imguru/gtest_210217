
// 7_비기능테스트.cpp
//  : 요구사항에 부합되는 기능적인 동작뿐 아니라,
//    성능, 메모리 등의 비기능 적인 요구사항을 검증하는 방법.

#include <gtest/gtest.h>
#include <unistd.h>

void LoadFromNetwork() {
	sleep(1);
}

#define EXPECT_TIMEOUT(fn, sec)				    \
	do {									    \
	  time_t startTime = time(0);				\
	  fn;										\
	  time_t endTime = time(0);				    \
	  time_t duration = endTime - startTime;	\
	  EXPECT_LE(duration, sec) << "시간 초과: " << duration << "초가 걸렸습니다."; \
	} while (0)

TEST(NetworkTest, LoadFromNetwork) {
	EXPECT_TIMEOUT(LoadFromNetwork(), 2);
	// int duration;
}

// LoadFromNetwork는 2초 안에 수행되어야 한다.
//  => 아래 테스트 케이스처럼 시간을 측정해야 하는 경우가 많다면, 별도의 테스트 유틸리티 함수를 통해 제공하는 것이 좋습니다.
//    단언 매크로를 통해 제공합니다.
TEST(NetworkTest, LoadFromNetwork_Bad) {
	//---
	time_t startTime = time(0);
	LoadFromNetwork();
	time_t endTime = time(0);
	time_t duration = endTime - startTime;
	//---
	
	EXPECT_LE(duration, 2) << "시간 초과: " << duration << "초가 걸렸습니다.";
}


