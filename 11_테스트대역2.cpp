// SUT
#include <string>
#include <iostream>

// 1. 테스트 대역은 SUT가 테스트 대역을 적용할 수 있는 설계이어야 합니다.
// 2. 테스트 대역 설계 방법
//    - 의존 관계: 약한 결합의 형태로 구성되어 있어야 합니다.
//    DIP(의존 관계 역전 원칙)
//      : 의존하는 객체를 구체적인 타입이 아니라 인터페이스나 추상 타입을 통해 이용해야 한다.

//  약한 결합
//   1) 인터페이스 기반
//   2) 의존 하는 객체를 직접 생성하는 것이 아니라, 외부에서 생성해서 전달 받아야 합니다.
//     : new를 직접하면 안됩니다.
//     => DI(Dependency Injection)
//    
//    의존성 주입 방법
//      1) 생성자 주입
//        : 의존하는 객체가 필수적일 때
//      2) 메소드 주입
//        : 의존하는 객체가 필수적이지 않을 때
//
//    의존성 주입 문제점
//       : 보일러플레이트가 발생합니다.
//       => DI 프레임워크를 사용하면, 보일러플레이트를 효과적으로 제거할 수 있습니다.
//         Java: Dagger2
//         C++: fruit
//
//      C* pc = new C;
//      B* pb = new B;
//		A* pa = new A(pb, pc);
struct IFileSystem {
	virtual bool IsValid(const std::string& filename) = 0;

	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& filename) {
		return false;
	}
};

class Logger {
	IFileSystem* fileSystem;
public:
	// 기존에 사용하던 방식대로 사용할 수 있도록 만들어 주는 것이 좋다.
	//  => 틈새 만들기
	Logger(IFileSystem* p = nullptr) : fileSystem(p) {
		if (fileSystem == nullptr) {
			fileSystem = new FileSystem;
		}
	}
	~Logger() { delete fileSystem; }

	// file.log -> 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//-----------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		std::cout << name << std::endl;

		if (name.size() < 5) {
			return false;
		}
		//------------
		bool result = fileSystem->IsValid(filename);
		return result;
	}
};

#include <gtest/gtest.h>

class LoggerTest : public testing::Test {
};

// FileSystem의 역활을 대신 테스트 대역을 만들어야 합니다.
class TestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

// 파일의 이름이 5글자 이상일때 true를 반환하는지 여부를 검증한다.
TEST_F(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue) {
	TestDouble* td = new TestDouble;
	Logger logger(td);
	std::string validFilename = "valid_filename.log";

	bool actual = logger.IsValidLogFilename(validFilename);

	EXPECT_TRUE(actual) << "파일명이 5글자 이상일 때";
	// EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 5글자 이상일 때";
}

// 파일의 이름이 5글자 미만일 때 false를 반환하는지 여부를 검증한다.
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestDouble* td = new TestDouble;
	Logger logger(td);
	std::string badFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(badFilename)) << "파일명이 5글자 미만일 때";
}

#if 0
// 파일의 이름이 5글자 이상일때 true를 반환하는지 여부를 검증한다.
TEST_F(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid_filename.log";

	bool actual = logger.IsValidLogFilename(validFilename);

	EXPECT_TRUE(actual) << "파일명이 5글자 이상일 때";
	// EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 5글자 이상일 때";
}

// 파일의 이름이 5글자 미만일 때 false를 반환하는지 여부를 검증한다.
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string badFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(badFilename)) << "파일명이 5글자 미만일 때";
}
#endif























