// 14_스파이

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
			// p->Write(level, message);
		}
	}
};

// FileTarget t1;
// NetworkTarget t2;
// DLogger logger;
// logger.AddTarget(&t1);
// logger.AddTarget(&t2);
//
// logger.Write(INFO, ".");




//------------------
#include <gtest/gtest.h>
#include <algorithm>

// Test Spy Pattern
// 의도: 함수를 호출하였을 때 발생하는 부수 효과 관찰할 수 없어서 테스트 되지 않은 요구사항이 존재한다.
// 방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//       "SUT 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다."

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




























