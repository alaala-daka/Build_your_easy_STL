#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
template<typename T>
class AVL {
private:
	struct Node {
		T val;
		Node* left;
		Node* right;
		int hei;
		Node(T val_ = T()) :
			val(val_),
			left(nullptr),
			right(nullptr),
			hei(1) {}
	};
	Node* root_;
public:
	AVL() :root_(nullptr) {};
	~AVL() {
		dele(root_);
	}
	int height (Node* p)const {
		if (p == nullptr) {
			return 0;
		}
		else return p->hei;
	}
	Node* rightrotate(Node* p) {
		Node* child = p->left;
		p->left = child->right;
		child->right = p;
		p->hei = max(height(p->right), height(p->left)) + 1;
		child->hei = max(height(child->right), height(child->left)) + 1;
		return child;
	}
	Node* leftrotate(Node* p) {
		Node* child = p->right;
		p->right = child->left;
		child->left = p;
		p->hei = max(height(p->right), height(p->left)) + 1;
		child->hei = max(height(child->right), height(child->left)) + 1;
		return child;
	}
	Node* rightbalance(Node* p) {
		Node* child = p->right;
		p->right = rightrotate(child);
		return leftrotate(p);
	}
	Node* leftbalance(Node* p) {
		Node* child = p->left;
		p->left = leftrotate(child);
		return rightrotate(p);
	}
	void add(const T& val) {
		root_=add(val, root_);
		return;
	}
	void remove(const T& val) {
		remove(val, root_);
		std::cout << "val has been del" << std::endl;
	}
private:
	void dele(Node* p) {
		if (p == nullptr) {
			return;
		}
		dele(p->left);
		dele(p->right);
		delete p;
		p = nullptr;
	}
	
	Node* add(const T& val, Node* p) {
		if (p == nullptr) {
			return new Node(val);
		}
		if (val < p->val) {
			p->left = add(val, p->left);
			if (height(p->left) - height(p->right) > 1) {
				if (height(p->left->left) >= height(p->left->right)) {
					p=rightrotate(p);
				}
				else {
					p=leftbalance(p);
				}
			}
		}
		else if (val > p->val) {
			p->right = add(val, p->right);
			if (height(p->right) - height(p->left) > 1) {
				if (height(p->right->right) >= height(p->right->left)) {
					p = leftrotate(p);
				}
				else {
					p = rightbalance(p);
				}
			}
		}
		p->hei = max(height(p->left), height(p->right)) + 1;
		return p;
	}
	Node* remove(const T& val, Node* p) {
		if (p == nullptr) {
			return p;
		}
		if (p->val > val) {
			p->left = remove(val, p->left);
			if (height(p->right) - height(p->left)>1) {
				if (height(p->right->right) >= height(p->right->left)) {
					p = leftrotate(p);
				}
				else {
					p = rightbalance(p);
				}
			}
		}
		else if (p->val < val) {
			p->right = remove(val, p->right);
			if (height(p->left) - height(p->right)>1) {
				if (height(p->left->left) >= height(p->left->right)) {
					p = rightrotate(p);
				}
				else p = leftbalance(p);
			}
		}
		else {
			if (p->right != nullptr && p->left != nullptr) {
				Node* pre = p->left;
				Node* last = nullptr;
				while (pre->right != nullptr) {
					last = pre;
					pre = pre->right;
				}
				p->val = pre->val;
				pre->val = val;
				p->left = remove(val, p->left);
			}
			else {
				Node* tem = nullptr;
				if (p->left != nullptr) {
					tem = p->left;
				}
				else {
					tem = p->right;
				}
				delete p;
				p = tem;
				if (p!=nullptr&&height(p->left) > 1) {
					if (height(p->left->left) > height(p->left->right)) {
						p = rightrotate(p);
					}
					else p = leftbalance(p);
				}
			}
		}
		return p;
	}
};

int main() {
	using std::cout;
	using std::endl;
	AVL<int> tree;
	std::cout << "star to insert" << endl;
	std::vector<int> seq = { 30, 20, 10, 25, 40, 50, 45 };
	for (int v : seq) {
		tree.add(v);
		std::cout << "already insert" << v << endl;
	}
	std::cout << endl << "try to remove num 10" << endl;
	tree.remove(10);
	std::cout << endl << "try to remove the Node that only has one child" << endl;
	tree.remove(50);
	std::cout << endl << "two child situation" << endl;
	tree.remove(30);
	std::cout << endl << "done" << endl;
	return 0;
}