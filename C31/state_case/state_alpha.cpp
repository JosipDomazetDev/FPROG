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
      
TEST_CASE ("Id")    {
   const auto autoIncrementIndex = initAutoIncrement (1);
   CHECK_EQ (1, value (autoIncrementIndex));
}
