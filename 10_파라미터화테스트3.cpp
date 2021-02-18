
#include <gtest/gtest.h>

enum Color { BLACK, GRAY, WHITE };
const char* animals[] = { "cat", "dog" };

// Input Data
//  1. "cat" Black
//  2. "cat" GRAY
//  3. "cat" WHITE
//  4. "dog" Black
//  5. "dog" GRAY
//  6. "dog" WHITE

class AnimalTest : public testing::TestWithParam<std::tuple<const char*, Color>> {
};

using testing::Combine;
using testing::ValuesIn;
using testing::Values;

INSTANTIATE_TEST_SUITE_P(inputValues, AnimalTest, 
	Combine(ValuesIn(animals), Values(BLACK, GRAY, WHITE)));

TEST_P(AnimalTest, AnimalLooks) {
	const char* animal = std::get<0>(GetParam());
	Color color = std::get<1>(GetParam());

	printf("%s - %d\n", animal, color);
}
