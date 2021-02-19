// 15_모의객체
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (auto p : targets) {
			p->Write(level, message);
		}
	}
};

//------------------
#include <gtest/gtest.h>

// Google Mock
// 1.
#include <gmock/gmock.h>

// 2. Mock Object 생성 - Mocking
//  virtual void Write(Level level, const std::string& message) = 0;
class MockDLoggerTarget : public DLoggerTarget {
public:
	// MOCK_METHOD{인자개수}(함수 이름, 함수의 타입)
	MOCK_METHOD2(Write, void (Level level, const std::string& message));
};

// 3. 행위 기반 검증을 기반으로 테스트 케이스를 작성
//  => 주의 사항
//     Google Mock은 Act를 수행하기 전에 검증하고자 하는 로직을 먼저 작성해야 합니다.
TEST(DLoggerTarget, Write) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget mock1, mock2;
	logger.AddTarget(&mock1);
	logger.AddTarget(&mock2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	// Assert
	EXPECT_CALL(mock1, Write(test_level, test_message));
	EXPECT_CALL(mock2, Write(test_level, test_message));

	// Act
	logger.Write(test_level, test_message);
}
// Mock Object Pattern
// 의도: 함수를 호출하였을 때 발생하는 부수 효과 관찰할 수 없어서 테스트 되지 않은 요구사항이 존재한다.
// 방법: 
//      Test Spy - "SUT 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다."
//      Mock Object - 행위 기반 검증을 수행한다.
//          상태 검증: 객체에 작용을 가한 후 내부적으로 변경된 값을 단언문을 통해 상태값을 검증한다.
//          동작 검증: 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 순서, 횟수 등을 통해 검증한다.
//			
//     모의 객체
//        : 내부적으로 발생한 함수의 호출 여부, 횟수, 순서 등의 정보를 기록한다.
//        => Mock Framework을 이용해서 모의 객체를 손쉽게 생성할 수 있습니다.
//          Java: jUnit + (jMock / EasyMock / Mockito)
//          C++: Google Mock

#if 0
class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string Concat(Level level, const std::string& message) {
		static const char* levelStr[] = {
			"I", "W", "E",
		};

		return std::string(levelStr[level]) + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(Concat(level, message));
	}

	// 핵심: 테스트에서 확인할 수 있도록 하는 함수를 제공해야 합니다.
	bool IsReceived(Level level, const std::string& message) {
		return std::find(history.begin(), history.end(), Concat(level, message)) != history.end();
	}
};

TEST(DLoggerTarget, Write) {
	DLogger logger;
	SpyTarget spy1, spy2;
	logger.AddTarget(&spy1);
	logger.AddTarget(&spy2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	logger.Write(test_level, test_message);

	EXPECT_TRUE(spy1.IsReceived(test_level, test_message));
	EXPECT_TRUE(spy2.IsReceived(test_level, test_message));
}
#endif




























