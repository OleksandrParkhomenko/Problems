#include "stdafx.h"
#include "catch.hpp"
#include<vector>
#include<thread>

#include"../Task 8 (Semaphore)/Semaphore.h"

using namespace std;

void sum(int a,int b, int& res, Semaphore &s) {
	//    cout << "1 enter" << endl;
	s.wait();
	//    cout << "1 start" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(4));
	res = a + b;
	//    cout << "2 should start" << endl;
	s.signal();
}

void multiply(int a, int b, int& res, Semaphore &s) {
	s.wait();
	res = a * b;
	s.signal();
}

TEST_CASE("Semaphore testing")
{
	Semaphore semaphore(1);

	int result = 0;
	vector<thread> threads(2);

	threads[0] = thread(sum, 10, 10, ref(result), ref(semaphore));
	// threads[0] should enter first
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	threads[1] = thread(multiply, 100, 100, ref(result), ref(semaphore));

	threads[0].join();
	threads[1].join();
	REQUIRE(result == 10000);
}