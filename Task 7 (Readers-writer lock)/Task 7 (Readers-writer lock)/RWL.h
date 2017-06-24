#include<iostream>
#include<mutex>
using namespace std;

class RWL
{
private:
	mutex r, w;
	int count;
public:
	RWL();
	~RWL();
	void beginRead();
	void endRead();
	void beginWrite();
	void endWrite();

};

RWL::RWL() :count(0){};
RWL::~RWL(){};

void RWL::beginRead()
{
	unique_lock<mutex>(r);
	count++;
	if (count == 1) w.lock();
}
void RWL::endRead()
{
	unique_lock<mutex>(r);
	count--;
	if (count == 0) w.unlock();
}
void RWL::beginWrite()
{
	w.lock();
}
void RWL::endWrite()
{
	w.unlock();
}