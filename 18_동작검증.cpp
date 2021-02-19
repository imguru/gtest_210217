
// 18_동작검증(행위기반검증)

// 동작 검증
// 1. 함수의 호출 여부
// 2. 함수의 호출 횟수
// 3. 함수의 호출 순서
// => 함수 인자 검증

#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual int Go(int x, int y) = 0 ;
	virtual void Say(const char* message) = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(int, Go, (int x, int y), (override));
	MOCK_METHOD(void, Say, (const char* message), (override));
};

// 호출 여부
//  => EXPECT_CALL
void Sample1(User* p) {
	p->Go(10, 20);
	p->Say("Hello");
}

TEST(UserTest, Sample1) {
	MockUser mock;

	EXPECT_CALL(mock, Go(10, 20));
	EXPECT_CALL(mock, Say("Hello"));

	Sample1(&mock);
}

// 호출 횟수
//  => EXPECT_CALL(...).Times(N);
void Sample2(User* p) {
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
}

TEST(UserTest, Sample2) {
	MockUser mock;

	EXPECT_CALL(mock, Go(10, 20)).Times(3);

	Sample2(&mock);
}




