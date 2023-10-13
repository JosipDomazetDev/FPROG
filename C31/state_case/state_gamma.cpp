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

auto value = [](const auto previous){
		return previous.first;
};

auto initAutoIncrement =[](const int initialId) {
  	function < int (const int) > nextId =[](const int lastId)
  	{
  			return lastId + 1;
  	};
   	return make_pair (initialId, nextId);
}; 

auto lambda = [](const auto previous){
		return previous.second;
};

auto computeNextAutoIncrement = [](pair<const int, function<int(const int)>> current){
		const auto currentValue = value(current);
		const auto functionToApply = lambda(current);
		const int newValue = functionToApply(currentValue);
		return make_pair(newValue, functionToApply);
};
      
TEST_CASE ("Id")    {
   const auto autoIncrementIndex = initAutoIncrement (1);
   CHECK_EQ (1, value (autoIncrementIndex));
}

TEST_CASE("Compute next auto increment index"){
	const auto autoIncrementIndex = initAutoIncrement(1);
	const auto nextAutoIncrementIndex = computeNextAutoIncrement(autoIncrementIndex);
	CHECK_EQ(2, value(nextAutoIncrementIndex));
}

TEST_CASE("Compute another auto increment index"){
	const auto autoIncrementIndex = initAutoIncrement(1);
	const auto nextAutoIncrementIndex = computeNextAutoIncrement(autoIncrementIndex);
	CHECK_EQ(2, value(nextAutoIncrementIndex));
	const auto newAutoIncrementIndex = 	computeNextAutoIncrement(nextAutoIncrementIndex);
	CHECK_EQ(3, value(newAutoIncrementIndex));
}