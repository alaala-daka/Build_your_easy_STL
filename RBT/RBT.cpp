#include<iostream>
template<class T>
class RBT {
private:
	enum color_ {
		black,
		red
	};
	struct Node {
		T val;
		Node* left;
		Node* right;
		Node* parent;
		color_ color;
		Node(T data = T(), Node* parent_ = nullptr, color_ colour = black, Node* left = nullptr, Node* right = nullptr) :
			val(data),
			parent(parent_),
			color(colour),
			left(left),
			right(right) {

		}

	};
	Node* head;
public:
	RBT() {
		head = nullptr;
	}
	~RBT() {
		dele(head);
	}
	void insert(T val_) {
		if (head == nullptr) {
			head = new Node(val_);
			return;
		}
		Node* parent = nullptr;
		Node* p = head;
		while (p != nullptr) {
			if (val_ < p->val) {
				parent = p;
				p=p->left;
			}
			else if (val_ > p->val) {
				parent = p;
				p = p->right;
			}
			else {
				return;
			}
		}
		if (val_ > parent->val) {
			parent->right = new Node(val_, parent,red);
			p = parent->right;
		}
		else {
			parent->left = new Node(val_, parent,red);
			p = parent->left;
		}
		if (color(parent) == black) {
			return;
		}
		else fix(p);
	}
	void remove(const T& val) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		while (cur != nullptr) {
			if (cur->val > val) {
				cur = cur->left;
			}
			else if (cur->val < val) {
				cur = cur->right;
			}
			else {
				break;
			}
		}
		if (cur == nullptr) {
			return;
		}
		if (cur->left != nullptr && cur->right != nullptr) {
			Node* pre = cur->left;
			while(pre->right != nullptr) {
				pre = pre->right;
			}
			cur->val = pre->val;
			cur = pre;
		}
		Node* child = cur->left;
		bool isright = 0;
		if (child == nullptr) {
			child = cur->right;
		}
		if (parent(cur) == nullptr) {
			head = child;
		}
		else {
			if (left(parent(cur)) == cur) {
				parent(cur)->left = child;
			}
			else {
				parent(cur)->right = child;
				isright = 1;
			}
		}
		if(nullptr!=child)
		child->parent=parent(cur);
		
		color_ c=color(cur);
		if (c == red) {
			delete cur;
			return;
		}
		else {
			if(child!=nullptr&&head!=child)
			afterfix(child);
			else {
				if (parent(cur) == nullptr) {
					if (child != nullptr) {
						if (color(child) == red) {
							set_color(child, black);
						}
					}
					delete cur;
					return;
				}
				if (isright == 0) {
					parent(cur)->left = cur;
				}
				else {
					parent(cur)->right = cur;
				}
				afterfix(cur);
				if (left(parent(cur)) == cur) {
					parent(cur)->left = nullptr;
				}
				else parent(cur)->right = nullptr;
			}
			delete cur;
		}
	}
private:
	void afterfix(Node* p) {
		while (p != nullptr && p != head && color(p) == black) {
			Node* par = parent(p);
			if (par == nullptr) break;
			if (left(par) == p) {
				Node* brother = right(par);
				if (color(brother) == red) {
					set_color(par, red);
					set_color(brother, black);
					leftrotate(par);
					brother = right(par);
				}
				if (color(left(brother)) == black && color(right(brother)) == black) {
					set_color(brother, red);
					if (color(par) == red) {
						set_color(par, black);
						return;
					} else {
						p = par;
						continue;
					}
				} else {
					if (color(right(brother)) != red) {
						set_color(brother, red);
						set_color(left(brother), black);
						rightrotate(brother);
						brother = right(par);
					}
					set_color(brother, color(par));
					set_color(par, black);
					set_color(right(brother), black);
					leftrotate(par);
					break;
				}
			} else {
				Node* brother = left(par);
				if (color(brother) == red) {
					set_color(par, red);
					set_color(brother, black);
					rightrotate(par);
					brother = left(par);
				}
				if (color(left(brother)) == black && color(right(brother)) == black) {
					set_color(brother, red);
					if (color(par) == red) {
						set_color(par, black);
						return;
					} else {
						p = par;
						continue;
					}
				} else {
					if (color(left(brother)) != red) {
						set_color(brother, red);
						set_color(right(brother), black);
						leftrotate(brother);
						brother = left(par);
					}
					set_color(brother, color(par));
					set_color(par, black);
					set_color(left(brother), black);
					rightrotate(par);
					break;
				}
			}
		}
		if (p != nullptr) set_color(p, black);
	}
	void fix(Node* p) {
		while (red == color(parent(p))) {
			if (left(parent(parent(p))) == parent(p)) {
				if (red == color(right(grand(p)))) {
					set_color(parent(p), black);
					set_color(grand(p), red);
					set_color(grand(p)->right, black);
					p = grand(p);
				}
				else {
					if (right(parent(p)) == p) {
						p = parent(p);
						leftrotate(p);
					}
					set_color(parent(p),black);
					set_color(grand(p),red);
					rightrotate(grand(p));
					break;
				}
			}
			else {
				if (red == color(left(grand(p)))) {
					set_color(parent(p), black);
					set_color(grand(p), red);
					set_color(grand(p)->left, black);
					p = grand(p);
				}
				else {
					if (left(parent(p)) == p) {
						p = parent(p);
						rightrotate(p);
					}
					set_color(parent(p), black);
					set_color(grand(p), red);
					leftrotate(grand(p));
					break;
				}
			}
		}
		set_color(head, black);
	}
	
	void dele(Node* p) {
		if (p == nullptr) {
			return;
		}
		dele(p->left);
		dele(p->right);
		delete p;
		p = nullptr;
	}
	color_ color(Node* p) {
		if (p == nullptr) {
			return black;
		}
		else return p->color;
	}
	void set_color(Node* p, color_ color) {
		p->color = color;
	}
	Node* grand(Node* p) {
		return parent(parent(p));
	}
	Node* parent(Node* p) {
		return p->parent;
	}
	Node* left(Node* p) {
		return p->left;
	}
	Node* right(Node* p) {
		return p->right;
	}
	void leftrotate(Node* p) {
		Node* child = p->right;
		Node* grand = p->parent;
		p->right = child->left;
		if (p->right != nullptr) {
			p->right->parent = p;
		}
		child->left = p;
		p->parent = child;
		if (grand == nullptr) {
			head = child;
			child->parent = nullptr;
		}
		else {
			if (grand->left == p) {
				grand->left = child;
			}
			else grand->right = child;
			child->parent = grand;
		}
	}
	void rightrotate(Node* p) {
		Node* child = p->left;
		Node* grand = p->parent;
		p->left = child->right;
		if (p->left != nullptr) {
			p->left->parent = p;
		}
		child->right = p;
		p->parent = child;
		if (grand == nullptr) {
			head = child;
			child->parent = nullptr;
		}
		else {
			if (grand->left == p) {
				grand->left = child;
			}
			else grand->right = child;
			child->parent = grand;
		}
	}
};

int main() {
	RBT<int> a{};
	for (int i = 1; i < 10; i++) {
		a.insert(i);
	}
	for (int i = 1; i < 10; i++) {
		a.remove(i);
	}
	a.remove(2);
	a.remove(1);
	std::cout << "done" << std::endl;
	return 0;
}