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
			// p->Write(level, message);
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

// 테스트 대역
//  핵심: 테스트 대역을 직접 작성하는 것 보다는 Mock Framework를 이용해서 사용하면 편리합니다.
//
//  정리
//    1. Stub: 특수한 상황을 시뮬레이션 한다. 협력 객체에 대해서 원하는 결과를 주는 테스트 대역
//    2. Fake: 의존 하는 객체가 준비되지 않거나, 사용하기 어려울 때 가벼운 테스트 대역을 만들어서
//             테스트를 수행한다.
//    3. Spy: 객체에 작용을 가했을 때, 관찰할 수 있는 부수효과가 없다.
//            숨겨진 정보를 확인할 수 있는 테스트 대역을 만들어서 검증한다.
//    4. Mock: 객체에 작용을 가했을 때, 관찰할 수 있는 부수효과가 없다.
//            행위 기반 검증 - 함수의 호출 여부 / 호출 횟수 / 호출 순서에 대한 부분을 통해 검증한다.
//
//    => Google Mock을 이용하면 Stub / Fake / Mock을 다 만족할 수 있습니다.
//      한계: Mock Object를 생성하는 Mocking 작업을 이해해야 합니다.
