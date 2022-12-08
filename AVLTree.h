#pragma once
#include<iostream>
#include"Others.h"
using namespace std;

//insert's value
//value operator

template<typename T>
struct Node {
public:
    T key;
    //Data* val;
   
    Value<int>* val;                     //---------> for sake of testing. Assuming that the data type is int to easily check > and <
   
    Node* left, * right;
    int height;
    Node() { key = 0; val = new Value<int>; left = NULL; right = NULL; height = -1; }
    Node(Value<T>* data) {
        key = data->tuple;
        val = data;
        left = NULL;
        right = NULL;
        height = 0;
    }
    void input(Value<T>* data) {
        key = data->tuple;
        val = data;
    }
    int getheight() { return height; }
};

template<typename T>
int Height(Node<T>* P)
{
    if (P == NULL)
        return -1;
    else
        return P->getheight();
}


template<typename T>
class AVLtree {
public:
    Node<T>* root;

    AVLtree() { root = NULL; }
    ~AVLtree() { delete root; }

    int Maximum(int x, int y) {
        if (x > y)
            return x;
        return y;
    }

    int height(Node<T>* N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }
    //A data type Value is made
    Node<T>* newNode(Value<T> key)
    {
        Node<T>* node = new Node<T>;
        node->key = key.tuple;
        node->val = key;                    //The Value val
        node->left = NULL;
        node->right = NULL;
        node->height = 1; // new node is initially
        // added at leaf 
        return(node);
    }

    Node<T>* rightRotate(Node<T>* y)
    {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;

        // Perform rotation 
        x->right = y;
        y->left = T2;

        // Update heights 
        y->height = Maximum(height(y->left),
            height(y->right)) + 1;
        x->height = Maximum(height(x->left),
            height(x->right)) + 1;

        // Return new root 
        return x;
    }

    Node<T>* leftRotate(Node<T>* x)
    {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;


        y->left = x;
        x->right = T2;


        x->height = Maximum(height(x->left),
            height(x->right)) + 1;
        y->height = Maximum(height(y->left),
            height(y->right)) + 1;
        return y;
    }


    int getBF(Node<T>* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    /*void insert(Node<T>* node) {
        T key = node->key;
        if (root = NULL) {
            root = node;
        }
        else
            root = insertNode(node, node->key);
    }*/

    Node<T>* insertNode(Node<T>* node, Value<T> key)
    {

        if (node == NULL)
            return(newNode(key));

        if (key < node->key)                                //comparison operator overloading of class data type is used
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else // Equal keys not allowed 
            return node;


        node->height = 1 + Maximum(height(node->left),
            height(node->right));
        int BF = getBF(node);

        // Left Left Case 
        if (BF > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case 
        if (BF < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case 
        if (BF > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case 
        if (BF < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }


    Node<T>* min(Node<T>* node)
    {
        Node<T>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }
    Node<T>* remove(Node<T>* root, int key)
    {

        // STEP 1: PERFORM STANDARD BST DELETE 
        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = remove(root->left, key);

        else if (key > root->key)
            root->right = remove(root->right, key);

        else
        {

            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                Node<T>* temp = root->left ?
                    root->left :
                    root->right;

                // No child case 
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case 
                    *root = *temp;

                free(temp);
            }
            else
            {
                Node<T>* temp = min(root->right);
                root->key = temp->key;
                root->right = remove(root->right,
                    temp->key);
            }
        }
        if (root == NULL)
            return root;

        root->height = 1 + Maximum(height(root->left),
            height(root->right));


        int BF = getBF(root);

        // Left Left Case 
        if (BF > 1 &&
            getBF(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case 
        if (BF > 1 &&
            getBF(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case 
        if (BF < -1 &&
            getBF(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case 
        if (BF < -1 &&
            getBF(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    
    //Depth for Search functiosn
    
    void PreOrderTraversal(Node<T>* root) {
        if (root == NULL)
            return;
        cout << root->key << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }

    void PostOrderTraversal(Node<T>* root) {
        if (root == NULL)
            return;
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        cout << root->key << " ";
    }

    void InOrderTraversal(Node<T>* root) {
        if (root == NULL)
            return;
        InOrderTraversal(root->left);
        cout << root->key << " ";
        InOrderTraversal(root->right);
    }

    //BFS traversal

    //void levelorder_newline() {
    //    if (this->root == NULL) {
    //        cout << "\n" << "Empty tree" << "\n";
    //        return;
    //    }
    //    levelorder_newline(this->root);
    //}

    /*void levelorder_newline( Node* v) {
        Queue <Node*> q;
        Node* cur;
        q.enqueue(v);
        q.enqueue(NULL);

        while (!q.isEmpty()) {
            cur = q.Front();
            q.dequeue();
            if (cur == NULL && q.size != 0) {
                cout << "\n";

                q.enqueue(NULL);
                continue;
            }
            if (cur != NULL) {
                cout << " " << cur->key;

                if (cur->left != NULL) {
                    q.enqueue(cur->left);
                }
                if (cur->right != NULL) {
                    q.enqueue(cur->right);
                }
            }


        }
    }*/

};


//AVLtree tree;
    //Node* root = tree.root;

    //Data d1(10, 2004, 42, "AIDS", "Ohio", 6.9);
    //Node n1(&d1);
    //tree.root = tree.insertNode(tree.root,10);

    //Data d2(20, 2004, 42, "Cancer", "Ohio", 6.9);
    //Node n2(&d2);
    //tree.root = tree.insertNode(tree.root,20);

    //Data d3(50, 2004, 42, "Cigis", "Ohio", 6.9);
    //Node n3(&d3);
    //tree.root = tree.insertNode(tree.root,50);

    //Data d4(80, 2004, 42, "Ligma", "Alabama", 6.9);
    //Node n4(&d4);
    //tree.root = tree.insertNode(tree.root,80);

    //Data d5(1, 2004, 42, "Saqmadiq", "Ohio", 6.9);
    //Node n5(&d5);
    //tree.root = tree.insertNode(tree.root,1);

    ////tree.InOrderTraversal(tree.root);
    ////tree.levelorder_newline();
    ////tree.levelorder_newline(tree.root);
