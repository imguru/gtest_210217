// 2_3A.cpp
//  - 단위 테스트를 구성하는 방법.

// 테스트 대상 코드
//  - SUT(System Under Test)
//  - CUT(Class or Code Under Test)

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};


//---------
#include <gtest/gtest.h>
