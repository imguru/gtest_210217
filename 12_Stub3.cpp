
// Stub: 특수한 상황을 시뮬레이션 하고 싶다.
#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class User {
	Time* time;
public:
	User(Time* t) : time(t) {}

	int Do() {
		std::string t = time->GetCurrentTime();
		if (t == "00:00") {
			return 42;
		}

		return 0;
	}
};

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class StubTime : public Time {
public:
	MOCK_METHOD(std::string, GetCurrentTime, (), (override));
#if 0
	std::string GetCurrentTime() override {
		return "00:00";
	}
#endif
};

using testing::Return;
using testing::NiceMock;

TEST(UserTest, Do) {
	NiceMock<StubTime> time;
	ON_CALL(time, GetCurrentTime).WillByDefault(Return("00:00"));
	User user(&time);

	int actual = user.Do();

	EXPECT_EQ(42, actual);
}









