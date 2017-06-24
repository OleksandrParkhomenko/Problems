#include "stdafx.h"
#include"catch.hpp"
#include<thread>
#include"../Task 7 (Readers-writer lock)/RWL.h"

RWL rwl;

vector<int> arr = { 1, 2, 3, 4, 5 };

map<int, vector<int> > res;

void reader(int index) {
	rwl.beginRead();

	for (int i(0); i < arr.size(); i++) {
		res[index].push_back(arr[i]);
	}

	rwl.endRead();
}

void print(vector<int> & result) {
	rwl.beginRead();

	for (int i(0); i < arr.size(); i++) {
		result.push_back(arr[i]);
	}

	rwl.endRead();
}

void writer(initializer_list<int> list) {
	rwl.beginWrite();
	arr.insert(arr.end(), list);
	rwl.endWrite();
}

TEST_CASE("Testing RWL")
{
	vector<int> test;

	thread readers[3];
	readers[0] = thread(reader, 0);
	readers[1] = thread(reader, 1);
	readers[2] = thread(print, ref(test));

	initializer_list<int> x = { 10, 20 };
	thread writer(writer, x);

	for (int i = 0; i < 3; i++) {
		readers[i].join();
	}

	writer.join();

	REQUIRE((int)res[0].size() == 5);
	REQUIRE((int)res[1].size() == 5);

	for (int i = 0; i < 5; i++) {

		REQUIRE((int)res[0][i] == i+1);
		REQUIRE((int)res[1][i] == i+1);
		REQUIRE(test[i] == i+1);
	}

	REQUIRE((int)arr.size() == 7);
	REQUIRE(arr[5] == 10);
	REQUIRE(arr[6] == 20);
}