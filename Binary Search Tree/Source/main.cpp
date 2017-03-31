
#include "BST.h"
using namespace std;

int main() {

	BinarySearchTree<int> x1;

	x1.insert(10);
	x1.insert(9);
	x1.insert(8);
	x1.insert(5);
	x1.insert(3);
	x1.insert(34);
	
	x1.insert(15);
	x1.insert(102);
	x1.insert(105);
	x1.insert(7);
	x1.insert(107);
	x1.insert(100);
	x1.insert(13);
	x1.insert(72);
	x1.insert(1);
	x1.insert(50);

	BinarySearchTree<int>::iterator begin = x1.begin();
	BinarySearchTree<int>::iterator end = x1.end();

	cout << "Print in order: ";
	while (begin != end) {
		cout << *begin << ' ';
		begin++;
	}
	cout << endl << endl;

	cout << "Print backwards: ";
	if (!x1.isEmpty())
	{
		end = x1.end();
		--end;
			while (end != x1.begin())
			{
				cout << *end << " ";
				--end;
			}
		cout << *end << endl;
	}

	return 0;
}
