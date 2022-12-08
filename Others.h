#pragma once
#include<iostream>
using namespace std;
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
	~Data() {}
	//int getID() { return ID; }


};

/*
	val of the Node of a tree
*/
template<typename T>
class Value {
public:
	int lineNumber[200];
	string fileName[200];
	T tuple;

	Value() {
		lineNumber = 0;
		//fileName= NULL;
		tuple = NULL;
	}
	void insert(string fn, int ln, T obj) {
		lineNumber = ln;
		fileName = fn;
		tuple = obj;
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

	/////////////////////////TASK2//////////////////////////////
	template<typename T>
	void mergeLists(SLinkedList<T> obj) {
		node_list<T>* current1 = head;
		node_list<T>* current2 = obj.head;
		SLinkedList<T>* temp = new SLinkedList<T>;
		int index_current = 0;
		while (current1 && current2) {
			temp->insert(current1->data);
			temp->insert(current2->data);
			current1 = current1->next;
			current2 = current2->next;
		}
		head = temp->head;
	}
};