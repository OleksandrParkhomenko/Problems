#include <condition_variable>
#include <mutex>

class Barrier {
	std::mutex mutex;
	std::condition_variable condVar;
	size_t counter;
	size_t numOfthreads;
	enum class State {
		Forward,
		Backward
	} state;
public:
	Barrier(const Barrier&) = delete;
	Barrier& operator = (const Barrier&) = delete;

	Barrier(uint8_t count);
	virtual auto waitForOthers() -> void const final;
};

Barrier::Barrier(uint8_t count) : counter(count), numOfthreads(count), state(State::Forward) { }

auto Barrier::waitForOthers() -> void const {
	std::unique_lock<std::mutex> lock(mutex);

	if (state == State::Forward) {
		--counter;
		if (!counter) {
			state = State::Backward;
			condVar.notify_all();
		}
		else {
			condVar.wait(lock, [&]() { return state == State::Backward; });
		}
	}
	else {
		++counter;
		if (counter == numOfthreads) {
			state = State::Forward;
			condVar.notify_all();
		}
		else {
			condVar.wait(lock, [&]() { return state == State::Forward; });
		}
	}
}