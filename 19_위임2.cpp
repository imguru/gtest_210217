
#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual int GetAge() const = 0;
};


class MockUser : public User {
public:
	MOCK_METHOD(int, GetAge, (), (const, override));
};

void Sample(User* p) {
	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());

	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());
	printf("%d\n", p->GetAge());
}

using testing::Return;

// EXPECT_CALL을 이용해서 결과를 제어하는 것이 가능합니다.
//  EXPECT_CALL(...).WillOnce
//                  .WillRepeatedly

// EXPECT_CALL + WillOnce + WillOnce + WillOnce => Times(3);
// EXPECT_CALL + WillOnce N 번 + WillRepeatedly => Times(atLeast(N));
// EXPECT_CALL + WillRepeatedly                 => Times(AnyNumber())

TEST(UserTest, Sample) {
	MockUser mock;

	EXPECT_CALL(mock, GetAge())
	//	.WillOnce(Return(10))
	//	.WillOnce(Return(20))
	//	.WillOnce(Return(30))
		.WillRepeatedly(Return(100));

	Sample(&mock);
}

#if 0
// 결과에 대한 제어와 행위 기반 검증을 같이 사용합니다.
TEST(UserTest, Sample) {
	MockUser mock;
	ON_CALL(mock, GetAge).WillByDefault(Return(10));

	EXPECT_CALL(mock, GetAge());
	
	Sample(&mock);
}
#endif
