#include <iostream>
using namespace std;

struct node {
	int key;
	node* left;
	node* right;
	node* parent;
};

node* splay(node *t);

void rotate(node* child, node* parent) {
	//node* pp = parent->parent;
	if (child == nullptr) {
		return;
	}
	else if (parent == nullptr) {
		return;
	}
	else if (child != nullptr && parent != nullptr) {
		//right rotation
		if (child == parent->left) {
			if (parent->parent != nullptr) {
				node * y = child->right;
				child->right = parent;
				parent->left = y;
				child->parent = parent->parent; //parent of child is now indicating grand parent
				parent->parent = child;//parent of parent is now child
				if (y != nullptr) {
					y->parent = parent;
				}
			}
			else if (parent->parent == nullptr) {
				node * y = child->right;
				node* pr = parent->right;
				child->parent = nullptr;
				child->right = parent;
				parent->parent = child;
				parent->left = y;
				if (y != nullptr) {
					y->parent = parent;
				}		
			}
		}
		//left rtation
		if (child == parent->right) {
			if (parent->parent != nullptr) {
				node * y = child->left;
				child->left = parent;
				parent->right = y;
				child->parent = parent->parent; // parent of child is now indicating grand parent
				parent->parent = child; //parent of parent is now child
				if (y != nullptr) {
					y->parent = parent;
				}
			}
			else if (parent->parent == nullptr) {
				node * y = child->left;
				child->left = parent;
				parent->parent = child;
				parent->right = y;
				child->parent = nullptr;
				if (y != nullptr) {
					y->parent = parent;
				}
			}
		}
	}
		
	return;
}


bool find(node*& root, int value) {
	node* temp = root;
	if (root == nullptr) {
		return false;
	}
	else if (temp->key == value) {
		root = splay(temp);
		return true;
	}
	else if (value > temp->key) {
		temp = temp->right;
		//root = temp;
		find(temp, value);
	}
	else if (value < temp->key) {
		temp = temp->left;
		find(temp, value);
	}
}

node* insert(node* root, int value) {
	if (root == nullptr) {
		return new node{ value,nullptr,nullptr,nullptr };
	}
	else if (root->key == value) {
		return root;
	}

	else {
		if (root->key < value) {
			if (root->right != nullptr) {
				return insert(root->right, value);
			}
			else if (root->right == nullptr) {
				root->right = new node{ value,nullptr, nullptr, nullptr };
				root->right->parent = root;
				return splay(root->right);
			}

		}
		else if (root->key > value) {
			if (root->left != nullptr) {
				return insert(root->left, value);
			}
			else if (root->left == nullptr) {
				root->left = new node{ value,nullptr,nullptr,nullptr };
				root->left->parent = root;
				return splay(root->left);
			}
		}
	}
}



node* splay(node *t) {
	if (t == nullptr) {
		return nullptr;
	}
	else if (t != nullptr && t->parent == nullptr) {
		return t;
	}
	else if (t != nullptr && t->parent != nullptr && t->parent->parent == nullptr) {
		//ZIG
		rotate(t, t->parent);
		return t;
	}
	else if (t != nullptr && t->parent != nullptr && t->parent->parent != nullptr) {
		node*p = t->parent;
		node*pp = p->parent;
		node* ppp = t->parent->parent->parent;

		if (t->parent == t->parent->parent->left) {
			if (t == t->parent->left) {
				//ZIGZIG		
				rotate(p, pp);
				p->right = pp;
				pp->parent = p;
				rotate(t, p);
				t->right = p;
				p->parent = t;
		
			}
			else {
				//ZIGZAG	
				rotate(t, p);
				t->parent = pp;
				pp->left = t;
				rotate(t, pp);
			}
		}
		else if (t->parent == t->parent->parent->right) {
			if (t == t->parent->right) {
				//ZIGZIG
				rotate(p, pp);
				p->left = pp;
				pp->parent = p;
				rotate(t, p);
				t->left = p;
				p->parent = t;
			}
			else {
				//ZIGZAG
				rotate(t, p);
				t->parent = pp;
				pp->right = t;
				rotate(t, pp);
			}
		}
		if (ppp != nullptr) {
			if (pp == ppp->left)
			{
				ppp->left = t;
				t->parent = ppp;
				
			}
			else if (pp == ppp->right)
			{
				ppp->right = t;
				t->parent = ppp;
				
			}
		}
		if (t->parent != nullptr) {
			splay(t);
		}
		return t;
	}
}

/*
node* splay(node* t) {
		//	node* p = t->parent;
		//	node* gp = t->parent->parent;
		if (t == nullptr) {
			return nullptr;
		}
		else if (t != nullptr) {
			if (t->parent != nullptr) {
				node* p = t->parent;
				//ZIG
				if (t == p->left) { rotate(t, p); }
				else if (t == p->right) { rotate(t, p); }


				//ZIG-ZIG
				if (t->parent->parent != nullptr) {
					node* gp = t->parent->parent;
					if (gp->left == p) {
						rotate(p, gp);
						if (p->left = t) {
							rotate(t, p);
						}
					}
					else if (gp->right == p) {
						if (gp->right == p) {
							rotate(p, gp);
							if (p->right == t) {
								rotate(t, p);
							}
						}
					}

					//ZIG-ZAG
					if (t == p->left && p == gp->right) { rotate(t, p); rotate(p, gp); }
					else if (t == p->right && p == gp->left) { rotate(t, p); rotate(p, gp); }
				}
			}
		}
		return t;
}
*/