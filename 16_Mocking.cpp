
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
	
	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;
};

// Mocking
//  - MOCK_METHOD(반환타입, 메소드이름, (인자), (한정자));
//  한정자
//   1. override  - virtual 함수(옵션) - 권장
//   2. const - 필수
//   3. noexcept - 필수
//   4. stdcall - Windows Platform에서 주로 사용합니다.

class MockMP3 : public MP3 {
public:
	MOCK_METHOD(std::string, GetName, (), (const, override));
	MOCK_METHOD(void, Foo, (), (noexcept, override));

	// void Play() override {} 
	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));
};

void Sample(MP3* mp3) {
	mp3->Play();
	mp3->Stop(10);
}

TEST(MP3Test, Sample) {
	MockMP3 mock;

	EXPECT_CALL(mock, Play());
	EXPECT_CALL(mock, Stop(10));

	Sample(&mock);
}








