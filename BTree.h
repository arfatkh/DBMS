#pragma once
#include<iostream>
#include"Others.h"
using namespace std;


// Path: BTree.h

/*
    ABOUT BTREE.h
    




*/






#define N 4 

class BNode {
public:
    // key of N-1 BNodes
    int key[N - 1];

    // Child array of 'N' length
    BNode* child[N];

    // To state whether a leaf or not; if BNode is a leaf, isleaf=True else isleaf=False
    bool isleaf=false;

    // Counts the number of filled keys in a BNode
    int numkeys;

    // Keeps track of the parent BNode
    BNode* parent;
};

// This function searches for the leaf 
// into which to insert element 'k'
class BTree {
     BNode* searchforleaf( BNode* root, int k, BNode* parent, int chindex){
        if (root) {

            // If the passed root is a leaf BNode, then
            // k can be inserted in this BNode itself
            if (root->isleaf)
                return root;

            // If the passed root is not a leaf BNode, 
            // implying there are one or more children
            else {
                int i;

                /*If passed root's initial key is itself g
                  reater than the element to be inserted,
                  we need to insert to a new leaf left of the root*/
                if (k < root->key[0])
                    root = searchforleaf(root->child[0], k, root, 0);

                else
                {
                    // Find the first key whose value is greater 
                    // than the insertion value
                    // and insert into child of that key
                    for (i = 0; i < root->numkeys; i++)
                        if (root->key[i] > k)
                            root = searchforleaf(root->child[i], k, root, i);

                    // If all the keys are less than the insertion 
                    // key value, insert to the right of last key
                    if (root->key[i - 1] < k)
                        root = searchforleaf(root->child[i], k, root, i);
                }
            }
        }
        else {

            // If the passed root is NULL (there is no such 
            // child BNode to search), then create a new leaf 
            // BNode in that location
            BNode* newleaf = new  BNode;
            newleaf->isleaf = true;
            newleaf->numkeys = 0;
            parent->child[chindex] = newleaf;
            newleaf->parent = parent;
            return newleaf;
        }
    }

     BNode* insert( BNode* root, int k)
    {
        if (root) {
             BNode* p = searchforleaf(root, k, NULL, 0);
             BNode* q = NULL;
            int e = k;

            // If the leaf BNode is empty, simply 
            // add the element and return
            for (int e = k; p; p = p->parent) {
                if (p->numkeys == 0) {
                    p->key[0] = e;
                    p->numkeys = 1;
                    return root;
                }
                // If number of filled keys is less than maximum
                if (p->numkeys < N - 1) {
                    int i;
                    for (i = 0; i < p->numkeys; i++) {
                        if (p->key[i] > e) {
                            for (int j = p->numkeys - 1; j >= i; j--)
                                p->key[j + 1] = p->key[j];
                            break;
                        }
                    }
                    p->key[i] = e;
                    p->numkeys = p->numkeys + 1;
                    return root;
                }

                // If number of filled keys is equal to maximum 
                // and it's not root and there is space in the parent
                if (p->numkeys == N - 1 && p->parent && p->parent->numkeys < N) {
                    int m;
                    for (int i = 0; i < p->parent->numkeys; i++)
                        if (p->parent->child[i] == p) {
                            m = i;
                            break;
                        }

                    // If right sibling is possible
                    if (m + 1 <= N - 1)
                    {
                        // q is the right sibling
                        q = p->parent->child[m + 1];

                        if (q) {

                            // If right sibling is full
                            if (q->numkeys == N - 1) {
                                 BNode* r = new  BNode;
                                int* z = new int[((2 * N) / 3)];
                                int parent1, parent2;
                                int* marray = new int[2 * N];
                                int i;
                                for (i = 0; i < p->numkeys; i++)
                                    marray[i] = p->key[i];
                                int fege = i;
                                marray[i] = e;
                                marray[i + 1] = p->parent->key[m];
                                for (int j = i + 2; j < ((i + 2) + (q->numkeys)); j++)
                                    marray[j] = q->key[j - (i + 2)];

                                // marray=bubblesort(marray, 2*N)
                                // a more rigorous implementation will 
                                // sort these elements

                                // Put first (2*N-2)/3 elements into keys of p
                                for (int i = 0; i < (2 * N - 2) / 3; i++)
                                    p->key[i] = marray[i];
                                parent1 = marray[(2 * N - 2) / 3];

                                // Put next (2*N-1)/3 elements into keys of q
                                for (int j = ((2 * N - 2) / 3) + 1; j < (4 * N) / 3; j++)
                                    q->key[j - ((2 * N - 2) / 3 + 1)] = marray[j];
                                parent2 = marray[(4 * N) / 3];

                                // Put last (2*N)/3 elements into keys of r
                                for (int f = ((4 * N) / 3 + 1); f < 2 * N; f++)
                                    r->key[f - ((4 * N) / 3 + 1)] = marray[f];

                                // Because m=0 and m=1 are children of the same key,
                                // a special case is made for them
                                if (m == 0 || m == 1) {
                                    p->parent->key[0] = parent1;
                                    p->parent->key[1] = parent2;
                                    p->parent->child[0] = p;
                                    p->parent->child[1] = q;
                                    p->parent->child[2] = r;
                                    return root;
                                }

                                else {
                                    p->parent->key[m - 1] = parent1;
                                    p->parent->key[m] = parent2;
                                    p->parent->child[m - 1] = p;
                                    p->parent->child[m] = q;
                                    p->parent->child[m + 1] = r;
                                    return root;
                                }
                            }
                        }
                        else // If right sibling is not full
                        {
                            int put;
                            if (m == 0 || m == 1)
                                put = p->parent->key[0];
                            else
                                put = p->parent->key[m - 1];
                            for (int j = (q->numkeys) - 1; j >= 1; j--)
                                q->key[j + 1] = q->key[j];
                            q->key[0] = put;
                            p->parent->key[m == 0 ? m : m - 1] = p->key[p->numkeys - 1];
                        }
                    }
                }
            }

            /*Cases of root splitting, etc. are omitted
             as this implementation is just to demonstrate
             the two-three split operation*/
        }
        else
        {
            // Create new BNode if root is NULL
            BNode* root = new  BNode;
            root->key[0] = k;
            root->isleaf = true;
            root->numkeys = 1;
            root->parent = NULL;
        }
    }
};