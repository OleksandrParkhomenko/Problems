#include <iostream>

#include <mutex>
#include <condition_variable>
#include <exception>
#include <vector>

class Semaphore {
	int counter;
	std::mutex mutex;
	std::condition_variable condVar;

public:
	Semaphore(int count = 0);

	void wait(); // enter()
	void signal(); // leave()

};

Semaphore::Semaphore(int count) {
	if (count < 0) {
		throw std::runtime_error("Semaphore: count cannot be less then 0");
	}
	counter = count;
}

void Semaphore::wait() {
	std::unique_lock<std::mutex> lock(mutex);
	condVar.wait(lock, [this]() {
		return counter > 0;
	});
	counter--;
	lock.unlock();
	condVar.notify_one();
}

void Semaphore::signal() {
	std::unique_lock<std::mutex> lock(mutex);
	counter++;
	lock.unlock();
	condVar.notify_one();
}