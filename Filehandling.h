#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "AVLtree.h"
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
		returnObj.datatype = "int";
		returnObj.tuple = stoi(value);
	}
	
	else if constexpr (std::is_same<T, float>::value) {
		returnObj.datatype = "float";
		returnObj.tuple = stof(value);
	}
	else if constexpr (std::is_same<T, string>::value) {
		returnObj.datatype = "string";
		returnObj.tuple = value;
	}
	else {
		//Error
		cout << "Error: Invalid type" << endl;
	}


	// cout<<returnObj.tuple<<endl;
	
	//Set the other values
	
	returnObj.lineNumber = lineNumber;
	returnObj.fileName = filename;
	



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


		cout<<"------------------"<<endl;
		v.print();





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

}


