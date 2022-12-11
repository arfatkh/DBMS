#include"AVLTree.h"
// #include"BTree.h"
// #include"Filehandling.h"
#include"RBTree.h"
// #include"Others.h"
#include "Menu.h"
using namespace std;









int main()
{
	RBTree<int> tree;
	Value<int> val;

	val.insert("22", 22, 22);
	tree.insert(val);
	// val.insert("22", 22, 7);
	// tree.insert(val);
	val.insert("22", 22, 6);
	tree.insert(val);
	val.insert("22", 22, 5);
	tree.insert(val);

	val.insert("24", 24, 3);
	tree.insert(val);

	val.insert("26", 27, 1);
	tree.insert(val);


	val.insert("29", 29, 9);
	tree.insert(val);



	// val.insert("22", 22, 4);
	// tree.insert(val);


	// tree.deleteByVal(val);
	tree.printInOrder();

	// val.insert("22", 22, 2);
	// tree.insert(val);
	// val.insert("22", 22, 1);
	// tree.insert(val);
	// tree.printInOrder();

	// cout << "Inorder Traversal of Created Tree\n";
	// tree.printInOrder();

	// val.insert("22",22,3);
	// tree.deleteByVal(val);
	// val.insert("22",22,5);
	// tree.deleteByVal(val);

	// tree.printInOrder();


	return 0;
}