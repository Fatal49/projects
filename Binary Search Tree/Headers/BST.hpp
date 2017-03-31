
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <exception>
using namespace std;

#define SMALL 0x01
#define LARGE 0x02

template <typename Comparable>
class BinarySearchTree;

template <typename Comparable>
class BSTIter;

template <typename Comparable>
class BinaryNode {

	friend class BinarySearchTree<Comparable>;
	friend class BSTIter<Comparable>;

	BinaryNode(const Comparable& x = Comparable(), BinaryNode* left = nullptr, BinaryNode* right = nullptr,
		int size = 1, BinaryNode* previous = nullptr, BinaryNode* small = nullptr, BinaryNode* large = nullptr)
		: element(x), left(left), right(right), size(size), previous(previous), smallest(small), largest(large) {}

	void setPrev(BinaryNode* t) { previous = t; }
	void setLar(BinaryNode* t) { large_tail = t; }
	void setSmall(BinaryNode* t) { small_tail = t; }

	BinaryNode* right;
	BinaryNode* left;
	BinaryNode* smallest;
	BinaryNode* largest;
	BinaryNode* previous;
	BinaryNode* large_tail;
	BinaryNode* small_tail;
	Comparable element;
	int size;
};


template <typename Comparable>
class BSTIter {
public:

	BSTIter& operator ++ ();
	BSTIter  operator ++ (int);
	BSTIter& operator -- ();
	BSTIter  operator -- (int);
	Comparable  operator *  ();
	bool     operator != (const BSTIter<Comparable>& rhs);

private:

	friend class BinarySearchTree < Comparable >;
	BSTIter(BinaryNode<Comparable>* current = nullptr, BinaryNode<Comparable>* large_tail = nullptr, BinaryNode<Comparable>* small_tail = nullptr) 
		: current(current), large_tail(large_tail), small_tail(small_tail), mode(SMALL) { 
		if (current != nullptr) {
			if (current->left != nullptr && current->right != nullptr) {
				operator++();
			} else {
				this->large_tail = &(BinaryNode<Comparable>(Comparable(), nullptr, nullptr, 0));
				this->large_tail->setLar(large_tail);
				this->small_tail = small_tail;
			}
		}	
	}

	BinaryNode<Comparable>* current;
	BinaryNode<Comparable>* small_tail;
	BinaryNode<Comparable>* large_tail;
	int mode;
};


template<typename Object>
BSTIter<Object>& BSTIter<Object>::operator ++ ()
{
	static BinaryNode<Object>* temp = current;

	if (current != nullptr) {
		if (mode == SMALL) {
			if (current->smallest == nullptr) {
				small_tail = current;
				current = temp;
				current = current->largest;
				mode = LARGE;
			} else
				current = current->smallest;
		} else if (mode == LARGE) {
			current = current->largest;
			large_tail = current;
		}
	}

	return *this;
}


template<typename Object>
BSTIter<Object> BSTIter<Object>::operator ++ (int)
{
	BSTIter<Object>* temp = this;
	operator++();
	return *temp;
}

template<typename Object>
BSTIter<Object>& BSTIter<Object>::operator -- ()
{
	if (current != nullptr) {
		if (mode == SMALL) {
			if (current->previous == nullptr) {
				mode = LARGE;
				current = small_tail;
			} else {
				current = current->previous;
			}
		} else if (mode == LARGE) {
			current = current->previous;
		}
	} else {
		current = large_tail;
	}

	return *this;
}


template<typename Object>
BSTIter<Object> BSTIter<Object>::operator -- (int)
{
	BSTIter<Object>* temp = this;
	operator--();
	return *temp;
}


template<typename Object>
Object BSTIter<Object>::operator * ()
{
	return current->element;
}


template<typename Object>
bool BSTIter<Object>::operator != (const BSTIter& rhs)
{
	return current != rhs.current;
}


template <typename Comparable>
class BinarySearchTree {
public:

	typedef BinaryNode<Comparable> Node;
	typedef BSTIter<Comparable> iterator;

	BinarySearchTree() : root(nullptr) { } // Construct the tree.
	~BinarySearchTree(){ makeEmpty(); } // Destructor for the tree.

	const Comparable* find(const Comparable& x) const { return elementAt(find(x, root)); }

	bool isEmpty() const { return root == nullptr; }
	void makeEmpty() { makeEmpty(root); }
	void insert(const Comparable & x) { insert(x, root, root); }

	BSTIter<Comparable> begin() { return BSTIter<Comparable>(root); }
	BSTIter<Comparable> end() { return BSTIter<Comparable>(nullptr, root->large_tail, root->small_tail); }

private: 

	Node* root;

	int treeSize(Node *t) const { return t == nullptr ? 0 : t->size; }

	void smallest(const Comparable& x, Node*& t);
	void largest(const Comparable& x, Node*& t);
	void filling(const Comparable& x, Node*& t);
	void display() const { display(root); };
	void display(Node* t) const;

	void insert(const Comparable & x, Node*& t, Node*& root);
	Node* find(const Comparable& x, Node* t) const;
	Comparable const * elementAt(Node *t) const;
	void makeEmpty(Node * & t) const;
	Node * clone(Node *t) const;
};


template<class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::find(const Comparable& x, Node* t) const
{
	while (t != nullptr)
	{
		if (x < t->element)
			t = t->left;
		else if (t->element > x)
			t = t->right;
		else
			return t;
	}

	return nullptr;
}

template <class Comparable>
Comparable const * BinarySearchTree<Comparable>::elementAt(Node *t) const
{
	if (t == nullptr)
		return nullptr;
	else
		return &(t->element);
}


template <typename Comparable>
void BinarySearchTree<Comparable>::smallest(const Comparable& x, Node*& t)
{
	// Check if t's smallest node is a nullptr
	if (t->smallest == nullptr) {
		t->smallest = new Node(x, nullptr, nullptr, 0);
		t->setSmall(t->smallest);
	} else {
		// Create a temp node
		Node* p = t; 
		Node* prev = nullptr;
	
		// Go through the nodes
		while (p->smallest != nullptr) {
			if (x < p->smallest->element) {
				p->smallest = new Node(x, nullptr, nullptr, 0, prev, p->smallest);
				p->smallest->smallest->setPrev(p->smallest);

				if (p->smallest->element > t->small_tail->element)
					t->setSmall(p->smallest);

				break;
			}
	
			p = p->smallest;
			prev = p;
		}
	}
}


template <typename Comparable>
void BinarySearchTree<Comparable>::largest(const Comparable& x, Node*& t)
{
	static Node* lar;

	// Check if t's largest node is a nullptr
	if (t->largest == nullptr) {
		t->largest = new Node(x, nullptr, nullptr, 0);
		lar = t->largest;
	} else {
		// Create a temp node
		static Node* prev = t;
		Node* p = t;
		Node* prev2 = nullptr, *prev3 = nullptr;
		Node* temp;

		// Go through the nodes
		while (p->largest != nullptr) {
			if (x > p->largest->element) {
				if (x > lar->element) {
					lar->largest = new Node(x, nullptr, nullptr, 0, lar, lar->smallest, lar->largest);
					lar = lar->largest;
					t->setLar(lar);
					break;
				} else {
					if (x > prev->element) {
						temp = prev;

						while (temp->largest != nullptr) {
							if (temp->largest->element > x) {
								temp->largest = new Node(x, nullptr, nullptr, 0, temp, temp->smallest, temp->largest);
								temp->largest->largest->setPrev(temp->largest);
								break;
							}

							temp = temp->largest;
							prev3 = temp;
						}
						break;
					} 
				}
			} else {
				if (x > t->element && x < p->largest->element) {
					p->largest = new Node(x, nullptr, nullptr, 0, nullptr, p->smallest, p->largest);
					p->largest->largest->setPrev(p->largest);
					break;
				}


				prev->largest = new Node(x, nullptr, nullptr, 0, prev2, prev->smallest, prev->largest);
				prev->largest->largest->setPrev(prev->largest);
				prev = prev->largest;
				break;
			}

			p = p->largest;
			prev2 = p;
		}
	}
}


template <typename Comparable>
void BinarySearchTree<Comparable>::filling(const Comparable& x, Node*& t)
{
	// Check if the t is a nullptr
	if (!t)
		t = new Node(x, nullptr, nullptr, 0);

	// Create a static variable
	static Comparable temp = x;

	// Check if the given is less 
	// than or equal to the root
	if (x <= temp)
		smallest(x, t);

	// Chekc if given is larger than
	// or equal to the root
	if (x > temp)
		largest(x, t);
}


template <typename Comparable>
void BinarySearchTree<Comparable>::display(Node* t) const
{
	if (t) {
		Node* p = t->smallest;

		cout << "smallest: ";
		while (p->smallest != nullptr) {
			cout << p->element << ' ';
			p = p->smallest;
		}
		cout << p->element << endl;

		while (p != nullptr) {
			cout << p->element << ' ';
			p = p->previous;
		}
		cout << endl;

		p = t->largest;
		cout << "largest: ";
		while (p->largest != nullptr) {
			cout << p->element << ' ';
			p = p->largest;
		}
		cout << p->element << endl;

		while (p != nullptr) {
			cout << p->element << ' ';
			p = p->previous;
		}
		cout << endl;
	}
}


template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, Node*& t, Node*& root)
{
	if (t == nullptr) {
		t = new Node(x, nullptr, nullptr, 0);
		filling(x, root);
	} else if (x < t->element)
		insert(x, t->left, root);
	else if (t->element < x)
		insert(x, t->right, root);
	else
		throw std::exception();

	t->size++;
}


template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(Node * & t) const
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}
}


#endif /* _BST_H defined */
