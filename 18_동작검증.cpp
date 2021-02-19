
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
//    
//    AtLeast(N): 적어도 N번 이상
//    AtMost(N): 최대 N번 이하
//
//  => 인자의 정보가 일치해야한다.
//     Matcher(Hamcrest)

using testing::AtLeast;
using testing::AtMost;
using testing::Between;

void Sample2(User* p) {
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(11, 21);
}

using testing::Lt; // <
using testing::Gt; // >
using testing::Eq; // ==
using testing::Ne; // !=
using testing::Le; // <=
using testing::Ge; // >=
using testing::_;  // 상관없음.

using testing::AllOf;  // &&
using testing::AnyOf;  // ||
using testing::Matcher;

// Go의 호출 여부를 검증한다.
//  첫번째 인자 - x != 0
//  두번째 인자 - 상관없습니다.
TEST(UserTest, Sample2) {
	MockUser mock;
	
	// Times를 한번만 사용해야 합니다.
	EXPECT_CALL(mock, Go(Ne(0), _)).Times(Between(2, 5));

	Sample2(&mock);
}
#if 0
// Go의 호출 여부를 검증한다.
//   첫번째 인자 - x >= 10 && x < 20
//   두번째 인자 - x < 0 || x > 10

TEST(UserTest, Sample2) {
	MockUser mock;
	Matcher<int> firstArg = AllOf(Ge(10), Lt(20));
	Matcher<int> secondArg = AnyOf(Lt(0), Gt(10)); 
	
	EXPECT_CALL(mock, Go(firstArg, secondArg)).Times(3);

	Sample2(&mock);
}
#endif

#if 0
// Go의 첫번째 인자는 10 이상이고, 두번째 인자는 25이하로 최대 3번 호출된다.
TEST(UserTest, Sample2) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(10, 20)).Times(3);
	EXPECT_CALL(mock, Go(Ge(10), Le(25))).Times(AtMost(3));

	Sample2(&mock);
}
#endif

#if 0
TEST(UserTest, Sample2) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(10, 20)).Times(3);
	EXPECT_CALL(mock, Go(10, 20)).Times(AtLeast(1));

	Sample2(&mock);
}
#endif




