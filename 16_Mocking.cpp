
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MP3 {
	virtual ~MP3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
	
	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;
};
