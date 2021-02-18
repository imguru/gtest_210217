// 9_테스트전용하위클래스.cpp

#include <stdio.h>

class Engine {
public:
	// 아래의 함수가 가상 함수 이어야 한다.
	//  => Testability(테스트 용이성)
	//     - 가상함수가 일반 함수보다 테스트 용이성이 좋습니다.
	void Start() {
		printf("Engine Start\n");
	}
#if 0
	virtual void Start() {
		printf("Engine Start\n");
	}
#endif
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ...
		engine->Start();
		// ...
	}
};

//------------------------
#include <gtest/gtest.h>

// 문제점: 테스트 하고자 하는 클래스가 테스트를 위한 기능을 제공하고 있지 않습니다.
//  => "테스트 전용 하위 클래스 패턴"을 통해 문제를 해결할 수 있습니다.
//   의도: 테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 됩니다.
class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	// void Start() override {
	void Start() {
		Engine::Start();     // 부모의 기능을 재사용한다.
		isStart = true;
	}

	bool IsStart() const {
		return isStart;
	}
};

// Car의 Go를 호출하였을 때, Engine의 Start가 제대로 수행되었는지 여부를 검증하고 싶다.
TEST(CarTest, Go) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	EXPECT_TRUE(engine.IsStart()) << "Car가 Go 하였을 때";
}


TEST(CarTest, Go_Bad) {
	Engine engine;
	Car car(&engine);

	car.Go();
}










