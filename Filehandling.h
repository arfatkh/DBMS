#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"dirent.h"
using namespace std;

//Read_all_field explaination:
//Opens the file and reads the given field of the file and stores it in an AVL tree


void Read_all_field_AVL(string field, string filename) {
	
	AVLtree<int> avltree;		//int for simplicities sake
	
	vector<Node<int>> keys;
	vector<string> fields;
	string firstrecord;
	ifstream file;
	bool endofline = false;
	int counter = 0;
	file.open(filename);
	//checking which cell of the record is the feild
	
	getline(file, firstrecord, '\n');

	cout << firstrecord << endl;
	


	file.close();
}
