
// 4_스위트픽스쳐.cpp

// SUT
#include <unistd.h>
#include <string>

class Database {
public:
	void Connect() {}
	void Disconnect() {}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//------
#include <gtest/gtest.h>

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













