#include "stdafx.h"
#include "catch.hpp"
#include <vector>
#include <exception>
#include <chrono>
#include <thread>

using namespace std;

vector<exception> errors;

#include"../Task 13 (Barrier)/Barrier.h"


void f1(int *&a, char *&b, Barrier &bar) {
	a = new int(18);

	// work simulation
	this_thread::sleep_for(chrono::seconds(1));

	// point to wait other threads
	bar.waitForOthers();

	// check oponent threads work
	try {
		if (!b) throw runtime_error("");
	}
	catch (const exception &ex) {
		errors.push_back(ex);
	}
}

void f2(int *&b, char *&a, Barrier &bar) {
	a = new char(100);

	// work simulation
	this_thread::sleep_for(chrono::seconds(5));

	// point to wait other threads
	bar.waitForOthers();

	// check oponent threads work
	try {
		if (!b) throw runtime_error("");
	}
	catch (const exception &ex) {
		errors.push_back(ex);
	}
}


TEST_CASE("Barrier Test")
{
	Barrier bar(2);
	int *a = nullptr;
	char *b = nullptr;

	thread two(f2, ref(a), ref(b), ref(bar));
	thread one(f1, ref(a), ref(b), ref(bar));

	one.join();
	two.join();

	REQUIRE(errors.size() == 0);
}