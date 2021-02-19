#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct User {
	virtual ~User() {}

	virtual void Say() = 0;
	virtual void Go() = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(void, Say, (), (override));
	MOCK_METHOD(void, Go, (), (override));
};

void UseUser(User* p) {
	p->Say();
	p->Go();
	// MOCK_METHOD를 한 메소드가 호출되었음에도 불구하고,
	// TEST 코드 안에서 EXPECT_CALL을 호출하지 않았습니다.
	//  - Mock 종류
	//    1. Naggy Mock(기본)
	//      : 경고가 발생한다.
	//        NaggyMock<MockUser> mock;
	//    2. Nice Mock
	//      : 경고가 발생하지 않는다.
	//        NiceMock<MockUser> mock;
	//    3. Strict Mock
	//      : 테스트가 실패합니다.
	//        StrictMock<MockUser> mock;
	//        => 테스트를 통과하는 기준이 어려워지기 때문에, 단위 테스트 작성 비용이 증가할 수 있다.
}

using testing::NiceMock;
using testing::StrictMock;
using testing::NaggyMock;

TEST(UserTest, Say) {
	// MockUser mock;
	// NiceMock<MockUser> mock;
	// StrictMock<MockUser> mock;
	NaggyMock<MockUser> mock;

	EXPECT_CALL(mock, Say());

	UseUser(&mock);
}
