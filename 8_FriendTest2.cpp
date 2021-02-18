// 8_FrinedTest.cpp
// SUT

#if 0
class User {
private:
	int age;

	int GetAge() const { return age; }
public:
	User() : age(42) {}
};
#endif

//----------
#include <gtest/gtest.h>

// 절대 사용하면 안됩니다.
// #define private public
// #define class struct
#include "User.h"
// #undef private
// #undef class

// SUT의 private 필드나 메소드에 접근할 필요성이 있다.
// 하지만, 제품 코드의 전략을 변경하고 싶지 않다.
//  FRIEND_TEST 라는 기능을 이용해서, 테스트 케이스에서만 접근할 수 있도록 할 수 있습니다.
//   => 문제점: 제품 코드가 google test에 대한 의존성이 발생합니다.

TEST(UserTest, age) {
	User user;

	// ...
	
	EXPECT_EQ(user.age, 42);
}





