
// 1. gtest 헤더 파일은 항상 동일합니다.
#include <gtest/gtest.h>

// 2. gtest를 사용하기 위해서 main을 작성하는 방법.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
