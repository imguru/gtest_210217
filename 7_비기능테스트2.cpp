#include <gtest/gtest.h>

// 1. 제품 코드의 Image 객체에 대한 new / delete 재정의 되어야 합니다.
// 2. 테스트 코드 에서만 재정의된 new / delete를 이용합니다.

class Image {
public:
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
};

int Image::allocCount = 0;

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

class ImageTest : public testing::Test {
public:
	int alloc;
	void SetUp() override {
		alloc = Image::allocCount;
	}

	void TearDown() override {
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(diff, 0) << diff << " object(s) leaks!";
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







