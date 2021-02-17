
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

class DatabaseTest : public testing::Test {
protected:
	Database* db;

	void SetUp() override {
		db = new Database;
		db->Connect();
	}

	void TearDown() override {
		db->Disconnect();
		delete db;
	}
};

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













