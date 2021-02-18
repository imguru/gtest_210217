
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>

class StringTest : public testing::TestWithParam<std::string> {

};

std::vector<std::string> LoadStrings() {
	// 파일을 통해 데이터를 로드해서, vector에 채운다.
	std::vector<std::string> v;
	v.push_back("hello");
	v.push_back("world");
	v.push_back("Tom");

	return v;
}

using testing::ValuesIn;
INSTANTIATE_TEST_SUITE_P(stringValues, StringTest, 
	ValuesIn(LoadStrings()));

TEST_P(StringTest, StrTest) {
	std::string s = GetParam();

	std::cout << s << std::endl;
}
