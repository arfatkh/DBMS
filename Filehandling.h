#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "AVLtree.h"
#include "myDataStructures.h"
using namespace std;


//Converts a string to a value of type T 
//The string is read from the file
template <typename T>
Value<T> StringToValue(string line, int fieldIndex, int lineNumber, string filename) {
	
	
	Value<T> returnObj;

	
	//Parse the line
	int index = 0;
	int field = 0;
	string value = "";
	while (index < line.length()) {

		//Check if the feild data is in quotes [This is for fields that contain commas]
		if(line[index]=='"')
		{
			index++;
			while(line[index]!='"')
			{
				value+=line[index];
				index++;
			}
			index++;
		}


		//Check if we have reached the end of the field
		if (line[index] == ',') {
			//End of the field
			if (field == fieldIndex) {
				//This is the field we want
				break;
			}
			else {
				//This is not the field we want
				field++;
				value = "";
			}
		}

		else {
			//Add the character to the value
			value += line[index];
		}

		//Increment the index
		index++;
	}
	

	//Convert the value to the correct type

	// Check the type of T
	if constexpr (std::is_same<T, int>::value) {

		returnObj.insert(filename, lineNumber,stoi(value));
	}
	
	else if constexpr (std::is_same<T, float>::value) {
		// returnObj.datatype = "float";
		// // strcpy(returnObj.datatype, "float");
		// returnObj.tuple = stof(value);
		returnObj.insert(filename, lineNumber, stof(value));
	}
	else if constexpr (std::is_same<T, string>::value) {
		// returnObj.datatype = "string";
		// returnObj.tuple = value;
		returnObj.insert(filename, lineNumber, value);
	}
	else {
		//Error
		cout << "Error: Invalid type" << endl;
	}


	// cout<<returnObj.tuple<<endl;
	
	//Set the other values
	
	// returnObj.lineNumber = lineNumber;
	// returnObj.fileName = filename;
	



	return returnObj;
}

//Get the index of the field in the file
int GetFieldIndex(string field) {

	if (field == "id") return 0;
	if (field == "year") return 1;
	if (field == "133cause") return 2;
	if (field == "cause") return 3;
	if (field == "state") return 4;
	if (field == "deaths") return 5;
	if (field == "agedeathrate") return 6;

	return -1;
}





//Read_all_field explaination:
//Opens the file and reads the given field of the file and stores it in an AVL tree
//Works on a single file
template <typename T>
void Read_all_field_AVL(AVLtree<T>* avltree,string  field, string filename) {
	
	// AVLtree<T>* avltree=new AVLtree<T>;		//int for simplicities sake
	int fieldIndex = GetFieldIndex(field);

	if (fieldIndex == -1) {
		cout << "Invalid field" << endl;
		return;
	}
	

	//Open the file
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "File not found" << endl;
		return;
	}

	//Read the file
	string line;
	int lineNumber = 1;
	while (getline(file, line)) {
		//Ignore the first line
		if (lineNumber == 1) {
			lineNumber++;
			continue;
		}


		//Read the line

		//Parse the line
		// cout << line << endl;

		Value<T> v = StringToValue<T>(line, fieldIndex, lineNumber, filename);
		
		
		//Insert the value into the tree
		avltree->root = avltree->insertNode(avltree->root, v);


	




		//Increment the line number
		lineNumber++;

	}




	// return avltree;
}


template <typename T>
void Read_all_files_AVL(AVLtree<T>* avltree, string field) {


	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv");
	Read_all_field_AVL<T>(avltree, field, "./datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv");


}




//========================================================================================================
// Saving the trees to a file



//Save the AVL tree to a file
template <typename T>
void saveAVLTree(AVLtree<T>* avltree, string filename) {

	//Open the file
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout << "File not found" << endl;
		return;
	}

	
	//Save the tree using the Level order traversal
	myDS::Queue<Node<T>*> ValueQueue;
	ValueQueue.enqueue(avltree->root);

	int count = 0;
	cout<<"Saving the tree to file"<<endl;
	while (!ValueQueue.isEmpty()) {
		
		

		Node<T>* current = ValueQueue.dequeue();

		// if(count<10) current->val->print();

		//Save the value to the file
		current->val->writeToBinaryFile(file);

		// count++;

		// cout<<current->val->datatype.c_<<endl;
		// cout<<current->val->datatype.i_<<endl;
		// cout<<current->val->datatype.f_<<endl;
		// cout<<current->val->datatype.d_<<endl;
		// cout<<current->val->lineNumber<<endl;
		// cout<<current->val->fileName<<endl;

		if (current->left != NULL) ValueQueue.enqueue(current->left);
		if (current->right != NULL) ValueQueue.enqueue(current->right);
	}



	// //Save the tree using the inorder traversal
	// // avltree->inorder(avltree->root, file);
	// myDS::stack<Node<T>*> ValueStack;
	// Node<T>* current = avltree->root;

	// //cout cuurent->val->tuple
	// // cout<<current->key<<endl;

	// cout<<"Saving the tree to file"<<endl;
	// while (current != NULL || !ValueStack.isEmpty()) {
	// 	while (current != NULL) {
	// 		ValueStack.push(current);
	// 		current = current->left;
	// 	}

	// 	current = ValueStack.Peek()->val;
	// 	ValueStack.pop();



	// 	// //Writing Value to file attribute by attribute
	// 	// file.write((char*)&current->val->datatype.c_str(), sizeof(current->val->datatype.c_str()));
	// 	// file.write("\0", sizeof(char));
	// 	// file.write((char*)&current->val->lineNumber, sizeof(current->val->lineNumber));
	// 	// file.write((char*)&current->val->fileName.c_str(), sizeof(current->val->fileName.c_str()));
	// 	// file.write("\0", sizeof(char));

	// 	//
	// 	current->val->print();

	// 	current->val->writeToBinaryFile(file);

	// 	// cout << current->value.tuple << endl;
	// 	// file << current->value.tuple << endl;
	// 	current = current->right;
	// }
	
	file.close();
}

template <typename T>
void LoadAVLTree(AVLtree<T>* avltree, string filename) {

	// Value<float> v;
	// v.datatype = "string";
	// v.lineNumber = 1;
	// v.fileName = "test3.txt";
	// v.tuple = 39.6;

	// ofstream file(filename, ios::binary );
	// if (!file.is_open()) {
	// 	cout << "File not found" << endl;
	// 	return;
	// }

	// v.writeToBinaryFile(file);





	//To read from the file
	ifstream file(filename, ios::binary);

	Value<T> v2;


	while(!file.eof()) {
		v2.readFromBinaryFile(file);
		// v2.print();
		avltree->root = avltree->insertNode(avltree->root, v2);

		// v2.print();


	}




	// file.write(v.datatype.c_str(), v.datatype.size());
	// file.write("\0", sizeof(char));
	// file.write((char*)&v.lineNumber, sizeof(v.lineNumber));
	// file.write(v.fileName.c_str(), v.fileName.size());
	// file.write("\0", sizeof(char));
	// file.write((char*)&v.tuple, sizeof(v.tuple));

	
	// Value<int> v2;
	// ifstream file(filename, ios::in | ios::binary);
	// if (!file.is_open()) {
	// 	cout << "File not found" << endl;
	// 	return;
	// }
	
	// getline(file, v2.datatype, '\0');
	// file.read((char*)&v2.lineNumber, sizeof(v2.lineNumber));
	// getline(file, v2.fileName, '\0');
	// file.read((char*)&v2.tuple, sizeof(v2.tuple));

	// v2.print();



	// //Open the file
	// ifstream file(filename, ios::in | ios::binary);
	// if (!file.is_open()) {
	// 	cout << "File not found" << endl;
	// 	return;
	// }

	






	// cout<<"Loading the ALV tree from file"<<endl;
	
	// //Read the file
	// Value<T> v;


	// // while (file.read((char*)&v, sizeof(v))) {
		





	// // }

}

