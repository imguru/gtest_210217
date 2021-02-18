#ifndef USER_H
#define USER_H

#include <gtest/gtest.h>

class User {
	int age;

public:
	int GetAge() const { return age; }
	User() : age(42) {}

	FRIEND_TEST(UserTest, age); // !!!
};

// 권장되는 해결책: 제품 코드가 변경되어야 한다.
//  - 로버트 C 마틴(클린코드)
//   : private 메소드의 목적은 public 메소드의 가독성을 높이기 위해서 사용해야 한다.
//     검증 되지 않은 private 메소드 보다 검증 된 public 메소드가 안전하다.

#endif
