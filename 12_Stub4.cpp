
// 12_Stub.cpp

// SUT
#include <iostream>

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	virtual void Attack() = 0;
};

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad Network State";
	}
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) {
		// TCP packet 만들어서 서버로 이동 메세지를 보냅니다.
	}
	virtual void Attack() {
	}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p = nullptr) : conn(p) {
		if (conn == nullptr) {
			conn = new TCPConnection;
		}
	}

	void Move(int x, int y) {
		//----
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			//....
			throw e;  // NetworkException을 외부로 다시 던진다.
		}
		//----
	}
};

///------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class StubConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
	MOCK_METHOD(void, Attack, (), (override));

#if 0
	void Move(int x, int y) {
		throw NetworkException();
	}
	virtual void Attack() {
	}
#endif
};

using testing::Throw;
using testing::NiceMock;

// 제품 코드를 사용하는 방식 그대로 테스트 코드를 작성할 수 있다.
TEST(PlayerTest, Move_TestDouble) {
	NiceMock<StubConnection> conn;
	ON_CALL(conn, Move).WillByDefault(Throw(NetworkException()));
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}







