#include "queue.h"
#include <vector>
#include <thread>

void add(MichaelScott &queue, int n) {
	for (int i = 0; i < n; i++) {
		queue.push(i);
	}
}

void rem(MichaelScott &queue, int n) {
	for (int i = 0; i < n; i++) {
		queue.pop();
	}
}

int main() {
	MichaelScott queue;
	vector<thread> threads(6);
	threads[0] = thread(add, ref(queue), 36);
	threads[1] = thread(add, ref(queue), 12);
	threads[2] = thread(add, ref(queue), 6);
	threads[3] = thread(rem, ref(queue), 120);
	threads[4] = thread(rem, ref(queue), 46);
	threads[5] = thread(rem, ref(queue), 5);
	for (int i = 0; i < 3; i++) threads[i].join();
	for (int i = 3; i < 6; i++) threads[i].join();
	system("pause");
	return 0;
}