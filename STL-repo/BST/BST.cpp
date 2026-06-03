#include<iostream>
using namespace std;
template<class T>
class BST {
private:
	struct Node {
		T data_{};
		Node* left;
		Node* right;
		Node(T data):
			data_(data),
			left(nullptr),
			right(nullptr){}
	};
	Node* head_{nullptr};
public:
	void non_recursion_insert(T val) {
		if (head_ == nullptr) {
			head_ = new Node{ val };
			return;
		}
		Node* premier,detec=head_;
		while (detec != nullptr) {
			if (val < detec->data_) {
				premier = detec;
				detec = detec->left;
			}
			else if (val > detec->data_) {
				premier = detec;
				detec = detec->right;
			}
			else {
				return;
			}
		}
		if (val > premier->data_) {
			premier->right = new Node{ val };
		}
		else premier->left = new Node{ val };
	}
};

int main() {
	cout<<"work";
	return 0;
}