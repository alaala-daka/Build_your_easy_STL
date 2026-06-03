#include<iostream>
#include<ctime>
#include<memory>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int a=0) :data(a), next(nullptr) {};
};

class List {
private:
	Node* Head;
	friend void gather(List& a, List& b);
	friend bool IsCircleExist(const List& a, int& val);
	friend bool IsListMeet(List& a,  List& b, int& val);
	friend int main();
public:
	List() {
		Head = new Node();
	}
	~List() {
		Node* p = Head;
		while (p != nullptr) {
			Head = Head->next;
			delete p;
			p = Head;
		}
	}
	void InsertTail(int val) {
		auto p = Head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = new Node(val);
	}
	void InsertHead(int val) {
		auto p = Head->next;
		Head->next = new Node(val);
		(Head->next)->next = p;
	}
	void removesg(int val) {
		Node* p = Head->next;
		Node* q = Head;
		while (p != nullptr) {
			if (p->data == val) {
				q->next = p->next;
				delete p;
				return;
			}
			else {
				q = p;
				p = p->next;
			}
		}
	}
	void removeal(int val){
		Node* p = Head->next;
		Node* q = Head;
		while (p != nullptr) {
			if (p->data == val) {
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else {
				q = q->next;
				p = p->next;
			}
		}
	}
	void display() {
		Node* p = Head->next;
		while (p != nullptr) {
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
	void reverse() {
		Node* p = Head->next;
		if (p == nullptr) {
			return;
		}
		Node* q = p->next;
		Head->next = nullptr;
		while (q != nullptr) {
			p->next = Head->next;
			Head->next = p;
			p = q;
			q = q->next;
		}
		p->next = Head->next;
		Head->next = p;
	}
	int feedback(int k) {
		if (k <= 0) {
			cout << "ileagal" << endl;
			return -1;
		}
		Node* p = Head;
		Node* q = Head;
		for (int i = 0; i < k; i++) {
			q = q->next;
			if (q == nullptr) {
				return -1;
			}
		}
		while (q != nullptr) {
			p = p->next;
			q = q->next;
		}
		return (p->data);
	}
	int length() {
		Node* p = Head->next;
		int length = 0;
		while (p != nullptr) {
			length++;
			p = p->next;
		}
		return length;
	}
};

void gather(List& a, List& b) {
	Node* up = a.Head->next;
	Node* down = b.Head->next;
	Node* Line = a.Head;
	while (up != nullptr && down != nullptr) {
		if (up->data > down->data) {
			Line->next = down;
			Line = Line->next;
			down = down->next;
		}
		if (up->data < down->data) {
			Line->next = up;
			Line = Line->next;
			up = up->next;
		}
		if (up == nullptr) {
			Line->next = down;
		}
		else {
			Line->next = up;
		}
	}
	b.Head->next = nullptr;
}

bool IsCircleExist(const List& a, int& val) {
	Node* fast = a.Head->next;
	Node* slow = a.Head->next;
	while (fast != nullptr && fast->next != nullptr) {
		fast = (fast->next)->next;
		slow = slow->next;
		if (fast == slow) {
			auto m = fast;
			auto n = a.Head->next;
			while (m != n) {
				m = m->next;
				n = n->next;
			}
			val = m->data;
			return true;
		}
	}
	return false;
}

bool IsListMeet(List& a, List& b, int& val) {
	Node* p = a.Head;
	Node* q = b.Head;
	int len = (a.length() - b.length());
	if (len < 0) {
		len = -len;
		while (len > 0) {
			len--;
			q = q->next;
		}
		if (p != nullptr || q != nullptr) {
			while (q != p) {
				q = q->next;
				p = p->next;
			}
			val = p->data;
			return true;
		}
		else return false;
	}
	if (len >= 0) {
		while (len > 0) {
			len--;
			p = p->next;
		}
		if (p != nullptr || q != nullptr) {
			while (q != p) {
				q = q->next;
				p = p->next;
			}
			val = p->data;
			return true;
		}
		else return false;
	}
}

int main(){
	List a;
	List b;
	Node n1(1);
	Node n2(2);
	Node n3(3);
	Node n4(4);
	Node n5(5);
	Node n6(6);

	a.Head->next = &n1;
	n1.next = &n4;
	n4.next = &n5;
	n5.next = &n6;
	b.Head->next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	int val;
	bool t = IsListMeet(a, b, val);
	if (t == true) {
		cout << "Meeting Exist " << "Entry is " << val << endl;
	}
	else cout << "No Meeting" << endl;
	n3.next = nullptr;
}