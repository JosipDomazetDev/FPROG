#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

auto increment = [](const int current){
		return current + 1;
};

template<typename ValueType>
struct State{
		const ValueType value;
		const function<ValueType(const ValueType)> computeNext;
};

TEST_CASE("Initialize auto increment"){
	const auto autoIncrementIndex = State<int>{1, increment};
	CHECK_EQ(1, autoIncrementIndex.value);
}
