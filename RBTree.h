#pragma once
#include<iostream>
#include<Others.h>

/*
	RB Tree Manual:
		Rules:
			-> The root will always be Black
			-> There are no Red Red parent child
			-> Number of Black nodes on each path are same (all over the tree)
		Insertion:
			-> If tree is emnewNodey then create new node as root node with color Black
			-> If tree is not emnewNodey then insert newnode with color Red
			-> If the parent of newnode is Black then return
			-> If the parent of newnode is Red then check the parent's sibling's color
			-> If the Parent_Sibling of newnode is Black or Null then make suitable rotation LL or RR
			-> If the Parent_Sibling of newnode is Red the Recolor the newnode and parent node
		Deletion:
			-> Find the node to be deleted using binary search tree traversal
			-> If node to be deleted has 2 Non-Null children, replace it with it's inorder successor
			-> If node to be deleted is re then just delete it
			-> If node to be deleted is black but has one red child replace it with that child and change color of child to black
			-> Otherwise Double Black situation comes and we see the 6 cases

*/
enum COLOR { RED, BLACK };
template<typename T>
class RBnode {
public:
	Value<T> val;
	COLOR color;
	RBnode<T>* leftChild;
	RBnode<T>* rightChild;
	RBnode<T>* parent;

	RBnode(Value<T> val) : val(val) {
		parent = leftChild = rightChild = NULL;
		// RBnode is red at insertion
		color = RED;
	}
	//Checking which child of the parent is the current node
	bool Is_left_child() {
		return this == parent->leftChild;
	}
	// returns pointer to Parent_Sibling
	RBnode<T>* Parent_Sibling() {
		// If no parent or grandparent, then no Parent_Sibling
		if (parent == NULL || parent->parent == NULL)
			return NULL;

		if (this == parent->leftChild)
			// Parent_Sibling on rightChild
			return parent->parent->rightChild;
		else
			// Parent_Sibling on leftChild
			return parent->parent->leftChild;
	}


	// returns pointer to sibling
	RBnode<T>* sibling() {
		// sibling null if no parent
		if (parent == NULL)
			return NULL;

		if (Is_left_child())
			return parent->rightChild;

		return parent->leftChild;
	}

	// moves node down and moves given node in its place
	void moveDown(RBnode<T>* Num_parent) {
		if (parent != NULL) {
			if (Is_left_child()) {
				parent->leftChild = Num_parent;
			}
			else {
				parent->rightChild = Num_parent;
			}
		}
		Num_parent->parent = parent;
		parent = Num_parent;
	}

	bool Is_Red_child() {
		return (leftChild != NULL and leftChild->color == RED) || (rightChild != NULL and rightChild->color == RED);
	}
};

template<typename T>
class RBTree {
	RBnode<T>* root;

	// leftChild rotates the given node
	void left_rotate(RBnode<T>* node) {
		// new parent will be node's rightChild child
		RBnode<T>* Num_parent = node->rightChild;

		// update root if current node is root
		if (node == root)
			root = Num_parent;

		node->moveDown(Num_parent);

		// connect node with new parent's leftChild element
		node->rightChild = Num_parent->leftChild;
		// connect new parent's leftChild element with node
		// if it is not null
		if (Num_parent->leftChild != NULL)
			Num_parent->leftChild->parent = node;

		// connect new parent with node
		Num_parent->leftChild = node;
	}

	void rightRotate(RBnode<T>* node) {
		// new parent will be node's leftChild child
		RBnode<T>* Num_parent = node->leftChild;

		// update root if current node is root
		if (node == root)
			root = Num_parent;

		node->moveDown(Num_parent);

		// connect node with new parent's rightChild element
		node->leftChild = Num_parent->rightChild;
		// connect new parent's rightChild element with node
		// if it is not null
		if (Num_parent->rightChild != NULL)
			Num_parent->rightChild->parent = node;

		// connect new parent with node
		Num_parent->rightChild = node;
	}

	void swap_color(RBnode<T>* node1, RBnode<T>* node2) {
		COLOR temp;
		temp = node1->color;
		node1->color = node2->color;
		node2->color = temp;
	}

	void swap_value(RBnode<T>* node1, RBnode<T>* node2) {
		Value<T> temp;
		temp = node1->val;
		node1->val = node2->val;
		node2->val = temp;
	}

	// fix red red at given node
	void Red_Red_relation(RBnode<T>* node) {
		// if node is root color it black and return
		if (node == root) {
			node->color = BLACK;
			return;
		}

		// initialize parent, grandparent, Parent_Sibling
		RBnode<T>* parent = node->parent;
		RBnode<T>* grandparent = parent->parent;
		RBnode<T>* Parent_Sibling = node->Parent_Sibling();		//Uncle

		if (parent->color != BLACK) {
			if (Parent_Sibling != NULL && Parent_Sibling->color == RED) {
				// Parent_Sibling red, perform recoloring and recurse
				parent->color = BLACK;
				Parent_Sibling->color = BLACK;
				grandparent->color = RED;
				Red_Red_relation(grandparent);
			}
			else {
				// Else perform LR, LL, RL, RR
				if (parent->Is_left_child()) {
					if (node->Is_left_child()) {
						// for leftChild rightChild
						swap_color(parent, grandparent);
					}
					else {
						left_rotate(parent);
						swap_color(node, grandparent);
					}
					// for leftChild leftChild and leftChild rightChild
					rightRotate(grandparent);
				}
				else {
					if (node->Is_left_child()) {
						// for rightChild leftChild
						rightRotate(parent);
						swap_color(node, grandparent);
					}
					else {
						swap_color(parent, grandparent);
					}

					// for rightChild rightChild and rightChild leftChild
					left_rotate(grandparent);
				}
			}
		}
	}

	// find node that do not have a leftChild child
	// in the subtree of the given node
	RBnode<T>* successor(RBnode<T>* node) {
		RBnode<T>* temp = node;

		while (temp->leftChild != NULL)
			temp = temp->leftChild;

		return temp;
	}

	// find node that replaces a deleted node in BST
	RBnode<T>* ReplaceNode(RBnode<T>* val) {
		// when node have 2 children
		if (val->leftChild != NULL and val->rightChild != NULL)
			return successor(val->rightChild);

		// when leaf
		if (val->leftChild == NULL and val->rightChild == NULL)
			return NULL;

		// when single child
		if (val->leftChild != NULL)
			return val->leftChild;
		else
			return val->rightChild;
	}

	// deletes the given node
	void deleteNode(RBnode<T>* node) {
		RBnode<T>* temp = ReplaceNode(node);

		// True when temp and node are both black
		bool Is_both_black = ((temp == NULL or temp->color == BLACK) and (node->color == BLACK));
		RBnode<T>* parent = node->parent;

		if (temp == NULL) {
			// temp is NULL therefore node is leaf
			if (node == root) {
				// node is root, making root null
				root = NULL;
			}
			else {
				if (Is_both_black) {
					// temp and node both black
					// node is leaf, fix double black at node
					Double_Black(node);
				}
				else {
					// temp or node is red
					if (node->sibling() != NULL)
						// sibling is not null, make it red"
						node->sibling()->color = RED;
				}

				// delete node from the tree
				if (node->Is_left_child()) {
					parent->leftChild = NULL;
				}
				else {
					parent->rightChild = NULL;
				}
			}
			delete node;
			return;
		}

		if (node->leftChild == NULL or node->rightChild == NULL) {
			// node has 1 child
			if (node == root) {
				// node is root, assign the value of temp to node, and delete temp
				node->val = temp->val;
				node->leftChild = node->rightChild = NULL;
				delete temp;
			}
			else {
				// Detach node from tree and move temp up
				if (node->Is_left_child()) {
					parent->leftChild = temp;
				}
				else {
					parent->rightChild = temp;
				}
				delete node;
				temp->parent = parent;
				if (Is_both_black) {
					// temp and node both black, fix double black at temp
					Double_Black(temp);
				}
				else {
					// temp or node red, color temp black
					temp->color = BLACK;
				}
			}
			return;
		}

		// node has 2 children, swap values with successor and recurse
		swap_value(temp, node);
		deleteNode(temp);
	}

	void Double_Black(RBnode<T>* node) {
		if (node == root)
			// Reached root
			return;

		RBnode<T>* sibling = node->sibling();
		RBnode<T>* parent = node->parent;
		if (sibling == NULL) {
			// No sibiling, double black pushed up
			Double_Black(parent);
		}
		else {
			if (sibling->color == RED) {
				// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->Is_left_child()) {
					// leftChild case
					rightRotate(parent);
				}
				else {
					// rightChild case
					left_rotate(parent);
				}
				Double_Black(node);
			}
			else {
				// Sibling black
				if (sibling->Is_Red_child()) {
					// at least 1 red children
					if (sibling->leftChild != NULL and sibling->leftChild->color == RED) {
						if (sibling->Is_left_child()) {
							// leftChild leftChild
							sibling->leftChild->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else {
							// rightChild leftChild
							sibling->leftChild->color = parent->color;
							rightRotate(sibling);
							left_rotate(parent);
						}
					}
					else {
						if (sibling->Is_left_child()) {
							// leftChild rightChild
							sibling->rightChild->color = parent->color;
							left_rotate(sibling);
							rightRotate(parent);
						}
						else {
							// rightChild rightChild
							sibling->rightChild->color = sibling->color;
							sibling->color = parent->color;
							left_rotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else {
					// 2 black children
					sibling->color = RED;
					if (parent->color == BLACK)
						Double_Black(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

	// prints level order for given node
	void levelOrder(RBnode<T>* node) {
		if (node == NULL)
			// return if node is null
			return;

		// queue for level order
		Queue<RBnode<T>*> q;
		RBnode<T>* curr;

		// push x
		q.push(node);

		while (!q.empty()) {
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			cout << curr->val << " ";

			// push children to queue
			if (curr->leftChild != NULL)
				q.push(curr->leftChild);
			if (curr->rightChild != NULL)
				q.push(curr->rightChild);
		}
	}

	// prints inorder recursively
	void inorder(RBnode<T>* Val) {
		if (Val == NULL)
			return;
		inorder(Val->leftChild);
		cout << Val->val.tuple << " ";
		inorder(Val->rightChild);
	}

public:
	// constructor
	// initialize root
	RBTree() { root = NULL; }

	RBnode<T>* getRoot() { return root; }

	// searches for given value
	// if found returns the node (used for delete)
	// else returns the last node while traversing (used in insert)
	RBnode<T>* search(Value<T> val) {
		RBnode<T>* temp = root;
		while (temp != NULL) {
			if (val < temp->val) {
				if (temp->leftChild == NULL)
					break;
				else
					temp = temp->leftChild;
			}
			else if (val == temp->val) {
				break;
			}
			else {
				if (temp->rightChild == NULL)
					break;
				else
					temp = temp->rightChild;
			}
		}

		return temp;
	}

	// inserts the given value to tree
	void insert(Value<T> val) {
		RBnode<T>* newNode = new RBnode<T>(val);
		if (root == NULL) {
			// when root is null simply insert value at root
			newNode->color = BLACK;
			root = newNode;
		}
		else {
			RBnode<T>* temp = search(val);

			if (temp->val == val) {
				// return if value already exists and record the duplicate of the val in the node
				root->val.duplicates(val.Entries,val.fileName, val.lineNumber, val.tuple); 
				return;
			}

			// if value is not found, search returns the node
			// where the value is to be inserted

			// connect new node to correct node
			newNode->parent = temp;

			if (val < temp->val)
				temp->leftChild = newNode;
			else
				temp->rightChild = newNode;

			// fix red red voilaton if exists
			Red_Red_relation(newNode);
		}
	}

	// utility function that deletes the node with given value
	void deleteByVal(Value<T> val) {
		// Tree is empty
		if (root == NULL)
			return;

		RBnode<T>* node = search(val);

		if (node->val != val) {
			cout << "No node found to delete with value:" << val.tuple << endl;
			return;
		}

		deleteNode(node);
	}

	// prints inorder of the tree
	void printInOrder() {
		cout << "Inorder: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			inorder(root);
		cout << endl;
	}

	// prints level order of the tree
	void printLevelOrder() {
		cout << "Level order: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			levelOrder(root);
		cout << endl;
	}
};










// // Driver Code
// int main()
// {
// 	RBTree<int> tree;
// 	Value<int> val;

// 	val.insert("22", 22, 22);
// 	tree.insert(val);
// 	// val.insert("22", 22, 7);
// 	// tree.insert(val);
// 	val.insert("22", 22, 6);
// 	tree.insert(val);
// 	val.insert("22", 22, 5);
// 	tree.insert(val);
// 	// val.insert("22", 22, 4);
// 	// tree.insert(val);


// 	tree.deleteByVal(val);
// 	tree.printInOrder();

// 	// val.insert("22", 22, 2);
// 	// tree.insert(val);
// 	// val.insert("22", 22, 1);
// 	// tree.insert(val);
// 	// tree.printInOrder();

// 	// cout << "Inorder Traversal of Created Tree\n";
// 	// tree.printInOrder();

// 	// val.insert("22",22,3);
// 	// tree.deleteByVal(val);
// 	// val.insert("22",22,5);
// 	// tree.deleteByVal(val);

// 	// tree.printInOrder();


// 	return 0;
// }
