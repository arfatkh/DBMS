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
			-> If the uncle of newnode is Black or Null then make suitable rotation LL or RR
			-> If the uncle of newnode is Red the Recolor the newnode and parent node
		Deletion:
			-> Find the node to be deleted using binary search tree traversal
			-> If node to be deleted has 2 Non-Null children, replace it with it's inorder successor
			-> If node to be deleted is re then just delete it 
			-> If node to be deleted is black but has one red child replace it with that child and change color of child to black
			-> Otherwise Double Black situation comes and we see the 6 cases

*/

enum Color { RED, BLACK };

template<typename T>
struct RBnode
{
	Value<T> data;
	bool color;
	RBnode* left, * right, * parent;

	// Constructor
	RBnode(Value<T> data)
	{
		this->data = data;
		left = right = parent = NULL;
		this->color = RED;					//whenever a new node is made it's color is Red
	}
};

// Class to represent Red-Black Tree
template<typename T>
class RBTree
{
private:
	RBnode<T>* root;
public:
	RBTree() { root = NULL; }
	void insert(Value<T> data)
	{
		RBnode<T>* newNode = new RBnode<T>(data);

		// Do a normal BST insert
		root = BSTInsert(root, newNode);

		// fix Red Black Tree violations
		// caused by BST insertion

		fixViolation(root, newNode);
	}
	//Performs LL to the tree
	void rotateLeft(RBnode<T>*& root, RBnode<T>*& newNode)
	{
		RBnode<T>* newN_Rightchild = newNode->right;

		newNode->right = newN_Rightchild->left;

		if (newNode->right != NULL)
			newNode->right->parent = newNode;

		newN_Rightchild->parent = newNode->parent;

		if (newNode->parent == NULL)
			root = newN_Rightchild;

		else if (newNode == newNode->parent->left)
			newNode->parent->left = newN_Rightchild;

		else
			newNode->parent->right = newN_Rightchild;

		newN_Rightchild->left = newNode;
		newNode->parent = newN_Rightchild;
	}
	//Performs to rightchild
	void rotateRight(RBnode<T>*& root, RBnode<T>*& newNode)
	{
		RBnode<T>* newNode_left = newNode->left;

		newNode->left = newNode_left->right;

		if (newNode->left != NULL)
			newNode->left->parent = newNode;

		newNode_left->parent = newNode->parent;

		if (newNode->parent == NULL)
			root = newNode_left;

		else if (newNode == newNode->parent->left)
			newNode->parent->left = newNode_left;

		else
			newNode->parent->right = newNode_left;

		newNode_left->right = newNode;
		newNode->parent = newNode_left;
	}

	// This function fixes violations
	// caused by BST insertion

	void fixViolation(RBnode<T>*& root, RBnode<T>*& newNode)
	{
		RBnode<T>* parent_newNode = NULL;
		RBnode<T>* grand_parent_newNode = NULL;

		while ((newNode != root) && (newNode->color != BLACK) &&
			(newNode->parent->color == RED))
		{

			parent_newNode = newNode->parent;
			grand_parent_newNode = newNode->parent->parent;

			/* Case : A
				Parent of newNode is left child
				of Grand-parent of newNode */
			if (parent_newNode == grand_parent_newNode->left)
			{

				RBnode<T>* uncle_newNode = grand_parent_newNode->right;

				/* Case : 1
				The uncle of newNode is also red
				Only Recoloring required */
				if (uncle_newNode != NULL && uncle_newNode->color ==
					RED)
				{
					grand_parent_newNode->color = RED;
					parent_newNode->color = BLACK;
					uncle_newNode->color = BLACK;
					newNode = grand_parent_newNode;
				}

				else
				{
					/* Case : 2
					newNode is right child of its parent
					Left-rotation required */
					if (newNode == parent_newNode->right)
					{
						rotateLeft(root, parent_newNode);
						newNode = parent_newNode;
						parent_newNode = newNode->parent;
					}

					/* Case : 3
					newNode is left child of its parent
					Right-rotation required */
					rotateRight(root, grand_parent_newNode);
					swap(parent_newNode->color,grand_parent_newNode->color);
					newNode = parent_newNode;
				}
			}

			/* Case : B
			Parent of newNode is right child
			of Grand-parent of newNode */
			else
			{
				RBnode<T>* uncle_newNode = grand_parent_newNode->left;

				/* Case : 1
					The uncle of newNode is also red
					Only Recoloring required */
				if ((uncle_newNode != NULL) && (uncle_newNode->color ==
					RED))
				{
					grand_parent_newNode->color = RED;
					parent_newNode->color = BLACK;
					uncle_newNode->color = BLACK;
					newNode = grand_parent_newNode;
				}
				else
				{
					/* Case : 2
					newNode is left child of its parent
					Right-rotation required */
					if (newNode == parent_newNode->left)
					{
						rotateRight(root, parent_newNode);
						newNode = parent_newNode;
						parent_newNode = newNode->parent;
					}

					/* Case : 3
					newNode is right child of its parent
					Left-rotation required */
					rotateLeft(root, grand_parent_newNode);
					swap(parent_newNode->color,grand_parent_newNode->color);
					newNode = parent_newNode;
				}
			}
		}

		root->color = BLACK;
	}
	
	
	void inorder() { HelperFunc_Inorder(root); }
	//void levelOrder();
};

// A recursive function to do inorder traversal
template<typename T>
void HelperFunc_Inorder(RBnode<T>* root)
{
	if (root == NULL)
		return;

	HelperFunc_Inorder(root->left);
	cout << root->data.tuple << " ";
	HelperFunc_Inorder(root->right);
}

/* A utility function to insert
	a new node with given key
in BST */
template<typename T>
RBnode<T>* BSTInsert(RBnode<T>* root, RBnode<T>* newNode)
{
	/* If the tree is emnewNodey, return a new node */
	if (root == NULL)
		return newNode;

	/* Otherwise, recur down the tree */
	if (newNode->data < root->data)
	{
		root->left = BSTInsert(root->left, newNode);
		root->left->parent = root;
	}
	else if (newNode->data > root->data)
	{
		root->right = BSTInsert(root->right, newNode);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}







//// Driver Code
//int main()
//{
//	RBTree<int> tree;
//	Value<int> val;
//	val.insert("22", 22, 7);
//	tree.insert(val);
//	val.insert("22", 22, 6);
//	tree.insert(val);
//	val.insert("22", 22, 5);
//	tree.insert(val);
//	val.insert("22", 22, 4);
//	tree.insert(val);
//	val.insert("22", 22, 3);
//	tree.insert(val);
//	val.insert("22", 22, 2);
//	tree.insert(val);
//	val.insert("22", 22, 1);
//	tree.insert(val);
//
//	cout << "Inorder Traversal of Created Tree\n";
//	tree.inorder();
//
//	return 0;
//}