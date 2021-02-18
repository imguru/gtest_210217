
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

// 테스트 대역을 고려한다면, 범용 인터페이스보다는 세분화된 인터페이스가 좋다.
//  ISP(Interface Segregation Principle) - 인터페이스 분리 원칙
//   => 테스트 대역을 만드는 부담을 줄일 수 있다.
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
		// ...
		// ...
		database->SaveUser(u->GetName(), u);
		// ...
		// ...
	}

	User* Load(const std::string& name) {
		// ...
		// ...
		return database->LoadUser(name);
	}
};

//--------------------------
#include <gtest/gtest.h>
#include <map>

// 문제점: 아직 Database 구현체가 제공되지 않는다.
//         UserManager를 검증할 수 없다.

// Fake Object Pattern
// 의도: 아직 준비되지 않은 의존 객체로 인해서, 테스트 되지 않은 요구사항이 있다.
// 방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서 문제를 해결할 수 있다.

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
};

TEST(UserManagerTest, Save) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_EQ(*actual, expected) << "로드 하였을 때";
}
