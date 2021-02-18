// 8_FrinedTest.cpp
// SUT

class User {
protected:
	int age;

	int GetAge() const { return age; }
public:
	User() : age(42) {}
};

//----------
#include <gtest/gtest.h>

// protected의 경우 - 테스트 전용 하위 클래스
class TestUser : public User {
public:
	// 부모의 protected를 자식 클래스에 public으로 접근할 수 있도록 변경할 수 있습니다.
	using User::age;
	using User::GetAge;
};

TEST(UserTest, age) {
	TestUser user;

	// ...
	
	EXPECT_EQ(user.age, 42);
}
#if 0
TEST(UserTest, age) {
	User user;

	// ...
	
	EXPECT_EQ(user.age, 42);
}
#endif
