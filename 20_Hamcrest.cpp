
// Hamcrest
//  => Matcher 라이브러리
//  => 단언문을 좀더 사람의 문장에 가깝게 표현하게 해주는 라이브러리

#include <gmock/gmock.h>

int GetAge() { return 201; }

using testing::Eq; // ==
using testing::AllOf;
using testing::Lt;
using testing::Gt;

TEST(HamcrestTest, GetAge) {
	// Age가 100 인지 체크한다.
	EXPECT_EQ(GetAge(), 100);

	// Age가 10보다 크고, 200보다 작아야한다.
	int age = GetAge();
	EXPECT_TRUE(age > 10 && age < 200);

	// Hamcrest 방식의 단언문을 사용하면, Matcher를 활용해서 단언문을 작성할 수 있습니다.
	EXPECT_THAT(GetAge(), Eq(100));
	EXPECT_THAT(GetAge(), AllOf(Gt(10), Lt(200)));
}
