/*
Coded By:

Muhammad Farjad i210660
Muhammad Arfat i210554
Sufian Sajjad i210688


*/

/*
	ABOUT OTHERS.h

	Basically all the functions and classes needed but not suitable for any other file are here
	like the Data class and the Value class 
	Also the functions that are used in multiple files are here
	like the stringLoadCSV function ETC






*/



#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// Write String to Data Obj and return it function




/*
	Data is the field of data
*/
template<typename T>
class Data {

public:

	int ID;
	int year;
	string Cause;
	string state;
	int deaths;
	float deathrate;

	Data() {
		ID = year = deaths = 0;
		Cause = state = " ";
		deathrate = 0;
	}
	Data(int i, int y, int d, string c, string s, float dr) {
		ID = i;
		year = i;
		deaths = d;
		Cause = c;
		state = s;
		deathrate = dr;
	}
	Data(const Data &obj) {
		ID = obj.ID;
		year = obj.year;
		Cause = obj.Cause;
		state = obj.state;
		deaths = obj.deaths;
		deathrate = obj.deathrate;
	}
// 	void stringLoadCSV(string line) {
// 		int index = 0;
// 		int field = 0;

// 		string value = "";
// 		while (index < line.length()) {

// 			//Check if the feild data is in quotes [This is for fields that contain commas]
// 			if (line[index] == '"')
// 			{
// 				index++;
// 				while (line[index] != '"')
// 				{
// 					value += line[index];
// 					index++;
// 				}



// 				index++;
// 			}
// 			if (line[index]==',')
// 			{

// 				index++;
// 			}
			




// 		}




	~Data() {}
	//int getID() { return ID; }


};

/*
	val of the Node of a tree
*/

template<typename T>
class Value {
public:
	string datatype;		//to record the data type of Value Read from the file
	int lineNumber[5000];
	string fileName[5000];
	T tuple;				//the key read from file
	int Entries=0;			//number of entries with same key


	Value() {
		lineNumber[0] = 0;
		//fileName= NULL;
		// tuple = NULL;
	}
	void insert(string fn, int ln, T obj) {
		
		lineNumber[Entries] = ln;
		fileName[Entries] = fn;
		tuple = obj;

		Entries++;

	}

	void duplicates(int ent,string* fn, int* ln, T obj)
	{

		for (int i = Entries; i < ent+Entries; i++)
		{
			lineNumber[i] = ln[i-Entries];		
		}

		for (int i = Entries; i < ent+Entries; i++)
		{
			fileName[i] = fn[i-Entries];		
		}


		Entries += ent;
		// lineNumber[Entries] = ln;
		// fileName = fn;
		tuple = obj;
		// fileName = fn;

		// Entries++;

	}
	

	// //comparison Operator overloading with Value<T> as parameter
	bool operator<(Value<T> v) {
		if (tuple < v.tuple)
			return true;
		return false;
	}
	bool operator>(Value<T> v) {
		if (tuple > v.tuple)
			return true;
		return false;
	}






	bool operator==(Value<T> obj) {
		if (tuple == obj.tuple)
			return true;
		return false;
	}
	bool operator!=(Value<T> obj) {
		if (tuple == obj.tuple)
			return false;
	}

	void operator=(T key) {
		tuple = key;
	}
	bool operator<(int obj) {		//When datatype int is compared e.g. when ID is compared or the number of deaths
		if (tuple < obj)
			return true;
		return false;
	}
	bool operator>(int obj) {
		if (tuple > obj)
			return true;
		return false;
	}
	//when the obj is float
	bool operator<(float obj) {		//When datatype float is compared e.g. when death rate is compared or the number of deaths
		if (tuple < obj)
			return true;
		return false;
	}
	bool operator>(float obj) {
		if (tuple > obj)
			return true;
		return false;
	}
	//when the obj is string
	bool operator<(string obj) {		//When datatype string is compared e.g. when Name is compared or the number of deaths
		if (strcmp(tuple.c_str(),obj.c_str()) < 0)
			return true;
		return false;
	}

	bool operator>(string obj) {
		if (strcmp(tuple.c_str(), obj.c_str()) > 0)
			return true;
		return false;
	}

	ostream& operator<<(ostream& out) {
		out << tuple;
		return out;
	}

	void print() {

		cout<<"----------------------------------"<<Entries<<"------------------------------"<<endl;
		for (int i = 0; i < Entries; i++)
		{
			cout<<"Entry Number: "<<i+1<<endl;
			cout << "Line Number: " << lineNumber[i] << endl;
			cout << "File Name: " << fileName[i] << endl;
			cout << "Tuple[KEY]: " << tuple << endl;
		}
		

	}


	void writeToBinaryFile(ofstream& out) {
		


	
		out.write(reinterpret_cast<char*>(&Entries), sizeof(Entries));
		out.write(datatype.c_str(), datatype.size());
		out.write("\0", sizeof(char));
		out.write(reinterpret_cast<char*>(&lineNumber), sizeof(lineNumber));
		for (int i=0; i < Entries; i++)
		{
			out.write(fileName[i].c_str(), fileName[i].size());
			out.write("\0", sizeof(char));
		}
	
		//if T is string
		if constexpr (std::is_same<T, string>::value) {
			out.write(tuple.c_str(), tuple.size());
			out.write("\0", sizeof(char));
		}
		else
			out.write(reinterpret_cast<char*>(&tuple), sizeof(tuple));

	}

	void readFromBinaryFile(ifstream& in) {

		in.read((char*)&Entries, sizeof(Entries)); //read the number of entries
		getline(in,datatype, '\0'); //read the datatype
		in.read((char*)&lineNumber, sizeof(lineNumber)); //read the line number
		for (int i=0; i < Entries; i++)
		{
			getline(in,fileName[i], '\0'); //read the file name

		}

		//if T is string
		if constexpr (std::is_same<T, string>::value) {
			getline(in,tuple, '\0'); //read the tuple
		}
		else
			in.read((char*)&tuple, sizeof(tuple)); //read the tuple


		// this->print();

	}

	

};

template<typename T>
class node_stack {
public:
	node_stack* next;
	T val;
	node_stack() {
		next = NULL;
		val = 0;
	}
};


template<typename T>
class stack {
	node_stack<T>* top;
public:
	stack(int ignored = 0) { top = NULL; }
	~stack() { delete top; }

	bool isEmpty() {
		if (top == NULL)
			return true;
		return false;
	}

	void push(const T DataItem) {
		node_stack<T>* temp = new node_stack<T>;
		temp->val = DataItem;
		temp->next = top;
		top = temp;
	}
	T pop() {
		node_stack<T>* temp = new node_stack<T>;
		temp = top;
		top = top->next;
		delete temp;
		return top->val;
	}
	node_stack<T>* Peek() {
		if (!isEmpty()) {
			return top;
		}
	}
	void clear() {
		node_stack<T>* temp = new node_stack<T>;
		while (top != NULL) {
			temp = top->next;
			pop();
		}
	}
	int sizeofstack() {
		int size = 0;
		node_stack<T>* temp = new node_stack<T>;
		temp = top;
		while (temp != NULL) {
			temp = temp->next;
			size += 1;
		}
		return size;
	}

};

template<typename T>
class node_queue {
public:
	node_queue* next;
	T data;
	node_queue() { next = NULL; data = NULL; }
};

//*****************TASK 1**********************//
template<typename T>
class Queue {

public:
	int size;
	node_queue<T>* front;
	node_queue<T>* rear;
	Queue() {
		front = NULL;
		rear = NULL;
		size = 0;
	}
	void enqueue(T data) {
		node_queue<T>* temp = new node_queue<T>;
		temp->data = data;
		if (front == NULL) {	//if there is no element in the queue
			front = temp;
			rear = temp;
			++size;
		}
		else {
			rear->next = temp;
			rear = temp;
			rear = temp;
		}
	}
	void dequeue() {
		node_queue<T>* temp = new node_queue<T>;
		temp = front;
		front = front->next;
		delete temp;
		--size;
	}
	T Front() {
		return front->data;
	}
	bool isEmpty() {
		if (front == NULL)
			return true;
		return false;
	}
	void print() {
		node_queue<T>* temp = new node_queue<T>;
		temp = front;
		int i = 0;
		while (temp != NULL && temp->data != '\0') {
			//cout<<"The node_queue "<<i+1<<" has  value : "<<temp->data<<endl;
			cout << temp->data;
			//++i;
			temp = temp->next;
		}
	}


};

template <class T>
class node_list
{
public:
	T data;
	node_list* next;
	node_list* prev;

	node_list()
	{
		data = 0;
		next = NULL;
		prev = NULL;
	}

	node_list(T d, node_list* n, node_list* p)
	{
		data = d;
		next = n;
		prev = p;
	}

	node_list(T d)
	{
		data = d;
		next = NULL;
	}

	void setData(T d)
	{
		data = d;
	}

	void setNext(node_list* n)
	{
		next = n;
	}

	T getData()
	{
		return data;
	}

	node_list* getNext()
	{
		return next;
	}

};

template <class T>
class SLinkedList {

public:

	node_list<T>* head;

	SLinkedList()
	{
		head = NULL;
	}

	void insert(T d) {

		node_list<T>* temp = new node_list<T>;
		temp->data = d;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
		}
		else {
			node_list<T>* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = temp;
		}
	}
	void insertAtHead(T d) {
		node_list<T>* current = head;
		node_list<T>* temp = new node_list<T>;
		temp->data = d;
		if (head == NULL)
			head = temp;
		else {
			temp->next = head;
			head = temp;
		}
	}
	bool isEmpty() {
		if (head = NULL)
			return true;
		else
			return false;
	}
	int search(T d) {
		node_list<T>* current = head;
		int curr_index = 0;
		bool found = false;
		while (current && current->data != d) {
			current = current->next;
			++curr_index;
		}
		if (current)
			return curr_index;
		else
			return 0;
	}
	void update(T d1, T d2) {
		node_list<T>* current = head;

		while (current->data != d1 && current) {
			current = current->next;
		}
		if (current)
			current->data = d2;
		else
			return;

	}
	void InsertAtIndex(T d, int index) {
		if (index < 0)
			return;
		node_list<T>* newnode_list = new node_list<T>;
		newnode_list->data = d;
		node_list<T>* current = head;
		int curr_index = 1;
		while (index > curr_index && current) {
			current = current->next;
			++curr_index;
		}
		if (current) {
			newnode_list->next = current->next;
			current->next = newnode_list;
		}
		else
			return;

	}
	void remove(T d) {
		node_list<T>* current = head;
		while (current && current->data != d) {
			current = current->next;
		}
		if (current) {
			node_list<T>* deletenode_list = current->next;
			current->next = deletenode_list->next;
			delete deletenode_list;
		}
	}
	void print() {
		node_list<T>* current = head;
		while (current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	
	
};
