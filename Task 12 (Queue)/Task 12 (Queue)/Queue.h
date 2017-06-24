#include <iostream>
using namespace std;

struct Node
{
	int value;
	Node* next;
};

class MichaelScott
{
	Node* Head;
	Node* Tail;
public:
	void push(int value);
	int pop();
	MichaelScott();
	~MichaelScott();
};

MichaelScott::MichaelScott()
{
	Head = new Node;
	Head->next = NULL;
	Head->value = 0;
	Tail = Head;
}

void MichaelScott::push(int value)
{
	Node* tmp = new Node;
	tmp->next = NULL;
	tmp->value = value;
	while (Tail->next)
		Tail = Tail->next;
	Tail->next = tmp;
	Tail = tmp;
}

int MichaelScott::pop()
{
	if (Head == Tail)
	{
		if (Head->next)
		{
			while (Tail->next)
				Tail = Tail->next;
		}
		else
		{
			cout << "Empty" << endl;
			return -1;
		}
	}
	Node* ptr = Head;
	Head = Head->next;
	delete ptr;
	return Head->value;
}

MichaelScott::~MichaelScott()
{
	while (Head->next)
	{
		Node* ptr = Head;
		Head = Head->next;
		delete ptr;
	}
}