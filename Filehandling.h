#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "AVLtree.h"
#include "myDataStructures.h"
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;

using namespace std;



//Special characters for printing in color
string prntRed = "\033[1;31m";
string prntGreen = "\033[1;32m";
string prntYellow = "\033[1;33m";
string prntBlue = "\033[1;34m";
string prntPurple = "\033[1;35m";
string prntCyan = "\033[1;36m";
string prntWhite = "\033[1;37m";
string prntClr = "\033[0m";




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
bool Read_all_field_AVL(AVLtree<T>* avltree,string  field, string filename) {
	
	// AVLtree<T>* avltree=new AVLtree<T>;		//int for simplicities sake
	int fieldIndex = GetFieldIndex(field);

	if (fieldIndex == -1) {
		cout<<prntRed;
		cout << "Invalid field" << endl;
		cout<<prntClr;
		return false;
	}
	

	//Open the file
	ifstream file(filename);
	if (!file.is_open()) {

		cout<<prntRed;
		cout << "File not found ["<<filename<<"] !" << endl;
		cout<<prntClr;
		return false;
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
		// v->print();
		
		//Insert the value into the tree
		avltree->root = avltree->insertNode(avltree->root, v);


	




		//Increment the line number
		lineNumber++;

	}


	return true;

	// return avltree;
}


template <typename T>
bool Read_all_files_AVL(AVLtree<T>* avltree, string field) {
	//set the current directory
	

	// cout<<"Current directory: "<<prntRed<<fs::current_path()<<prntClr<<endl;
	// string DataFileFolder="./datafiles/";

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

	return true;

}




//========================================================================================================
// Saving the trees to a file



//Save the AVL tree to a file
template <typename T>
bool saveAVLTree(AVLtree<T>* avltree, string filename) {


	//Open the file
	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout << "Error Opening File ["<<filename<<"]!" << endl;
		return false;
	}

	
	//Save the tree using the Level order traversal
	myDS::Queue<Node<T>*> ValueQueue;
	ValueQueue.enqueue(avltree->root);

	int count = 0;
	cout<<"Saving the tree to file"<<endl;
	while (!ValueQueue.isEmpty()) {
		
		

		Node<T>* current = ValueQueue.dequeue();

		
		current->val->writeToBinaryFile(file);

	

		if (current->left != NULL) ValueQueue.enqueue(current->left);
		if (current->right != NULL) ValueQueue.enqueue(current->right);
	}



	cout<<prntGreen;
	cout<<"Tree saved to file ["<<filename<<"]"<<endl;
	cout<<prntClr;
	
	file.close();
}

template <typename T>
void LoadAVLTree(AVLtree<T>* avltree, string filename) {

	





	//To read from the file
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout<<prntRed;
		cout << "Error Opening File ["<<filename<<"]!" << endl;
		exit(1);
		cout<<prntClr;
		return;
	}

	Value<T> v2;


	while(!file.eof()) {
		v2.readFromBinaryFile(file);
		// v2.print();
		avltree->root = avltree->insertNode(avltree->root, v2);

		// v2.print();


	}




	

	






	cout<<prntGreen;
	cout<<"Loading the ALV tree from file ["<<filename<<"] !"<<endl;
	cout<<prntClr;



	file.close();
	


}


void printRecordFromFile(string filename,int LineNumber)
{
    ifstream file;
    file.open(filename);
    string line;
    int count = 1;
    while (getline(file, line))
    {
        count++;
        if(count==LineNumber)
        {
           
			cout<<line<<endl;
			break;
        }
    }
    file.close();
}



//========================================================================================================
void DeleteRowFromCSV(string filename, int LineNumber)
{
	
	ifstream file;
	file.open(filename);
	if(!file.is_open())
	{
		cout<<prntRed;
		cout<<"Error opening file"<<endl;
		cout<<prntClr;
		return;
	}


	string line;
	int count = 0;
	string temp = "";
	while (getline(file, line))
	{
		count++;
		if(count==LineNumber)
		{
			temp += "0,0, , , ,0,0.0\n"; //Replace the line with this dummy line
			continue;
		}
		temp += line + "\n";
	}

	file.close();
	ofstream file2;
	file2.open(filename);
	if (!file2.is_open())
	{
		cout<<prntRed;
		cout<<"Error opening file"<<endl;
		cout<<prntClr;
		return;
	}
	


	file2 << temp;
	file2.close();


	cout<<prntGreen;
	cout<<"Row ["<<LineNumber<<"] ["<<filename<<"] deleted successfully"<<endl;
	cout<<prntClr;

}





void UpdateInCSV(int lineNumber, string filename, string field,string oldValue, string newValue)
{

	cout<<"running on file ["<<filename<<"]"<<endl;

	//Considers the first line as the header as 1
	//Considers the first field as 0

	//if the new value has a comma, then cover it with quotes
	if(newValue.find(",")!=string::npos)
	{
		newValue = "\""+newValue+"\"";
	}

	// // if the new value has a quote, then cover it with double quotes
	// if(newValue.find("\"")!=string::npos)
	// {
	// 	newValue = "\""+newValue+"\"";
	// }




	fstream file(filename,ios::in | ios::out);
	if(!file.is_open())
	{
		cout<<prntRed;
		cout<<"Error opening file"<<endl;
		cout<<prntClr;
		return;
	}

	//MAke a temp file
	
	
	
	

	ofstream tempFile("./datafiles/temp.csv",ios::out);




	string line;
	int LineCount = 0;
	while (getline(file, line))
	{	
		

		LineCount++;
		
		if(LineCount==lineNumber)
		{
			// cout<<"Tell G while reading: "<<file.tellg()<<endl;
			string tempLine = "";
			int fieldIndex = GetFieldIndex(field);
			int fieldCount = 0;
			int index = 0;
			//Go to the field while ignoring quotes
			while (index < line.length())
			{
				tempLine += line[index];

				if(line[index]=='"')
				{
					index++;
					tempLine += line[index];
					while(line[index]!='"')
					{
						index++;
						tempLine += line[index];
					}
					index++;
					tempLine += line[index];
				}

				else if(line[index]==',')
				{
					fieldCount++;
					if(fieldCount==fieldIndex+1)
					{
						
						// cout<<"oldValue: "<<oldValue<<endl;
						// cout<<"newValue: "<<newValue<<endl;




						// //Replace the old value with the new value
						int oldIndex = tempLine.find(oldValue);
						if(oldIndex==-1)
						{
							cout<<prntRed;
							cout<<"Error: The old value ["<<oldValue<<"] does not exist in the file"<<endl;
							cout<<prntClr;
							cout<<tempLine<<endl;
							return;
						}

						tempLine.replace(oldIndex,oldValue.length(),newValue);
						// line= tempLine;
						// cout<<"Old Index: "<<oldIndex<<endl;
						// break;


					}
				}
				index++;
			}

			tempFile<<tempLine<<endl;
		}
		else
		{
			tempFile<<line<<endl;
		}
		

	





	}
	
	file.close();
	tempFile.close();
	
	//Remove the original file
	remove(filename.c_str());
	//Rename the temp file to the original file
	rename("./datafiles/temp.csv",filename.c_str());

	

	
}


