
// 4_스위트픽스쳐.cpp

// SUT
#include <unistd.h>
#include <string>

class Database {
public:
	// Connect / Disconnect가 느리다.
	void Connect() { sleep(2); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//------
#include <gtest/gtest.h>

// 문제점: 테스트 픽스쳐 설치/해체로 인해 느린 테스트의 문제가 발생하였다.
//  => 느린 테스트(Slow Test)
//    : 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//      테스트가 느려서 아무도 코드가 변경되어도, 테스트를 수행하고자 하지 않는다.
//    해결방법: 스위트 픽스쳐 설치 / 해체를 이용하면 됩니다.
//      => xUnit Test Framework가 제공하는 기능입니다.

// Suite Fixture SetUp / TearDown
//  => 더 이상 신선한 픽스쳐의 전략을 사용할 수 없습니다.
//     : 공유 픽스쳐 전략
//   - TestSuite 안에 있는 모든 TestCase가 같은 픽스쳐를 공유하고 있습니다.
//   문제점: 더 이상 TestCase는 독립적이지 않습니다.
//           "변덕스러운 테스트" 문제가 발생할 가능성이 있습니다.
//           테스트케이스의 신뢰성에 문제가 발생합니다.
//    - 공유 픽스쳐의 전략을 사용할 경우, 하나의 TestSuite에 너무 많은 테스트 케이스를 두지 않는 것이 좋습니다.

// DatabaseTest - 100
//   => DatabaseTest1 - 50 - 25/25
//      DatabaseTest2 - 50 - 25/25

class DatabaseTest : public testing::Test {
protected:
	static Database* db;

#if 1 // 1.10 
	static void SetUpTestSuite() {
		db = new Database;
		db->Connect();
	}

	static void TearDownTestSuite() {
		db->Disconnect();
		delete db;
	}
#endif
#if 0 // 1.10 이전
	static void SetUpTestCase() {
		db = new Database;
		db->Connect();
	}

	static void TearDownTestCase() {
		db->Disconnect();
		delete db;
	}
#endif

	void SetUp() override {
		// db = new Database;
		// db->Connect();
	}

	void TearDown() override {
		// db->Disconnect();
		// delete db;
	}
};

// 정적 멤버 변수는 외부 정의가 필요합니다. - 소스 파일
Database* DatabaseTest::db = nullptr;

TEST_F(DatabaseTest, LoginTest) {
	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(DatabaseTest, foo) {}
TEST_F(DatabaseTest, goo) {}


#if 0
TEST(DatabaseTest, LoginTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";

	db->Disconnect();
	delete db;
}

TEST(DatabaseTest, LogoutTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";

	db->Disconnect();
	delete db;
}
#endif













