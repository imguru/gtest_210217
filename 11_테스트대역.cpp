// SUT
#include <string>
#include <iostream>

class FileSystem {
public:
	virtual bool IsValid(const std::string& filename) {
		return false;
	}
};

class Logger {
public:
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

		FileSystem* fileSystem = new FileSystem;
		bool result = fileSystem->IsValid(filename);
		delete fileSystem;
		return result;
	}
};

#include <gtest/gtest.h>

class LoggerTest : public testing::Test {
};


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























