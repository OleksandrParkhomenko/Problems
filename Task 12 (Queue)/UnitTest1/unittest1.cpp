#include "stdafx.h"
#include"catch.hpp"
#include"../Task 12 (Queue)/Queue.h"

TEST_CASE("Test queue")
{
	MichaelScott queue;
	queue.push(5);
	REQUIRE(queue.pop() == 5);
	REQUIRE(queue.pop() == -1);
}