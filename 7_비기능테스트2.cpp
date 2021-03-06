#include <gtest/gtest.h>

// 1. 제품 코드의 Image 객체에 대한 new / delete 재정의 되어야 합니다.
// 2. 테스트 코드 에서만 재정의된 new / delete를 이용합니다.
//   => 조건부 컴파일을 활용하면 좋습니다.

class Image {
public:
#ifdef LEAK_TEST
	static int allocCount;

	// Image* p = new Image;
	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	// delete p;
	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif
};

#ifdef LEAK_TEST
int Image::allocCount = 0;
#endif

void Draw() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;
	Image* p4 = new Image;

	delete p1;
	delete p2;
	delete p3;
	delete p4;
}

void Draw2() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;
	Image* p4 = new Image;

	delete p1;
	delete p2;
}

//---------

class ImageTest : public testing::Test {
public:
	int alloc;
	void SetUp() override {
#ifdef LEAK_TEST
		alloc = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef LEAK_TEST
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(diff, 0) << diff << " object(s) leaks!";
#endif
	}
};


TEST_F(ImageTest, Draw) {
	Draw();
}

TEST_F(ImageTest, Draw2) {
	Draw2();
}

#if 0
TEST(ImageTest, Draw) {
	int alloc = Image::allocCount;
	Draw();
	int diff = Image::allocCount - alloc;

	EXPECT_EQ(diff, 0) << diff << " object(s) leaks!";
}

TEST(ImageTest, Draw2) {
	int alloc = Image::allocCount;
	Draw();
	int diff = Image::allocCount - alloc;

	EXPECT_EQ(diff, 0) << diff << " object(s) leaks!";
}
#endif







