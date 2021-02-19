
#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* u) {
		// ...검증해야 코드
		// ...
		database->SaveUser(u->GetName(), u);
		// ...
		// ...
	}

	User* Load(const std::string& name) {
		// ...검증해야 코드
		// ...
		// ...
		return database->LoadUser(name);
	}
};

//--------------------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <map>

class FakeDatabase : public IDatabase {
public:
	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));
};

bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

using testing::NiceMock;

TEST(UserManagerTest, Save) {
	NiceMock<FakeDatabase> fake;
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);
	ON_CALL(fake, LoadUser).WillByDefault([&](const std::string& name) {
		return &expected;
	});
	UserManager manager(&fake);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	ASSERT_NE(actual, nullptr);
	EXPECT_EQ(*actual, expected) << "로드 하였을 때";
}






