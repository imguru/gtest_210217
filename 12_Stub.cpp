
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

// Player의 Move를 수행했을 때, Network 연결이 없을 경우, 예외가 제대로 발생하는지 여부를 검증하고 싶다.

//  Test Stub Pattern
//  의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 한다.
//   => "특수한 상황"을 시뮬레이션 하고 싶다.
//     : 네트워크 오류, 시간 등의 제어가 불가능한 환경을 제어할 수 있다.

class StubConnection : public IConnection {
public:
	void Move(int x, int y) {
		throw NetworkException();
	}
	virtual void Attack() {
	}
};


TEST(PlayerTest, Move_TestDouble) {
	StubConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}
#if 0
TEST(PlayerTest, Move) {
	TCPConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}
#endif











