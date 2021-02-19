
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

//----
struct Foo {
	virtual ~Foo() {}

	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
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


// 호출 순서 검증
//  : EXPECT_CALL은 기본적으로 순서를 판단하지 않습니다.
//
//  1) InSequence 객체
//     - InSequence 객체를 생성하면, 전체적인 순서를 검증할 수 있다.

using testing::InSequence;

void Sample3(Foo* p) {
	p->First();
	p->Forth();
	p->Third();
	p->Second();
}

using testing::Sequence;
//  2) Sequence 객체
//     First ---- Second          ; s1
//            |
//            |
//            --- Third - Forth   ; s2

TEST(FooTest, Sample3) {
	MockFoo mock;
	Sequence s1, s2;

	EXPECT_CALL(mock, First()).InSequence(s1, s2);
	EXPECT_CALL(mock, Second()).InSequence(s1);
	EXPECT_CALL(mock, Third()).InSequence(s2);
	EXPECT_CALL(mock, Forth()).InSequence(s2);
	
	Sample3(&mock);
}




#if 0
// First -> Second -> Third -> Forth
TEST(FooTest, Sample3) {
	InSequence seq;         // !!!!
	MockFoo mock;

	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());
	EXPECT_CALL(mock, Third());
	EXPECT_CALL(mock, Forth());
	
	Sample3(&mock);
}
#endif






















