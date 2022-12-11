#include"AVLTree.h"
// #include"BTree.h"
#include"Filehandling.h"
// #include"RBTree.h"
// #include"Others.h"
#include "Menu.h"
using namespace std;









int main() {
	
	

	typedef string Choosen;
	string field = "state";

	AVLtree<Choosen>* test= new AVLtree<Choosen>;
	// // Read_all_field_AVL<int>(test,field, filename);
	Read_all_files_AVL<Choosen>(test, field);


	Value<Choosen> some;
	some.tuple = "California";

	Node<Choosen>* result =  test->Search(test->root,some);
	// // test->root = test->remove(test->root, some);

	// if(result!=NULL)
	// 	result->val->print(); 
	// else
	// 	cout << "Not found" << endl;


	for(int i=0;i<result->val->Entries;i++)
	{

	UpdateInCSV(result->val->lineNumber[i],result->val->fileName[i], "state", "California", "Dikhan");
	
	}



	


	return 0;

}

