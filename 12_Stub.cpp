
// 12_Stub.cpp
//  Test Stub Pattern

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

// Player의 Move를 수행했을 때, Network 연결이 없을 경우, 예외가 제대로 발생하는지 여부를 검증하고 싶다.

TEST(PlayerTest, Move) {
	TCPConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}











