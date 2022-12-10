#include"AVLTree.h"
// #include"BTree.h"
#include"Filehandling.h"
// #include"RBTree.h"
// #include"Others.h"
#include "Menu.h"
using namespace std;









int main() {
	
	/*int c;
	string field, filename="NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
	
	cout << "1.\tRead from file\n";
	cout << "2.\tUpdate in file\n";
	cout << "3.\tDelete from file\n";
	cin >> c;
	switch (c)	
	{
	case 1:
		cout << "Which field you want to read?\n";
		getline(cin, field);
		Read_all_field_AVL(field, filename);
		break;
	case 2:

		break;
	case 3:

		break;
	default:
		break;
	}*/

// 	AVLtree<int> tree;
// 	//Node<int>* root = tree.root;

// 	Value<int> d1;
// 	d1.insert("11", 1, 10);
// 	Node<int> n1(&d1);
// 	tree.root = tree.insertNode(tree.root,d1);

// 	Value<int> d2;
// 	d2.insert("!!", 1, 20);
// 	Node<int> n2(&d2);
// 	tree.root = tree.insertNode(tree.root,d2);

// 	//Data<int> d3(50, 2004, 42, "Cigis", "Ohio", 6.9);
// 	d2.insert("!!", 1, 50);

// 	Node<int> n3(&d2);
// 	tree.root = tree.insertNode(tree.root,d2);

// 	//Data<int> d4(80, 2004, 42, "Ligma", "Alabama", 6.9);
// 	d2.insert("!!", 1, 80);
// 	Node<int> n4(&d2);
// 	tree.root = tree.insertNode(tree.root,d2);

// //	Data<int> d5(1, 2004, 42, "Saqmadiq", "Ohio", 6.9);
// 	d2.insert("!!", 1, 1);

// 	Node<int> n5(&d2);
// 	tree.root = tree.insertNode(tree.root,d2);

// 	tree.InOrderTraversal(tree.root);
	//tree.levelorder_newline();
	////tree.levelorder_newline(tree.root);

	// string filename = "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
	
	//Availble fields


	// if (field == "id") return 0;
	// if (field == "year") return 1;
	// if (field == "133cause") return 2;
	// if (field == "cause") return 3;
	// if (field == "state") return 4;
	// if (field == "deaths") return 5;
	// if (field == "agedeathrate") return 6;


	// typedef string Choosen;
	// string field = "state";

	// AVLtree<Choosen>* test= new AVLtree<Choosen>;
	// // // Read_all_field_AVL<int>(test,field, filename);
	// Read_all_files_AVL<Choosen>(test, field);


	// Value<Choosen> some;
	// some.tuple = "Washington";

	// Node<Choosen>* result =  test->Search(test->root,some);
	// test->root = test->remove(test->root, some);

	// if(result!=NULL)
	// 	result->val->print(); 
	// else
	// 	cout << "Not found" << endl;



// 	// saveAVLTree(test, "avlString.dat");
	
// 	// LoadAVLTree<Choosen>(test, "avlString.dat");


// 	// printTree(test->root, nullptr, false);

// // 
	// test->InOrderTraversal(test->root);

	MenuMain();
	// printRecordFromFile("./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv",43);

	// DeleteRowFromCSV("./datafiles/100test.csv", 4);

	return 0;

}

