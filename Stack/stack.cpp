#include<iostream>
#include<memory>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int val = 0) :data(val), next(nullptr) {};
};

class stack {
private:
	Node* head;
	int H = 0;
public:
	stack() {
		head = new Node();
	}
	~stack() {
		Node* p = head;
		while (p != nullptr) {
			head = head->next;
			delete p;
			p = head;
		}
	}
	void push(int val) {
		Node* p = new Node(val);
		p->next = head->next;
		head->next = p;
		H++;
	}
	void pop() {
		if (head->next == nullptr) {
			throw"EMPTY";
		}
		Node* p = head->next;
		head->next = p->next;
		delete p;
		H--;
	}
	bool empty() {
		return head->next == nullptr;
	}
	int top() {
		if (head->next != nullptr)
			return head->next->data;
		else throw"Stack Empty";
	}
	int size() {
		return H;
	}
};

class stack__ {
private:
	int* ptr;
	int cap;
	int top;
public:
	stack__(int size=10) {
		ptr = new int[size];
		top = 0;
		cap = size;
	}
	~stack__() {
		delete []ptr;
		ptr = nullptr;
	}
	void push(int val) {
		if (top == cap) {
			expand(2 * cap);
		}
		ptr[top++] = val;
	}
	void pop() {
		if (top == 0) {
			throw"ERRO";
		}
		top--;
	}
	int top_() {
		if (top == 0) {
			throw"STACK EMPTY";
		}
		return ptr[top - 1];
	}
	bool empty() {
		if (top == 0) {
			return true;
		}
		else return false;
	}
	void expand(int size) {
		int* p = new int[size];
		memcpy(p, ptr, cap * sizeof(int));
		delete[]ptr;
		ptr = p;
		p = nullptr;
	}
	int size() {
		return cap;
	}
};

int main() {
	stack a{};
	int arr[10] = { 12,34,15,64,83,75,98,2,13,76 };
	for (int i = 0; i < 10; i++) {
		a.push(arr[i]);
	}
	cout << a.size() << endl;

	if (a.empty() == false) {
		cout << "Not Empty" << endl;
	}
	else cout << "Empty" << endl;

	int top = a.top();
	cout << "top is " << top << endl;

	a.pop();
	top = a.top();
	cout << "top is " << top << endl;

	return 0;
}